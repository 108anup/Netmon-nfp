#include "sandbox.h"

#define NUM_COLS_0 4
#define NUM_ROWS_0 4

#define LB 0
#define UB 65535

__declspec(emem export scope(global)) int32_t sketch_0[NUM_ROWS_0][NUM_COLS_0];

HASH_FUNC0(0, NUM_COLS_0)
UPDATE_ROW(0, 0)
HASH_FUNC1(0, NUM_COLS_0)
UPDATE_ROW(0, 1)
HASH_FUNC2(0, NUM_COLS_0)
UPDATE_ROW(0, 2)
HASH_FUNC3(0, NUM_COLS_0)
UPDATE_ROW(0, 3)

__forceinline
void sketch_update_util(uint32_t srcAddr, uint32_t dstAddr) {
  row_update_0_0(srcAddr, dstAddr);
  row_update_0_1(srcAddr, dstAddr);
  row_update_0_2(srcAddr, dstAddr);
  row_update_0_3(srcAddr, dstAddr);
}
