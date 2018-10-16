/*
 * @ Description:Realize "alias" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-14
 */

#include "built_in.h"
#include "main.h"

extern Array* aliases;

static int create_alias(char *name,char* value);
static int print_alias(ElemType* data);
static int set_alias(char *name,char* value);

/*
 * @ Function:Define "alias" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_alias(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc>2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //alias
    if(argc==1){
        //Print alias.
        aliases->traverse_array(aliases,print_alias);

        return 0;
    }

    //Format
    char * ch;
    if(!(ch=strchr(argv[1],'='))){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    //Add alias.
    *ch='\0';
    set_alias(argv[1],ch+1);

    return 0;
}

/*
 * @ Function:Set a alias.
 * @ Input:name:alias name.
 *         value:alias value.
 * @ Return:success:0
 *          failure:-1
 */
static int set_alias(char *name,char* value){
    //Search for repeating alias.
    int i;
    for (i=0;i<aliases->len;i++)
        if(!strcmp(((Alias*)aliases->data[i])->name,name))
            break;

    //Create a new alias or update old alias.
    if(i==aliases->len)
        create_alias(name,value);
    else{
        Alias *alias=(Alias*)*aliases->get_addr(aliases,i);
        free(alias->value);
        alias->value=(char*)malloc(strlen(value)+1);
        strcpy(alias->value,value);
    }

    return 0;
}

/*
 * @ Function:Output alias.
 * @ Input:data:alias information.
 * @ Return:success:0
 *          failure:-1
 */
static int print_alias(ElemType* data){
    Alias*p=(Alias*)data;
    printf("%s=%s\n",p->name,p->value);
    return 0;
}

/*
 * @ Function:Create a alias.
 * @ Input:name:alias name
 *         value:alias value
 * @ Return:success:0
 *          failure:-1
 */
static int create_alias(char *name,char* value){
    //Create a alias.
    Alias* p;
    if(!(p=(Alias*)malloc(sizeof(Alias)))){
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

    //Add a alias.
    aliases->array_append(aliases,(ElemType*)p);

    return 0;
}

/*
 * @ Function:Initialize "alias" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * alias_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="alias";
    pt->cmd_usage="alias: usage: alias [name = value]";
    pt->cmd_func=sh_alias;
    return pt;
}
