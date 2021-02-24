#include "sandbox.h"

#define LB 0
#define UB 65535

#define NUM_COLS_0 1048576
#define NUM_ROWS_0 8

__declspec(emem export scope(global)) int32_t sketch_0[NUM_ROWS_0][NUM_COLS_0];

HASH_FUNC0(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 0)
HASH_FUNC1(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 1)
HASH_FUNC2(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 2)
HASH_FUNC3(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 3)
HASH_FUNC4(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 4)
HASH_FUNC5(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 5)
HASH_FUNC6(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 6)
HASH_FUNC7(index, 0, NUM_COLS_0)
UPDATE_ROW(0, 7)

__forceinline
void sketch_update_util(uint32_t srcAddr, uint32_t dstAddr) {
  row_update_0_0(srcAddr, dstAddr);
  row_update_0_1(srcAddr, dstAddr);
  row_update_0_2(srcAddr, dstAddr);
  row_update_0_3(srcAddr, dstAddr);
  row_update_0_4(srcAddr, dstAddr);
  row_update_0_5(srcAddr, dstAddr);
  row_update_0_6(srcAddr, dstAddr);
  row_update_0_7(srcAddr, dstAddr);
}
