/******************************************************************************
*     File Name           :     multitype.h                                   *
*     Created By          :     Klas Segeljakt <klasseg@kth.se>               *
*     Creation Date       :     [2017-11-18 18:18]                            *
*     Last Modified       :     [2018-01-05 18:19]                            *
*     Description         :     Heap-based multitype.h                        *
******************************************************************************/
#ifndef MULTITYPE_H
#define MULTITYPE_H
/*****************************************************************************/

#include <stdlib.h>

/* ============================= HELPER MACROS ============================= */

/* __typeof__(V) abbreviation */

#define TOF(V) __typeof__(V)

/* Expand variables list to list of typeof and variable names */

#define TO3(_0,_1,_2,_3) TOF(_0) v0; TOF(_1) v1; TOF(_2) v2; TOF(_3) v3;
#define TO2(_0,_1,_2)    TOF(_0) v0; TOF(_1) v1; TOF(_2) v2;
#define TO1(_0,_1)       TOF(_0) v0; TOF(_1) v1;
#define TO0(_0)          TOF(_0) v0;

#define TO_(_0,_1,_2,_3,TO_MACRO,...) TO_MACRO

#define TO(...) TO_(__VA_ARGS__,TO3,TO2,TO1,TO0)(__VA_ARGS__)

/* Assign to multitype */

#define MTA3(_0,_1,_2,_3) _0 = mtr.v0; _1 = mtr.v1; _2 = mtr.v2; _3 = mtr.v3;
#define MTA2(_0,_1,_2)    _0 = mtr.v0; _1 = mtr.v1; _2 = mtr.v2;
#define MTA1(_0,_1)       _0 = mtr.v0; _1 = mtr.v1;
#define MTA0(_0)          _0 = mtr.v0;

#define MTA_(_0,_1,_2,_3,MTA_MACRO,...) MTA_MACRO

#define MTA(...) MTA_(__VA_ARGS__,MTA3,MTA2,MTA1,MTA0)(__VA_ARGS__)

/* Return multitype if multiple arguments, return normally if only one */

#define MTR1(...) {                                                           \
  typedef struct mtr_s {                                                    \
    TO(__VA_ARGS__)                                                         \
  } mtr_t;                                                                  \
  mtr_t *mtr = malloc(sizeof(mtr_t));                                       \
  *mtr = (mtr_t){__VA_ARGS__};                                              \
  return mtr;                                                               \
}

#define MTR0(_0) return(_0)

#define MTR_(_0,_1,_2,_3,MTR_MACRO,...) MTR_MACRO

/* ============================== API MACROS =============================== */

/* Declare return type before function */

typedef void* multitype;

#define multitype(...) multitype

/* Assign return values to variables */

#define let(...)                                                              \
  for(int mti = 0; !mti;)                                                     \
for(multitype mt; mti < 2; mti++)                                         \
if(mti) {                                                               \
  typedef struct mtr_s {                                                \
    TO(__VA_ARGS__)                                                     \
  } mtr_t;                                                              \
  mtr_t mtr = *(mtr_t*)mt;                                              \
  MTA(__VA_ARGS__)                                                      \
  free(mt);                                                             \
} else                                                                  \
mt

/* Return */

#define return(...) MTR_(__VA_ARGS__,MTR1,MTR1,MTR1,MTR0)(__VA_ARGS__)

/*****************************************************************************/
#endif /* MULTITYPE_H */
