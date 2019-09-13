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

#include <ulibc/string.h>
#include <ulibc/glue.h>
#include <stddef.h>
#include <posix/errno.h>

/**
 * @brief nanvix_expand() in at least NALLOC blocks.
 */
#define NALLOC 511

/**
 * @brief Size of block structure.
 */
#define SIZEOF_BLOCK (sizeof(struct block))

/**
 * @brief Memory block.
 */
struct block
{
	struct block *nextp; /* Next free block.  */
	unsigned nblocks;    /* Size (in blocks). */
};

/**
 * @brief Free list of blocks.
 */
static struct block head;
static struct block *freep = NULL;

/**
 * The nanvix_free() function causes the space pointed to by @p ptr to be
 * deallocated, that is, made available for further allocation. If @p
 * ptr is a null pointer, no action occurs. Otherwise, if the argument
 * does not match a pointer earlier returned by the nanvix_calloc,
 * nanvix_malloc, or nanvix_realloc function, or if the space has been
 * deallocated by a call to nanvix_free or nanvix_realloc, the behavior is
 * undefined.
 */
void nanvix_free(void *ptr)
{
	struct block *p;  /* Working block.     */
	struct block *bp; /* Block being freed. */

	/* Nothing to be done. */
	if (ptr == NULL)
		return;

	bp = (struct block *)ptr - 1;

	/* Look for insertion point. */
	for (p = freep; p > bp || p->nextp < bp; p = p->nextp)
	{
		/* Freed block at start or end. */
		if (p >= p->nextp && (bp > p || bp < p->nextp))
			break;
	}

	/* Merge with upper block. */
	if (bp + bp->nblocks == p->nextp)
	{
		bp->nblocks += p->nextp->nblocks + 1;
		bp->nextp = p->nextp->nextp;
	}
	else
		bp->nextp = p->nextp;

	/* Merge with lower block. */
	if (p + p->nblocks == bp)
	{
		p->nblocks += bp->nblocks + 1;
		p->nextp = bp->nextp;
	}
	else
		p->nextp = bp;

	freep = p;
}

/**
 * @brief Expands the heap.
 *
 * @details Expands the heap by @p nblocks.
 *
 * @param nblocks Number of blocks to expand.
 *
 * @returns Upon successful completion a pointed to the expansion
 * is returned.  Upon failure, a null pointed is returned instead
 * and errno is set to indicate the error.
 */
static void *nanvix_expand(unsigned nblocks)
{
	struct block *p;

	/* Expand in at least NALLOC blocks. */
	if (nblocks < NALLOC)
		nblocks = NALLOC;

	/* Request more memory to the kernel. */
	if ((p = __nanvix_sbrk((nblocks + 1)*SIZEOF_BLOCK)) == (void *)-1)
		return (NULL);

	p->nblocks = nblocks;
	nanvix_free(p + 1);

	return (freep);
}

/**
 * The nanvix_malloc() function allocates space for an object whose size is
 * specified by @p size and whose value is indeterminate.
 */
void *nanvix_malloc(size_t size)
{
	struct block *p;     /* Working block.            */
	struct block *prevp; /* Previous working block.   */
	unsigned nblocks;    /* Request size (in blocks). */

	/* Nothing to be done. */
	if (size == 0)
		return (NULL);

	nblocks = (size + (SIZEOF_BLOCK - 1))/SIZEOF_BLOCK + 1;

	/* Create free list. */
	if ((prevp = freep) == NULL)
	{
		head.nextp = freep = prevp = &head;
		head.nblocks = 0;
	}

	/* Look for a free block that is big enough. */
	for (p = prevp->nextp; /* void */ ; prevp = p, p = p->nextp)
	{
		/* Found. */
		if (p->nblocks >= nblocks)
		{
			/* Exact. */
			if (p->nblocks == nblocks)
				prevp->nextp = p->nextp;

			/* Split block. */
			else
			{
				p->nblocks -= nblocks;
				p += p->nblocks;
				p->nblocks = nblocks;
			}

			freep = prevp;

			return (p + 1);
		}

		/* Wrapped around free list. */
		if (p == freep)
		{
			/* Expand heap. */
			if ((p = nanvix_expand(nblocks)) == NULL)
				break;
		}
	}

	return (NULL);
}

/**
 * The nanvix_realloc function deallocates the old object pointed to
 * by @p ptr and returns a pointer to a new object that has the size
 * specified by @p size. The contents of the new object shall be the
 * same as that of the old object prior to deallocation, up to the
 * lesser of the new and old sizes. Any bytes in the new object beyond
 * the @p size of the old object have indeterminate values.
 *
 * If @p ptr is a null pointer, the nanvix_realloc function behaves
 * like the nanvix_malloc function for the specified @p size.
 * Otherwise, if @p ptr does not match a pointer earlier returned by
 * the nanvix_calloc, nanvix_malloc, or nanvix_realloc function, or if
 * the space has been deallocated by a call to the free or
 * nanvix_realloc function, the behavior is undefined. If memory for
 * the new object cannot be allocated, the old object is not
 * deallocated and its value is unchanged.
 */
void *nanvix_realloc(void *ptr, size_t size)
{
	void *newptr;

	/* Nothing to be done. */
	if (size == 0)
	{
		errno = EINVAL;
		return (NULL);
	}

	newptr = nanvix_malloc(size);
	if (ptr != NULL)
		nanvix_memcpy(newptr, ptr, size);

	nanvix_free(ptr);

	return (newptr);
}

/**
 * The nanvix_calloc() function allocates space for an array of @p nmemb objects,
 * each of whose size is size. The space is initialized to all bits
 * zero.)
 */
void *nanvix_calloc(size_t nmemb, size_t size)
{
  register char *cp;

  nmemb *= size;

  cp = nanvix_malloc(nmemb);
  if (cp == NULL)
    return (NULL);

  nanvix_memset(cp, 0, nmemb);

  return (cp);
}
