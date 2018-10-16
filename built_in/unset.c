/*
 * @ Description:Realize "unset" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"
#include "main.h"

extern Array* vars;

/*
 * @ Function:Define "unset" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_unset(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc!=2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //unset.
    unsetenv(argv[1]);
    int i;
    for (i=0;i<vars->len;i++)
        if(!strcmp(((Var*)vars->data[i])->name,argv[1]))
            break;
    if(i!=vars->len)
        vars->array_delete(vars,i);

    return 0;
}

/*
 * @ Function:Initialize "unset" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * unset_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="unset";
    pt->cmd_usage="unset: usage: unset name ";
    pt->cmd_func=sh_unset;
    return pt;
}
