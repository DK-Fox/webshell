/*
 * @ Description:This is the command "chmod".
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
        err_quit("chmod: usage: chmod [+-][rwx] file");

    struct stat statbuf;

    if(stat(argv[2],&statbuf)<0)
        err_sys("stat error");
    if (argv[1][1]=='+'){
        if(argv[1][2]=='r'){
            if(chmod(argv[2],statbuf.st_mode |S_IRUSR)<0)
                err_sys("chmod error");
        }
        else if(argv[1][2]=='w'){
            if(chmod(argv[2],statbuf.st_mode |S_IWUSR)<0)
                err_sys("chmod error");
        }
        else if(argv[1][2]=='x'){
            if(chmod(argv[2],statbuf.st_mode |S_IXUSR)<0)
                err_sys("chmod error");
        }
        else
            err_quit("chmod: usage: chmod [+-][rwx] file");
    }else if(argv[1][1]=='-'){
        if(argv[1][2]=='r'){
            if(chmod(argv[2],statbuf.st_mode &~S_IRUSR)<0)
                err_sys("chmod error");
        }
        else if(argv[1][2]=='w'){
            if(chmod(argv[2],statbuf.st_mode &~S_IWUSR)<0)
                err_sys("chmod error");
        }
        else if(argv[1][2]=='x'){
            if(chmod(argv[2],statbuf.st_mode &~S_IXUSR)<0)
                err_sys("chmod error");
        }
        else
            err_quit("chmod: usage: chmod [+-][rwx] file");

    }
    exit(0);
}
