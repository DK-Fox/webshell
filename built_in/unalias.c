/*
 * @ Description:Realize "unalias" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"
#include "main.h"

extern Array* aliases;

/*
 * @ Function:Define "unalias" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_unalias(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc!=2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //unalias.
    int i;
    for (i=0;i<aliases->len;i++)
        if(!strcmp(((Alias*)aliases->data[i])->name,argv[1]))
            break;
    if(i!=aliases->len)
        aliases->array_delete(aliases,i);

    return 0;
}

/*
 * @ Function:Initialize "unalias" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * unalias_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="unalias";
    pt->cmd_usage="unalias: usage: unalias name ";
    pt->cmd_func=sh_unalias;
    return pt;
}
