#include "aegis.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 25 24 19 18 11 10   0
  //    03    02    01
  // 26 23 20 17 12 09   1
  //    04    05    06
  // 27 22 21 16 13 08   2
  //
  //          15 14 07   3
  //
  // Right
  // 0  1  2  3  4  5
  //                    ROWS
  // 25 24 19 18 11 10   4
  //    03    02    01
  // 26 23 20 17 12 09   5
  //    04    05    06
  // 27 22 21 16 13 08   6
  //
  //          15 14 07   7
  //
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 25 24 19 18 11 10       10 11 18 19 24 25  0
  //    03    02    01       01    02    03
  // 26 23 20 17 12 09       09 12 17 20 23 26  1
  //    04                               04
  // 27 22 21 16 13 08       08 13 16 21 22 27  2
  //          05    06       06    05
  //           15 14 07     07 14 15              3


led_config_t g_led_config = { {
    { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 }
}, {
    { 74, 0},{ 37, 0},{ 0, 0},{ 0, 64},{ 37, 64},{ 74, 64},{ 90, 50},{ 111, 32},{ 130, 50},{ 148, 64},{ 185, 64},{ 222, 64},{ 222, 0},{ 148, 0},{ 185, 0}
}, {
    2, 2, 2, 2, 2, 2, 2,2
} };
#endif
