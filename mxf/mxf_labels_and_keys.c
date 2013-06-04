/*
 * MXF labels, keys, track numbers, etc.
 *
 * Copyright (C) 2006, British Broadcasting Corporation
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

#include <mxf/mxf.h>



mxfKey g_KLVFill_key = /* g_LegacyKLVFill_key */
    {0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x02, 0x10, 0x01, 0x00, 0x00, 0x00};



int mxf_is_op_atom(const mxfUL *label)
{
    static const mxfUL opAtomPrefix = MXF_ATOM_OP_L(0);

    /* ignoring octet7, the registry version byte */
    return memcmp(label,          &opAtomPrefix,        7) == 0 &&
           memcmp(&label->octet8, &opAtomPrefix.octet8, 5) == 0;
}

int mxf_is_op_1a(const mxfUL *label)
{
    static const mxfUL op1APrefix = MXF_1A_OP_L(0);

    /* ignoring octet7, the registry version byte */
    return memcmp(label,          &op1APrefix,        7) == 0 &&
           memcmp(&label->octet8, &op1APrefix.octet8, 5) == 0;
}

int mxf_is_op_1b(const mxfUL *label)
{
    static const mxfUL op1BPrefix = MXF_1B_OP_L(0);

    /* ignoring octet7, the registry version byte */
    return memcmp(label,          &op1BPrefix,        7) == 0 &&
           memcmp(&label->octet8, &op1BPrefix.octet8, 5) == 0;
}



int mxf_is_picture(const mxfUL *label)
{
    return memcmp(label, &MXF_DDEF_L(Picture), sizeof(mxfUL)) == 0 ||
           memcmp(label, &MXF_DDEF_L(LegacyPicture), sizeof(mxfUL)) == 0;
}

int mxf_is_sound(const mxfUL *label)
{
    return memcmp(label, &MXF_DDEF_L(Sound), sizeof(mxfUL)) == 0 ||
           memcmp(label, &MXF_DDEF_L(LegacySound), sizeof(mxfUL)) == 0;
}

int mxf_is_timecode(const mxfUL *label)
{
    return memcmp(label, &MXF_DDEF_L(Timecode), sizeof(mxfUL)) == 0 ||
           memcmp(label, &MXF_DDEF_L(LegacyTimecode), sizeof(mxfUL)) == 0;
}

int mxf_is_data(const mxfUL *label)
{
    return memcmp(label, &MXF_DDEF_L(Data), sizeof(mxfUL)) == 0;
}

int mxf_is_descriptive_metadata(const mxfUL *label)
{
    return memcmp(label, &MXF_DDEF_L(DescriptiveMetadata), sizeof(mxfUL)) == 0;
}

MXFDataDefEnum mxf_get_ddef_enum(const mxfUL *label)
{
    if (mxf_is_picture(label))
        return MXF_PICTURE_DDEF;
    else if (mxf_is_sound(label))
        return MXF_SOUND_DDEF;
    else if (mxf_is_timecode(label))
        return MXF_TIMECODE_DDEF;
    else if (mxf_is_data(label))
        return MXF_DATA_DDEF;
    else if (mxf_is_descriptive_metadata(label))
        return MXF_DM_DDEF;
    else
        return MXF_UNKNOWN_DDEF;
}

int mxf_get_ddef_label(MXFDataDefEnum data_def, mxfUL *label)
{
    switch (data_def)
    {
        case MXF_PICTURE_DDEF:
            memcpy(label, &MXF_DDEF_L(Picture), sizeof(*label));
            return 1;
        case MXF_SOUND_DDEF:
            memcpy(label, &MXF_DDEF_L(Sound), sizeof(*label));
            return 1;
        case MXF_TIMECODE_DDEF:
            memcpy(label, &MXF_DDEF_L(Timecode), sizeof(*label));
            return 1;
        case MXF_DATA_DDEF:
            memcpy(label, &MXF_DDEF_L(Data), sizeof(*label));
            return 1;
        case MXF_DM_DDEF:
            memcpy(label, &MXF_DDEF_L(DescriptiveMetadata), sizeof(*label));
            return 1;
        case MXF_UNKNOWN_DDEF:
            break;
    }

    return 0;
}



int mxf_is_generic_container_label(const mxfUL *label)
{
    static const mxfUL gcLabel = MXF_GENERIC_CONTAINER_LABEL(0x00, 0x00, 0x00, 0x00);

    /* compare first 7 bytes, skip the registry version and compare another 5 bytes */
    return memcmp(label, &gcLabel, 7) == 0 &&
           memcmp(&label->octet8, &gcLabel.octet8, 5) == 0;
}



int mxf_is_avc_ec(const mxfUL *label, int frame_wrapped)
{
    return mxf_is_generic_container_label(label) &&
           label->octet13 == 0x10 &&                         /* AVC byte stream */
           (label->octet14 & 0xf0) == 0x60 &&                /* video stream */
           ((frame_wrapped && label->octet15 == 0x01) ||     /* frame wrapped or */
               (!frame_wrapped && label->octet15 == 0x02));  /*   clip wrapped */
}

int mxf_is_mpeg_video_ec(const mxfUL *label, int frame_wrapped)
{
    return mxf_is_generic_container_label(label) &&
           label->octet13 == 0x04 &&                         /* MPEG elementary stream */
           (label->octet14 & 0xf0) == 0x60 &&                /* video stream */
           ((frame_wrapped && label->octet15 == 0x01) ||     /* frame wrapped or */
               (!frame_wrapped && label->octet15 == 0x02));  /*   clip wrapped */
}



void mxf_complete_essence_element_key(mxfKey *key, uint8_t count, uint8_t type, uint8_t num)
{
    key->octet13 = count;
    key->octet14 = type;
    key->octet15 = num;
}

void mxf_complete_essence_element_track_num(uint32_t *trackNum, uint8_t count, uint8_t type, uint8_t num)
{
    *trackNum &= 0xFF000000;
    *trackNum |= ((uint32_t)count) << 16;
    *trackNum |= ((uint32_t)type)  << 8;
    *trackNum |=  (uint32_t)(num);
}

