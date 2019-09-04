/*
 * MIT License
 *
 * Copyright(c) 2011-2019 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ulibc/string.h>
#include <ulibc/stdlib.h>
#include <stddef.h>

/**
 * @brief Compare function.
 */
static int (*_cmp)(const void *, const void *) = NULL;

/**
 * @brief Finds sorting pivot.
 */
static int find_pivot(void *base, int i, int j, size_t size)
{
	void *first_key;
	void *next_key;

	first_key = (void *) (((char *) base) + (i*size));
	next_key = first_key;

	for (int k = i + 1; k <= j; k++)
    {
		int res;

		next_key = (void *) (((char *) next_key) + size);
		res = (*_cmp) (next_key, first_key);

		if (res > 0)
			return (k);
		else if (res < 0)
			return (i);
	}

	return (-1);
}

/**
 * @brief Swaps two elements.
 */
static void swap(void *base, int i, int j, size_t size)
{
	static void *temp = NULL;
	static size_t max_size = 0;
	void *elem1, *elem2;

	if (size > max_size)
	{
		temp = realloc(temp, size);
		max_size = size;
	}

	elem1 = ((char *) base) + (i * size);
	elem2 = ((char *) base) + (j * size);

	memcpy (temp, elem1, size);
	memcpy (elem1, elem2, size);
	memcpy (elem2, temp, size);
}

/**
 * @brief Partitions the array.
 */
static int partition(void *base, int i, int j, int pivot_index, size_t size)
{
	int left, right;

	left = i;
	right = j;

	do
	{
		swap (base, left, right, size);

		if (pivot_index == left)
			pivot_index = right;
		else if (pivot_index == right)
			pivot_index = left;

		while (_cmp ((void *) (((char *) base) + (left * size)),
			(void *) (((char *) base) + (pivot_index * size))) < 0)
			left++;

		while (_cmp ((void *) (((char *) base) + (right * size)),
			(void *) (((char *) base) + (pivot_index * size))) >= 0)
			right--;
	} while (left <= right);

	return (left);
}

/**
 * @brief Internal qsort().
 */
static void _qsort(void *base, int i, int j, size_t size)
{
	int pivot_index, mid;

	pivot_index = find_pivot(base, i, j, size);

	if (pivot_index == -1)
		return;

	/* Sort. */
	mid = partition (base, i, j, pivot_index, size);
	_qsort (base, i, mid - 1, size);
	_qsort (base, mid, j, size);
}

/**
 * The qsort() function sorts an array of @p nmemb objects, the
 * initial element of which is pointed to by @p base. The size of each
 * object is specified by @p size.
 *
 * The contents of the array are sorted into ascending order according
 * to a comparison function pointed to by @p compar, which is called
 * with two arguments that point to the objects being compared. The
 * function shall return an integer less than, equal to, or greater
 * than zero if the first argument is considered to be respectively
 * less than, equal to, or greater than the second.
 */
void qsort(
	void *base,
	size_t nmemb,
	size_t size,
	int (*cmp)(const void *, const void *))
{
	_cmp = cmp;
	_qsort(base, 0, nmemb - 1, size);
}
