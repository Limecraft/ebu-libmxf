/*
 * Copyright (C) 2012, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <mxf/mxf.h>
#include <mxf/mxf_memory_file.h>
#include <mxf/mxf_macros.h>


#define DEFAULT_CHUNK_SIZE      4096


typedef struct
{
    unsigned char *data;
    int64_t allocSize;
    int64_t size;
} Chunk;

struct MXFMemoryFile
{
    MXFFile *mxfFile;
};

struct MXFFileSysData
{
    MXFMemoryFile mxfMemFile;
    uint32_t chunkSize;
    int contiguous;
    int64_t virtualStartPos;
    Chunk *chunks;
    int64_t numChunks;
    int64_t position;
};



static int get_chunk_pos(MXFFileSysData *sysData, int64_t *posChunkIndex, int64_t *posChunkPos)
{
    int64_t chunkIndex;
    int64_t chunkPos;

    if (sysData->numChunks == 0)
        return 0;

    assert(sysData->position >= 0);
    if (sysData->numChunks == 1) {
        chunkIndex = 0;
        chunkPos = sysData->position;
    } else {
        chunkIndex = sysData->position / sysData->chunkSize;
        assert(chunkIndex <= sysData->numChunks);
        if (chunkIndex == sysData->numChunks)
            chunkIndex--;
        chunkPos = sysData->position - sysData->chunkSize * chunkIndex;
    }
    assert(chunkPos <= sysData->chunks[chunkIndex].size);

    *posChunkIndex = chunkIndex;
    *posChunkPos = chunkPos;
    return 1;
}

static int extend_mem_file(MXFFileSysData *sysData, uint32_t minSize)
{
    uint32_t i;
    Chunk *newChunks;
    uint32_t numExtendChunks;

    numExtendChunks = (minSize + sysData->chunkSize - 1) / sysData->chunkSize;
    if (numExtendChunks == 0)
        numExtendChunks = 1;

    newChunks = (Chunk*)realloc(sysData->chunks, (sysData->numChunks + numExtendChunks) * sizeof(Chunk));
    if (!newChunks) {
        mxf_log_error("Failed to reallocate memory file chunks" LOG_LOC_FORMAT, LOG_LOC_PARAMS);
        return 0;
    }
    sysData->chunks = newChunks;

    for (i = 0; i < numExtendChunks; i++) {
        CHK_MALLOC_ARRAY_ORET(sysData->chunks[sysData->numChunks].data, unsigned char, sysData->chunkSize);
        sysData->chunks[sysData->numChunks].allocSize = sysData->chunkSize;
        sysData->chunks[sysData->numChunks].size = 0;
        sysData->numChunks++;
    }

    return 1;
}


static void free_mem_file(MXFFileSysData *sysData)
{
    free(sysData);
}

static void mem_file_close(MXFFileSysData *sysData)
{
    if (!sysData)
        return;

    int64_t i;
    for (i = 0; i < sysData->numChunks; i++)
        free(sysData->chunks[i].data);
    free(sysData->chunks);
    sysData->chunks = NULL;
    sysData->numChunks = 0;
    sysData->position = 0;
}

static int64_t mem_file_size(MXFFileSysData *sysData)
{
    if (!sysData)
        return -1;

    return sysData->virtualStartPos + mxf_mem_file_get_size(&sysData->mxfMemFile);
}

static uint32_t mem_file_read(MXFFileSysData *sysData, uint8_t *data, uint32_t count)
{
    uint32_t totalRead = 0;
    int64_t posChunkIndex;
    int64_t posChunkPos;
    int64_t numRead;

    if (count == 0 || !get_chunk_pos(sysData, &posChunkIndex, &posChunkPos))
        return 0;

    while (totalRead < count) {
        numRead = sysData->chunks[posChunkIndex].size - posChunkPos;
        if (numRead > 0) {
            if (numRead > count - totalRead)
                numRead = count - totalRead;
            memcpy(&data[totalRead], &sysData->chunks[posChunkIndex].data[posChunkPos], numRead);
            totalRead += numRead;
            sysData->position += numRead;
            posChunkPos += numRead;
        }

        if (posChunkPos >= sysData->chunks[posChunkIndex].size) {
            if (posChunkIndex + 1 >= sysData->numChunks)
                break;
            posChunkIndex++;
            posChunkPos = 0;
        }
    }

    return totalRead;
}

static uint32_t mem_file_write(MXFFileSysData *sysData, const uint8_t *data, uint32_t count)
{
    uint32_t totalWrite = 0;
    int64_t posChunkIndex;
    int64_t posChunkPos;
    int64_t numWrite;

    if (count == 0)
        return 0;

    if (sysData->numChunks == 0 && !extend_mem_file(sysData, count))
        return 0;

    /* note that check here is not strictly neccessary */
    if (!get_chunk_pos(sysData, &posChunkIndex, &posChunkPos))
        return 0;

    while (totalWrite < count) {
        numWrite = sysData->chunks[posChunkIndex].allocSize - posChunkPos;
        if (numWrite > 0) {
            if (numWrite > count - totalWrite)
                numWrite = count - totalWrite;
            memcpy(&sysData->chunks[posChunkIndex].data[posChunkPos], &data[totalWrite], numWrite);
            totalWrite += numWrite;
            sysData->position += numWrite;
            posChunkPos += numWrite;
            if (posChunkPos > sysData->chunks[posChunkIndex].size)
                sysData->chunks[posChunkIndex].size = posChunkPos;
        }

        if (posChunkPos >= sysData->chunks[posChunkIndex].allocSize) {
            if (totalWrite < count &&
                posChunkIndex + 1 >= sysData->numChunks &&
                !extend_mem_file(sysData, count - totalWrite))
            {
                break;
            }
            posChunkIndex++;
            posChunkPos = 0;
        }
    }

    return totalWrite;
}

static int mem_file_getchar(MXFFileSysData *sysData)
{
    unsigned char data;
    if (mem_file_read(sysData, &data, 1) == 0)
        return EOF;

    return data;
}

static int mem_file_putchar(MXFFileSysData *sysData, int c)
{
    unsigned char data = (unsigned char)c;
    if (mem_file_write(sysData, &data, 1) == 0)
        return EOF;

    return c;
}

static int mem_file_eof(MXFFileSysData *sysData)
{
    return sysData->position >= mxf_mem_file_get_size(&sysData->mxfMemFile);
}

static int mem_file_seek(MXFFileSysData *sysData, int64_t offset, int whence)
{
    int64_t position;
    int64_t size;

    size = mxf_mem_file_get_size(&sysData->mxfMemFile);

    switch (whence)
    {
        case SEEK_SET:
            position = offset - sysData->virtualStartPos;
            break;
        case SEEK_CUR:
            position = sysData->position + offset;
            break;
        case SEEK_END:
            position = size + offset;
            break;
        default:
            position = sysData->position;
            break;
    }
    if (position < 0 || position > size)
        return 0;

    sysData->position = position;
    return 1;
}

static int64_t mem_file_tell(MXFFileSysData *sysData)
{
    return sysData->virtualStartPos + sysData->position;
}

static int mem_file_is_seekable(MXFFileSysData *sysData)
{
    (void)sysData;

    return 1;
}



int mxf_mem_file_open_new(uint32_t chunkSize, int64_t virtualStartPos, MXFMemoryFile **mxfMemFile)
{
    MXFFile *newMXFFile = NULL;

    CHK_MALLOC_ORET(newMXFFile, MXFFile);
    memset(newMXFFile, 0, sizeof(*newMXFFile));

    newMXFFile->close           = mem_file_close;
    newMXFFile->read            = mem_file_read;
    newMXFFile->write           = mem_file_write;
    newMXFFile->get_char        = mem_file_getchar;
    newMXFFile->put_char        = mem_file_putchar;
    newMXFFile->eof             = mem_file_eof;
    newMXFFile->seek            = mem_file_seek;
    newMXFFile->tell            = mem_file_tell;
    newMXFFile->is_seekable     = mem_file_is_seekable;
    newMXFFile->size            = mem_file_size;
    newMXFFile->free_sys_data   = free_mem_file;


    CHK_MALLOC_OFAIL(newMXFFile->sysData, MXFFileSysData);
    memset(newMXFFile->sysData, 0, sizeof(*newMXFFile->sysData));

    newMXFFile->sysData->chunkSize          = (chunkSize == 0 ? DEFAULT_CHUNK_SIZE : chunkSize);
    newMXFFile->sysData->virtualStartPos    = virtualStartPos;
    newMXFFile->sysData->mxfMemFile.mxfFile = newMXFFile;


    *mxfMemFile = &newMXFFile->sysData->mxfMemFile;
    return 1;

fail:
    if (newMXFFile)
        mxf_file_close(&newMXFFile);
    return 0;
}

MXFFile* mxf_mem_file_get_file(MXFMemoryFile *mxfMemFile)
{
    return mxfMemFile->mxfFile;
}

int64_t mxf_mem_file_get_num_chunks(MXFMemoryFile *mxfMemFile)
{
    return mxfMemFile->mxfFile->sysData->numChunks;
}

unsigned char* mxf_mem_file_get_chunk_data(MXFMemoryFile *mxfMemFile, int64_t chunkIndex)
{
    if (chunkIndex < 0 || chunkIndex >= mxfMemFile->mxfFile->sysData->numChunks) {
        mxf_log_error("Invalid chunk index value %"PRId64""LOG_LOC_FORMAT, chunkIndex, LOG_LOC_PARAMS);
        return NULL;
    }

    return mxfMemFile->mxfFile->sysData->chunks[chunkIndex].data;
}

int64_t mxf_mem_file_get_chunk_size(MXFMemoryFile *mxfMemFile, int64_t chunkIndex)
{
    if (chunkIndex < 0 || chunkIndex >= mxfMemFile->mxfFile->sysData->numChunks) {
        mxf_log_error("Invalid chunk index value %"PRId64""LOG_LOC_FORMAT, chunkIndex, LOG_LOC_PARAMS);
        return 0;
    }

    return mxfMemFile->mxfFile->sysData->chunks[chunkIndex].size;
}

int64_t mxf_mem_file_get_size(MXFMemoryFile *mxfMemFile)
{
    MXFFileSysData *sysData = mxfMemFile->mxfFile->sysData;

    if (sysData->numChunks == 0)
        return 0;

    return sysData->chunkSize * (sysData->numChunks - 1) +
           sysData->chunks[sysData->numChunks - 1].size;
}

int mxf_mem_file_flush_to_file(MXFMemoryFile *mxfMemFile, MXFFile *mxfFile)
{
    MXFFileSysData *sysData = mxfMemFile->mxfFile->sysData;

    int64_t i;
    for (i = 0; i < sysData->numChunks; i++) {
        const unsigned char *data = sysData->chunks[i].data;
        int64_t remainder = sysData->chunks[i].size;
        uint32_t writeSize;
        while (remainder > 0) {
            if (remainder > 0xffffffff)
                writeSize = 0xffffffff;
            else
                writeSize = (uint32_t)remainder;

            if (!mxf_file_write(mxfFile, data, writeSize))
                return 0;

            data += writeSize;
            remainder -= writeSize;
        }
    }

    return 1;
}

