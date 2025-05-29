// This is an implementation file, so omit include guards.

#include <cstdint>
#include <map>

const int8_t simplex_1[] = {5, 21, 5, 7, -1, -1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2};
const int8_t simplex_2[] = {4, 21, 4, 14, -1, -1, 12, 21, 12, 14};
const int8_t simplex_3[] = {11, 25, 4, -7, -1, -1, 17, 25, 10, -7, -1, -1, 4, 12, 18, 12, -1, -1, 3, 6, 17, 6};
const int8_t simplex_4[] = {8,  25, 8,  -4, -1, -1, 12, 25, 12, -4, -1, -1, 17, 18, 15, 20, 12, 21,
                            8,  21, 5,  20, 3,  18, 3,  16, 4,  14, 5,  13, 7,  12, 13, 10, 15, 9,
                            16, 8,  17, 6,  17, 3,  15, 1,  12, 0,  8,  0,  5,  1,  3,  3};
const int8_t simplex_5[] = {21, 21, 3,  0, -1, -1, 8,  21, 10, 19, 10, 17, 9,  15, 7,  14, 5,  14, 3,  16, 3,
                            18, 4,  20, 6, 21, 8,  21, 10, 20, 13, 19, 16, 19, 19, 20, 21, 21, -1, -1, 17, 7,
                            15, 6,  14, 4, 14, 2,  16, 0,  18, 0,  20, 1,  21, 3,  21, 5,  19, 7,  17, 7};
const int8_t simplex_6[] = {23, 12, 23, 13, 22, 14, 21, 14, 20, 13, 19, 11, 17, 6,  15, 3,  13, 1,  11, 0,  7,  0,  5,
                            1,  4,  2,  3,  4,  3,  6,  4,  8,  5,  9,  12, 13, 13, 14, 14, 16, 14, 18, 13, 20, 11, 21,
                            9,  20, 8,  18, 8,  16, 9,  13, 11, 10, 16, 3,  18, 1,  20, 0,  22, 0,  23, 1,  23, 2};
const int8_t simplex_7[] = {5, 19, 4, 20, 5, 21, 6, 20, 6, 18, 5, 16, 4, 15};
const int8_t simplex_8[] = {11, 25, 9, 23, 7, 20, 5, 16, 4, 11, 4, 7, 5, 2, 7, -2, 9, -5, 11, -7};
const int8_t simplex_9[] = {3, 25, 5, 23, 7, 20, 9, 16, 10, 11, 10, 7, 9, 2, 7, -2, 5, -5, 3, -7};
const int8_t simplex_10[] = {8, 21, 8, 9, -1, -1, 3, 18, 13, 12, -1, -1, 13, 18, 3, 12};
const int8_t simplex_11[] = {13, 18, 13, 0, -1, -1, 4, 9, 22, 9};
const int8_t simplex_12[] = {6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6, -1, 5, -3, 4, -4};
const int8_t simplex_13[] = {4, 9, 22, 9};
const int8_t simplex_14[] = {5, 2, 4, 1, 5, 0, 6, 1, 5, 2};
const int8_t simplex_15[] = {20, 25, 2, -7};
const int8_t simplex_16[] = {9, 21, 6, 20, 4, 17, 3, 12, 3,  9,  4,  4,  6,  1,  9,  0, 11,
                             0, 14, 1, 16, 4, 17, 9, 17, 12, 16, 17, 14, 20, 11, 21, 9, 21};
const int8_t simplex_17[] = {6, 17, 8, 18, 11, 21, 11, 0};
const int8_t simplex_18[] = {4,  16, 4,  17, 5,  19, 6,  20, 8,  21, 12, 21, 14, 20,
                             15, 19, 16, 17, 16, 15, 15, 13, 13, 10, 3,  0,  17, 0};
const int8_t simplex_19[] = {5, 21, 16, 21, 10, 13, 13, 13, 15, 12, 16, 11, 17, 8, 17,
                             6, 16, 3,  14, 1,  11, 0,  8,  0,  5,  1,  4,  2,  3, 4};
const int8_t simplex_20[] = {13, 21, 3, 7, 18, 7, -1, -1, 13, 21, 13, 0};
const int8_t simplex_21[] = {15, 21, 5, 21, 4, 12, 5, 13, 8, 14, 11, 14, 14, 13, 16, 11, 17,
                             8,  17, 6, 16, 3, 14, 1, 11, 0, 8,  0,  5,  1,  4,  2,  3,  4};
const int8_t simplex_22[] = {16, 18, 15, 20, 12, 21, 10, 21, 7, 20, 5,  17, 4,  12, 4,  7,  5,  3, 7,  1, 10, 0, 11,
                             0,  14, 1,  16, 3,  17, 6,  17, 7, 16, 10, 14, 12, 11, 13, 10, 13, 7, 12, 5, 10, 4, 7};
const int8_t simplex_23[] = {17, 21, 7, 0, -1, -1, 3, 21, 17, 21};
const int8_t simplex_24[] = {8,  21, 5,  20, 4,  18, 4,  16, 5,  14, 7,  13, 11, 12, 14, 11, 16, 9, 17, 7,
                             17, 4,  16, 2,  15, 1,  12, 0,  8,  0,  5,  1,  4,  2,  3,  4,  3,  7, 4,  9,
                             6,  11, 9,  12, 13, 13, 15, 14, 16, 16, 16, 18, 15, 20, 12, 21, 8,  21};
const int8_t simplex_25[] = {16, 14, 15, 11, 13, 9,  10, 8,  9,  8,  6, 9,  4, 11, 3, 14, 3, 15, 4, 18, 6, 20, 9,
                             21, 10, 21, 13, 20, 15, 18, 16, 14, 16, 9, 15, 4, 13, 1, 10, 0, 8,  0, 5,  1, 4,  3};
const int8_t simplex_26[] = {5, 14, 4, 13, 5, 12, 6, 13, 5, 14, -1, -1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2};
const int8_t simplex_27[] = {5, 14, 4, 13, 5, 12, 6, 13, 5, 14, -1, -1, 6, 1,
                             5, 0,  4, 1,  5, 2,  6, 1,  6, -1, 5,  -3, 4, -4};
const int8_t simplex_28[] = {20, 18, 4, 9, 20, 0};
const int8_t simplex_29[] = {4, 12, 22, 12, -1, -1, 4, 6, 22, 6};
const int8_t simplex_30[] = {4, 18, 20, 9, 4, 0};
const int8_t simplex_31[] = {3,  16, 3,  17, 4, 19, 5, 20, 7,  21, 11, 21, 13, 20, 14, 19, 15, 17, 15, 15,
                             14, 13, 13, 12, 9, 10, 9, 7,  -1, -1, 9,  2,  8,  1,  9,  0,  10, 1,  9,  2};
const int8_t simplex_32[] = {18, 13, 17, 15, 15, 16, 12, 16, 10, 15, 9,  14, 8,  11, 8,  8,  9,  6,  11, 5,  14, 5,
                             16, 6,  17, 8,  -1, -1, 12, 16, 10, 14, 9,  11, 9,  8,  10, 6,  11, 5,  -1, -1, 18, 16,
                             17, 8,  17, 6,  19, 5,  21, 5,  23, 7,  24, 10, 24, 12, 23, 15, 22, 17, 20, 19, 18, 20,
                             15, 21, 12, 21, 9,  20, 7,  19, 5,  17, 4,  15, 3,  12, 3,  9,  4,  6,  5,  4,  7,  2,
                             9,  1,  12, 0,  15, 0,  18, 1,  20, 2,  21, 3,  -1, -1, 19, 16, 18, 8,  18, 6,  19, 5};
const int8_t simplex_33[] = {9, 21, 1, 0, -1, -1, 9, 21, 17, 0, -1, -1, 4, 7, 14, 7};
const int8_t simplex_34[] = {4,  21, 4,  0, -1, -1, 4,  21, 13, 21, 16, 20, 17, 19, 18, 17, 18, 15, 17, 13, 16, 12, 13,
                             11, -1, -1, 4, 11, 13, 11, 16, 10, 17, 9,  18, 7,  18, 4,  17, 2,  16, 1,  13, 0,  4,  0};
const int8_t simplex_35[] = {18, 16, 17, 18, 15, 20, 13, 21, 9, 21, 7,  20, 5,  18, 4,  16, 3,  13,
                             3,  8,  4,  5,  5,  3,  7,  1,  9, 0,  13, 0,  15, 1,  17, 3,  18, 5};
const int8_t simplex_36[] = {4,  21, 4,  0,  -1, -1, 4, 21, 11, 21, 14, 20, 16, 18, 17,
                             16, 18, 13, 18, 8,  17, 5, 16, 3,  14, 1,  11, 0,  4,  0};
const int8_t simplex_37[] = {4, 21, 4, 0, -1, -1, 4, 21, 17, 21, -1, -1, 4, 11, 12, 11, -1, -1, 4, 0, 17, 0};
const int8_t simplex_38[] = {4, 21, 4, 0, -1, -1, 4, 21, 17, 21, -1, -1, 4, 11, 12, 11};
const int8_t simplex_39[] = {18, 16, 17, 18, 15, 20, 13, 21, 9,  21, 7,  20, 5,  18, 4,  16, 3,  13, 3,  8, 4,  5,
                             5,  3,  7,  1,  9,  0,  13, 0,  15, 1,  17, 3,  18, 5,  18, 8,  -1, -1, 13, 8, 18, 8};
const int8_t simplex_40[] = {4, 21, 4, 0, -1, -1, 18, 21, 18, 0, -1, -1, 4, 11, 18, 11};
const int8_t simplex_41[] = {4, 21, 4, 0};
const int8_t simplex_42[] = {12, 21, 12, 5, 11, 2, 10, 1, 8, 0, 6, 0, 4, 1, 3, 2, 2, 5, 2, 7};
const int8_t simplex_43[] = {4, 21, 4, 0, -1, -1, 18, 21, 4, 7, -1, -1, 9, 12, 18, 0};
const int8_t simplex_44[] = {4, 21, 4, 0, -1, -1, 4, 0, 16, 0};
const int8_t simplex_45[] = {4, 21, 4, 0, -1, -1, 4, 21, 12, 0, -1, -1, 20, 21, 12, 0, -1, -1, 20, 21, 20, 0};
const int8_t simplex_46[] = {4, 21, 4, 0, -1, -1, 4, 21, 18, 0, -1, -1, 18, 21, 18, 0};
const int8_t simplex_47[] = {9, 21, 7, 20, 5, 18, 4, 16, 3, 13, 3,  8,  4,  5,  5,  3,  7,  1,  9,  0, 13,
                             0, 15, 1, 17, 3, 18, 5, 19, 8, 19, 13, 18, 16, 17, 18, 15, 20, 13, 21, 9, 21};
const int8_t simplex_48[] = {4,  21, 4,  0,  -1, -1, 4,  21, 13, 21, 16, 20, 17,
                             19, 18, 17, 18, 14, 17, 12, 16, 11, 13, 10, 4,  10};
const int8_t simplex_49[] = {9,  21, 7,  20, 5,  18, 4,  16, 3,  13, 3,  8,  4,  5, 5,  3,
                             7,  1,  9,  0,  13, 0,  15, 1,  17, 3,  18, 5,  19, 8, 19, 13,
                             18, 16, 17, 18, 15, 20, 13, 21, 9,  21, -1, -1, 12, 4, 18, -2};
const int8_t simplex_50[] = {4,  21, 4,  0,  -1, -1, 4,  21, 13, 21, 16, 20, 17, 19, 18, 17,
                             18, 15, 17, 13, 16, 12, 13, 11, 4,  11, -1, -1, 11, 11, 18, 0};
const int8_t simplex_51[] = {17, 18, 15, 20, 12, 21, 8,  21, 5,  20, 3,  18, 3,  16, 4, 14, 5, 13, 7, 12,
                             13, 10, 15, 9,  16, 8,  17, 6,  17, 3,  15, 1,  12, 0,  8, 0,  5, 1,  3, 3};
const int8_t simplex_52[] = {8, 21, 8, 0, -1, -1, 1, 21, 15, 21};
const int8_t simplex_53[] = {4, 21, 4, 6, 5, 3, 7, 1, 10, 0, 12, 0, 15, 1, 17, 3, 18, 6, 18, 21};
const int8_t simplex_54[] = {1, 21, 9, 0, -1, -1, 17, 21, 9, 0};
const int8_t simplex_55[] = {2, 21, 7, 0, -1, -1, 12, 21, 7, 0, -1, -1, 12, 21, 17, 0, -1, -1, 22, 21, 17, 0};
const int8_t simplex_56[] = {3, 21, 17, 0, -1, -1, 17, 21, 3, 0};
const int8_t simplex_57[] = {1, 21, 9, 11, 9, 0, -1, -1, 17, 21, 9, 11};
const int8_t simplex_58[] = {17, 21, 3, 0, -1, -1, 3, 21, 17, 21, -1, -1, 3, 0, 17, 0};
const int8_t simplex_59[] = {4, 25, 4, -7, -1, -1, 5, 25, 5, -7, -1, -1, 4, 25, 11, 25, -1, -1, 4, -7, 11, -7};
const int8_t simplex_60[] = {0, 21, 14, -3};
const int8_t simplex_61[] = {9, 25, 9, -7, -1, -1, 10, 25, 10, -7, -1, -1, 3, 25, 10, 25, -1, -1, 3, -7, 10, -7};
const int8_t simplex_62[] = {6, 15, 8, 18, 10, 15, -1, -1, 3, 12, 8, 17, 13, 12, -1, -1, 8, 17, 8, 0};
const int8_t simplex_63[] = {0, -2, 16, -2};
const int8_t simplex_64[] = {6, 21, 5, 20, 4, 18, 4, 16, 5, 15, 6, 16, 5, 17};
const int8_t simplex_65[] = {15, 14, 15, 0, -1, -1, 15, 11, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3,  8,  3, 6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_66[] = {4,  21, 4, 0,  -1, -1, 4, 11, 6, 13, 8, 14, 11, 14, 13, 13, 15,
                             11, 16, 8, 16, 6,  15, 3, 13, 1, 11, 0, 8,  0,  6,  1,  4,  3};
const int8_t simplex_67[] = {15, 11, 13, 13, 11, 14, 8, 14, 6,  13, 4,  11, 3,  8,
                             3,  6,  4,  3,  6,  1,  8, 0,  11, 0,  13, 1,  15, 3};
const int8_t simplex_68[] = {15, 21, 15, 0, -1, -1, 15, 11, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3,  8,  3, 6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_69[] = {3,  8, 15, 8, 15, 10, 14, 12, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3, 8,  3, 6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_70[] = {10, 21, 8, 21, 6, 20, 5, 17, 5, 0, -1, -1, 2, 14, 9, 14};
const int8_t simplex_71[] = {15, 14, 15, -2, 14, -5, 13, -6, 11, -7, 8, -7, 6, -6, -1, -1, 15, 11, 13, 13, 11, 14,
                             8,  14, 6,  13, 4,  11, 3,  8,  3,  6,  4, 3,  6, 1,  8,  0,  11, 0,  13, 1,  15, 3};
const int8_t simplex_72[] = {4, 21, 4, 0, -1, -1, 4, 10, 7, 13, 9, 14, 12, 14, 14, 13, 15, 10, 15, 0};
const int8_t simplex_73[] = {3, 21, 4, 20, 5, 21, 4, 22, 3, 21, -1, -1, 4, 14, 4, 0};
const int8_t simplex_74[] = {5, 21, 6, 20, 7, 21, 6, 22, 5, 21, -1, -1, 6, 14, 6, -3, 5, -6, 3, -7, 1, -7};
const int8_t simplex_75[] = {4, 21, 4, 0, -1, -1, 14, 14, 4, 4, -1, -1, 8, 8, 15, 0};
const int8_t simplex_76[] = {4, 21, 4, 0};
const int8_t simplex_77[] = {4,  14, 4,  0,  -1, -1, 4,  10, 7,  13, 9,  14, 12, 14, 14, 13, 15, 10,
                             15, 0,  -1, -1, 15, 10, 18, 13, 20, 14, 23, 14, 25, 13, 26, 10, 26, 0};
const int8_t simplex_78[] = {4, 14, 4, 0, -1, -1, 4, 10, 7, 13, 9, 14, 12, 14, 14, 13, 15, 10, 15, 0};
const int8_t simplex_79[] = {8, 14, 6, 13, 4, 11, 3, 8,  3, 6,  4,  3,  6,  1,  8,  0, 11,
                             0, 13, 1, 15, 3, 16, 6, 16, 8, 15, 11, 13, 13, 11, 14, 8, 14};
const int8_t simplex_80[] = {4,  14, 4, -7, -1, -1, 4, 11, 6, 13, 8, 14, 11, 14, 13, 13, 15,
                             11, 16, 8, 16, 6,  15, 3, 13, 1, 11, 0, 8,  0,  6,  1,  4,  3};
const int8_t simplex_81[] = {15, 14, 15, -7, -1, -1, 15, 11, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3,  8,  3,  6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_82[] = {4, 14, 4, 0, -1, -1, 4, 8, 5, 11, 7, 13, 9, 14, 12, 14};
const int8_t simplex_83[] = {14, 11, 13, 13, 10, 14, 7, 14, 4, 13, 3, 11, 4, 9, 6, 8, 11,
                             7,  13, 6,  14, 4,  14, 3, 13, 1, 10, 0, 7,  0, 4, 1, 3, 3};
const int8_t simplex_84[] = {5, 21, 5, 4, 6, 1, 8, 0, 10, 0, -1, -1, 2, 14, 9, 14};
const int8_t simplex_85[] = {4, 14, 4, 4, 5, 1, 7, 0, 10, 0, 12, 1, 15, 4, -1, -1, 15, 14, 15, 0};
const int8_t simplex_86[] = {2, 14, 8, 0, -1, -1, 14, 14, 8, 0};
const int8_t simplex_87[] = {3, 14, 7, 0, -1, -1, 11, 14, 7, 0, -1, -1, 11, 14, 15, 0, -1, -1, 19, 14, 15, 0};
const int8_t simplex_88[] = {3, 14, 14, 0, -1, -1, 14, 14, 3, 0};
const int8_t simplex_89[] = {2, 14, 8, 0, -1, -1, 14, 14, 8, 0, 6, -4, 4, -6, 2, -7, 1, -7};
const int8_t simplex_90[] = {14, 14, 3, 0, -1, -1, 3, 14, 14, 14, -1, -1, 3, 0, 14, 0};
const int8_t simplex_91[] = {9,  25, 7, 24, 6, 23, 5, 21, 5, 19, 6, 17, 7, 16, 8, 14, 8,  12, 6, 10,
                             -1, -1, 7, 24, 6, 22, 6, 20, 7, 18, 8, 17, 9, 15, 9, 13, 8,  11, 4, 9,
                             8,  7,  9, 5,  9, 3,  8, 1,  7, 0,  6, -2, 6, -4, 7, -6, -1, -1, 6, 8,
                             8,  6,  8, 4,  7, 2,  6, 1,  5, -1, 5, -3, 6, -5, 7, -6, 9,  -7};
const int8_t simplex_92[] = {4, 25, 4, -7};
const int8_t simplex_93[] = {5,  25, 7, 24, 8, 23, 9, 21, 9, 19, 8, 17, 7, 16, 6, 14, 6,  12, 8,  10,
                             -1, -1, 7, 24, 8, 22, 8, 20, 7, 18, 6, 17, 5, 15, 5, 13, 6,  11, 10, 9,
                             6,  7,  5, 5,  5, 3,  6, 1,  7, 0,  8, -2, 8, -4, 7, -6, -1, -1, 8,  8,
                             6,  6,  6, 4,  7, 2,  8, 1,  9, -1, 9, -3, 8, -5, 7, -6, 5,  -7};
const int8_t simplex_94[] = {3,  6, 3, 8, 4,  11, 6,  12, 8,  12, 10, 11, 14, 8,  16, 7,  18, 7,  20, 8,  21, 10, -1,
                             -1, 3, 8, 4, 10, 6,  11, 8,  11, 10, 10, 14, 7,  16, 6,  18, 6,  20, 7,  21, 10, 21, 12};

struct glyph {
    uint8_t width;
    uint8_t length;
    const int8_t *data;
};

// Font data From Hershey Simplex Font
// http://paulbourke.net/dataformats/hershey/

const glyph simplex[] = {
    /* 32	  */ {.width = 16, .length = 0, .data = nullptr},
    /* 33	! */
    {.width = 10, .length = sizeof(simplex_1), .data = simplex_1},
    /* 34	" */
    {.width = 16, .length = sizeof(simplex_2), .data = simplex_2},
    /* 35	# */
    {.width = 21, .length = sizeof(simplex_3), .data = simplex_3},
    /* 36	$ */
    {.width = 20, .length = sizeof(simplex_4), .data = simplex_4},
    /* 37	% */
    {.width = 24, .length = sizeof(simplex_5), .data = simplex_5},
    /* 38	& */
    {.width = 26, .length = sizeof(simplex_6), .data = simplex_6},
    /* 39	' */
    {.width = 10, .length = sizeof(simplex_7), .data = simplex_7},
    /* 40	( */
    {.width = 14, .length = sizeof(simplex_8), .data = simplex_8},
    /* 41	) */
    {.width = 14, .length = sizeof(simplex_9), .data = simplex_9},
    /* 42	* */
    {.width = 16, .length = sizeof(simplex_10), .data = simplex_10},
    /* 43	+ */
    {.width = 26, .length = sizeof(simplex_11), .data = simplex_11},
    /* 44	, */
    {.width = 10, .length = sizeof(simplex_12), .data = simplex_12},
    /* 45	- */
    {.width = 26, .length = sizeof(simplex_13), .data = simplex_13},
    /* 46	. */
    {.width = 10, .length = sizeof(simplex_14), .data = simplex_14},
    /* 47	/ */
    {.width = 22, .length = sizeof(simplex_15), .data = simplex_15},
    /* 48	0 */
    {.width = 20, .length = sizeof(simplex_16), .data = simplex_16},
    /* 49	1 */
    {.width = 20, .length = sizeof(simplex_17), .data = simplex_17},
    /* 50	2 */
    {.width = 20, .length = sizeof(simplex_18), .data = simplex_18},
    /* 51	3 */
    {.width = 20, .length = sizeof(simplex_19), .data = simplex_19},
    /* 52	4 */
    {.width = 20, .length = sizeof(simplex_20), .data = simplex_20},
    /* 53	5 */
    {.width = 20, .length = sizeof(simplex_21), .data = simplex_21},
    /* 54	6 */
    {.width = 20, .length = sizeof(simplex_22), .data = simplex_22},
    /* 55	7 */
    {.width = 20, .length = sizeof(simplex_23), .data = simplex_23},
    /* 56	8 */
    {.width = 20, .length = sizeof(simplex_24), .data = simplex_24},
    /* 57	9 */
    {.width = 20, .length = sizeof(simplex_25), .data = simplex_25},
    /* 58	: */
    {.width = 10, .length = sizeof(simplex_26), .data = simplex_26},
    /* 59	; */
    {.width = 10, .length = sizeof(simplex_27), .data = simplex_27},
    /* 60	< */
    {.width = 24, .length = sizeof(simplex_28), .data = simplex_28},
    /* 61	= */
    {.width = 26, .length = sizeof(simplex_29), .data = simplex_29},
    /* 62	> */
    {.width = 24, .length = sizeof(simplex_30), .data = simplex_30},
    /* 63	? */
    {.width = 18, .length = sizeof(simplex_31), .data = simplex_31},
    /* 64	@ */
    {.width = 27, .length = sizeof(simplex_32), .data = simplex_32},
    /* 65	A */
    {.width = 18, .length = sizeof(simplex_33), .data = simplex_33},
    /* 66	B */
    {.width = 21, .length = sizeof(simplex_34), .data = simplex_34},
    /* 67	C */
    {.width = 21, .length = sizeof(simplex_35), .data = simplex_35},
    /* 68	D */
    {.width = 21, .length = sizeof(simplex_36), .data = simplex_36},
    /* 69	E */
    {.width = 19, .length = sizeof(simplex_37), .data = simplex_37},
    /* 70	F */
    {.width = 18, .length = sizeof(simplex_38), .data = simplex_38},
    /* 71	G */
    {.width = 21, .length = sizeof(simplex_39), .data = simplex_39},
    /* 72	H */
    {.width = 22, .length = sizeof(simplex_40), .data = simplex_40},
    /* 73	I */
    {.width = 8, .length = sizeof(simplex_41), .data = simplex_41},
    /* 74	J */
    {.width = 16, .length = sizeof(simplex_42), .data = simplex_42},
    /* 75	K */
    {.width = 21, .length = sizeof(simplex_43), .data = simplex_43},
    /* 76	L */
    {.width = 17, .length = sizeof(simplex_44), .data = simplex_44},
    /* 77	M */
    {.width = 24, .length = sizeof(simplex_45), .data = simplex_45},
    /* 78	N */
    {.width = 22, .length = sizeof(simplex_46), .data = simplex_46},
    /* 79	O */
    {.width = 22, .length = sizeof(simplex_47), .data = simplex_47},
    /* 80	P */
    {.width = 21, .length = sizeof(simplex_48), .data = simplex_48},
    /* 81	Q */
    {.width = 22, .length = sizeof(simplex_49), .data = simplex_49},
    /* 82	R */
    {.width = 21, .length = sizeof(simplex_50), .data = simplex_50},
    /* 83	S */
    {.width = 20, .length = sizeof(simplex_51), .data = simplex_51},
    /* 84	T */
    {.width = 16, .length = sizeof(simplex_52), .data = simplex_52},
    /* 85	U */
    {.width = 22, .length = sizeof(simplex_53), .data = simplex_53},
    /* 86	V */
    {.width = 18, .length = sizeof(simplex_54), .data = simplex_54},
    /* 87	W */
    {.width = 24, .length = sizeof(simplex_55), .data = simplex_55},
    /* 88	X */
    {.width = 20, .length = sizeof(simplex_56), .data = simplex_56},
    /* 89	Y */
    {.width = 18, .length = sizeof(simplex_57), .data = simplex_57},
    /* 90	Z */
    {.width = 20, .length = sizeof(simplex_58), .data = simplex_58},
    /* 91	[ */
    {.width = 14, .length = sizeof(simplex_59), .data = simplex_59},
    /* 92	\ */
    {.width = 14, .length = sizeof(simplex_60), .data = simplex_60},
    /* 93	] */
    {.width = 14, .length = sizeof(simplex_61), .data = simplex_61},
    /* 94	^ */
    {.width = 16, .length = sizeof(simplex_62), .data = simplex_62},
    /* 95	_ */
    {.width = 16, .length = sizeof(simplex_63), .data = simplex_63},
    /* 96	` */
    {.width = 10, .length = sizeof(simplex_64), .data = simplex_64},
    /* 97	a */
    {.width = 19, .length = sizeof(simplex_65), .data = simplex_65},
    /* 98	b */
    {.width = 19, .length = sizeof(simplex_66), .data = simplex_66},
    /* 99	c */
    {.width = 18, .length = sizeof(simplex_67), .data = simplex_67},
    /* 100	d */
    {.width = 19, .length = sizeof(simplex_68), .data = simplex_68},
    /* 101	e */
    {.width = 18, .length = sizeof(simplex_69), .data = simplex_69},
    /* 102	f */
    {.width = 12, .length = sizeof(simplex_70), .data = simplex_70},
    /* 103	g */
    {.width = 19, .length = sizeof(simplex_71), .data = simplex_71},
    /* 104	h */
    {.width = 19, .length = sizeof(simplex_72), .data = simplex_72},
    /* 105	i */
    {.width = 8, .length = sizeof(simplex_73), .data = simplex_73},
    /* 106	j */
    {.width = 10, .length = sizeof(simplex_74), .data = simplex_74},
    /* 107	k */
    {.width = 17, .length = sizeof(simplex_75), .data = simplex_75},
    /* 108	l */
    {.width = 8, .length = sizeof(simplex_76), .data = simplex_76},
    /* 109	m */
    {.width = 30, .length = sizeof(simplex_77), .data = simplex_77},
    /* 110	n */
    {.width = 19, .length = sizeof(simplex_78), .data = simplex_78},
    /* 111	o */
    {.width = 19, .length = sizeof(simplex_79), .data = simplex_79},
    /* 112	p */
    {.width = 19, .length = sizeof(simplex_80), .data = simplex_80},
    /* 113	q */
    {.width = 19, .length = sizeof(simplex_81), .data = simplex_81},
    /* 114	r */
    {.width = 13, .length = sizeof(simplex_82), .data = simplex_82},
    /* 115	s */
    {.width = 17, .length = sizeof(simplex_83), .data = simplex_83},
    /* 116	t */
    {.width = 12, .length = sizeof(simplex_84), .data = simplex_84},
    /* 117	u */
    {.width = 19, .length = sizeof(simplex_85), .data = simplex_85},
    /* 118	v */
    {.width = 16, .length = sizeof(simplex_86), .data = simplex_86},
    /* 119	w */
    {.width = 22, .length = sizeof(simplex_87), .data = simplex_87},
    /* 120	x */
    {.width = 17, .length = sizeof(simplex_88), .data = simplex_88},
    /* 121	y */
    {.width = 16, .length = sizeof(simplex_89), .data = simplex_89},
    /* 122	z */
    {.width = 17, .length = sizeof(simplex_90), .data = simplex_90},
    /* 123	{ */
    {.width = 14, .length = sizeof(simplex_91), .data = simplex_91},
    /* 124	| */
    {.width = 8, .length = sizeof(simplex_92), .data = simplex_92},
    /* 125	} */
    {.width = 14, .length = sizeof(simplex_93), .data = simplex_93},
    /* 126	~ */
    {.width = 24, .length = sizeof(simplex_94), .data = simplex_94},
};
