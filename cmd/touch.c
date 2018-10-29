/*
 * @ Description:This is the command "touch".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=4)
        err_quit("touch: usage: touch -t sourcefile symlinkfile");

    if(symlink(argv[2],argv[3])<0)
        err_sys("symlink failed");

    exit(0);
}
