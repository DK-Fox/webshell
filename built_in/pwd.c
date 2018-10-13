/*
 * @ Description:Realize "pwd" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include "built_in.h"

/*
 * @ Function:Define "pwd" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_pwd(int argc,char **argv,Cmd *pcmd){
    //Check.
    if(argc!=1){
        printf("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //Get the current path.
    char *path=getcwd(NULL,0);
    if(path==NULL){
        err_ret("getcwd failed");
        return -1;
    }
    printf("%s\n",path);

    return 0;
}

/*
 * @ Function:Initialize "pwd" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * pwd_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="pwd";
    pt->cmd_usage="pwd: usage: pwd";
    pt->cmd_func=sh_pwd;
    return pt;
}
