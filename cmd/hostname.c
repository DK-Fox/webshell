/*
 * @ Description:
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include "build_in.h"

int hostname(int argc,char **argv,Cmd *pcmd){
    if(argc!=1){
        printf("%s\n",pcmd->cmd_usage);
        return -1;
    }

    char h_name[HOST_NAME_MAX];
    if(gethostname(h_name,HOST_NAME_MAX-1)!=0)
        err_sys("gethostname failed");

    printf("%s\n",h_name);

    return 0;
}

Cmd * hostname_init(){
    Cmd *pt=(Cmd *)malloc(sizeof(Cmd));
    pt->cmd_name="hostname";
    pt->cmd_usage="hostname: usage: hostname";
    pt->cmd_func=hostname;
    return pt;
}
