/*
 * @ Description:Realize "cd" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"

//Environment.
extern char env_pwd[MAXLINE];
extern char env_oldpwd[MAXLINE];

/*
 * @ Function:Define "cd" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_cd(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc>2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //cd.
    if(chdir(argv[1])){
        err_ret("chdir failed");
        return -1;
    }

    //Update environment.

    //Env:OLDPWD
    char *env;
    if(!(env=getenv("PWD"))){
        err_ret("getenv failed:PWD");
        return -1;
    }
    sprintf(env_oldpwd,"OLDPWD=%s",env);
    if(putenv(env_oldpwd)){
        err_ret("putenv failed:OLDPWD");
        return -1;
    }

    //Env:PWD
    char *cur_pwd=getcwd(NULL,0);
    sprintf(env_pwd,"PWD=%s",cur_pwd);
    if(putenv(env_pwd)){
        err_ret("putenv failed:PWD");
        return -1;
    }

    return 0;
}

/*
 * @ Function:Initialize "cd" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * cd_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="cd";
    pt->cmd_usage="cd: usage: cd [dir]";
    pt->cmd_func=sh_cd;
    return pt;
}
