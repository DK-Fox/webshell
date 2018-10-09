/*
 * ******************************************************
 * @ Filename:main.c
 * @ Author:syc
 * @ Description:This is the main program of the shell
 * ******************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include "build_in.h"
#include "apue_err.h"

int main(){
    printf("start...\n");

   // char line_buf[MAX_SIZE];
    //while(1){
        print_pr();
        //readline();
        //parse_command();
        //external_cmd();
    //}
    exit(0);
}
/*
 * Print prompt.
 */
void print_pr(){
    char hostname[HOST_NAME_MAX];
    gethostname(hostname,HOST_NAME_MAX-1);

    char * logname=getlogin();
    char * path=getcwd(NULL,0);
    printf("%s@%s:%s$ ",logname,hostname,path);

}


