/*
 * @ Description:
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include "build_in.h"

int pwd(int argc,char **argv,Cmd *pcmd){
    if(argc!=1){
        printf("%s\n",pcmd->cmd_usage);
        return -1;
    }
    char *path=getcwd(NULL,0);
    if(path==NULL)
        err_ret("getcwd faild");

    printf("%s\n",path);

    return 0;
}

Cmd * pwd_init(){
    Cmd *pt=(Cmd *)malloc(sizeof(Cmd));
    pt->cmd_name="pwd";
    pt->cmd_usage="pwd: usage: pwd";
    pt->cmd_func=pwd;
    return pt;
}
