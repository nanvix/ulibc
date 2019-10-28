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

#ifndef NANVIX_ULIB_H_
#define NANVIX_ULIB_H_

	#include <nanvix/const.h>
	#include <posix/sys/types.h>
	#include <posix/stddef.h>
	#include <posix/stdarg.h>
	#include <nanvix/barelib.h>

/*============================================================================*
 * Glue                                                                       *
 *============================================================================*/

/**
 * @addtogroup ulib-glue
 * @ingroup ulib
 */
/**@{*/

	/**
	 * @brief Stub exit() function.
	 */
	extern NORETURN void ___nanvix_exit(int status);

	/**
	 * @brief Stub write() function.
	 */
	extern ssize_t __nanvix_write(int fd, const void *buf, size_t n);

/**@}*/

/*============================================================================*
 * Memory Manipulation                                                        *
 *============================================================================*/

/**
 * @addtogroup ulib-memory
 * @ingroup ulib
 */
/**@{*/

	/**
	 * @see __memchr().
	 */
	#define umemchr(s,c,n) __memchr(s,c,n)

	/**
	 * @see __memcpy().
	 */
	#define umemcpy(s1,s2,n) __memcpy(s1,s2,n)

	/**
	 * @see __memmove().
	 */
	#define umemmove(s1,s2,n) __memmove(s1,s2,n)

	/**
	 * @see __memset().
	 */
	#define umemset(s,c,n) __memset(s,c,n)

/**@}*/

/*============================================================================*
 * String Manipulation                                                        *
 *============================================================================*/

/**
 * @addtogroup ulib-string String Manipulation
 * @ingroup ulib
 */
/**@{*/

	/**
	 * @see __strcat().
	 */
	#define ustrcat(s1,s2) __strcat(s1,s2)

	/**
	 * @see __strchr().
	 */
	#define ustrchr(s,c) __strchr(s,c)

	/**
	 * @see __strcmp().
	 */
	#define ustrcmp(s1,s2) __strcmp(s1,s2)

	/**
	 * @see __strcpy().
	 */
	#define ustrcpy(s1,s2) __strcpy(s1,s2)

	/**
	 * @see __strcspn().
	 */
	#define ustrcspn(s1,s2) __strcspn(s1,s2)

	/**
	 * @see __strlen()
	 */
	#define ustrlen(str) __strlen(str)

	/**
	 * @see __strncat()
	 */
	#define ustrncat(s1,s2,n) __strncat(s1,s2,n)

	/**
	 * @see __strncmp().
	 */
	#define ustrncmp(s1,s2,n) __strncmp(s1,s2,n)

	/**
	 * @see __strncpy().
	 */
	#define ustrncpy(s1,s2,n) __strncpy(s1,s2,n)

	/**
	 * @see __strnlen().
	 */
	#define ustrnlen(s,maxlen) __strnlen(s,maxlen)

	/**
	 * @see __strpbrk().
	 */
	#define ustrpbrk(s1,s2) __strpbrk(s1,s2)

	/**
	 * @see __strrchr().
	 */
	#define ustrrchr(s,c) __strrchr(s,c)

	/**
	 * @see __strspn().
	 */
	#define ustrspn(s1,s2) __strspn(s1,s2)

	/**
	 * @see __strstr().
	 */
	#define ustrstr(s1,s2) __strstr(s1,s2)

/**@}*/

/*============================================================================*
 * String Formatting                                                          *
 *============================================================================*/

/**
 * @addtogroup ulib-formatting String Formatting
 * @ingroup ulib
 */
/**@{*/

	/**
	 * @see __vsprintf().
	 */
	#define uvsprintf(str,fmt,args) __vsprintf(str,fmt,args)

	/**
	 * @see __sprintf().
	 */
	#define usprintf(str,fmt,...) __sprintf(str,fmt,__VA_ARGS__)

	/**
	 * @todo: TODO implement this function.
	 */
	extern int usnprintf(char *s, size_t n, const char * restrict format, ...);

/**@}*/

/*============================================================================*
 * Debugging                                                                  *
 *============================================================================*/

/**
 * @addtogroup ulib-formatting String Formatting
 * @ingroup ulib
 */
/**@{*/
	/**
	 * @brief Asserts a condition.
	 *
	 * @param cond Condition to assert.
	 */
	#ifndef NDEBUG
		#define uassert(cond) ((cond) ?                                        \
				(void) 0 :                                                     \
				(void) _uassertfail("assertion failed: %s, file %s, line %d\n",\
										#cond, __FILE__, __LINE__ ))
	#else
		#define uassert(cond) ((void)(cond))
	#endif

	/**
	 * @brief Fails an assertion.
	 */
	extern void _uassertfail(const char *, const char *, const char *, int);

	/**
	 * @brief Causes abnormal termination.
	 */
	extern void uabort(void);

	/**
	 * @brief Gets error message string.
	 *
	 * @returns A pointer to the generated message string.
	 *
	 * @todo Use collating information.
	 */
	extern char *ustrerror(int errnum);

	/**
	 * @brief Writes a formatted string to the output device.
	 *
	 * @param fmt Formatted string.
	 *
	 * @returns The number of characters written to the output device.
	 */
	extern int uprintf(const char * restrict fmt, ...);

/**@}*/

#endif /* NANVIX_ULIB_H_ */
