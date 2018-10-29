/*
 * @ Description:This is the command "rmdir".
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
    if(argc!=2)
        err_quit("rmdir: usage: rmdir dir");

    if(rmdir(argv[1])<0)
        err_sys("rmdir failed");

    exit(0);
}
