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
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ulibc/ctype.h>
#include <errno.h>
#include <ulibc/limits.h>

/**
 * The strtoll() function converts the initial portion of the string
 * pointed to by @p nptr to long long int. First, they decompose the
 * input string into three parts: an initial, possibly empty, sequence
 * of white-space characters (as specified by the isspace function), a
 * subject sequence resembling an integer represented in some radix
 * determined by the value of @p base, and a final string of one or
 * more unrecognized characters, including the terminating null
 * character of the input string. Then, they attempt to convert the
 * subject sequence to an integer, and return the result.
 *
 * If the value of @p base is zero, the expected form of the subject
 * sequence is that of an integer constant, optionally preceded by a
 * plus or minus sign, but not including an integer suffix. If the
 * value of @p base is between 2 and 36 (inclusive), the expected form
 * of the subject sequence is a sequence of letters and digits
 * representing an integer with the radix specified by @p base,
 * optionally preceded by a plus or minus sign, but not including an
 * integer suffix. The letters from a (or A) through z (or Z) are
 * ascribed the values 10 through 35; only letters and digits whose
 * ascribed values are less than that of @p base are permitted. If the
 * value of @p base is 16, the characters 0x or 0X may optionally
 * precede the sequence of letters and digits, following the sign if
 * present.
 *
 * The subject sequence is defined as the longest initial subsequence
 * of the input string, starting with the first non-white-space
 * character, that is of the expected form. The subject sequence
 * contains no characters if the input string is empty or consists
 * entirely of white space, or if the first non-white-space character
 * is other than a sign or a permissible letter or digit.
 *
 * If the subject sequence has the expected form and the value of @p
 * base is zero, the sequence of characters starting with the first
 * digit is interpreted as an integer constant. If the subject
 * sequence has the expected form and the value of @p base is between
 * 2 and 36, it is used as the @p base for conversion, ascribing to
 * each letter its value as given above. If the subject sequence
 * begins with a minus sign, the value resulting from the conversion
 * is negated (in the return type). A pointer to the final string is
 * stored in the object pointed to by @p endptr, provided that @p
 * endptr is not a null pointer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
long long nanvix_strtoll(const char *nptr, char **endptr, int base)
{
	const char *s;
	long long acc, cutoff;
	int c;
	int neg, any, cutlim;

	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	s = nptr;
	do
	{
		c = (unsigned char) *s++;
	} while (nanvix_isspace(c));
	if (c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else
	{
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;

	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for long longs is
	 * [-9223372036854775808..9223372036854775807] and the input base
	 * is 10, cutoff will be set to 922337203685477580 and cutlim to
	 * either 7 (neg==0) or 8 (neg==1), meaning that if we have
	 * accumulated a value > 922337203685477580, or equal but the
	 * next digit is > 7 (or 8), the number is too big, and we will
	 * return a range error.
	 *
	 * Set any if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
	cutoff = neg ? NANVIX_LLONG_MIN : NANVIX_LLONG_MAX;
	cutlim = cutoff % base;
	cutoff /= base;
	if (neg)
	{
		if (cutlim > 0)
		{
			cutlim -= base;
			cutoff += 1;
		}
		cutlim = -cutlim;
	}
	for (acc = 0, any = 0;; c = (unsigned char) *s++)
	{
		if (nanvix_isdigit(c))
			c -= '0';
		else if (nanvix_isalpha(c))
			c -= nanvix_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if (neg)
		{
			if (acc < cutoff || (acc == cutoff && c > cutlim))
			{
				any = -1;
				acc = NANVIX_LLONG_MIN;
				errno = ERANGE;
			}
			else
			{
				any = 1;
				acc *= base;
				acc -= c;
			}
		}
		else
		{
			if (acc > cutoff || (acc == cutoff && c > cutlim))
			{
				any = -1;
				acc = NANVIX_LLONG_MAX;
				errno = ERANGE;
			}
			else
			{
				any = 1;
				acc *= base;
				acc += c;
			}
		}
	}
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : nptr);
	return (acc);
}
