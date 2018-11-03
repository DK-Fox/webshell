/*
 * @ Description:This is the command "uname".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=1)
        err_quit("uname: usage: uname");

    struct utsname* puname;
    if((puname=(struct utsname*)malloc(sizeof(struct utsname)))==NULL){
        err_sys("malloc failed");
    }

    if(uname(puname)<0){
        err_sys("uname failed");
    }

    printf("%s %s %s %s %s\n",puname->sysname,puname->nodename,puname->release,puname->version,puname->machine);

    exit(0);
}
