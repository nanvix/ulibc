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

#ifndef ULIBC_GLUE_H_
#define ULIBC_GLUE_H_

	#include <sys/types.h>
	#include <stddef.h>
	#include <nanvix.h>

	/**
	 * @name File Offsets
	 */
	/**@{*/
	#define NANVIX_SEEK_CUR 0 /* Set file offset to current plus offset. */
	#define NANVIX_SEEK_END 1 /* Set file offset to EOF plus offset.     */
	#define NANVIX_SEEK_SET 2 /* Set file offset to offset.              */
	/**@}*/

	/**
	 * @brief Stub __sbrk() function.
	 */
	extern void *__nanvix_sbrk(size_t size);

	/**
	 * @brief Stub lseek() function.
	 */
	extern off_t __nanvix_lseek(int fildes, off_t offset, int whence);

	/**
	 * @brief Stub exit() function.
	 */
	extern NORETURN void ___nanvix_exit(int status);

	/**
	 * @brief Stub write() function.
	 */
	extern ssize_t __nanvix_write(int fd, const void *buf, size_t n);

#endif /* ULIBC_GLUE_H_ */
