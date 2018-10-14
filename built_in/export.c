/*
 * @ Description:Realize "export" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"

/*
 * @ Function:Define "export" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_export(int argc,char **argv,Cmd *pcmd){
    char *ch;

    //Check format.
    if(argc!=2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //export.
    char *new_env;
    if(!(new_env=(char*)malloc(MAXLINE))){
        err_ret("malloc failed");
        return -1;
    }

    //None value.
    if(!(ch=strchr(argv[1],'=')))
        sprintf(new_env,"%s=",argv[1]);
    else{
        //Convert quote.
        if(*(ch+1)=='\"'||*(ch+1)=='\''){
            if(*(ch+1)=='\"'&&argv[1][strlen(argv[1])-1]=='\"')
                argv[1][strlen(argv[1])-1]='\0';
            if(*(ch+1)=='\''&&argv[1][strlen(argv[1])-1]=='\'')
                argv[1][strlen(argv[1])-1]='\0';
            *(ch+1)='\0';
            sprintf(new_env,"%s%s",argv[1],ch+2);
        }else
            sprintf(new_env,"%s",argv[1]);
    }

    //Update environment.
    if(putenv(new_env)){
        err_ret("putenv failed:new_env");
        free(new_env);
        return -1;
    }

    return 0;
}

/*
 * @ Function:Initialize "export" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * export_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="export";
    pt->cmd_usage="export: usage: export [name[=value] ...]";
    pt->cmd_func=sh_export;
    return pt;
}
