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
#include <ulibc/stdlib.h>
#include <stddef.h>
#include <posix/errno.h>
#include "stdio.h"

/**
 * @todo TODO: provide a detailed description for this function.
 */
int nanvix_setvbuf(NANVIX_FILE *stream, char *buf, int type, size_t size)
{
	int ret = 0;

	spinlock_lock(&stdio_lock);

		/* Invalid file stream. */
		if (stream->flags == 0)
		{
			ret = errno = EBADF;
			goto done;
		}

		/* Buffer already assigned. */
		if (stream->buf != NULL)
		{
			ret = errno = EBUSY;
			goto done;
		}

		/* Not buffered. */
		if (type == _NANVIX_IONBF)
		{
			stream->flags &= ~(_NANVIX_IOLBF | _NANVIX_IOFBF);
			stream->flags |= _NANVIX_IONBF;
			stream->count = 0;
		}

		/* Buffered. */
		else
		{
			/* Invalid buffer size. */
			if (size == 0)
			{
				ret = errno = EINVAL;
				goto done;
			}

			/* Assign own buffer. */
			if (buf == NULL)
			{
				/* Failed to allocate buffer. */
				if ((buf = nanvix_malloc(size)) == NULL)
				{
					ret = errno;
					goto done;
				}

				stream->flags |= _NANVIX_IOMYBUF;
			}

			stream->flags &= ~(_NANVIX_IOFBF | _NANVIX_IONBF | _NANVIX_IOFBF);
			stream->flags |= (type == _NANVIX_IOLBF) ? _NANVIX_IOLBF : _NANVIX_IOFBF;
			stream->buf = buf;
			stream->ptr = buf;
			stream->bufsiz = size;
			stream->count = 0;
		}

done:

	spinlock_unlock(&stdio_lock);

	return (ret);
}
