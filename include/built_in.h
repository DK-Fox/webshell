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
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <sys/stat.h>
#include "apue_err.h"
#include "general_array.h"

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

#endif
