/*
 * @ Description:This is the command "sync".
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
    sync();

    exit(0);
}
