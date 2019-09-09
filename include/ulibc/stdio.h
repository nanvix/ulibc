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
	#define NANVIX_FOPEN_MAX 8

	/**
	 * @brief Standard buffer size (in bytes).
	 */
	#define NANVIX_BUFSIZ 1024

	/**
	 * @brief End of file.
	 */
	#define NANVIX_EOF -1

	/**
	 * @name File Stream Flags
	 */
	/**@{*/
	#define _NANVIX_IOFBF    00001 /**< Fully buffered?               */
	#define _NANVIX_IOLBF    00002 /**< Line buffered?                */
	#define _NANVIX_IONBF    00004 /**< Unbuffered?                   */
	#define _NANVIX_IORW     00010 /**< Read/Write                    */
	#define _NANVIX_IOREAD   00020 /**< Readable?                     */
	#define _NANVIX_IOWRITE  00040 /**< Writable?                     */
	#define _NANVIX_IOAPPEND 00100 /**< Append?                       */
	#define _NANVIX_IOEOF    00200 /**< End of file reached?          */
	#define _NANVIX_IOERROR  00400 /**< Error encountered?            */
	#define _NANVIX_IOMYBUF  01000 /**< Library buffer?               */
	#define _NANVIX_IOSYNC   02000 /**< Sync file position on append? */
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
	} NANVIX_FILE;

	/**
	 * @brief Standard File Streams
	 */
	/**@{*/
	extern NANVIX_FILE *nanvix_stdin;  /**< Standard Input  */
	extern NANVIX_FILE *nanvix_stdout; /**< Standard Output */
	extern NANVIX_FILE *nanvix_stderr; /**< Standard Error  */
	/**@}*/

/*============================================================================*
 * Operation on Files                                                         *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_remove(const char *filename);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_rename(const char *old, const char *new);

	/**
	 * @todo: TODO implement this function.
	 */
	extern NANVIX_FILE *nanvix_tmpfile(void);

	/**
	 * @todo: TODO implement this function.
	 */
	extern char *nanvix_tmpnam(char *s);

/*============================================================================*
 * File Access Functions                                                      *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fclose(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fflush(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern NANVIX_FILE *nanvix_fopen(const char * restrict filename, const char * restrict mode);

	/**
	 * @todo: TODO implement this function.
	 */
	extern NANVIX_FILE *nanvix_freopen(const char * restrict filename, const char * restrict mode, NANVIX_FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern void nanvix_setbuf(NANVIX_FILE * restrict stream, char * restrict buf);

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
	extern int nanvix_setvbuf(
		NANVIX_FILE * restrict stream,
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
	extern int nanvix_fprintf(
		NANVIX_FILE * restrict stream,
		const char * restrict format, ...
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fscanf(NANVIX_FILE * restrict stream, const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_printf(const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_scanf(const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_snprintf(char * restrict s, size_t n, const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_sprintf(char * restrict s, const char * restrict format, ...);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_sscanf(const char * restrict s, const char * restrict format, ...);

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
	extern int nanvix_vfprintf(
		NANVIX_FILE * restrict stream,
		const char * restrict format,
		va_list arg
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_vfscanf(NANVIX_FILE * restrict stream, const char * restrict format, va_list arg);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_vprintf(const char * restrict format, va_list arg);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_vscanf(const char * restrict format, va_list arg);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_vsnprintf(
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
	extern int nanvix_vsprintf(
		char * restrict s,
		const char * restrict format,
		va_list arg
	);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_vsscanf(const char * restrict s, const char * restrict format, va_list arg);

/*============================================================================*
 * Character Input/Output Functions                                           *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fgetc(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern char *nanvix_fgets(char * restrict s, int n, NANVIX_FILE * restrict stream);

	/**
	 * @brief Writes a string to a file.
	 *
	 * @param s      String.
	 * @param stream File stream.
	 *
	 * @param Upon successful completion, a non-negative value is
	 * returned. Upon failure, EOF is returned instead.
	 */
	extern int nanvix_fputs(const char * restrict s, NANVIX_FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_getc(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_getchar(void);

	/**
	 * @todo: TODO implement this function.
	 */
	extern char *nanvix_gets(char *s);

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
	extern int nanvix_putc(int c, NANVIX_FILE *stream);

	/**
	 * @brief Writes a string to the standard output file..
	 *
	 * @param s      String.
	 * @param stream File stream.
	 *
	 * @param Upon successful completion, a non-negative value is
	 * returned. Upon failure, EOF is returned instead.
	 */
	extern int nanvix_puts(const char *s);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_ungetc(int c, NANVIX_FILE *stream);

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
	static inline int nanvix_putchar(int c)
	{
		return (nanvix_putc(c, nanvix_stdout));
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
	static inline int fputc(int c, NANVIX_FILE *stream)
	{
		return (nanvix_putc(c, stream));
	}

/*============================================================================*
 * Direct Input/Output Functions                                              *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t nanvix_fread(void * restrict ptr, size_t size, size_t nmemb, NANVIX_FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t nanvix_fwrite(const void * restrict ptr, size_t size, size_t nmemb, NANVIX_FILE * restrict stream);

/*============================================================================*
 * File Positioning Functions                                                 *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern size_t nanvix_fread(void * restrict ptr, size_t size, size_t nmemb, NANVIX_FILE * restrict stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fgetpos(NANVIX_FILE * restrict stream, fpos_t * restrict pos);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fseek(NANVIX_FILE *stream, long int offset, int whence);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_fsetpos(NANVIX_FILE *stream, const fpos_t *pos);

	/**
	 * @todo: TODO implement this function.
	 */
	extern long int nanvix_ftell(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern void nanvix_rewind(NANVIX_FILE *stream);

/*============================================================================*
 * Error-Handling Functions                                                   *
 *============================================================================*/

	/**
	 * @todo: TODO implement this function.
	 */
	extern void nanvix_clearerr(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_feof(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern int nanvix_ferror(NANVIX_FILE *stream);

	/**
	 * @todo: TODO implement this function.
	 */
	extern void nanvix_perror(const char *s);

#endif /* ULIBC_STDIO_H_ */
