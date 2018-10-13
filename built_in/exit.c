/*
 * @ Description:Realize "exit" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"

/*
 * @ Function:Define "exit" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_exit(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc>2||(argc==2&&!isdigit(argv[1][0]))){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //exit.
    int status=0;
    if(argc==2)
        status=atoi(argv[1]);
    exit(status);
}

/*
 * @ Function:Initialize "exit" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * exit_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="exit";
    pt->cmd_usage="exit: usage: exit [n]";
    pt->cmd_func=sh_exit;
    return pt;
}
