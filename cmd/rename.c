/*
 * @ Description:This is the command "rename".
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
    if(argc!=3)
        err_quit("rename: usage: rename oldname newname");

    if(rename(argv[1],argv[2])<0)
        err_sys("rename failed");

    exit(0);
}
