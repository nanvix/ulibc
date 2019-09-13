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

/*
 * Copyright (C) 1991-1996 Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library.
 *
 * The GNU C Library free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <ulibc/wchar.h>
#include <stddef.h>
#include <posix/errno.h>

/**
 * @brief Number of bytes needed for the current character.
 */
static int count = 0;
static wint_t value = 0;

/**
 * @brief Internal mbtowc().
 */
static size_t _mbtowc(wchar_t *pwc, const char *s, size_t n)
{
	size_t used = 0;

	if (s == NULL)
    {
		pwc = NULL;
		s = "";
		n = 1;
	}

	if (n > 0)
	{
		if (count == 0)
		{
			unsigned char byte = (unsigned char) *s++;
			++used;

			/* We must look for a possible first byte of a UTF8 sequence.  */
			if (byte < 0x80)
			{
				/* One byte sequence.  */
				if (pwc != NULL)
					*pwc = (wchar_t) byte;
				return byte ? used : 0;
			}

			if ((byte & 0xc0) == 0x80 || (byte & 0xfe) == 0xfe)
			{
				/* Oh, oh.  An encoding error.  */
				errno = EILSEQ;
				return (size_t) -1;
			}

			if ((byte & 0xe0) == 0xc0)
			{
				/* We expect two bytes.  */
				count = 1;
				value = byte & 0x1f;
			}
			else if ((byte & 0xf0) == 0xe0)
			{
				/* We expect three bytes.  */
				count = 2;
				value = byte & 0x0f;
			}
			else if ((byte & 0xf8) == 0xf0)
			{
				/* We expect four bytes.  */
				count = 3;
				value = byte & 0x07;
			}
			else if ((byte & 0xfc) == 0xf8)
			{
				/* We expect five bytes.  */
				count = 4;
				value = byte & 0x03;
			}
			else
			{
				/* We expect six bytes.  */
				count = 5;
				value = byte & 0x01;
			}
		}

		/*
		 * We know we have to handle a multibyte character and there
		 * are some more bytes to read.
		 */
		while (used < n)
		{
			/* The second to sixths byte must be of the form 10xxxxxx.  */
			unsigned char byte = (unsigned char) *s++;
			++used;

			if ((byte & 0xc0) != 0x80)
			{
				/* Oh, oh.  An encoding error.  */
				errno = EILSEQ;
				return (size_t) -1;
			}

			value <<= 6;
			value |= byte & 0x3f;

			if (--count == 0)
			{
				/* The character is finished.  */
				if (pwc != NULL)
					*pwc = (wchar_t) value;
				return value ? used : 0;
			}
		}
	}

	return ((size_t) -2);
}

/**
 * If @p s is not a null pointer, the mbtowc() function determines the
 * number of bytes that are contained in the multibyte character
 * pointed to by @p s. It then determines the code for the value of
 * type wchar_t that corresponds to that multibyte character. (The
 * value of the code corresponding to the null character is zero.) If
 * the multibyte character is valid and @p pwc is not a null pointer,
 * the mbtowc function stores the code in the object pointed to by @p
 * pwc. At most @p n bytes of the array pointed to by @p s will be
 * examined.
 *
 * The implementation shall behave as if no library function calls the
 * mbtowc() function.
 */
int nanvix_mbtowc(wchar_t *pwc, const char *s, size_t n)
{
	int result;

	/*
	 * If S is NULL the function has to return null or not null
	 * depending on the encoding having a state depending encoding or
	 * not.  This is nonsense because any multibyte encoding has a
	 * state.  The ISO C amendment 1 corrects this while introducing the
	 * restartable functions. We simply say here all encodings have a
	 * state.
	 */
	if (s == NULL)
		return (1);

	result = _mbtowc(pwc, s, n);

	/*
	 * The `mbrtowc' functions tell us more than we need.
	 * Fold the -1 and -2 result into -1.
	 */
	if (result < 0)
	result = -1;

	return (result);
}
