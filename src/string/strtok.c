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
 * Copyright (c) 1990 The Regents of the University of California.
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
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

#include <posix/stddef.h>

/**
 * @brief Scan point.
 */
static char *_scanpoint = NULL;

/**
 * A sequence of calls to the strtok() function breaks the string
 * pointed to by @p s1 into a sequence of tokens, each of which is
 * delimited by a character from the string pointed to by @p s2. The
 * first call in the sequence has a non-null first argument;
 * subsequent calls in the sequence have a null first argument. The
 * separator string pointed to by @p s2 may be different from call to
 * call.
 *
 * The first call in the sequence searches the string pointed to by @p
 * s1 for the first character that is not contained in the current
 * separator string pointed to by @p s2. If no such character is
 * found, then there are no tokens in the string pointed to by @p s1
 * and the strtok function returns a null pointer. If such a character
 * is found, it is the start of the first token.
 *
 * The strtok function then searches from there for a character that
 * is contained in the current separator string. If no such character
 * is found, the current token extends to the end of the string
 * pointed to by @p s1, and subsequent searches for a token will
 * return a null pointer. If such a character is found, it is
 * overwritten by a null character, which terminates the current
 * token. The strtok() function saves a pointer to the following
 * character, from which the next search for a token will start.
 *
 * Each subsequent call, with a null pointer as the value of the first
 * argument, starts searching from the saved pointer and behaves as
 * described above.
 *
 * The implementation shall behave as if no library function calls the
 * strtok() function.
 */
char *nanvix_strtok(char *s1, const char *s2)
{
	char *scan;
	char *tok;
	const char *dscan;

	if ((s1 == NULL) && (_scanpoint == NULL))
      return (NULL);

	if (s1 != NULL)
		scan = s1;
	else
		scan = _scanpoint;

	/*
	 * Scan leading delimiters.
	 */
	for (/* noop*/ ; *scan != '\0'; scan++)
	{
		for (dscan = s2; *dscan != '\0'; dscan++)
		{
			if (*scan == *dscan)
				break;
		}

		if (*dscan == '\0')
			break;
	}
	if (*scan == '\0')
	{
		_scanpoint = NULL;
		return (NULL);
    }

	tok = scan;

	/*
	 * Scan token.
	 */
	for (/* noop */; *scan != '\0'; scan++)
	{
		/* ++ moved down. */
		for (dscan = s2; *dscan != '\0';)
		{
			if (*scan == *dscan++)
			{
				_scanpoint = scan + 1;
				*scan = '\0';
				return (tok);
			}
		}
	}

	/* Reached end of string. */
	_scanpoint = NULL;

	return (tok);
}
