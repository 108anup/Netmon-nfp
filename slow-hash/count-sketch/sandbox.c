#include "sandbox.h"

#define LB 0
#define UB 65535

#define NUM_COLS 4194304
#define NUM_ROWS 8

__declspec(emem export scope(global)) int32_t sketch[NUM_ROWS][NUM_COLS];

int pif_plugin_sketch_update(EXTRACTED_HEADERS_T *headers,
                             ACTION_DATA_T *action_data)
{

  __xread uint32_t in_xfer_sketch;
  __gpr uint32_t out_reg_sketch;
  __xwrite uint32_t out_xfer_sketch;

  PIF_PLUGIN_tcp_T *tcp_header = pif_plugin_hdr_get_tcp(headers);
  uint32_t srcPort = PIF_HEADER_GET_tcp___srcPort(tcp_header);

  if(LB <= (srcPort & 65535) < UB){
    PIF_PLUGIN_ipv4_T *ipv4_header = pif_plugin_hdr_get_ipv4(headers);
    uint32_t srcAddr =
      PIF_HEADER_GET_ipv4___srcAddr(ipv4_header);
    /* uint32_t dstAddr = */
    /*   PIF_HEADER_GET_ipv4___dstAddr(ipv4_header); */
    for(uint32_t row = 0; row<NUM_ROWS; row++){
      uint32_t index = compute_hash(srcAddr, NUM_COLS,
                                    index_a[row], index_b[row]);
      uint32_t filter = compute_hash(srcAddr, NUM_COLS,
                                     filter_a[row], filter_b[row]);
      if(filter == 0)
        atomic_add(&sketch[row][index], 1);
      else
        atomic_sub(&sketch[row][index], 1);
    }
  }

  return PIF_PLUGIN_RETURN_FORWARD;
}

/*

  mem_read_atomic(&in_xfer_sketch,                                \
  &sketch[ROW_NUM][hv], sizeof(uint32_t));                        \
  out_reg_sketch = in_xfer_sketch;                                \
  out_reg_sketch += 1;                                            \
  out_xfer_sketch = out_reg_sketch;                               \
  mem_write_atomic(&out_xfer_sketch,                              \
  &sketch[ROW_NUM][hv], sizeof(uint32_t));                        \

*/

