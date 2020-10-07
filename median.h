#ifndef _MEDIAN_H_
#define _MEDIAN_H_

typedef int (*median_is_greater_func_t)(void *left, void *right);
typedef void *median_t;

median_t median_init(median_is_greater_func_t func);
void median_uninit(median_t ctx);
int median_add(median_t ctx, void *elm);
void *median_calc(median_t ctx);

#endif

