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

#ifndef ULIBC_CTYPE_H_
#define ULIBC_CTYPE_H_

/*============================================================================*
 * Character Testing Functions                                                *
 *============================================================================*/

	/**
	 * @brief Tests for an alpha numeric character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is an alphanumeric character;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_isalnum(int c);

	/**
	 * @brief Tests for an alphabetic character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is an alphabetic character;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_isalpha(int c);

	/**
	 * @brief Tests for a control character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a control character;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_iscntrl(int c);

	/**
	 * @brief Tests for a decimal digit.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a decimal digit; otherwise, it
	 * returns 0.
	 */
	extern int nanvix_isdigit(int c);

	/**
	 * @brief Tests for a visible character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a character with a visible
	 * representation; otherwise, it returns 0.
	 */
	extern int nanvix_isgraph(int c);

	/**
	 * @brief Tests for a lowercase letter.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a lowercase letter; otherwise,
	 * it returns 0.
	 */
	extern int nanvix_islower(int c);

	/**
	 * @brief Tests for a printable character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a printable character;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_isprint(int c);

	/**
	 * @brief Tests for a punctuation character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a punctuation character;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_ispunct(int c);

	/**
	 * @brief Tests for a white-space character.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a white-space character;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_isspace(int c);

	/**
	 * @brief Tests for an uppercase letter.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is an uppercase letter;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_isupper(int c);

	/**
	 * @brief Tests for a hexadecimal digit.
	 *
	 * @param Character to test.
	 *
	 * @returns Returns non-zero if @p c is a hexadecimal digit;
	 * otherwise, it returns 0.
	 */
	extern int nanvix_isxdigit(int c);

/*============================================================================*
 * Character Case Mapping Functions                                           *
 *============================================================================*/

	/**
	 * @brief Transliterates uppercase characters to lowercase.
	 *
	 * @param Character to transliterate.
	 *
	 * @returns Returns the lowercase letter corresponding to the argument
	 * passed; otherwise, they returns the argument unchanged.
	 */
	extern int nanvix_tolower(int c);

	/**
	 * @brief Transliterates lowercase characters to uppercase.
	 *
	 * @param Character to transliterate.
	 *
	 * @returns Returns the uppercase letter corresponding to the argument
	 * passed; otherwise, they returns the argument unchanged.
	 */
	extern int nanvix_toupper(int c);

#endif /* ULIBC_CTYPE_H_ */
