/*
 * @ Description:This is the command "logname"
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"

int main(int argc,char **argv){
    //Check format.
    if(argc!=1)
        err_quit("logname: usage: logname\n");

    //Get login name.
    char * l_name=getlogin();
    if(l_name==NULL)
        err_sys("getlogin failed");
    printf("%s\n",l_name);

    exit(0);
}

