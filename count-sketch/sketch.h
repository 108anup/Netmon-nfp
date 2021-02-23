#include "sandbox.h"

#define LB 0
#define UB 65535

#define NUM_COLS_0 16
#define NUM_ROWS_0 2

__declspec(emem export scope(global)) int32_t sketch_0[NUM_ROWS_0][NUM_COLS_0];

HASH_FUNC0(index, 0, NUM_COLS_0)
HASH_FUNC0(filter, 0, 2)
UPDATE_ROW(0, 0)
HASH_FUNC1(index, 0, NUM_COLS_0)
HASH_FUNC1(filter, 0, 2)
UPDATE_ROW(0, 1)

__forceinline
void sketch_update_util(uint32_t srcAddr, uint32_t dstAddr) {
  row_update_0_0(srcAddr, dstAddr);
  row_update_0_1(srcAddr, dstAddr);
}
