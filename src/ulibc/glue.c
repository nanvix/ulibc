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

#include <nanvix/sys/dev.h>
#include <nanvix/sys/thread.h>
#include <posix/sys/types.h>
#include <posix/stddef.h>

/**
 * @brief Heap size (in bytes).
 */
#define HEAP_SIZE (64*KB)

/**
 * @brief Heap.
 */
static struct
{
	unsigned char *brk;
	unsigned char data[HEAP_SIZE];
} heap = {
	NULL, {0, }
};

/**
 * The sbrk() function changes the breakpoint value of the calling process to
 * @p size bytes ahead from the current value.
 */
void *__nanvix_sbrk(size_t size)
{
	unsigned char *ptr;
	unsigned char *brk;

	/* Initialize heap. */
	if (heap.brk == NULL)
		heap.brk = heap.data;

	ptr = brk = heap.brk;

	brk += size;

	/* Cannot increase break value. */
	if ((brk < heap.data) || (brk >= (heap.data + HEAP_SIZE)))
		return (NULL);

	heap.brk = brk;

	return (ptr);
}

/**
 *  Terminates the calling process.
 */
NORETURN void ___nanvix_exit(int status)
{
	if (kthread_self() == KTHREAD_LEADER_TID)
		_kexit(status);
	else
		kthread_exit(&status);

	UNREACHABLE();
}

/**
 * Writes to a file.
 */
ssize_t __nanvix_write(int fd, const void *buf, size_t n)
{
	return (nanvix_write(fd, buf, n));
}

#ifdef __mppa256__

/**
 * @brief Stub main().
 */
int main(int argc, const char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	return (0);
}

#endif /* __mppa256__ */
