/*!
 * @file preproc_log2.hpp
 * @author Christian Amstutz
 * @date Mar 20, 2014
 *
 * @brief
 *
 */

#define NBITS2(n) ((n&2)?1:0)
#define NBITS4(n) ((n&(0xC))?(2+NBITS2(n>>2)):(NBITS2(n)))
#define NBITS8(n) ((n&0xF0)?(4+NBITS4(n>>4)):(NBITS4(n)))
#define NBITS16(n) ((n&0xFF00)?(8+NBITS8(n>>8)):(NBITS8(n)))
#define NBITS32(n) ((n&0xFFFF0000)?(16+NBITS16(n>>16)):(NBITS16(n)))
#define NBITS64(n) ((n&0xFFFFFFFF00000000)?(32+NBITS32(n>>32)):(NBITS32(n)))
#define NBITS128(n) ((n&0xFFFFFFFFFFFFFFFF0000000000000000)?(64+NBITS64(n>>64)):(NBITS64(n)))
#define NBITS(n) (n==0?0:NBITS128(n)+1)
