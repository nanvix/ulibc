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

#ifndef LIMITS_H_
#define LIMITS_H_

	/* Number of functions that may be registered with atexit() */
	#ifndef NANVIX_ATEXIT_MAX
	#define NANVIX_ATEXIT_MAX 32
	#endif

	/* Default process priority. */
	#ifndef NANVIX_NZERO
	#define NANVIX_NZERO 20
	#endif

	/* Maximum number of links to a single file. */
	#ifndef NANVIX_LINK_MAX
	#define NANVIX_LINK_MAX 8
	#endif

	/* Maximum value of a long. */
	#ifndef NANVIX_LONG_MAX
	#define NANVIX_LONG_MAX 2147483647
	#endif

	/* Minimum value of type long. */
	#ifndef NANVIX_LONG_MIN
	#define NANVIX_LONG_MIN -2147483647
	#endif

	/* Maximum value for an object of type int. */
	#ifndef NANVIX_INT_MAX
	#define NANVIX_INT_MAX 2147483647
	#endif

	/* Minimum value for an object of type int. */
	#ifndef NANVIX_INT_MIN
	#define NANVIX_INT_MIN -2147483647
	#endif

	/**
	 * @brief Maximum value for an object of type long long.
	 */
	#ifndef NANVIX_LLONG_MAX
	#define NANVIX_LLONG_MAX +9223372036854775807
	#endif

	/**
	 * @brief Minimum value for an object of type long long.
	 */
	#ifndef NANVIX_LLONG_MIN
	#define NANVIX_LLONG_MIN -9223372036854775807
	#endif

	/**
	 * @brief Maximum number of bytes in a filename.
	 */
	#ifndef NANVIX_NAME_MAX
	#define NANVIX_NAME_MAX 14
	#endif

	/* Files that one process can have open simultaneously. */
	#ifndef NANVIX_OPEN_MAX
	#define NANVIX_OPEN_MAX 20
	#endif

	/* Length of argument to the execve(). */
	#ifndef NANVIX_ARG_MAX
	#define NANVIX_ARG_MAX 2048
	#endif

	/**
	 * @brief Maximum number of bytes in a pathname.
	 */
	#ifndef NANVIX_PATH_MAX
	#define NANVIX_PATH_MAX 512
	#endif

	/* Maximum value for unsigned long. */
	#ifndef NANVIX_ULONG_MAX
	#define NANVIX_ULONG_MAX 4294967295u
	#endif

	/**
	 * @brief Maximum value for an object of type unsigned long long.
	 */
	#ifndef NANVIX_ULLONG_MAX
	#define NANVIX_ULLONG_MAX 18446744073709551615u
	#endif

#endif /* LIMITS_H_ */
