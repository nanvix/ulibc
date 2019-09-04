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

#include <ulibc/stdio.h>
#include <stddef.h>
#include "stdio.h"

/**
 * Global lock for stdio.
 */
spinlock_t stdio_lock = SPINLOCK_UNLOCKED;

/**
 * File streams table.
 */
FILE streams[FOPEN_MAX] = {
	{ 0, _IOREAD  | _IOLBF, NULL, NULL, 0, 0 },
	{ 1, _IOWRITE | _IOLBF, NULL, NULL, 0, 0 },
	{ 2, _IOWRITE | _IONBF, NULL, NULL, 0, 0 },
};

FILE *stdin = &streams[0];  /* Standard input.  */
FILE *stdout = &streams[1]; /* Standard output. */
FILE *stderr = &streams[2]; /* Standard error.  */

/*
 * Stdio library house keeping.
 */
void stdio_cleanup(void)
{
	FILE *stream;

	/* Close all streams. */
	for (stream = &streams[0]; stream < &streams[FOPEN_MAX]; stream++)
	{
		/* Valid stream. */
		if (stream->flags & (_IORW | _IOREAD | _IOWRITE))
			fflush(stream);
	}
}
