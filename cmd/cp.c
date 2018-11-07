/*
 * @ Description:This is the command "cp".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=3)
        err_quit("cp: usage: cp pathname1 pathname2");

    FILE *fp1,*fp2;
    if((fp1=fopen(argv[1],"rb"))==NULL)
        err_sys("fopen failed");
    if((fp2=fopen(argv[2],"wb"))==NULL){
        fclose(fp1);
        err_sys("fopen failed");
    }
    char buf[MAXLINE];
    int cnt;
    while((cnt=fread(buf,1,MAXLINE,fp1))==MAXLINE){
        if(fwrite(buf,1,cnt,fp2)!=cnt){
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
    }else{
        if(fwrite(buf,1,cnt,fp2)!=cnt){
            fclose(fp1);
            fclose(fp2);
            if(access(argv[2],F_OK))
                remove(argv[2]);
            err_sys("fputs failed");
        }
    }
    fclose(fp1);
    fclose(fp2);

    exit(0);
}

