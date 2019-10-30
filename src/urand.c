/*-
 * Copyright (c) 1990, 1993 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * @brief Next random number.
 */
static unsigned long next = 2;

/**
 * @brief Computes a random number.
 *
 * @param state Random number generator state.
 *
 * Compute x = (7^5 * x) mod (2^31 - 1) without overflowing 31 bits:
 *
 * (2^31 - 1) = 127773 * (7^5) + 2836
 *
 * From "Random number generators: good ones are hard to find", Park
 * and Miller, Communications of the ACM, vol. 31, no. 10, October
 * 1988, p. 1195.
 */
static int do_rand(unsigned long *state)
{
	long hi, lo, x;

	/* Must be in [1, 0x7ffffffe] range at this point. */
	hi = *state / 127773;
	lo = *state % 127773;
	x = 16807 * lo - 2836 * hi;

	if (x < 0)
		x += 0x7fffffff;
	*state = x;

	/* Transform to [0, 0x7ffffffd] range. */
	return (x - 1);
}

/**
 * @todo TODO: provide a detailed description for this function.
 */
void usrand(unsigned seed)
{
	next = seed;

	/* Transform to [1, 0x7ffffffe] range. */
	next = (next % 0x7ffffffe) + 1;
}

/**
 * @todo TODO: provide a detailed description for this function.
 */
int urand(void)
{
	return (do_rand(&next));
}

/**
 * @todo TODO: provide a detailed description for this function.
 */
int urand_r(unsigned *state)
{
	int r;
	unsigned long val;

	/* Transform to [1, 0x7ffffffe] range. */
	val = (*state % 0x7ffffffe) + 1;
	r = do_rand(&val);

	*state = (unsigned int)(val - 1);

	return (r);
}
