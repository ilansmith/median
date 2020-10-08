#ifndef _MEDIAN_H_
#define _MEDIAN_H_

typedef int (*median_is_greater_func_t)(void *left, void *right);
typedef void (*media_set_val_div2_func_t)(void *elm1, void *elm2, void *val);
typedef void *median_t;

median_t median_init(median_is_greater_func_t is_greater,
	media_set_val_div2_func_t set_val_div2);
void median_uninit(median_t ctx);
int median_add(median_t ctx, void *elm);
int median_calc(median_t median, void *value);

#endif

