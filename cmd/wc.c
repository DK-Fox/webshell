/*
 * @ Description:This is the command "wc".
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
    if(argc!=3||argv[1][1]!='l')
        err_quit("wc: usage: wc -l file");

    //verify it is a regular file.
    struct stat statbuf;
    if(stat(argv[2],&statbuf)<0)
        err_sys("stat failed");
    if(!S_ISREG(statbuf.st_mode)){
        err_quit("file is not a regular file");
    }

    //calculate line number.
    FILE * fp;
    if((fp=fopen(argv[2],"r"))==NULL){
        err_sys("fopen failed");
    }
    char buf[MAXLINE];
    int cnt=0;
    memset(buf,0,MAXLINE);
    while(fgets(buf, MAXLINE-1, fp)!=NULL){
        if(strchr(buf,'\n')!=NULL){
            cnt++;
        }
    }
    if(ferror(fp)){
        fclose(fp);
        err_sys("ferror");
    }

    printf("%d\t%s\n",cnt,argv[2]);

    fclose(fp);

    exit(0);
}

