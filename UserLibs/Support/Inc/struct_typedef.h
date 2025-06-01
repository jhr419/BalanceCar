#ifndef STRUCT_TYPEDEF_H
#define STRUCT_TYPEDEF_H

/**
  * @file    struct_typedef.h
  * @brief   通用类型和宏定义 | Common type and macro definitions
  */

/* 切换布尔值 | Toggle boolean value */
#define BOOL_TOGGLE(bool) ((0 == (bool)) ? 1 : 0)

/* 限制 x 在 [min, max] 范围内 | Constrain x within [min, max] */
#define LIMIT(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

#define TRUE  1
#define FALSE 0

/* 精确宽度数据类型 | Exact-width data types */
typedef unsigned char bool_t;
typedef float         fp32;
typedef double        fp64;

#endif /* STRUCT_TYPEDEF_H */
