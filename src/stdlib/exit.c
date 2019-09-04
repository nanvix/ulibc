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
#include "atexit.h"

/**
 * The exit() function causes normal program termination to occur. If
 * more than one call to the exit function is executed by a program,
 * the behavior is undefined.
 *
 * First, all functions registered by the atexit() function are
 * called, in the reverse order of their registration.
 *
 * Next, all open streams with unwritten buffered data are flushed,
 * all open streams are closed, and all files created by the tmpfile
 * function are removed.
 *
 * Finally, control is returned to the host environment. If the value
 * of @p status is zero or EXIT_SUCCESS, an implementation-defined
 * form of the @p status successful termination is returned. If the
 * value of @p status is EXIT_FAILURE, an implementation-defined form
 * of the @p status unsuccessful termination is returned. Otherwise
 * the @p status returned is implementation-defined.
 */
void exit(int status)
{
	/*
	 * Call registered atexit() functions
	 * in the reverse order in which they were
	 * registered.
	 */
	while (__atexit._ind-- > 0)
		__atexit._fns[__atexit._ind]();

	___exit(status);
}
