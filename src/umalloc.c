/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
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

#include <nanvix/hlib.h>
#include <nanvix/ulib.h>
#include <posix/sys/types.h>
#include <posix/errno.h>
#include <posix/stddef.h>

/**
 * @brief expand() in blocks of BLOCK_SIZE bytes.
 */
#define BLOCK_SIZE 512

/**
 * @brief Memory block.
 */
struct block
{
	struct block *nextp; /* Next free block.  */
	size_t size;         /* Size (in bytes). */
};

/**
 * @brief Free list of blocks.
 */
static struct block head;
static struct block *freep = NULL;

/**
 * @brief Frees allocated memory.
 *
 * @param ptr Memory area to free.
 */
void ufree(void *ptr)
{
	struct block *p;  /* Working block.     */
	struct block *bp; /* Block being freed. */

	/* Nothing to be done. */
	if (ptr == NULL)
		return;

	bp = (struct block *)ptr - 1;

	/* Look for insertion point. */
	for (p = freep; !(p < bp && p->nextp > bp); p = p->nextp)
	{
		/* Freed block at start or end. */
		if (p >= p->nextp && (bp > p || bp < p->nextp))
			break;
	}

	/* Merge with upper block. */
	if (bp + bp->size == p->nextp)
	{
		bp->size += p->nextp->size;
		bp->nextp = p->nextp->nextp;
	}
	else
		bp->nextp = p->nextp;

	/* Merge with lower block. */
	if (p + p->size == bp)
	{
		p->size += bp->size;
		p->nextp = bp->nextp;
	}
	else
		p->nextp = bp;

	freep = p;
}

/**
 * @brief Expands the heap.
 *
 * @details Expands the heap by @p size (in bytes).
 *
 * @param size Number of bytes to expand.
 *
 * @returns Upon successful completion a pointed to the expansion is returned.
 *          Upon failure, a null pointed is returned instead and errno is set
 *          to indicate the error.
 */
static void *expand(size_t size)
{
	struct block *p;
	size_t n;

	/* Expand in BLOCK_SIZE multiple bytes. */
	n = TRUNCATE(size, BLOCK_SIZE);	

	/* Request more memory to the kernel. */
	if ((p = __nanvix_sbrk(n)) == NULL)
		return (NULL);

	p->size = n;
	ufree(p + 1);

	return (freep);
}

/**
 * @brief Allocates memory.
 *
 * @param size Number of bytes to allocate.
 *
 * @returns Upon successful completion with size not equal to 0, nanvix_malloc()
 *          returns a pointer to the allocated space. If size is 0, either a
 *          null pointer or a unique pointer that can be successfully passed to
 *          nanvix_free() is returned. Otherwise, it returns a null pointer and set
 *          errno to indicate the error.
 */
void *umalloc(size_t size)
{
	struct block *p;     /* Working block.            */
	struct block *prevp; /* Previous working block.   */

	/* Nothing to be done. */
	if (size == 0)
		return (NULL);

	/* Create free list. */
	if ((prevp = freep) == NULL)
	{
		head.nextp = freep = prevp = &head;
		head.size = 0;
	}

	/* Look for a free block that is big enough. */
	for (p = freep; /* void */ ; prevp = p, p = p->nextp)
	{
		/* Found. */
		if (p->size >= size)
		{
			/* Exact. */
			if (p->size == size)
				prevp->nextp = p->nextp;

			/* Split block. */
			else
			{
				p->size -= size;
				p += p->size;
				p->size = size;
			}

			freep = prevp;

			return (p + 1);
		}

		/* Wrapped around free list. */
		if (p == freep)
		{
			/* Expand heap. */
			if ((p = expand(size)) == NULL)
				break;
		}
	}

	return (NULL);
}

/**
 * @brief Allocates memory to hold @p num elements of size @p size,
 * and initializes it to zero.
 *
 * @param num  Number of elements of @p size to be allocated.
 * @param size Number of bytes of one element.
 *
 * @returns Pointer to the new allocated region.
 */
void * ucalloc(unsigned int num, size_t size)
{
	void *p;
	size_t num_bytes;

	num_bytes = num * size;

	/* Nothing to be done. */
	if (num_bytes == 0)
		return (NULL);

	p = umalloc(num_bytes);

	/* Initializes the region to ZERO. */
	if (p != NULL)
		umemset(p, 0, num_bytes);

	return (p);
}

/**
 * @brief Reallocates a memory chunk.
 *
 * @param ptr  Pointer to old object.
 * @param size Size of new object.
 *
 * @returns Upon successful completion, nanvix_realloc() returns a pointer to the
 *           allocated space. Upon failure, a null pointer is returned instead.
 *
 * @todo Check if we can simply expand.
 */
void *urealloc(void *ptr, size_t size)
{
	void *newptr;
	struct block *p;

	/* Nothing to be done. */
	if (size == 0)
		return (NULL);

	newptr = umalloc(size);

	/* Checks if there are more operations to be done. */
	if (ptr != NULL)
	{
		p = (struct block *) ptr-1;

		umemcpy(newptr, ptr, p->size);

		ufree(ptr);
	}

	return (newptr);
}
