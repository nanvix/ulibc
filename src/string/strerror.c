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

#include <errno.h>

/**
 * The strerror() function maps the number in @p errnum to a message
 * string. Typically, the values for errnum come from @p errno, but
 * strerror() shall map any value of type int to a message.
 */
char *strerror(int errnum)
{
	char *error;

	switch (errnum)
	{
		case 0:
			error = "No error";
			break;
		case EPERM:
			error = "Operation not permitted";
			break;
		case ENOENT:
			error = "No such file or directory";
			break;
		case ESRCH:
			error = "No such process";
			break;
		case EINTR:
			error = "Interrupted function";
			break;
		case EIO:
			error = "I/O error";
			break;
		case ENXIO:
			error = "No such device or address";
			break;
		case E2BIG:
			error = "Argument list too long";
			break;
		case ENOEXEC:
			error = "Exec format error";
			break;
		case EBADF:
			error = "Bad file number";
			break;
		case ECHILD:
			error = "No children";
			break;
		case EAGAIN:
			error = "No more processes";
			break;
		case ENOMEM:
			error = "Not enough space";
			break;
		case EACCES:
			error = "Permission denied";
			break;
		case EFAULT:
			error = "Bad address";
			break;
		case EBUSY:
			error = "Device or resource busy";
			break;
		case EEXIST:
			error = "File exists";
			break;
		case ENODEV:
			error = "No such device";
			break;
		case ENOTDIR:
			error = "Not a directory";
			break;
		case EISDIR:
			error = "Is a directory";
			break;
		case EINVAL:
			error = "Invalid argument";
			break;
		case ENFILE:
			error = "File table overflow";
			break;
		case EMFILE:
			error = "Too many open files";
			break;
		case ENOTTY:
			error = "Not a character device";
			break;
		case EFBIG:
			error = "File too large";
			break;
		case ENOSPC:
			error = "No space left on device";
			break;
		case ESPIPE:
			error = "Invalid seek";
			break;
		case EROFS:
			error = "Read-only file system";
			break;
		case EMLINK:
			error = "Too many links";
			break;
		case EPIPE:
			error = "Broken pipe";
			break;
		case EDOM:
			error = "Math argument";
			break;
		case ERANGE:
			error = "Result too large";
			break;
		case ENOMSG:
			error = "No message of desired type";
			break;
		case EIDRM:
			error = "Identifier removed";
			break;
		case EDEADLK:
			error = "Deadlock";
			break;
		case ENOLCK:
			error = "No lock";
			break;
		case ENOLINK:
			error = "Virtual circuit is gone";
			break;
		case EPROTO:
			error = "Protocol error";
			break;
		case EMULTIHOP:
			error = "Multihop attempted";
			break;
		case EBADMSG:
			error = "Bad message";
			break;
		case EADDRINUSE:
			error = "Address in use";
			break;
		case EADDRNOTAVAIL:
			error = "Address not available";
			break;
		case EAFNOSUPPORT:
			error = "Address family not supported";
			break;
		case EALREADY:
			error = "Connection already in progress";
			break;
		case ECANCELED:
			error = "Operation canceled";
			break;
		case ECONNABORTED:
			error = "Connection aborted";
			break;
		case ECONNREFUSED:
			error = "Connection refused";
			break;
		case ECONNRESET:
			error = "Connection reset";
			break;
		case EDESTADDRREQ:
			error = "Destination address required";
			break;
		case EDQUOT:
			error = "Quota exceeded";
			break;
		case EHOSTUNREACH:
			error = "Host is unreachable";
			break;
		case EILSEQ:
			error = "Illegal byte sequence";
			break;
		case EINPROGRESS:
			error = "Operation in progress";
			break;
		case EISCONN:
			error = "Socket is connected";
			break;
		case ELOOP:
			error = "Too many levels of symbolic links";
			break;
		case EMSGSIZE:
			error = "Message too large";
			break;
		case ENAMETOOLONG:
			error = "Filename too long";
			break;
		case ENETDOWN:
			error = "Network is down";
			break;
		case ENETRESET:
			error = "Connection aborted by network";
			break;
		case ENETUNREACH:
			error = "Network unreachable";
			break;
		case ENOBUFS:
			error = "No buffer space is available";
			break;
		case ENOPROTOOPT:
			error = "Protocol not available";
			break;
		case ENOSYS:
			error = "Function not supported";
			break;
		case ENOTCONN:
			error = "The socket is not connected";
			break;
		case ENOTEMPTY:
			error = "Directory not empty";
			break;
		case ENOTSOCK:
			error = "Not a socket";
			break;
#ifndef __unix64__
		case EOPNOTSUPP:
#endif
		case ENOTSUP:
			error = "Operation not supported";
			break;
		case EOVERFLOW:
			error = "Value too large to be stored in data type";
			break;
		case EPROTONOSUPPORT:
			error = "Protocol not supported";
			break;
		case EPROTOTYPE:
			error = "Protocol wrong type for socket";
			break;
		case ETIMEDOUT:
			error = "Connection timed out";
			break;
		case ENOTRECOVERABLE:
			error = "State not recoverable";
			break;
		case EOWNERDEAD:
			error = "Previous owner died.";
			break;
		case ESTALE:
			error = "Stale NFS file handle";
			break;
#if defined(_XOPEN_SOURCE)
		case ENODATA:
			error = "No message is available on the stream head read queue";
			break;
		case ENOSR:
			error = "No stream resources";
			break;
		case ENOSTR:
			error = "Not a stream";
			break;
		case ETIME:
			error = "Stream ioctl() timeout";
			break;
#endif
		default:
			errno = EINVAL;
			error = "Not a valid error number";
			break;
	}

	return error;
}
