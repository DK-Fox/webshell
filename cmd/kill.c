/*
 * @ Description:This is the command "kill".
 * @ Author: SangYuchen
 * @ Date:2018-11-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"
#include <sys/stat.h>
#include <signal.h>
#include <string.h>

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=3)
        err_quit("kill: usage: kill -signo pid");

    if(kill(atol(argv[2]),atoi(&argv[1][1]))<0){
        err_sys("kill failed");
    }

    exit(0);
}

