/*
 * @ Description:This is the header file requied for the built-in command
 * @ Author:SangYuchen
 * @ Date:2018-10-10
 */
#ifndef __BUILT_IN__
#define __BUILT_IN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include "apue_err.h"
#include "general_array.h"

//Command information.
typedef struct cmd{
    char *cmd_name;//Command name
    char *cmd_usage;//Command usage
    int (* cmd_func)(int argc,char **argv,struct cmd * pcmd);//Command function
}Cmd;

int cmd_array_register(Array* ap);

//Commands initization
Cmd * pwd_init();
Cmd * exit_init();
Cmd * cd_init();
Cmd * umask_init();
Cmd * help_init();
Cmd * ulimit_init();
Cmd * echo_init();
Cmd * export_init();
Cmd * set_init();
Cmd * unset_init();
Cmd * alias_init();
Cmd * unalias_init();

//ulimit information.
typedef struct ulimit{
    char opt;
    char * desc;
    int source;
    struct rlimit *rlptr;
}Ulimit;

#define ULIMIT_NUM 16
#define ULIMIT_T "cpu time (second)"
#define ULIMIT_F "file size (blocks)"
#define ULIMIT_D "data seg size (kbytes)"
#define ULIMIT_S "stack size (kbytes)"
#define ULIMIT_C "core file size (blocks)"
#define ULIMIT_M "resident set size (kbytes)"
#define ULIMIT_U "processes"
#define ULIMIT_N "file descriptors"
#define ULIMIT_L "locked-in-memory size (kbytes)"
#define ULIMIT_V "address space (kbytes)"
#define ULIMIT_X "file locks"
#define ULIMIT_I "pending signals"
#define ULIMIT_Q "bytes in POSIX msg queues"
#define ULIMIT_E "max nice"
#define ULIMIT_R "max rt priority"

#endif
