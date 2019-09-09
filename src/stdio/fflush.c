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

#include <ulibc/glue.h>
#include <ulibc/stdio.h>
#include <stddef.h>
#include "stdio.h"

/*
 * Flushes a stream.
 */
static int do_fflush(NANVIX_FILE *stream)
{
	char *buf; /* Buffer.              */
	ssize_t n; /* Byte count to flush. */

	/* Not buffered. */
	if (stream->flags & _NANVIX_IONBF)
		return (0);

	/* Not writable. */
	if (!(stream->flags & _NANVIX_IOWRITE))
		return (0);

	/* No buffer assigned. */
	if ((buf = stream->buf) == NULL)
		return (0);

	/* Nothing to flushed. */
	if ((n = stream->ptr - buf) == 0)
		return (0);

	/* Reset buffer. */
	stream->ptr = buf;
	stream->count = (stream->flags & _NANVIX_IOLBF) ? 0 : stream->bufsiz - 1;

	/* Flush. */
	if (__nanvix_write(stream->fd, buf, n) != n)
	{
		stream->flags |= _NANVIX_IOERROR;
		return (NANVIX_EOF);
	}

	return (0);
}

/*
 * Flushes a file stream.
 */
int nanvix_fflush(NANVIX_FILE *stream)
{
	int ret = 0;

	spinlock_lock(&stdio_lock);

		/* Flush all streams. */
		if (stream == NULL)
		{
			for (stream = &streams[0]; stream < &streams[NANVIX_FOPEN_MAX]; stream++)
				ret |= do_fflush(stream);

			goto done;
		}

		ret = do_fflush(stream);

done:

	spinlock_unlock(&stdio_lock);

	return (ret);
}
