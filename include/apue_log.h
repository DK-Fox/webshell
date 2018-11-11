/*
 * @ Description:This is the header file of apue_log.c
 * @ From:APUE
 * @ Date:2018-11-11
 */

#ifndef __APUE_LOG__
#define __APUE_LOG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

#define MAXLINE 4096

void log_msg(const char* fmt,...);
void log_cont(int,const char* fmt,...);
void log_ret(const char* fmt,...);
void log_dump(const char* fmt,...) __attribute__((noreturn));
void log_quit(const char* fmt,...) __attribute__((noreturn));
void log_exit(int,const char* fmt,...) __attribute__((noreturn));
void log_sys(const char* fmt,...) __attribute__((noreturn));

#endif
