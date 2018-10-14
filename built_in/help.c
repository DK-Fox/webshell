/*
 * @ Description:Realize "help" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-14
 */

#include "built_in.h"

extern Array* cmds;

static int output_usage(ElemType* data);

/*
 * @ Function:Define "help" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_help(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc>1){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //help.
   cmds->traverse_array(cmds,output_usage);

    return 0;
}

/*
 * @ Function:Output command usage.
 * @ Input:data:command information
 * @ Return:success:0
 *          failure:-1
 */
static int output_usage(ElemType* data){
    Cmd*p=(Cmd*)data;
    printf("%s\n",p->cmd_usage);
    return 0;
}

/*
 * @ Function:Initialize "help" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * help_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="help";
    pt->cmd_usage="help: usage: help ";
    pt->cmd_func=sh_help;
    return pt;
}
