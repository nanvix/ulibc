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

#ifndef ULIBC_STDIO_H_
#define ULIBC_STDIO_H_

	#include <stdarg.h>
	#include <stddef.h>

	/**
	 * @brief maximum number of opened file stream.
	 */
	#define FOPEN_MAX 8

	/**
	 * @brief Standard buffer size (in bytes).
	 */
	#define BUFSIZ 1024

	/**
	 * @brief End of file.
	 */
	#define EOF -1

	/**
	 * @name File Stream Flags
	 */
	/**@{*/
	#define _IOFBF    00001 /**< Fully buffered?               */
	#define _IOLBF    00002 /**< Line buffered?                */
	#define _IONBF    00004 /**< Unbuffered?                   */
	#define _IORW     00010 /**< Read/Write                    */
	#define _IOREAD   00020 /**< Readable?                     */
	#define _IOWRITE  00040 /**< Writable?                     */
	#define _IOAPPEND 00100 /**< Append?                       */
	#define _IOEOF    00200 /**< End of file reached?          */
	#define _IOERROR  00400 /**< Error encountered?            */
	#define _IOMYBUF  01000 /**< Library buffer?               */
	#define _IOSYNC   02000 /**< Sync file position on append? */
	/**@}*/

	/**
	 * @brief Uniquely specifies a position within a file.
	 */
	typedef size_t fpos_t;

	/**
	 * @brief File stream.
	 */
	typedef struct _iobuf
	{
		int fd;        /**< File Descriptor */
		int flags;     /**< Flags           */
		char *buf;     /**< Stream Buffer   */
		char *ptr;     /**< Next Character  */
		size_t bufsiz; /**< Buffer Size     */
		int count;     /**< Character Count */
	} FILE;

	/**
	 * @brief Standard File Streams
	 */
	/**@{*/
	extern FILE *stdin;  /**< Standard Input  */
	extern FILE *stdout; /**< Standard Output */
	extern FILE *stderr; /**< Standard Error  */
	/**@}*/

/*============================================================================*
 * Operation on Files                                                         *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern int remove(const char *filename);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int rename(const char *old, const char *new);

	/**
	 * @todo: TODO implement this function.
	 */
	extern FILE *tmpfile(void);

	/**
	 * @todo: TODO implement this function.
	 */
	extern char *tmpnam(char *s);

/*============================================================================*
 * File Access Functions                                                      *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fclose(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fflush(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern FILE *fopen(const char * restrict filename, const char * restrict mode);

	/**
	 * @todo: TODO implement this function.
	 */
	extern FILE *freopen(const char * restrict filename, const char * restrict mode, FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern void setbuf(FILE * restrict stream, char * restrict buf);

	/**
	 * @brief Assigns a buffer to a stream.
	 *
	 * @param stream File stream.
	 * @param buf    Buffer.
	 * @param mode   Buffer mode.
	 * @param size   Buffer size.
	 *
	 * @param Upon successful completion, zero is returned. Upon
	 * failure non-zero is returned instead.
	 */
	extern int setvbuf(
		FILE * restrict stream,
		char * restrict buf,
		int mode,
		size_t size
	);

/*============================================================================*
 * Formatted Input/Output Functions                                           *
 *============================================================================*/

	/**
	 * @brief Writes a formatted string to a file.
	 *
	 * @param stream File stream
	 * @param format Formatted string.
	 *
	 * @returns Upon successful completion, the number of characters
	 * written is returned. Upon failure, a negative value is returned
	 * instead.
	 */
	extern int fprintf(
		FILE * restrict stream,
		const char * restrict format, ...
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fscanf(FILE * restrict stream, const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int printf(const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int scanf(const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int snprintf(char * restrict s, size_t n, const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int sprintf(char * restrict s, const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int sscanf(const char * restrict s, const char * restrict format, ...);

	/**
	 * @brief Writes format output of an argument list to a file.
	 *
	 * @param stream File stream
	 * @param format Formatted string.
	 * @param arg    Argument list.
	 *
	 * @returns Upon successful completion, the number of characters
	 * written is returned. Upon failure, a negative value is returned
	 * instead.
	 */
	extern int vfprintf(
		FILE * restrict stream,
		const char * restrict format,
		va_list arg
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int vfscanf(FILE * restrict stream, const char * restrict format, va_list arg);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int vprintf(const char * restrict format, va_list arg);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int vscanf(const char * restrict format, va_list arg);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int vsnprintf(
		char * restrict s,
		size_t n,
		const char * restrict format,
		va_list arg
	);

	/**
	 * @brief Writes format output of an argument list to a string.
	 *
	 * @param stream File stream
	 * @param format Formatted string.
	 * @param arg    Argument list.
	 *
	 * @returns Upon successful completion, the number of characters
	 * written is returned. Upon failure, a negative value is returned
	 * instead.
	 */
	extern int vsprintf(
		char * restrict s,
		const char * restrict format,
		va_list arg
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int vsscanf(const char * restrict s, const char * restrict format, va_list arg);

/*============================================================================*
 * Character Input/Output Functions                                           *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fgetc(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern char *fgets(char * restrict s, int n, FILE * restrict stream);

	/**
	 * @brief Writes a string to a file.
	 *
	 * @param s      String.
	 * @param stream File stream.
	 *
	 * @param Upon successful completion, a non-negative value is
	 * returned. Upon failure, EOF is returned instead.
	 */
	extern int fputs(const char * restrict s, FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int getc(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int getchar(void);

	/**
	 * @todo: TODO implement this function.
	 */
	extern char *gets(char *s);

	/**
	 * @brief Writes a character to a file.
	 *
	 * @param c      Character.
	 * @param stream File stream.
	 *
	 * @returns Upon successful completion, the character written is
	 * returned. Upon failure, the error indicator for the stream is
	 * set and EOF is returned.
	 */
	extern int putc(int c, FILE *stream);

	/**
	 * @brief Writes a string to the standard output file..
	 *
	 * @param s      String.
	 * @param stream File stream.
	 *
	 * @param Upon successful completion, a non-negative value is
	 * returned. Upon failure, EOF is returned instead.
	 */
	extern int puts(const char *s);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int ungetc(int c, FILE *stream);

	/**
	 * @brief Writes a character to the standard output file.
	 *
	 * @param c      Character.
	 * @param stream File stream.
	 *
	 * @returns Upon successful completion, the character written is
	 * returned. Upon failure, the error indicator for the stream is
	 * set and EOF is returned.
	 */
	static inline int putchar(int c)
	{
		return (putc(c, stdout));
	}

	/**
	 * @brief Writes a character to a file.
	 *
	 * @param c      Character.
	 * @param stream File stream.
	 *
	 * @returns Upon successful completion, the character written is
	 * returned. Upon failure, the error indicator for the stream is
	 * set and EOF is returned.
	 */
	static inline int fputc(int c, FILE *stream)
	{
		return (putc(c, stream));
	}

/*============================================================================*
 * Direct Input/Output Functions                                              *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

/*============================================================================*
 * File Positioning Functions                                                 *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fgetpos(FILE * restrict stream, fpos_t * restrict pos);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fseek(FILE *stream, long int offset, int whence);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int fsetpos(FILE *stream, const fpos_t *pos);

	/**
	 * @todo: TODO implement this function.
	 */
	extern long int ftell(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern void rewind(FILE *stream);

/*============================================================================*
 * Error-Handling Functions                                                   *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern void clearerr(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int feof(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int ferror(FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern void perror(const char *s);

#endif /* ULIBC_STDIO_H_ */
