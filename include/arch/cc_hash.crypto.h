#ifndef CCLIB_CC_HASH_CRYPTO_H
#define CCLIB_CC_HASH_CRYPTO_H

#include <stdint.h>
#include <arm_neon.h>

#define CC_HASH_AES_ENABLED

/* for ARM with AES (Crypto) target */
typedef uint8x16_t CCTY(cc_aes128);

#define CC_AES128_OR(a, b) (veorq_u8(a, b))
#define CC_SHUFFLE_KEY     0x020a07000c01030eull

/* FIXME: MSVC is not considered in the prototype */


static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_shuffle)(CCTY(cc_aes128) data) {
    static const unsigned long masks[2] = {
        0x020a07000c01030eull, 0x050f0d0806090b04ull};
    return vqtbl1q_p8(data, vld1q_u64(masks));
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_shuffle_add)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    return return vaddq_s64(shuffle(x), y);;
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_add)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    return vaddq_s64(x, y);
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_encode)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    /* FIXME: GNU Vector Extension is used */
    return (aes128_t)vaesmcq_u8(vaeseq_u8((uint8x16_t)x, (uint8x16_t){})) ^ y;
}

static CC_FAST_PATH CCTY(cc_aes128)
CCFN(cc_hash_decode)(CCTY(cc_aes128) x, CCTY(cc_aes128) y) {
    /* FIXME: GNU Vector Extension is used */
    return (aes128_t)vaesimcq_u8(vaesdq_u8((uint8x16_t)x, (uint8x16_t){})) ^ y;
}

static CC_FAST_PATH
uint64_t rotate_left(uint64_t x, uint64_t bit) {
#if __has_builtin(__builtin_rotateleft64)
    return __builtin_rotateleft64(x, y);
#else
    return (x >> (64 - bit)) | (x << bit);
#endif
}

#endif //CCLIB_CC_HASH_CRYPTO_H