/*
 * @ Description:This is the command "hostname".
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=1)
        err_quit("hostname: usage: hostnam");

    //Get hostname.
    char h_name[HOST_NAME_MAX];
    if(gethostname(h_name,HOST_NAME_MAX-1)!=0)
        err_sys("gethostname failed");
    printf("%s\n",h_name);

    exit(0);
}
