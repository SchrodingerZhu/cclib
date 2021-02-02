//
// Created by schrodinger on 2/3/21.
//

#ifndef CCLIB_CC_HASH_GENERIC_H
#define CCLIB_CC_HASH_GENERIC_H

#include <stdint.h>
#include "../cc_defs.h"


#define CC_HASH_FALLBACK

#ifndef __SIZEOF_INT128__

static CC_FAST_PATH void
CCFN(cc_hash_emu_multiply)(uint64_t op1, uint64_t op2, uint64_t *hi, uint64_t *lo) {
    uint64_t u1 = (op1 & 0xffffffff);
    uint64_t v1 = (op2 & 0xffffffff);
    uint64_t t = (u1 * v1);
    uint64_t w3 = (t & 0xffffffff);
    uint64_t k = (t >> 32);

    op1 >>= 32;
    t = (op1 * v1) + k;
    k = (t & 0xffffffff);
    uint64_t w1 = (t >> 32);

    op2 >>= 32;
    t = (u1 * op2) + k;
    k = (t >> 32);

    *hi = (op1 * op2) + w1 + k;
    *lo = (t << 32) + w3;
}

#endif

static CC_FAST_PATH uint64_t
CCFN(cc_hash_folded_multiply)(uint64_t x, uint64_t y) {
#ifdef __SIZEOF_INT128__
    __int128 result = (__int128)(s) * (__int128)(by);
    return (uint64_t)(result & 0xffffffffffffffff) ^ (uint64_t)(result >> 64);
#else
    uint64_t high, low;
    CCFN(cc_hash_emu_multiply)(s, by, &high, &low);
    return high ^ low;
#endif
}

#endif //CCLIB_CC_HASH_GENERIC_H
