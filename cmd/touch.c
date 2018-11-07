/*
 * @ Description:This is the command "touch".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=4)
        err_quit("touch: usage: touch -t YYYYmmddHHMMSS file");

    int fd=-1;
    if(!access(argv[3],F_OK)){
        if((fd=open(argv[3],(O_CREAT|O_RDWR|O_TRUNC)))<0){
            err_sys("open failed");
        }
    }
    close(fd);

    struct stat stat_buf;
    if(stat(argv[3],&stat_buf)<0){
        err_sys("stat failed");
    }

    struct tm tmbuf;
    strptime(argv[2],"%Y%m%d%H%M%S",&tmbuf);
    stat_buf.st_mtime=mktime(&tmbuf);

    exit(0);
}
