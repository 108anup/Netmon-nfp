#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_atomic.h>
#include <pif_common.h>
#include "pif_plugin.h"

#define NUM_ROWS 80
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
UPDATE_ROW(4, 1)
UPDATE_ROW(5, 2)
UPDATE_ROW(6, 0)
UPDATE_ROW(7, 1)
UPDATE_ROW(8, 2)
UPDATE_ROW(9, 0)
UPDATE_ROW(10, 1)
UPDATE_ROW(11, 2)
UPDATE_ROW(12, 0)
UPDATE_ROW(13, 1)
UPDATE_ROW(14, 2)
UPDATE_ROW(15, 0)
UPDATE_ROW(16, 1)
UPDATE_ROW(17, 2)
UPDATE_ROW(18, 0)
UPDATE_ROW(19, 1)
UPDATE_ROW(20, 2)
UPDATE_ROW(21, 0)
UPDATE_ROW(22, 1)
UPDATE_ROW(23, 2)
UPDATE_ROW(24, 0)
UPDATE_ROW(25, 1)
UPDATE_ROW(26, 2)
UPDATE_ROW(27, 0)
UPDATE_ROW(28, 1)
UPDATE_ROW(29, 2)
UPDATE_ROW(30, 0)
UPDATE_ROW(31, 1)
UPDATE_ROW(32, 2)
UPDATE_ROW(33, 0)
UPDATE_ROW(34, 1)
UPDATE_ROW(35, 2)
UPDATE_ROW(36, 0)
UPDATE_ROW(37, 1)
UPDATE_ROW(38, 2)
UPDATE_ROW(39, 0)
UPDATE_ROW(40, 1)
UPDATE_ROW(41, 2)
UPDATE_ROW(42, 0)
UPDATE_ROW(43, 1)
UPDATE_ROW(44, 2)
UPDATE_ROW(45, 0)
UPDATE_ROW(46, 1)
UPDATE_ROW(47, 2)
UPDATE_ROW(48, 0)
UPDATE_ROW(49, 1)
UPDATE_ROW(50, 2)
UPDATE_ROW(51, 0)
UPDATE_ROW(52, 1)
UPDATE_ROW(53, 2)
UPDATE_ROW(54, 0)
UPDATE_ROW(55, 1)
UPDATE_ROW(56, 2)
UPDATE_ROW(57, 0)
UPDATE_ROW(58, 1)
UPDATE_ROW(59, 2)
UPDATE_ROW(60, 0)
UPDATE_ROW(61, 1)
UPDATE_ROW(62, 2)
UPDATE_ROW(63, 0)
UPDATE_ROW(64, 1)
UPDATE_ROW(65, 2)
UPDATE_ROW(66, 0)
UPDATE_ROW(67, 1)
UPDATE_ROW(68, 2)
UPDATE_ROW(69, 0)
UPDATE_ROW(70, 1)
UPDATE_ROW(71, 2)
UPDATE_ROW(72, 0)
UPDATE_ROW(73, 1)
UPDATE_ROW(74, 2)
UPDATE_ROW(75, 0)
UPDATE_ROW(76, 1)
UPDATE_ROW(77, 2)
UPDATE_ROW(78, 0)
UPDATE_ROW(79, 1)
