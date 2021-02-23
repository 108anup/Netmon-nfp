#ifndef SANDBOX_H
#define SANDBOX_H

#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_atomic.h>
#include <pif_common.h>
#include "pif_plugin.h"

#define HASH_FUNC0(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func0_##SK_NUM(uint32_t a, uint32_t b) {              \
    return a % NUM_COLS;                                                       \
  }

#define HASH_FUNC1(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func1_##SK_NUM(uint32_t a, uint32_t b) {              \
    return b % NUM_COLS;                                                       \
  }

#define HASH_FUNC2(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func2_##SK_NUM(uint32_t a, uint32_t b) {              \
    return (a & b) % NUM_COLS;                                                 \
  }

#define HASH_FUNC3(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func3_##SK_NUM(uint32_t a, uint32_t b) {              \
    return (a | b) % NUM_COLS;                                                 \
  }

#define HASH_FUNC4(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func4_##SK_NUM(uint32_t a, uint32_t b) {              \
    return a % NUM_COLS;                                                       \
  }

#define HASH_FUNC5(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func5_##SK_NUM(uint32_t a, uint32_t b) {              \
    return b % NUM_COLS;                                                       \
  }

#define HASH_FUNC6(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func6_##SK_NUM(uint32_t a, uint32_t b) {              \
    return (a & b) % NUM_COLS;                                                 \
  }

#define HASH_FUNC7(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func7_##SK_NUM(uint32_t a, uint32_t b) {              \
    return (a | b) % NUM_COLS;                                                 \
  }

#define HASH_FUNC8(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func8_##SK_NUM(uint32_t a, uint32_t b) {              \
    return a % NUM_COLS;                                                       \
  }

#define HASH_FUNC9(NAME, SK_NUM, NUM_COLS)                                     \
  uint32_t hash_##NAME##_func9_##SK_NUM(uint32_t a, uint32_t b) {              \
    return b % NUM_COLS;                                                       \
  }

#define HASH_FUNC10(NAME, SK_NUM, NUM_COLS)                                    \
  uint32_t hash_##NAME##_func10_##SK_NUM(uint32_t a, uint32_t b) {             \
    return (a & b) % NUM_COLS;                                                 \
  }

#define HASH_FUNC11(NAME, SK_NUM, NUM_COLS)                                    \
  uint32_t hash_##NAME##_func11_##SK_NUM(uint32_t a, uint32_t b) {             \
    return (a | b) % NUM_COLS;                                                 \
  }

#define UPDATE_ROW(SK_NUM, ROW_NUM)                                            \
  __forceinline void row_update_##SK_NUM##_##ROW_NUM(uint32_t srcAddr,         \
                                                     uint32_t dstAddr) {       \
    uint32_t hv = hash_index_func##ROW_NUM##_##SK_NUM(srcAddr, dstAddr);       \
    atomic_add(&sketch_##SK_NUM[ROW_NUM][hv], 1);                              \
  }

__intrinsic void
atomic_add(volatile __declspec(mem addr40) void  *addr, int x)
{
    unsigned int addr_hi, addr_lo;
    __declspec(write_reg) int xfer;
    SIGNAL my_signal;
    addr_hi = ((unsigned long long int)addr >> 8) & 0xff000000;
    addr_lo = (unsigned long long int)addr & 0xffffffff;

    if (__is_ct_const(x) && x == 1) {
        __asm {
            mem[incr, --, addr_hi, <<8, addr_lo, 1];
        }
    } else {
        xfer = x;
        __asm {
            mem[add, xfer, addr_hi, <<8, addr_lo, 1],   \
                ctx_swap[my_signal];
        }
    }
}

__intrinsic void
atomic_sub(volatile __declspec(mem addr40) void  *addr, int x)
{
  unsigned int addr_hi, addr_lo;
  __declspec(write_reg) int xfer;
  SIGNAL my_signal;
  addr_hi = ((unsigned long long int)addr >> 8) & 0xff000000;
  addr_lo = (unsigned long long int)addr & 0xffffffff;

  if (__is_ct_const(x) && x == 1) {
    __asm {
      mem[decr, --, addr_hi, <<8, addr_lo, 1];
    }
  } else {
    xfer = x;
    __asm {
      mem[sub, xfer, addr_hi, <<8, addr_lo, 1],   \
        ctx_swap[my_signal];
    }
  }
}

#endif // SANDBOX_H
