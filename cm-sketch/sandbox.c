#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_atomic.h>
#include <pif_common.h>
#include "pif_plugin.h"

#define NUM_ROWS 4
#define NUM_COLS 2048
#define SKETCH_COLUMN_COUNT_MASK 1023

uint32_t hash_func0(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr ^ dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

uint32_t hash_func1(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr | dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

uint32_t hash_func2(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr & dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
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
        mem_read_atomic(&in_xfer_sketch,                                \
                        &sketch[ROW_NUM][hv], sizeof(uint32_t));        \
        out_reg_sketch = in_xfer_sketch;                                \
        out_reg_sketch += 1;                                            \
        out_xfer_sketch = out_reg_sketch;                               \
        mem_write_atomic(&out_xfer_sketch,                              \
                         &sketch[ROW_NUM][hv], sizeof(uint32_t));       \
                                                                        \
        return PIF_PLUGIN_RETURN_FORWARD;                               \
    }                                                                   \


//PIF_PLUGIN_HDR_T *pif_plugin_hdr_get_HDR(EXTRACTED_HEADERS_T *headers)
UPDATE_ROW(0, 0)
UPDATE_ROW(1, 1)
UPDATE_ROW(2, 2)
UPDATE_ROW(3, 0)
