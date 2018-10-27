/*
 * @ Description:This is the header file of main.c
 * @ Author:Sangyuchen
 * @ Date:2018-10-10
 */

#ifndef __MAIN__
#define __MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "built_in.h"
#include "apue_err.h"
#include "general_array.h"

#define MAXLINE 4096 //Max size of a line
#define CMD_NUM 256 //Number of built-in commands
#define DEFAULT_UMASK (S_IWGRP|S_IWOTH)//Default umask
#define CMD_DIR "/home/dkfox/code/webshell/bin/" //External command dir

//Color of front
#define F_L_RED "\033[1;31m" //Light red
#define F_WHITE "\033[0;37m" //white
#define F_L_BLUE "\033[1;34m" //Light blue

typedef int PArgc;
typedef char** PArgv;

//Variable
typedef struct{
    char *name;
    char *value;
}Var;

//Alias
typedef struct{
    char *name;
    char *value;
}Alias;

#endif
