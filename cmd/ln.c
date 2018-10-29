/*
 * @ Description:This is the command "ln".
 * @ Author: SangYuchen
 * @ Date:2018-10-29
 */
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=4)
        err_quit("ln: usage: ln -s sourcefile symlinkfile");

    if(symlink(argv[2],argv[3])<0)
        err_sys("symlink failed");

    exit(0);
}
