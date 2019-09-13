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

#include <ulibc/string.h>
#include <ulibc/stdio.h>
#include <posix/stdarg.h>
#include "stdio.h"

/**
 * @brief Converts an integer to a string.
 *
 * @param num Number.
 * @param base Base.
 *
 * @returns The number characters in the string.
 */
static int nanvix_itoa(char *string, unsigned num, int base)
{
	char tmp;          /* Temporary variable. */
	char *s;           /* Working substring.  */
	char *p, *p1, *p2; /* Working characters. */
	unsigned divisor;  /* Base divisor.       */

	s = string;

	if (nanvix_strchr("ud", base) != NULL)
		divisor = 10;

	else
	{
		*s++ = '0'; *s++ = 'x';
		divisor = 16;
	}

	p = s;

	/* Convert number. */
	do
	{
		int remainder = num % divisor;

		*p++ = (remainder < 10) ? remainder + '0' :
		                          remainder + 'a' - 10;
	} while (num /= divisor);

	/* Fill up with zeros. */
	if (divisor == 16)
		while ((p - s) < 8)
			*p++ = '0';

	/* Reverse BUF. */
	p1 = s; p2 = p - 1;
	while (p1 < p2)
	{
		tmp = *p1;
		*p1++ = *p2;
		*p2-- = tmp;
	}

	return(p - string);
}

/**
 * @todo TODO: provide a detailed description for this function.
 */
int nanvix_vsprintf(char *string, const char *format, va_list ap)
{
	char *s;    /* Working string. */
	char *base; /* Base string.    */

	base = string;

    /* Format string. */
    while (*format != '\0')
    {
        /* No conversion needed. */
        if (*format != '%')
            *string++ = *format;

        /* Parse format. */
        else
        {
            switch (*(++format))
            {
				/* Character. */
                case 'c':
					*string++ = va_arg(ap, int);
					break;

				/* Decimal. */
				case 'd':
				case 'u':
					string += nanvix_itoa(string, va_arg(ap, unsigned int), *format);
					break;

				/* Hexadecimal. */
				case 'X':
				case 'x':
					string += nanvix_itoa(string, va_arg(ap, unsigned int), *format);
					break;

				/* String. */
                case 's':
					s = va_arg(ap, char*);
                    while (*s != '\0')
						*string++ = *s++;
					break;

                /* Ignore. */
                default:
                    break;
            }
		}

        format++;
    }

    *string++ = '\0';

    return (string - base);
}
