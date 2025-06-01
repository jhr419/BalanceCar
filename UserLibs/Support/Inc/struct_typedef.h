#ifndef STRUCT_TYPEDEF_H
#define STRUCT_TYPEDEF_H

//用于补充一些额外用到的变量类型，一些常用宏函数
#define BOOL_TOGGLE(bool) (0 == bool) ? 1 : 0
#define LIMIT(x, min, max)  ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

#define TRUE 1
#define FALSE 0

/* exact-width unsigned integer types */
typedef unsigned char bool_t;
typedef float fp32;
typedef double fp64;


#endif



