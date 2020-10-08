#include <stdlib.h>
#include <stdio.h>
#include "median.h"

#define ARR_SIZE(_arr_) (sizeof(_arr_) / sizeof(_arr_[0]))

static int is_greater_than_int(void *left, void *right)
{
	int *pleft = (int*)left;
	int *pright = (int*)right;

	return *pleft < *pright;
}

static void set_median_float(void *vec_e1, void *vec_e2, void *val)
{
	float *fval = (float*)val;

	*fval = (*(int*)vec_e1 + *(int*)vec_e2) / (float)2;
}

int main(int argc, char **argv)
{
	int arr[] = { 2, 4, 7, 3, 3, 98, 15, 3, 77, 47 };
	int i;
	float median;
	median_t ctx;

	ctx = median_init((median_is_greater_func_t)is_greater_than_int,
		(media_set_val_div2_func_t )set_median_float);
	if (!ctx) {
		printf("Failed to init median\n");
		return -1;
	}

	for (i = 0; i < ARR_SIZE(arr); i++) {
		if (median_add(ctx, (void*)&arr[i]))
			goto exit;
	}

	if (median_calc(ctx, &median)) {
		printf("Error calculating median\n");
		goto exit;
	}

	printf("median of {");
	for (i = 0; i < ARR_SIZE(arr); i++)
		printf("%s%d", i ? ", " : "", arr[i]);
	printf("} is: %.2g\n", median);

exit:
	median_uninit(ctx);
	return 0;
}

