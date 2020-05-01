#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_atomic.h>
#include <pif_common.h>
#include "pif_plugin.h"

#define NUM_ROWS 12
#define NUM_COLS 1024
#define SKETCH_COLUMN_COUNT_MASK 1023

uint32_t hash_func0(uint32_t srcAddr, uint32_t dstAddr)
{
	return srcAddr % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

uint32_t hash_func1(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr | dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

uint32_t hash_func2(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr & dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
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

// __declspec(emem export scope(global))
// __export __mem
__declspec(emem export scope(global)) int32_t sketch[NUM_ROWS][NUM_COLS];

#define UPDATE_ROW(ROW_NUM, HASH_NUM)                                   \
    int pif_plugin_cms_update_##ROW_NUM##_##HASH_NUM(                   \
        EXTRACTED_HEADERS_T *headers,                                   \
        ACTION_DATA_T *action_data)                                     \
    {                                                                   \
                                                                        \
        __xread uint32_t in_xfer_sketch;                                \
        __gpr uint32_t out_reg_sketch;                                  \
        __xwrite uint32_t out_xfer_sketch;                              \
                                                                        \
                                                                        \
        PIF_PLUGIN_ipv4_T *ipv4_header = pif_plugin_hdr_get_ipv4(       \
            headers);                                                   \
        uint32_t srcAddr = PIF_HEADER_GET_ipv4___srcAddr(ipv4_header);  \
        uint32_t dstAddr = PIF_HEADER_GET_ipv4___dstAddr(ipv4_header);  \
        uint32_t hv = hash_func##HASH_NUM(srcAddr, dstAddr);            \
                                                                        \
        atomic_add(&sketch[ROW_NUM][hv], 1);                            \
                                                                        \
        return PIF_PLUGIN_RETURN_FORWARD;                               \
    }                                                                   \

/*

  mem_read_atomic(&in_xfer_sketch,                                \
  &sketch[ROW_NUM][hv], sizeof(uint32_t));                        \
  out_reg_sketch = in_xfer_sketch;                                \
  out_reg_sketch += 1;                                            \
  out_xfer_sketch = out_reg_sketch;                               \
  mem_write_atomic(&out_xfer_sketch,                              \
  &sketch[ROW_NUM][hv], sizeof(uint32_t));                        \

 */

//PIF_PLUGIN_HDR_T *pif_plugin_hdr_get_HDR(EXTRACTED_HEADERS_T *headers)
UPDATE_ROW(0, 0)
UPDATE_ROW(1, 1)
UPDATE_ROW(2, 2)
UPDATE_ROW(3, 0)
UPDATE_ROW(4, 1)
UPDATE_ROW(5, 2)
UPDATE_ROW(6, 0)
UPDATE_ROW(7, 1)
UPDATE_ROW(8, 2)
UPDATE_ROW(9, 0)
UPDATE_ROW(10, 1)
UPDATE_ROW(11, 2)
