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

#include <nanvix/sys/dev.h>
#include <posix/stdarg.h>
#include <nanvix/ulib.h>

/**
 * @todo: TODO provide a detailed description for this function.
 */
int uprintf(const char *fmt, ...)
{
	size_t len;                    /* String length.           */
	va_list args;                  /* Variable arguments list. */
	char buffer[KBUFFER_SIZE + 1]; /* Temporary buffer.        */

	/* Convert to raw string. */
	va_start(args, fmt);
	len = uvsprintf(buffer, KBUFFER_SIZE + 1, fmt, args);
	buffer[++len] = '\0';
	va_end(args);

	nanvix_write(0, buffer, ustrlen(buffer));

	return (len);
}
