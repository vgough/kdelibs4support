/*  -*- C++ -*-
 *  Copyright (C) 2003,2005 Thiago Macieira <thiago@kde.org>
 *
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef KDE_SYSSOCKET_H
#define KDE_SYSSOCKET_H

#ifdef KSOCKETBASE_H
#error syssocket.h must be included before ksocketbase.h!
#endif

#include <config-kdelibs4support.h>

// needed for Solaris, but shouldn't hurt on other operating systems
// and to avoid ifdef mess, rather include them for all
#include <unistd.h>
#if HAVE_STROPTS_H
#include <stropts.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

namespace
{

/*
 * These function here are just wrappers for the real system calls.
 *
 * Unfortunately, a number of systems out there work by redefining
 * symbols through the preprocessor -- symbols that we need.
 *
 * So we write wrappers for all the low-level system calls.
 *
 * Qt has a very similar implementation. I got the idea from them, but
 * I copied no code.
 */

// socket
inline int kde_socket(int af, int style, int protocol)
{
    return ::socket(af, style, protocol);
}

// bind
inline int kde_bind(int fd, const struct sockaddr *sa, socklen_t len)
{
    return ::bind(fd, sa, len);
}

// listen
inline int kde_listen(int fd, int backlog)
{
    return ::listen(fd, backlog);
}

// connect
inline int kde_connect(int fd, const struct sockaddr *sa, socklen_t len)
{
    return ::connect(fd, (struct sockaddr *)sa, len);
}

// accept
inline int kde_accept(int fd, struct sockaddr *sa, socklen_t *len)
{
    return ::accept(fd, sa, len);
}

// getpeername
inline int kde_getpeername(int fd, struct sockaddr *sa, socklen_t *len)
{
    return ::getpeername(fd, sa, len);
}

// getsockname
inline int kde_getsockname(int fd, struct sockaddr *sa, socklen_t *len)
{
    return ::getsockname(fd, sa, len);
}

// ioctl
inline int kde_ioctl(int fd, int cmd, int *argp)
{
#if defined _WIN32 || defined _WIN64
    unsigned long l_argp = *argp;
    int iRet = ::ioctlsocket(fd, cmd, &l_argp);
    *argp = (int) l_argp;
    return iRet;
#else
    return ::ioctl(fd, cmd, argp);
#endif
}

} // anonymous namespace

#endif
