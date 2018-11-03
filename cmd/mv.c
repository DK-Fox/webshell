/*
 * @ Description:This is the command "mv".
 * @ Author: SangYuchen
 * @ Date:2018-11-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=3)
        err_quit("mv: usage: mv pathname1 pathname2");

    FILE *fp1,*fp2;
    if((fp1=fopen(argv[1],"rb"))==NULL)
        err_sys("fopen failed");
    if((fp2=fopen(argv[2],"wb"))==NULL){
        fclose(fp1);
        err_sys("fopen failed");
    }
    char buf[MAXLINE];
    while(fgets(buf,MAXLINE,fp1)!=NULL){
        if(fputs(buf,fp2)==EOF){
            fclose(fp1);
            fclose(fp2);
            if(access(argv[2],F_OK))
                remove(argv[2]);
            err_sys("fputs failed");
        }
    }

    if(ferror(fp1)){
        if(access(argv[2],F_OK))
            remove(argv[2]);
        err_ret("ferror");
    }
    fclose(fp1);
    fclose(fp2);

    remove(argv[1]);

    exit(0);
}

