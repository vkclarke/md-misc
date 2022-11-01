/*
 * ANSI C compatible fixed-size integer types
 * (accounting for varying type sizes)
 *
 * if you don't like this naming convention you are
 * free to either edit or re-typedef them yourself
 */

#include <limits.h>

/* i8 */
#ifndef i8
#ifdef int8_t
typedef int8_t i8;
#elif CHAR_BIT == 8
typedef char i8;
#endif
#endif

/* u8 */
#ifndef u8
#ifdef uint8_t
typedef uint8_t u8;
#elif CHAR_BIT == 8
typedef unsigned char u8;
#endif
#endif

/* i16 */
#ifndef i16
#ifdef int16_t
typedef int16_t i16;
#elif SHRT_MAX == 0x7FFF
typedef short i16;
#elif INT_MAX == 0x7FFF
typedef int i16;
#endif
#endif

/* u16 */
#ifndef u16
#ifdef uint16_t
typedef uint16_t u16;
#elif USHRT_MAX == 0xFFFF
typedef unsigned short u16;
#elif UINT_MAX == 0xFFFF
typedef unsigned int u16;
#endif
#endif

/* i32 */
#ifndef i32
#ifdef int32_t
typedef int32_t i32;
#elif INT_MAX == 0x7FFFFFFF
typedef int i32;
#elif LONG_MAX == 0x7FFFFFFF
typedef long i32;
#endif
#endif

/* u32 */
#ifndef u32
#ifdef uint32_t
typedef uint32_t u32;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int u32;
#elif ULONG_MAX == 0xFFFFFFFF
typedef unsigned long u32;
#endif
#endif

/* i64 */
#ifndef i64
#ifdef int64_t
typedef int64_t i64;
#elif LONG_MAX == 0x7FFFFFFFFFFFFFFF
typedef long i64;
#elif LLONG_MAX == 0x7FFFFFFFFFFFFFFF
typedef long long i64;
#endif
#endif

/* u64 */
#ifndef u64
#ifdef uint64_t
typedef uint64_t u64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned long u64;
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned long long u64;
#endif
#endif
