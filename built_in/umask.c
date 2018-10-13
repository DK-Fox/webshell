/*
 * @ Description:Realize "umask" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"
extern mode_t umask_mode;

/*
 * @ Function:Define "umask" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_umask(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc>2){
        printf("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //umask.
    if(argc==1){
        umask_mode=umask(umask_mode);
        printf("%04o\n",umask_mode);
    }else{
        ;
    }

    return 0;
}

/*
 * @ Function:Initialize "umask" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * umask_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="umask";
    pt->cmd_usage="umask: usage: umask [mode]";
    pt->cmd_func=sh_umask;
    return pt;
}
