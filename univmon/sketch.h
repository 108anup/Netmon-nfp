#include "sandbox.h"

#define LB 0
#define UB 65535

#define NUM_COLS_0 65536
#define NUM_ROWS_0 9

#define NUM_LEVELS_0 16

__declspec(emem export scope(global)) int32_t sketch_0[NUM_LEVELS_0][NUM_ROWS_0][NUM_COLS_0];

HASH_LEVEL(0)
GET_LEVEL(0)
HASH_FUNC0(index, 0, NUM_COLS_0)
HASH_FUNC0(filter, 0, 2)
UPDATE_ROW(0, 0)
HASH_FUNC1(index, 0, NUM_COLS_0)
HASH_FUNC1(filter, 0, 2)
UPDATE_ROW(0, 1)
HASH_FUNC2(index, 0, NUM_COLS_0)
HASH_FUNC2(filter, 0, 2)
UPDATE_ROW(0, 2)
HASH_FUNC3(index, 0, NUM_COLS_0)
HASH_FUNC3(filter, 0, 2)
UPDATE_ROW(0, 3)
HASH_FUNC4(index, 0, NUM_COLS_0)
HASH_FUNC4(filter, 0, 2)
UPDATE_ROW(0, 4)
HASH_FUNC5(index, 0, NUM_COLS_0)
HASH_FUNC5(filter, 0, 2)
UPDATE_ROW(0, 5)
HASH_FUNC6(index, 0, NUM_COLS_0)
HASH_FUNC6(filter, 0, 2)
UPDATE_ROW(0, 6)
HASH_FUNC7(index, 0, NUM_COLS_0)
HASH_FUNC7(filter, 0, 2)
UPDATE_ROW(0, 7)
HASH_FUNC8(index, 0, NUM_COLS_0)
HASH_FUNC8(filter, 0, 2)
UPDATE_ROW(0, 8)

__forceinline
void sketch_update_util(uint32_t srcAddr, uint32_t dstAddr) {
  uint32_t level_0 = get_level_0(srcAddr, dstAddr);
  row_update_0_0(srcAddr, dstAddr, level_0);
  row_update_0_1(srcAddr, dstAddr, level_0);
  row_update_0_2(srcAddr, dstAddr, level_0);
  row_update_0_3(srcAddr, dstAddr, level_0);
  row_update_0_4(srcAddr, dstAddr, level_0);
  row_update_0_5(srcAddr, dstAddr, level_0);
  row_update_0_6(srcAddr, dstAddr, level_0);
  row_update_0_7(srcAddr, dstAddr, level_0);
  row_update_0_8(srcAddr, dstAddr, level_0);
}
