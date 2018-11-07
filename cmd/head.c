/*
 * @ Description:This is the command "head".
 * @ Author: SangYuchen
 * @ Date:2018-11-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "apue_err.h"
#include <sys/stat.h>

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=4)
        err_quit("head: usage: head -n num file");

    //verify it is a regular file.
    struct stat statbuf;
    if(stat(argv[3],&statbuf)<0)
        err_sys("stat failed");
    if(!S_ISREG(statbuf.st_mode)){
        err_quit("file is not a regular file ");
    }

    //read some lines.
    FILE * fp;
    if((fp=fopen(argv[3],"r"))==NULL){
        err_sys("fopen failed");
    }
    char buf[MAXLINE];
    for(int i=0;i<atoi(argv[2]);i++){
        if(fgets(buf, MAXLINE, fp)==NULL){
            if(ferror(fp)){
                fclose(fp);
                err_sys("ferror");
            }
        }
        if(fputs(buf,stdout)==EOF){
            fclose(fp);
            err_sys("fputs failed");
        }
    }
    fflush(stdout);
    fclose(fp);

    exit(0);
}

