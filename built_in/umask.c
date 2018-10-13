/*
 * @ Description:Realize "umask" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"

#define TO_NUM(x) ((x)-48)

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
    char usr_m,grp_m,oth_m;
    int flag=0;

    //Check format.
    if(argc>2)
        flag=1;
    else if(argc==2){
        if(strlen(argv[1])!=3)
            flag=1;
        else{
            sscanf(argv[1],"%c%c%c",&usr_m,&grp_m,&oth_m);
            if(!(isdigit(usr_m)&&isdigit(grp_m)&&isdigit(oth_m)))
                flag=1;
        }
    }
    if(flag==1){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //umask.
    if(argc==1){
        umask_mode=umask(umask_mode);
        printf("%04o\n",umask_mode);
    }else{
        umask_mode=TO_NUM(usr_m)<<6|TO_NUM(grp_m)<<3|TO_NUM(oth_m);
        umask(umask_mode);
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
