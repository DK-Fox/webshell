/*
 * @ Description:Realize "set" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-14
 */

#include "built_in.h"
#include "main.h"

extern Array* vars;

static int create_variable(char *name,char* value);
static int print_var(ElemType* data);

/*
 * @ Function:Define "set" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_set(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc!=1){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //Set
    if(!strcmp(argv[0],"set")){
        //Print envionment.
        ;

        //Print variable.
        vars->traverse_array(vars,print_var);

        return 0;
    }

    char * ch=strchr(argv[0],'=');
    //Add variable.
    if(*(ch+1)=='\"'||*(ch+1)=='\''){
        if(*(ch+1)=='\"'&&argv[0][strlen(argv[0])-1]=='\"')
            argv[0][strlen(argv[0])-1]='\0';
        if(*(ch+1)=='\''&&argv[0][strlen(argv[0])-1]=='\'')
            argv[0][strlen(argv[0])-1]='\0';
        *(ch+1)='\0';
        *ch='\0';
        create_variable(argv[0],ch+2);
    }else{
        *ch='\0';
        create_variable(argv[0],ch+1);
    }

    return 0;
}

/*
 * @ Function:Output variable.
 * @ Input:data:variable information.
 * @ Return:success:0
 *          failure:-1
 */
static int print_var(ElemType* data){
    Var*p=(Var*)data;
    printf("%s=%s\n",p->name,p->value);
    return 0;
}

/*
 * @ Function:Create a var.
 * @ Input:name:variable name
 *         value:variable value
 * @ Return:success:0
 *          failure:-1
 */
static int create_variable(char *name,char* value){
    //Create a variable.
    Var* p;
    if(!(p=(Var*)malloc(sizeof(Var)))){
        err_ret("malloc failed");
        return -1;
    }
    if(!(p->name=(char*)malloc(strlen(name)+1))){
        err_ret("malloc failed");
        free(p);
        return -1;
    }
    if(!(p->value=(char*)malloc(strlen(value)+1))){
        err_ret("malloc failed");
        free(p->name);
        free(p);
        return -1;
    }
    memcpy(p->name,name,strlen(name)+1);
    memcpy(p->value,value,strlen(value)+1);

    //Add a variable.
    vars->array_append(vars,(ElemType*)p);

    return 0;
}

/*
 * @ Function:Initialize "set" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * set_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="set";
    pt->cmd_usage="set: usage: set ";
    pt->cmd_func=sh_set;
    return pt;
}
