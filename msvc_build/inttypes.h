#ifndef __INTTYPES_H__
#define __INTTYPES_H__

/* subset of C99 inttypes.h for Microsoft Visual Studio build */

#if defined(_MSC_VER)


/* exact width integer types */

#if (_MSC_VER >= 1600)

/* Visual Studio 2010 provides a stdint.h */

#include <stdint.h>

#else

typedef unsigned char       uint8_t;
typedef unsigned __int16    uint16_t;
typedef unsigned __int32    uint32_t;
typedef unsigned __int64    uint64_t;

typedef signed char         int8_t;
typedef __int16             int16_t;
typedef __int32             int32_t;
typedef __int64             int64_t;

#endif


/* print format specifiers */

#define PRId64  "I64d"
#define PRIu64  "I64u"
#define PRIszt  "u"



#endif

#endif

