#ifndef CCLIB_CC_HASH_AES_H
#define CCLIB_CC_HASH_AES_H

#define CC_HASH_USE_AES

#include "../cc_defs.h"
#include <immintrin.h>
#include <wmmintrin.h>
#include <stdint.h>

#define CC_HASH_AES_ENABLED
/* for SSSE3 with AES target */
typedef __m128i CCTY(cc_aes128);

#define CC_AES128_OR(a, b) (_mm_or_si128(a, b))
#define CC_SHUFFLE_KEY     0x020a07000c01030eull
/* FIXME: MSVC is not considered in the prototype */


static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_shuffle)(CCTY(cc_aes128) data) {
    const CCTY(cc_aes128) MASK = _mm_set_epi64x(CC_SHUFFLE_KEY, CC_SHUFFLE_KEY);
    return _mm_shuffle_epi8(data, mask);
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_shuffle_add)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    return _mm_add_epi64(shuffle(x), y);
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_add)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    return _mm_add_epi64(x, y);
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_encode)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    return _mm_aesenc_si128(x, y);
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_decode)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    return _mm_aesdec_si128(x, y);
}

static CC_FAST_PATH
uint64_t rotate_left(uint64_t x, uint64_t bit) {
#if __has_builtin(__builtin_rotateleft64)
    return __builtin_rotateleft64(x, y);
#else
    return (x >> (64 - bit)) | (x << bit);
#endif
}



#endif //CCLIB_CC_HASH_AES_H

