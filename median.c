#include <stdlib.h>
#ifdef DEBUG
#include <stdio.h>
#endif

#include "vector/vector.h"
#include "median.h"

struct median {
	vector_t vector;
	median_is_greater_func_t func;
};

#ifdef DEBUG
/* works only for integer vector elements */
static void print_vecotr(struct median *ctx, char *header)
{
	int **iter;
	int is_first = 1;

	printf("vecotr %s: (", header);
	VEC_FOREACH(ctx->vector, iter) {
		printf("%s%d", is_first ? "" : ", ", **iter);
		is_first = 0;
	}
	printf(")\n");
}
#else
#define print_vecotr(_ctx_, _header_)
#endif

static void swap(vector_t vector, int idx_a, int idx_b)
{
	void *a = vec_at(vector, idx_a);
	void *b = vec_at(vector, idx_b);

	vec_insert(vector, a, (unsigned int)idx_b);
	vec_insert(vector, b, (unsigned int)idx_a);
}

static void quicksort(struct median *ctx, int l, int r)
{
	void *pivot;
	int cnt;
	int i;

	/* Base case: no need to sort arrays of length <= 1*/
	if (l >= r)
		return;

	/* choose pivot to be the last element in the subarray */
	pivot = vec_at(ctx->vector, r);

	/* Index indicating the "split" between elements smaller than pivot
	 * and elements greater than pivot */
	cnt = 1;

	/* Traverse through array from 1 to r */
	for (i = 1; i <= r; i++) {
		/* if an element is greater than pivot, continue... */
		if (ctx->func(pivot, vec_at(ctx->vector, i)))
			continue;

		/* Swap vector[cnt] and vector[i] so that the smaller alement
		 * vector[i] is to the left of all elements greater than
		 * pivot */
		swap(ctx->vector, cnt, i);

		/* Make sure to increment cnt so we can keep track of what to
		 * swap vector[i] with */
		cnt++;
	}

	/* NOTE:
	 *   cnt is currently a t one plus the pivot's index
	 *   (Hence, the cnt-2 when recursively sorting the left side of pivot)
	 */
	quicksort(ctx, 1, cnt-2); /* Recursively sort the left side of pivot */
	quicksort(ctx, cnt, r); /* Recursively sort the right side of pivot */
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
	struct median *ctx = (struct median*)median;

	print_vecotr(ctx, "before");
	quicksort(ctx, 0, vec_size(ctx->vector) - 1);
	print_vecotr(ctx, "after");
	return NULL;
}

