/*
 * @ Description:This is the command "mkdir".
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"

int main(int argc,char *argv[]){
    //Check format.
    if(argc!=2&&argc!=3)
        err_quit("mkdir: usage: mkdir [-p] dir");

    //makdir dir
    char *ch,*env;
    if(argc==2){
        if((ch=strrchr(argv[1],'/'))){
            *ch='\0';
            if()
        }
        if()
        exit(0;)
    }

    //mkdir -p dir
    int c,i;
    while((c=getopt(argc,argv,"p:"))!=EOF){
        switch(c){
            case '?':
                err_msg("unrecognized option: -%c",optopt);
                err_quit("mkdir: usage: mkdir [-p] dir");
                break;
            case 'p':
                ulimits->traverse_array(ulimits,print_ulimit);
                break;
        }
    }

    exit(0);
}
