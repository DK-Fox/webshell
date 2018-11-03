/*
 * @ Description:This is the command "basename".
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
    if(argc!=2)
        err_quit("basename: usage: basename pathname");

    char *ch;
    if ((ch = strrchr(argv[1],'/'))!=NULL) {
        printf("%s\n",ch+1);
    }else{
        printf("%s\n",argv[1]);
    }

    exit(0);
}

