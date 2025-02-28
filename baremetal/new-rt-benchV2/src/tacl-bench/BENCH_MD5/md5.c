/**
 * @file md5.c
 * @defgroup md5 Md5
 * @ingroup rt-tacle-bench
 * @brief RT-Bench compatible md5 benchmark from TACle Bench.
 * @details
 * The original script has been broken down in three components:
 * - init: benchmark_init();
 * - execution: benchmark_execution();
 * - teardown: benchmark_teardown();
 *
 * Code is courtesy of TACle Bench project (see https://github.com/tacle/tacle-bench)
 * This header was generated automatically, please consult the code at bench/kernel/md5/md5.c for the exact license(s).
 *

  This program is part of the TACLeBench benchmark suite.
  Version V 2.0

  Name: md5.c

  @author unknown

  Function: MD5 cryptographic hash function (see also RFC 1321).

  Source: RSA Data Security, Inc., MD5 message-digest algorithm

  Original name: md5c.c

  Changes: no major functional changes, inlined include files

  @copyright see below

*/

// Libraries used by rt-bench

// Description: This is the MD5 algorithm comming form the Diffie-Hellman
// application in the Netbench benchmark suite

#define RANDOM_BYTES_NEEDED 256

// Here, it can be defined how many keys should be exchanged
#define EXCHANGEKEYS 10
////////////////////////// md5c.c /////////////////////
/* MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm
*/

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
   rights reserved.

   License to copy and use this software is granted provided that it
   is identified as the "RSA Data Security, Inc. MD5 Message-Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   License is also granted to make and use derivative works provided
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD5 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
*/

//////// global.h ///////////////
//#include "global.h"
/* GLOBAL.H - RSAREF types and constants */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
*/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_ 1

/* PROTOTYPES should be set to one if and only if the compiler supports
     function argument prototyping.
   The following makes PROTOTYPES default to 1 if it has not already been
     defined as 0 with C compiler flags.
*/
#ifndef PROTOTYPES
#define PROTOTYPES 1
#endif

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

#ifndef NULL_PTR
#define NULL_PTR ((POINTER)0)
#endif

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) x = *(&x);
#endif

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
   If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
     returns an empty list.
*/
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif

#endif /* end _GLOBAL_H_ */
//////// end global.h ///////////////


///////////// md5.h //////////////
//#include "md5.h"
/* MD5.H - header file for MD5C.C
*/

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
   rights reserved.

   License to copy and use this software is granted provided that it
   is identified as the "RSA Data Security, Inc. MD5 Message-Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   License is also granted to make and use derivative works provided
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD5 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
*/

#ifndef _MD5_H_
#define _MD5_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* MD5 context. */
typedef struct {
  UINT4 state[ 16 ];                                   /* state (ABCD) */
  UINT4 count[ 2 ];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[ 64 ];                         /* input buffer */
} MD5_CTX;

#ifdef __cplusplus
}
#endif

#endif
/////////// end md5.h /////////

/* Constants for MD5Transform routine.
*/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* Random structure.
*/
typedef struct {
  unsigned int bytesNeeded;
  unsigned char state[ 16 ];
  unsigned int outputAvailable;
  unsigned char output[ 16 ];
} R_RANDOM_STRUCT;

void md5_orig_init PROTO_LIST ( ( MD5_CTX * ) );
void md5_update PROTO_LIST ( ( MD5_CTX *, unsigned char *, unsigned int ) );
void md5_final PROTO_LIST ( ( unsigned char [ 64 ], MD5_CTX * ) );
void md5_memset PROTO_LIST ( ( POINTER, int, unsigned int ) );
void md5_transform PROTO_LIST ( ( UINT4 [ 4 ], unsigned char [ 64 ] ) );
void md5_encode PROTO_LIST ( ( unsigned char *, UINT4 *, int ) );
void md5_decode PROTO_LIST ( ( UINT4 *, unsigned char *, unsigned int ) );
void md5_memcpy PROTO_LIST ( ( POINTER, POINTER, unsigned int ) );
void md5_R_memset ( POINTER output, int value, unsigned int len );
void md5_memset_x( unsigned char *ptr, int value, unsigned long len );
int md5_R_RandomInit ( R_RANDOM_STRUCT *randomStruct );
int md5_R_RandomUpdate ( R_RANDOM_STRUCT *randomStruct, unsigned char *block,
                         unsigned int blockLen );
void md5_InitRandomStruct ( R_RANDOM_STRUCT *randomStruct );
int md5_R_GetRandomBytesNeeded ( unsigned int *bytesNeeded,
                                 R_RANDOM_STRUCT *randomStruct );

int md5_bytesNeeded;

int main( void );

unsigned char md5_PADDING[ 64 ] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions.
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
   Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }


/* MD5 initialization. Begins an MD5 operation, writing a new context.
*/
void md5_orig_init ( MD5_CTX
                     *context )                                        /* context */
{
  context->count[ 0 ] = context->count[ 1 ] = 0;

  /* Load magic initialization constants.
  */
  context->state[ 0 ] = 0x67452301;
  context->state[ 1 ] = 0xefcdab89;
  context->state[ 2 ] = 0x98badcfe;
  context->state[ 3 ] = 0x10325476;
  context->state[ 4 ] = 0x0;
  context->state[ 5 ] = 0x0;
  context->state[ 6 ] = 0x0;
  context->state[ 7 ] = 0x0;
  context->state[ 8 ] = 0x0;
  context->state[ 9 ] = 0x0;
  context->state[ 10 ] = 0x0;
  context->state[ 11 ] = 0x0;
  context->state[ 12 ] = 0x0;
  context->state[ 13 ] = 0x0;
  context->state[ 14 ] = 0x0;
  context->state[ 15 ] = 0x0;
}

/* MD5 block update operation. Continues an MD5 message-digest
     operation, processing another message block, and updating the
     context.
*/
void md5_update ( MD5_CTX *context, unsigned char *input,
                  unsigned int inputLen )
//MD5_CTX *context;                                        /* context */
//unsigned char *input;                                /* input block */
//unsigned int inputLen;                     /* length of input block */
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = ( unsigned int )( ( context->count[ 0 ] >> 3 ) & 0x3F );

  /* Update number of bits */
  if ( ( context->count[ 0 ] += ( ( UINT4 )inputLen << 3 ) )
       < ( ( UINT4 )inputLen << 3 ) )
    context->count[ 1 ]++;
  context->count[ 1 ] += ( ( UINT4 )inputLen >> 29 );

  partLen = 64 - index;

  /* Transform as many times as possible.
  */
  if ( inputLen >= partLen ) {
    md5_memcpy ( ( POINTER )&context->buffer[ index ], ( POINTER )input, partLen );
    md5_transform ( context->state, context->buffer );

    _Pragma( "loopbound min 0 max 0" )
    for ( i = partLen; i + 63 < inputLen; i += 64 )
      md5_transform ( context->state, &input[ i ] );

    index = 0;
  } else
    i = 0;

  /* Buffer remaining input */
  md5_memcpy ( ( POINTER )&context->buffer[ index ], ( POINTER )&input[ i ],
               inputLen - i );
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
     the message digest and zeroizing the context.
*/
void md5_final ( unsigned char digest[ 64 ], MD5_CTX *context )
//unsigned char digest[ 16 ];                         /* message digest */
//MD5_CTX *context;                                       /* context */
{
  unsigned char bits[ 8 ];
  unsigned int index, padLen;

  /* Save number of bits */
  md5_encode ( bits, context->count, 8 );

  /* Pad out to 56 mod 64.
  */
  index = ( unsigned int )( ( context->count[ 0 ] >> 3 ) & 0x3f );
  padLen = ( index < 56 ) ? ( 56 - index ) : ( 120 - index );
  md5_update ( context, md5_PADDING, padLen );

  /* Append length (before padding) */
  md5_update ( context, bits, 8 );

  /* Store state in digest */
  md5_encode ( digest, context->state, 64 );

  /* Zeroize sensitive information.
  */
  md5_memset ( ( POINTER )context, 0, sizeof ( *context ) );
}

/* Note: Replace "for loop" with standard memset if possible.
*/
void md5_memset ( POINTER output, int value, unsigned int len )
{
  unsigned int i;

  _Pragma( "loopbound min 128 max 208" )
  for ( i = 0; i < len; i++ )
    ( ( char * )output )[ i ] = ( char )value;
}

/* MD5 basic transformation. Transforms state based on block.
*/
void md5_transform ( UINT4 state[ 4 ], unsigned char block[ 64 ] )
{
  UINT4 a = state[ 0 ], b = state[ 1 ], c = state[ 2 ], d = state[ 3 ], x[ 16 ];

  md5_decode ( x, block, 64 );

  /* Round 1 */
  FF ( a, b, c, d, x[  0 ], S11, 0xd76aa478 ); /* 1 */
  FF ( d, a, b, c, x[  1 ], S12, 0xe8c7b756 ); /* 2 */
  FF ( c, d, a, b, x[  2 ], S13, 0x242070db ); /* 3 */
  FF ( b, c, d, a, x[  3 ], S14, 0xc1bdceee ); /* 4 */
  FF ( a, b, c, d, x[  4 ], S11, 0xf57c0faf ); /* 5 */
  FF ( d, a, b, c, x[  5 ], S12, 0x4787c62a ); /* 6 */
  FF ( c, d, a, b, x[  6 ], S13, 0xa8304613 ); /* 7 */
  FF ( b, c, d, a, x[  7 ], S14, 0xfd469501 ); /* 8 */
  FF ( a, b, c, d, x[  8 ], S11, 0x698098d8 ); /* 9 */
  FF ( d, a, b, c, x[  9 ], S12, 0x8b44f7af ); /* 10 */
  FF ( c, d, a, b, x[ 10 ], S13, 0xffff5bb1 ); /* 11 */
  FF ( b, c, d, a, x[ 11 ], S14, 0x895cd7be ); /* 12 */
  FF ( a, b, c, d, x[ 12 ], S11, 0x6b901122 ); /* 13 */
  FF ( d, a, b, c, x[ 13 ], S12, 0xfd987193 ); /* 14 */
  FF ( c, d, a, b, x[ 14 ], S13, 0xa679438e ); /* 15 */
  FF ( b, c, d, a, x[ 15 ], S14, 0x49b40821 ); /* 16 */

  /* Round 2 */
  GG ( a, b, c, d, x[  1 ], S21, 0xf61e2562 ); /* 17 */
  GG ( d, a, b, c, x[  6 ], S22, 0xc040b340 ); /* 18 */
  GG ( c, d, a, b, x[ 11 ], S23, 0x265e5a51 ); /* 19 */
  GG ( b, c, d, a, x[  0 ], S24, 0xe9b6c7aa ); /* 20 */
  GG ( a, b, c, d, x[  5 ], S21, 0xd62f105d ); /* 21 */
  GG ( d, a, b, c, x[ 10 ], S22,  0x2441453 ); /* 22 */
  GG ( c, d, a, b, x[ 15 ], S23, 0xd8a1e681 ); /* 23 */
  GG ( b, c, d, a, x[  4 ], S24, 0xe7d3fbc8 ); /* 24 */
  GG ( a, b, c, d, x[  9 ], S21, 0x21e1cde6 ); /* 25 */
  GG ( d, a, b, c, x[ 14 ], S22, 0xc33707d6 ); /* 26 */
  GG ( c, d, a, b, x[  3 ], S23, 0xf4d50d87 ); /* 27 */
  GG ( b, c, d, a, x[  8 ], S24, 0x455a14ed ); /* 28 */
  GG ( a, b, c, d, x[ 13 ], S21, 0xa9e3e905 ); /* 29 */
  GG ( d, a, b, c, x[  2 ], S22, 0xfcefa3f8 ); /* 30 */
  GG ( c, d, a, b, x[  7 ], S23, 0x676f02d9 ); /* 31 */
  GG ( b, c, d, a, x[ 12 ], S24, 0x8d2a4c8a ); /* 32 */

  /* Round 3 */
  HH ( a, b, c, d, x[  5 ], S31, 0xfffa3942 ); /* 33 */
  HH ( d, a, b, c, x[  8 ], S32, 0x8771f681 ); /* 34 */
  HH ( c, d, a, b, x[ 11 ], S33, 0x6d9d6122 ); /* 35 */
  HH ( b, c, d, a, x[ 14 ], S34, 0xfde5380c ); /* 36 */
  HH ( a, b, c, d, x[  1 ], S31, 0xa4beea44 ); /* 37 */
  HH ( d, a, b, c, x[  4 ], S32, 0x4bdecfa9 ); /* 38 */
  HH ( c, d, a, b, x[  7 ], S33, 0xf6bb4b60 ); /* 39 */
  HH ( b, c, d, a, x[ 10 ], S34, 0xbebfbc70 ); /* 40 */
  HH ( a, b, c, d, x[ 13 ], S31, 0x289b7ec6 ); /* 41 */
  HH ( d, a, b, c, x[  0 ], S32, 0xeaa127fa ); /* 42 */
  HH ( c, d, a, b, x[  3 ], S33, 0xd4ef3085 ); /* 43 */
  HH ( b, c, d, a, x[  6 ], S34,  0x4881d05 ); /* 44 */
  HH ( a, b, c, d, x[  9 ], S31, 0xd9d4d039 ); /* 45 */
  HH ( d, a, b, c, x[ 12 ], S32, 0xe6db99e5 ); /* 46 */
  HH ( c, d, a, b, x[ 15 ], S33, 0x1fa27cf8 ); /* 47 */
  HH ( b, c, d, a, x[  2 ], S34, 0xc4ac5665 ); /* 48 */

  /* Round 4 */
  II ( a, b, c, d, x[  0 ], S41, 0xf4292244 ); /* 49 */
  II ( d, a, b, c, x[  7 ], S42, 0x432aff97 ); /* 50 */
  II ( c, d, a, b, x[ 14 ], S43, 0xab9423a7 ); /* 51 */
  II ( b, c, d, a, x[  5 ], S44, 0xfc93a039 ); /* 52 */
  II ( a, b, c, d, x[ 12 ], S41, 0x655b59c3 ); /* 53 */
  II ( d, a, b, c, x[  3 ], S42, 0x8f0ccc92 ); /* 54 */
  II ( c, d, a, b, x[ 10 ], S43, 0xffeff47d ); /* 55 */
  II ( b, c, d, a, x[  1 ], S44, 0x85845dd1 ); /* 56 */
  II ( a, b, c, d, x[  8 ], S41, 0x6fa87e4f ); /* 57 */
  II ( d, a, b, c, x[ 15 ], S42, 0xfe2ce6e0 ); /* 58 */
  II ( c, d, a, b, x[  6 ], S43, 0xa3014314 ); /* 59 */
  II ( b, c, d, a, x[ 13 ], S44, 0x4e0811a1 ); /* 60 */
  II ( a, b, c, d, x[  4 ], S41, 0xf7537e82 ); /* 61 */
  II ( d, a, b, c, x[ 11 ], S42, 0xbd3af235 ); /* 62 */
  II ( c, d, a, b, x[  2 ], S43, 0x2ad7d2bb ); /* 63 */
  II ( b, c, d, a, x[  9 ], S44, 0xeb86d391 ); /* 64 */

  state[ 0 ] += a;
  state[ 1 ] += b;
  state[ 2 ] += c;
  state[ 3 ] += d;

  /* Zeroize sensitive information.
  */
  md5_memset ( ( POINTER )x, 0, sizeof ( x ) );
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
     a multiple of 4.
*/
void md5_encode ( unsigned char *output, UINT4 *input, int len )
{
  int i = 0,
      j;

  _Pragma( "loopbound min 2 max 16" )
  for ( j = 0; j < len; j += 4 ) {
    output[ j ] = ( unsigned char )( input[ i ] & 0xff );
    output[ j + 1 ] = ( unsigned char )( ( input[ i ] >> 8 ) & 0xff );
    output[ j + 2 ] = ( unsigned char )( ( input[ i ] >> 16 ) & 0xff );
    output[ j + 3 ] = ( unsigned char )( ( input[ i ] >> 24 ) & 0xff );
    ++i;
  }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
     a multiple of 4.
*/
void md5_decode ( UINT4 *output, unsigned char *input, unsigned int len )
{
  unsigned int i, j;

  _Pragma( "loopbound min 16 max 16" )
  for ( i = 0, j = 0; j < len; i++, j += 4 ) {
    output[ i ] = ( ( UINT4 )input[ j ] ) | ( ( ( UINT4 )input[ j + 1 ] ) << 8 ) |
                ( ( ( UINT4 )input[ j + 2 ] ) << 16 ) | ( ( ( UINT4 )input[ j + 3 ] ) << 24 );
  }
}

/* Note: Replace "for loop" with standard memcpy if possible.
*/
void md5_memcpy ( POINTER output, POINTER input, unsigned int len )
{
  unsigned int i;

  _Pragma( "loopbound min 0 max 55" )
  for ( i = 0; i < len; i++ )
    output[ i ] = input[ i ];
}

/////////////////// end md5c.c ////////////////////////

void md5_R_memset ( POINTER output, int value, unsigned int len )
//POINTER output;                                             /* output block */
//int value;                                                         /* value */
//unsigned int len;                                        /* length of block */
{
  if ( len )
    md5_memset_x ( output, value, len );
}


// Basic implementation of C's memset
void md5_memset_x( unsigned char *ptr, int value, unsigned long len )
{
  _Pragma( "loopbound min 16 max 64" )
  while ( len-- )
    *ptr++ = value;

  return;
}


int md5_R_RandomInit ( R_RANDOM_STRUCT *randomStruct )
//R_RANDOM_STRUCT *randomStruct;                      /* new random structure */
{
  randomStruct->bytesNeeded = RANDOM_BYTES_NEEDED;
  md5_R_memset ( ( POINTER )randomStruct->state, 0,
                 sizeof ( randomStruct->state ) );
  randomStruct->outputAvailable = 0;

  return ( 0 );
}

int md5_R_RandomUpdate ( R_RANDOM_STRUCT *randomStruct, unsigned char *block,
                         unsigned int blockLen )
//R_RANDOM_STRUCT *randomStruct;                          /* random structure */
//unsigned char *block;                          /* block of values to mix in */
//unsigned int blockLen;                                   /* length of block */
{
  MD5_CTX context;
  unsigned char digest[ 64 ];
  unsigned int i, x;

  md5_orig_init ( &context );
  md5_update ( &context, block, blockLen );
  md5_final ( digest, &context );

  /* add digest to state */
  x = 0;

  _Pragma( "loopbound min 16 max 16" )
  for ( i = 0; i < 16; i++ ) {
    x += randomStruct->state[ 15 - i ] + digest[ 15 - i ];
    randomStruct->state[ 15 - i ] = ( unsigned char )x;
    x >>= 8;
  }

  if ( randomStruct->bytesNeeded < blockLen )
    randomStruct->bytesNeeded = 0;
  else
    randomStruct->bytesNeeded -= blockLen;

  /* Zeroize sensitive information.
  */
  md5_R_memset ( ( POINTER )digest, 0, sizeof ( digest ) );

  return ( 0 );
}


/* Initialize the random structure with all zero seed bytes for test purposes.
   NOTE that this will cause the output of the "random" process to be
     the same every time.  To produce random bytes, the random struct
     needs random seeds!
*/
void md5_InitRandomStruct ( R_RANDOM_STRUCT *randomStruct )
{
  static unsigned char seedByte = 0;
  unsigned int bytesNeeded;

  md5_R_RandomInit ( randomStruct );

  /* Initialize with all zero seed bytes, which will not yield an actual
       random number output.
  */
  _Pragma( "loopbound min 256 max 256" )
  while ( 1 ) {
    md5_R_GetRandomBytesNeeded ( &bytesNeeded, randomStruct );
    if ( bytesNeeded == 0 )
      break;

    md5_R_RandomUpdate ( randomStruct, &seedByte, 1 );
  }
}

int md5_R_GetRandomBytesNeeded ( unsigned int *bytesNeeded,
                                 R_RANDOM_STRUCT *randomStruct )
//unsigned int *bytesNeeded;                 /* number of mix-in bytes needed */
//R_RANDOM_STRUCT *randomStruct;                          /* random structure */
{
  *bytesNeeded = randomStruct->bytesNeeded;

  return ( 0 );
}

int benchmark_init(int parameters_num, void **parameters)
{
  return 0;
}

int md5_return( void )
{
  return md5_bytesNeeded;
}

void benchmark_execution(int parameters_num, void **parameters)
{
  R_RANDOM_STRUCT randomStruct;
  R_RANDOM_STRUCT randomStruct2;
  /* We first generate parameters, and then do some key exchange each followed by a key computation...*/
  int keys_exchanged = 0;

  md5_InitRandomStruct ( &randomStruct );

  _Pragma( "loopbound min 10 max 10" )
  while ( keys_exchanged != EXCHANGEKEYS ) {
    keys_exchanged++;
    md5_InitRandomStruct ( &randomStruct2 );
  }

  md5_bytesNeeded = randomStruct.bytesNeeded + randomStruct2.bytesNeeded;
}

void benchmark_teardown(int parameters_num, void **parameters)
{}
