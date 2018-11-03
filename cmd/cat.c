/*
 * @ Description:This is the command "cat".
 * @ Author: SangYuchen
 * @ Date:2018-11-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "apue_err.h"
#include <sys/stat.h>

int main(int argc,char *argv[]){
    //Check format.
    if(argc<2)
        err_quit("cat: usage: cat file1 file2 ...");

    int i;
    for (i=1;i<argc;i++){
        if(access(argv[i],F_OK)<0){
            err_sys("access failed");
        }

        struct stat statbuf;
        if(stat(argv[i],&statbuf)<0)
            err_sys("stat failed");
        if(S_ISDIR(statbuf.st_mode)){
            err_quit("%s is a directory",argv[1]);
        }else if(S_ISREG(statbuf.st_mode)){
            FILE * fp;
            if((fp=fopen(argv[i],"r"))==NULL){
                err_sys("fopen failed");
            }
            char buf[MAXLINE];
            while(fgets(buf,MAXLINE,fp)!=NULL){
                if(fputs(buf,stdout)==EOF){
                    fclose(fp);
                    err_sys("fputs failed");
                }
            }
            fclose(fp);
        }
    }

    exit(0);
}

