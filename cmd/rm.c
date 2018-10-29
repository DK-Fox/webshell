/*
 * @ Description:This is the command "rm".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"
#include <dirent.h>

static void rm_dir(char *dirname);

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=2)
        err_quit("rm: usage: rm file/dir");

    rm_dir(argv[1]);
    remove(argv[1]);
    exit(0);

}

static void rm_dir(char *dirname){
    DIR *dp;
    struct dirent *dirp;
    struct stat statbuf;
    char path[MAXLINE];
    if((dp=opendir(dirname))==NULL)
        err_sys("can't open %s",dirname);
    while((dirp=readdir(dp))!=NULL){
        if(!strcmp(dirp->d_name,".")||!strcmp(dirp->d_name,".."))
            continue;
        sprintf(path,"%s/%s",dirname,dirp->d_name);
        if(stat(path,&statbuf)<0)
            err_sys("stat failed");
        if(S_ISDIR(statbuf.st_mode)){
            rm_dir(path);
            remove(path);
        }
        else
            remove(path);
    }
}

