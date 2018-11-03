/*
 * @ Description:This is the command "date".
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
    if(argc!=1)
        err_quit("date: usage: date");

    time_t ptm;
    struct tm* tmz;
    time(&ptm);
    tmz=localtime(&ptm);

    char buf[MAXLINE];
    strftime(buf,MAXLINE,"%a %b %d %T %Z %Y",tmz);
    printf("%s\n",buf);

    exit(0);
}
