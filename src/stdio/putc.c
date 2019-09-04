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
#include <ulibc/glue.h>
#include "stdio.h"

/**
 * @todo TODO: provide a detailed description for this function.
 */
int putc(int c, FILE *stream)
{
	int n;     /* Characters actually written. */
	int count; /* Characters to write.         */
	char *buf; /* Buffer.                      */

	spinlock_lock(&stdio_lock);

	/* Buffer is not full. */
	if (--stream->count >= 0)
	{
		*stream->ptr++ = c;

		spinlock_unlock(&stdio_lock);

		return (c);
	}

	/* Now writing. */
	if (stream->flags & _IORW)
	{
		stream->flags &= ~_IOREAD;
		stream->flags |= _IOWRITE;
	}

	/* File is not writable. */
	if (!(stream->flags & _IOWRITE))
	{
		c = EOF;
		goto done;
	}

	/* Synchronize file position. */
	if (!(stream->flags & _IOEOF))
	{
		if ((stream->flags & (_IOSYNC | _IOAPPEND)) == (_IOSYNC | _IOAPPEND))
		{
			/* Failed. */
			if (__lseek(stream->fd, 0, SEEK_END) < 0)
			{
				stream->flags |= _IOERROR;
				c = EOF;
				goto done;
			}
		}
	}

again:
	count = n = 0;

	/* Not buffered. */
	if (stream->flags & _IONBF)
	{
		/* Reset buffer. */
		stream->count = 0;

		n = __write(stream->fd, &c, count = 1);
	}

	/* Buffered. */
	else
	{
		/* Assign buffer. */
		if ((buf = stream->buf) == NULL)
		{
			/* Failed to allocate buffer. */
			if ((buf = malloc(BUFSIZ)) == NULL)
			{
				stream->flags &= ~(_IOLBF | _IOFBF);
				stream->flags |= _IONBF;
				goto again;
			}

			/* Initialize buffer. */
			stream->flags |= _IOMYBUF;
			stream->buf = buf;
			stream->ptr = buf;
			stream->bufsiz = BUFSIZ;
		}

		/* Line buffered. */
		if (stream->flags & _IOLBF)
		{
			*stream->ptr++ = c;

			/* Reset buffer. */
			stream->count = 0;

			/* Flush buffer. */
			if ((stream->ptr == (buf + stream->bufsiz)) || (c == '\n'))
			{
				n = __write(stream->fd, buf, count = stream->ptr - buf);
				stream->ptr = buf;
			}
		}

		/* Fully buffered. */
		else
		{
			/* Flush buffer. */
			if (stream->ptr == (buf + stream->bufsiz))
			{
				n = __write(stream->fd, buf, count = stream->bufsiz);
				stream->ptr = buf;
			}

			*stream->ptr++ = c;

			/* Reset buffer. */
			stream->count = stream->bufsiz - 1;
		}
	}

	/* Failed to write. */
	if (n != count)
	{
		stream->flags |= _IOERROR;
		c = EOF;
		goto done;
	}

done:

	spinlock_unlock(&stdio_lock);

	return (c);
}
