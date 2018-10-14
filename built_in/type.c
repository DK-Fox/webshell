/*
 * @ Description:Realize "type" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"

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

    //Quote.
    if(argv[1][0]=='\"'||argv[1][0]=='\''){
        if(argv[1][0]=='\"'&&argv[1][strlen(argv[1])-1]=='\"')
            argv[1][strlen(argv[1])-1]='\0';
        if(argv[1][0]=='\''&&argv[1][strlen(argv[1])-1]=='\'')
            argv[1][strlen(argv[1])-1]='\0';
        printf("%s\n",&argv[1][1]);
        return 0;
    }

    //Variable
    char * var;
    if(argv[1][0]=='$'){
        //In variable.
        ;

        //In environment.
        if((var=getenv(&argv[1][1]))){
            printf("%s\n",var);
            return 0;
        }
    }

    printf("%s\n",argv[1]);

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
