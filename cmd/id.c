/*
 * @ Description:This is the command "id".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=2)
        err_quit("id: usage: id username");

    struct passwd* pw;
    struct group* pg;

    pw=getpwnam(argv[1]);
    pg=getgrgid(pw->pw_gid);


    exit(0);
}
