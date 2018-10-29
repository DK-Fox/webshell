/*
 * @ Description:This is the command "mkdir".
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
    if(argc!=2&&argc!=3)
        err_quit("mkdir: usage: mkdir [-p] dir");

    //makdir dir
    if(argc==2){
        if(mkdir(argv[1],S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH))
            err_sys("mkdir failed");
        exit(0);
    }

    //mkdir -p dir
    if(argc==3&&strcmp(argv[1],"-p")==0){
        if(mkdir(argv[2],S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH))
            err_sys("mkdir failed");
        exit(0);

    }else{
        err_quit("mkdri :usage: mkdir [-p] dir");
    }
}
