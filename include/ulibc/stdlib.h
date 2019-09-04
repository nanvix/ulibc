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

#ifndef ULIBC_STDLIB_H_
#define ULIBC_STDLIB_H_

	#include <stddef.h>

/*============================================================================*
 * String Conversion Functions                                                *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern double atof(const char *nptr);

	/**
	 * @brief Converts a string to an integer.
	 *
	 * @param str String to convert.
	 *
	 * @returns The converted value if the value can be represented.
	 */
	extern int atoi(const char *nptr);

	/**
	 * @brief Converts a string to a long eger.
	 *
	 * @param str String to convert.
	 *
	 * @returns The converted value if the value can be represented.
	 */
	extern long atol(const char *nptr);

	/**
	 * @brief Converts a string to a long long eger.
	 *
	 * @param nptr String to convert.
	 *
	 * @returns The converted value if the value can be represented.
	 */
	extern long long atoll(const char *nptr);

	/**
	 * @todo: TODO implement this function.
	 */
	extern double strtod(
		const char * restrict nptr,
		char ** restrict endptr
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern float strtof(
		const char * restrict nptr,
		char ** restrict endptr
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern long double strtold(
		const char * restrict nptr,
		char ** restrict endptr
	);

	/*
	 * Convert a string to a long eger.
	 *
	 * Ignores `locale' stuff.  Assumes that the upper and lower case
	 * alphabets and digits are each contiguous.
	 */
	extern long strtol(
		const char * restrict nptr,
		char ** restrict endptr,
		int base
	);

	/**
	 * @brief Converts a string to a long long eger.
	 *
	 * @param nptr   Start of string
	 * @param endptr End of string.
	 * @param base   Base
	 *
	 * @returns The converted value
	 */
	extern long long strtoll(
		const char * restrict nptr,
		char ** restrict endptr,
		int base
	);

	/**
	 * @brief Converts a string to an unsigned long.
	 *
	 * @param str    Start of string.
	 * @param endptr End of string.
	 * @param base   Base.
	 *
	 * @returns The converted value.
	 */
	extern unsigned long strtoul(
		const char * restrict nptr,
		char ** restrict endptr,
		int base
	);

	/**
	 * @brief Converts a string to an unsigned long long.
	 *
	 * @param str    Start of string.
	 * @param endptr End of string.
	 * @param base   Base.
	 *
	 * @returns The converted value.
	 */
	extern unsigned long long strtoull(
		const char * restrict nptr,
		char ** restrict endptr,
		int base
	);

/*============================================================================*
 * Pseudo-Random Sequence Generation Functions                                *
 *============================================================================*/

	/**
	 * @brief Maximum value returned by rand().
	 */
	#define RAND_MAX 0x7fffffff

	/**
	 * @brief Generates a pseudo-random number.
	 *
	 * @returns A pseudo-random integer.
	 */
	extern int rand(void);

	/**
	 * @brief Sets seed value for pseudo-random number generator.
	 *
	 * @param seed Pseudo-random number sequence's seed value.
	 */
	extern void srand(unsigned seed);

/*============================================================================*
 * Memory Management Functions                                                *
 *============================================================================*/

	/**
	 * @brief Allocates a chunk of memory and cleans it.
	 *
	 * @param n    Number of elements to allocate.
	 * @param size Size of each element.
	 *
	 * @returns Upon successful completion with both @n and @p size
	 * non-zero, calloc() returns a pointer to the allocated space. If
	 * either @p n or @p size is 0, then either a null pointer or a
	 * unique pointer value that can be successfully passed to free()
	 * is returned.  Otherwise, it returns a null pointer and set
	 * errno to indicate the error.
	 */
	extern void *calloc(size_t nmemb, size_t size);

	/**
	 * @brief Frees allocated memory.
	 *
	 * @param ptr Memory area to free.
	 */
	extern void free(void *ptr);

	/**
	 * @brief Allocates memory.
	 *
	 * @param size Number of bytes to allocate.
	 *
	 * @returns Upon successful completion with size not equal to 0,
	 * malloc() returns a pointer to the allocated space. If size is
	 * 0, either a null pointer or a unique pointer that can be
	 * successfully passed to free() is returned. Otherwise, it
	 * returns a null pointer and set errno to indicate the error.
	 */
	extern void *malloc(size_t size);

	/**
	 * @brief Reallocates a memory chunk.
	 *
	 * @param ptr  Pointer to old object.
	 * @param size Size of new object.
	 *
	 * @returns Upon successful completion, realloc() returns a
	 * pointer to the allocated space. Upon failure, a null pointer is
	 * returned instead.
	 *
	 * @todo Check if we can simply expand.
	 */
	extern void *realloc(void *ptr, size_t size);

/*============================================================================*
 * Communication with the Environment                                         *
 *============================================================================*/

	/**
	 * @brief Causes abnormal process termination.
	 *
	 * @bug FIXME: this function should conform to the standards.
	 */
	extern void abort(void);

	/**
	 * @brief Registers a function to run at process termination.
	 *
	 * @param func Function to be registered.
	 *
	 * @returns Upon successful completion 0 is returned; otherwise, a
	 * non-zero value is returned.
	 */
	extern int atexit(void (*func)(void));

	/**
	 * @brief Terminates the calling process.
	 *
	 * @param status Exit status.
	 *
	 * @bug FIXME: this function should conform to the standards.
	 */
	extern void exit(int status);

	/**
	 * @brief Gets value of an environment variable.
	 *
	 * @param name Variable name.
	 *
	 * @returns A pointer to a string containing the value for the
	 * specified name, upon successful completion. If the specified
	 * name cannot be found in the environment of the calling process,
	 * a null pointer is returned instead.
	 */
	extern char *getenv(const char *name);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int system(const char *string);

/*============================================================================*
 * Searching and Sorting Utilities                                            *
 *============================================================================*/

	/**
	 * @brief Performs a binary search on a sorted table.
	 *
	 * @param key    Key to compare.
	 * @param base   Base of the array.
	 * @param nmemb  Number of elements in the array.
	 * @param size   Size of each element.
	 * @param compar Comparison function.
	 *
	 * @returns A pointer to a matching member of the array, or a null
	 * pointer if no match is found. If two or more members compare
	 * equal, which member is returned is unspecified.
	 */
	extern void *bsearch(
		const void *key,
		const void *base,
		size_t nmemb,
		size_t size,
		int (*compar)(const void *, const void *)
	);

	/**
	 * @brief Sorts a table of data.
	 *
	 * @param base  Array to sort.
	 * @param nmemb Number of elements in the array.
	 * @param size  Size of each element.
	 * @param cmp   Comparison function.
	 */
	extern void qsort(
		void *base,
		size_t nmemb,
		size_t size,
		int (*compar)(const void *, const void *))
	;

/*============================================================================*
 * Integer Arithmetic Functions                                               *
 *============================================================================*/

#if defined(__mppa256__)

	#include <ulibc/glue.h>

#elif defined(__unix64__)

	#include <stdlib.h>

#else

	/**
	 * @brief Structure type returned by the div() function.
	 */
	typedef struct
	{
		int quot; /**< Quotient.  */
		int rem;  /**< Remainder. */
	} div_t;

	/**
	 * @brief Structure type returned by the ldiv() function.
	 */
	typedef struct
	{
		long int quot; /**< Quotient.  */
		long int rem;  /**< Remainder. */
	} ldiv_t;

#ifndef __STRICT_ANSI__

	/**
	 * @brief Structure type returned by the lldiv() function.
	 */
	typedef struct
	{
		long long int quot; /**< Quotient.  */
		long long int rem;  /**< Remainder. */
	} lldiv_t;

#endif /* __STRICT_ANSI__ */

#endif

	/**
	 * @brief Returns an integer absolute value.
	 *
	 * @param j Integer operand.
	 *
	 * @returns The absolute value of its integer operand.
	 */
	extern int abs(int j);

	/**
	 * @brief Returns a long eger absolute value.
	 *
	 * @param j Integer operand.
	 *
	 * @returns The absolute value of the long eger operand.
	 */
	extern long  labs(long  j);

	/**
	 * @brief Returns a long long eger absolute value.
	 *
	 * @param j Integer operand.
	 *
	 * @returns The absolute value of the long eger operand.
	 */
	extern long long  llabs(long long  j);

	/**
	 * @brief Computes the quotient and remainder of an integer division.
	 *
	 * @param numer Numerator.
	 * @param denom Denominator.
	 *
	 * @returns A structure of type div_t, comprising both the quotient and the
	 *          remainder.
	 */
	extern div_t div(int numer, int denom);

	/**
	 * @brief Computes quotient and remainder of a long division.
	 *
	 * @param numer Numerator.
	 * @param denom Denominator.
	 *
	 * @returns A structure of type ldiv_t, comprising both the quotient and the
	 *          remainder.
	 */
	extern ldiv_t ldiv(long  numer, long  denom);

#ifndef __STRICT_ANSI__

	/**
	 * @brief Computes quotient and remainder of a long long division.
	 *
	 * @param numer Numerator.
	 * @param denom Denominator.
	 *
	 * @returns A structure of type lldiv_t, comprising both the
	 * quotient and the remainder.
	 */
	extern lldiv_t lldiv(long long  numer, long long  denom);

#endif /* __STRICT_ANSI__ */

/*============================================================================*
 * Multibyte Character Functions                                              *
 *============================================================================*/

	/**
	 * @brief Gets number of bytes in a character.
	 *
	 * @param s Multi-byte character.
	 * @param n Maximum number of bytes to consider.
	 *
	 * @returns If s is a null pointer, mblen() returns a non-zero or
	 * 0 value, if character encodings, respectively, do or do not
	 * have state-dependent encodings. If s is not a null pointer,
	 * mblen() either returns 0 (if s points to the null byte), or
	 * returns the number of bytes that constitute the character (if
	 * the next n or fewer bytes form a valid character), or return -1
	 * (if they do not form a valid character) and is set errno to
	 * indicate the error. In no case shall the value returned be
	 * greater than @p n or the value of the MB_CUR_MAX macro.
	 *
	 * @note The mblen() function is not thread-safe.
	 */
	extern int mblen(const char *s, size_t n);

	/**
	 * @brief Converts a character to a wide-character code.
	 *
	 * @param pwc Wide-character code.
	 * @param s   Wide-character.
	 * @param n   Number of bytes to consider.
	 *
	 * @returns If @p s is a null pointer, mbtowc() returns a non-zero
	 * or 0 value, if character encodings, respectively, do or do not
	 * have state- dependent encodings. If @p s is not a null pointer,
	 * mbtowc() either returns 0 (if s points to the null byte), or
	 * returns the number of bytes that constitute the converted
	 * character (if the next @p n or fewer bytes form a valid
	 * character), or return -1 and sets errno to indicate the error
	 * (if they do not form a valid character).  In no case the value
	 * returned is greater than @p n or the value of the MB_CUR_MAX
	 * macro.
	 *
	 * @note The mbtowc() function is not thread-safe.
	 */
	extern int mbtowc(wchar_t * restrict pwc, const char * restrict s, size_t n);

	/**
	 * @brief Cconverts a wide-character code to a character.
	 *
	 * @param s     Store location.
	 * @param wchar Wide-character to convert.
	 *
	 * @returns If @p s is a null pointer,a non-zero or 0 value is
	 * returns, if character encodings, respectively, do or do not
	 * have state-dependent encodings. If @p s is not a null pointer,
	 * -1 is returned if the value of @p wchar does not correspond to
	 * a valid character, or return the number of bytes that
	 * constitute the character
	 * corresponding to the value of @p wchar.
	 */
	extern int wctomb(char *s, wchar_t wchar);

/*============================================================================*
 * Multibyte String Functions                                                 *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t mbstowcs(
		wchar_t * restrict pwcs,
		const char * restrict s,
		size_t n
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t wcstombs(char * restrict s,
		const wchar_t * restrict pwcs,
		size_t n
	);

#endif /* ULIBC_STDLIB_H_ */
