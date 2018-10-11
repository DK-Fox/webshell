/*
 * @ Description:This is the header file requied for the build-in command
 * @ Author:SangYuchen
 * @ Date:2018-10-10
 */
#ifndef __BUILD_IN__
#define __BUILD_IN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "apue_err.h"
#include "general_list.h"

typedef struct cmd{
    char *cmd_name;
    char *cmd_usage;
    int (* cmd_func)(int argc,char **argv,struct cmd * pcmd);
}Cmd;

int cmd_array_register(Array* ap);
Cmd * pwd_init();

#endif
