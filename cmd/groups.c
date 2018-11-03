/*
 * @ Description:This is the command "groups".
 * @ Author: SangYuchen
 * @ Date:2018-10-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <sys/types.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=1)
        err_quit("groups: usage: groups");

    gid_t *gl;
    struct group* pg;
    int size;
    if((size=getgroups(0,NULL))<0)
        err_sys("getgroups failed");

    gl=(gid_t*)malloc(size);
    getgroups(size,gl);
    for (int i=0;i<size;i++){
        pg=getgrgid(gl[i]);
        printf("%s ",pg->gr_name);
    }
    printf("\n");
    free(gl);

    exit(0);
}
