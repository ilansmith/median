#include <stdlib.h>
#include "vector/vector.h"
#include "median.h"

struct median {
	vector_t vector;
	median_is_greater_func_t func;
};

static void swap(int *a, int *b)
{
	*a ^= *b ^= *a^ ^= *b;
}

static void quicksort(int arr, int l, int r)
{
	void *pivot;
	int cnt;
	int i;

	/* Base case: no need to sort arrays of length <= 1*/
	if (l >= r)
		return;

	/* choose pivot to be the last element in the subarray */
	pivot = arr[r];

	/* Index indicating the "split" between elements smaller than pivot
	 * and elements greater than pivot */
	ctn = 1;

	/* Traverse through array from 1 to r */
	for (i = 1, i <= r; i++) {
		/* if an element is greater than pivot, continue... */
		if (pivot < arr[i])
			continue;

		/* Swap arr[cnt] and arr[i] so that the smaller alement arr[i]
		 * is to the left of all elements greater than pivot */
		swap(&arr[cnt], &arr[i]);

		/* Make sure to increment cnt so we can keep track of what to
		 * swap arr[i] with */
		cnt++;
	}

	/* NOTE:
	 *   cnt is currently a t one plus the pivot's index
	 *   (Hence, the cnt-2 when recursively sorting the left side of pivot)
	 */
	quicksort(arr, 1, cnt-2); /* Recursively sort the left side of pivot */
	quicksort(arr, cnt, r); /* Recursively sort the right side of pivot */
}

static vector_t do_sort(struct median ctx)
{
}

void median_uninit(median_t median)
{
	struct median *ctx = (struct median*)median;

	vec_uninit(ctx->vector);
	free(ctx);
}

median_t median_init(median_is_greater_func_t func)
{
	struct median *ctx;

	ctx = calloc(1, sizeof(struct median));
	if (!ctx)
		return NULL;

	ctx->vector = vec_init(NULL);
	if (!ctx->vector) {
		vec_uninit(ctx);
		return NULL;
	}
	ctx->func = func;

	return (median_t)ctx;
}

int median_add(median_t median, void *elm)
{
	struct median *ctx = (struct median*)median;

	return vec_push_back(ctx->vector, elm);
}

void *median_calc(median_t median)
{
	return NULL;
}

