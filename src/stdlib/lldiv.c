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
 * Copyright (C) 1991, 1996 Free Software Foundation, Inc.
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

#include <ulibc/stdlib.h>

#ifndef __STRICT_ANSI__

/**
 * The lldiv() function computes @p numer / @p denom and @p numer % @p
 * denom in a single operation.
 */
lldiv_t lldiv (long long int numer, long long int denom)
{
	lldiv_t result;

	result.quot = numer/denom;
	result.rem = numer%denom;

	/*
	 * The ANSI standard says that |QUOT| <= |NUMER / DENOM|, where
	 * NUMER / DENOM is to be computed in infinite precision.  In
	 * other words, we should always truncate the quotient towards
	 * zero, never -infinity.  Machine division and remainer may
	 * work either way when one or both of NUMER or DENOM is
	 * negative.  If only one is negative and QUOT has been
	 * truncated towards -infinity, REM will have the same sign as
	 * DENOM and the opposite sign of NUMER; if both are negative
	 * and QUOT has been truncated towards -infinity, REM will be
	 * positive (will have the opposite sign of NUMER).  These are
	 * considered `wrong'.  If both are NUM and DENOM are positive,
	 * RESULT will always be positive.  This all boils down to: if
	 * NUMER >= 0, but REM < 0, we got the wrong answer.  In that
	 * case, to get the right answer, add 1 to QUOT and subtract
	 * DENOM from REM.
	 */
	if (numer >= 0 && result.rem < 0)
	{
		++result.quot;
		result.rem -= denom;
	}

	return (result);
}

#endif /* __STRICT_ANSI__ */
