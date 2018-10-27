/*
 * @ Description:Realize "type" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"
#include "main.h"

extern Array* aliases;
extern Array* cmds;

/*
 * @ Function:Define "type" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_type(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc!=2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //type.
    //In alias.
    int i;
    for (i=0;i<aliases->len;i++)
        if(!strcmp(((Alias*)aliases->data[i])->name,argv[1]))
            break;
    if (i!=aliases->len){
        printf("%s is an alias for %s\n",argv[1],((Alias*)aliases->data[i])->value);
        return 0;
    }

    //In cmds.
    for (i = 0; i < cmds->len && strcmp(((Cmd*)cmds->data[i])->cmd_name,argv[1]); i++);
    if(i!=cmds->len){
        printf("%s is a shell builtin\n",argv[1]);
        return 0;
    }

    //In external cmds.
    char path[MAXLINE];
    sprintf(path,CMD_DIR"%s",argv[1]);
    if(!access(path,F_OK)){
        printf("%s is %s\n",argv[1],path);
        return 0;
    }else{
        printf("Command not found\n");
    }
    return 0;
}

/*
 * @ Function:Initialize "type" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * type_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="type";
    pt->cmd_usage="type: usage: type name";
    pt->cmd_func=sh_type;
    return pt;
}
