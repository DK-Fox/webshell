/*
 * **********************************************
 * @ Filename:apue_err.h
 * @ From:APUE
 * @ Description:This is the header file of apue_err.c
 * **********************************************
 */

#ifndef __APUE_ERR__
#define __APUE_ERR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define MAXLINE 4096

void err_msg(const char* fmt,...);
void err_cont(int,const char* fmt,...);
void err_ret(const char* fmt,...);
void err_dump(const char* fmt,...) __attribute__((noreturn));
void err_quit(const char* fmt,...) __attribute__((noreturn));
void err_exit(int,const char* fmt,...) __attribute__((noreturn));
void err_sys(const char* fmt,...) __attribute__((noreturn));

#endif
