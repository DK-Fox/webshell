/*
 * @ Description:Realize "echo" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-13
 */

#include "built_in.h"
#include "main.h"

extern Array* vars;

/*
 * @ Function:Define "echo" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_echo(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc!=2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //Echo.

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
        int i;
        for (i=0;i<vars->len;i++)
            if(!strcmp(((Var*)vars->data[i])->name,&argv[1][1]))
                break;
        if (i==vars->len) {
            printf("\n");
        } else {
            printf("%s\n",((Var*)vars->data[i])->value);
        }

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
 * @ Function:Initialize "echo" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * echo_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="echo";
    pt->cmd_usage="echo: usage: echo [arg ...]";
    pt->cmd_func=sh_echo;
    return pt;
}
