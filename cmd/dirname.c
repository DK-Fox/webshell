/*
 * @ Description:This is the command "dirname".
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
        err_quit("dirname: usage: dirname pathname");

    char *ch;
    if ((ch = strrchr(argv[1],'/'))!=NULL) {
        *ch='\0';
        printf("%s\n",argv[0]);
    }else{
        printf("%s\n",argv[1]);
    }

    exit(0);
}

