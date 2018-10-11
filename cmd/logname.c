/*
 * @ Description:
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include "build_in.h"

int logname(int argc,char **argv,Cmd *pcmd){
    if(argc!=1){
        printf("%s\n",pcmd->cmd_usage);
        return -1;
    }

    char * l_name=getlogin();
    if(l_name==NULL)
        err_sys("getlogin failed");

    printf("%s\n",l_name);

    return 0;
}

Cmd * logname_init(){
    Cmd *pt=(Cmd *)malloc(sizeof(Cmd));
    pt->cmd_name="logname";
    pt->cmd_usage="logname: usage: logname";
    pt->cmd_func=logname;
    return pt;
}
