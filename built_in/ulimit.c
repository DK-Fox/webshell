/*
 * @ Description:Realize "ulimit" command.
 * @ Author: SangYuchen
 * @ Date:2018-10-14
 */

#include "built_in.h"

static int fill_ulimit(ElemType* data);
static int print_ulimit(ElemType* data);
static int fill_ulimit_array(Array* ulimits);
static Ulimit * create_limit(char opt,char* desc,int source);

/*
 * @ Function:Define "ulimit" command.
 * @ Input:argc:number of parameter
 *         argv:all parameter
 *         pcmd:command information
 * @ Return:success:0
 *          failure:-1
 */
int sh_ulimit(int argc,char **argv,Cmd *pcmd){
    //Check format.
    if(argc!=2){
        err_msg("%s\n",pcmd->cmd_usage);
        return -1;
    }

    Array* ulimits;
    ulimits=create_array(ULIMIT_NUM);
    fill_ulimit_array(ulimits);
    ulimits->traverse_array(ulimits,fill_ulimit);

    //ulimit.
    int c,i;
    while((c=getopt(argc,argv,"atfdscmunlviqe"))!=EOF){
        switch(c){
            case '?':
                err_msg("unrecognized option: -%c",optopt);
                break;
            case 'a':
                ulimits->traverse_array(ulimits,print_ulimit);
                break;
            default:
                for (i = 0; i < ulimits->len && ((Ulimit*)ulimits->data[i])->opt!=c; i++);
                if(i!=ulimits->len){
                    Ulimit* cur_ulimit=(Ulimit*)ulimits->data[i];
                    print_ulimit((ElemType*)cur_ulimit);
                }
                break;
        }
    }

    return 0;
}

/*
 * @ Function:Fill the ulimit struct.
 * @ Input:data:ulimit information.
 * @ Return:success:0
 *          failure:-1
 */
static int fill_ulimit(ElemType* data){
    Ulimit* p=(Ulimit*)data;
    if(getrlimit(p->source,p->rlptr)){
        err_ret("getrlimit failed");
        return -1;
    }
    return 0;
}

/*
 * @ Function:Output limit.
 * @ Input:data:ulimit information.
 * @ Return:success:0
 *          failure:-1
 */
static int print_ulimit(ElemType* data){
    Ulimit*p=(Ulimit*)data;
    char lch[MAXLINE];
    if(p->rlptr->rlim_cur==(rlim_t)(-1))
        sprintf(lch,"%s","unlimited");
    else if(strchr("dsmlv",p->opt))
        sprintf(lch,"%ld",p->rlptr->rlim_cur/1024);
    else
        sprintf(lch,"%ld",p->rlptr->rlim_cur);
    printf("-%c: %-31s %s\n",p->opt,p->desc,lch);
    return 0;
}

/*
 * @ Function:Create a limit.
 * @ Input:opt:option
 *         desc:description
 *         source:getrlimit parameter
 * @ Return:success:limit by created
 *          failure:NULL
 */
static Ulimit * create_limit(char opt,char* desc,int source){
    Ulimit* p;
    if(!(p=(Ulimit*)malloc(sizeof(Ulimit)))){
        err_ret("malloc failed");
        return NULL;
    }
    p->opt=opt;
    p->desc=desc;
    p->source=source;
    if(!(p->rlptr=(struct rlimit*)malloc(sizeof(struct rlimit)))){
        err_ret("malloc failed");
        free(p);
        return NULL;
    }

    return p;
}

/*
 * @ Function:Fill Ulimit array.
 * @ Input:ulimits:ulimit array
 * @ Return:success:0
 *          failure:-1
 */
static int fill_ulimit_array(Array* ulimits){
    ulimits->array_append(ulimits,(ElemType*)create_limit('t',ULIMIT_T,RLIMIT_CPU));
    ulimits->array_append(ulimits,(ElemType*)create_limit('f',ULIMIT_F,RLIMIT_FSIZE));
    ulimits->array_append(ulimits,(ElemType*)create_limit('d',ULIMIT_D,RLIMIT_DATA));
    ulimits->array_append(ulimits,(ElemType*)create_limit('s',ULIMIT_S,RLIMIT_STACK));
    ulimits->array_append(ulimits,(ElemType*)create_limit('c',ULIMIT_C,RLIMIT_CORE));
    ulimits->array_append(ulimits,(ElemType*)create_limit('m',ULIMIT_M,RLIMIT_RSS));
    ulimits->array_append(ulimits,(ElemType*)create_limit('u',ULIMIT_U,RLIMIT_NPROC));
    ulimits->array_append(ulimits,(ElemType*)create_limit('n',ULIMIT_N,RLIMIT_NOFILE));
    ulimits->array_append(ulimits,(ElemType*)create_limit('l',ULIMIT_L,RLIMIT_MEMLOCK));
    ulimits->array_append(ulimits,(ElemType*)create_limit('v',ULIMIT_V,RLIMIT_AS));
    ulimits->array_append(ulimits,(ElemType*)create_limit('i',ULIMIT_I,RLIMIT_SIGPENDING));
    ulimits->array_append(ulimits,(ElemType*)create_limit('q',ULIMIT_Q,RLIMIT_MSGQUEUE));
    ulimits->array_append(ulimits,(ElemType*)create_limit('e',ULIMIT_E,RLIMIT_NICE));

    return 0;
}

/*
 * @ Function:Initialize "ulimit" command.
 * @ return:success:command information after initializing
 *          failure:NULL
 */
Cmd * ulimit_init(){
    Cmd *pt;
    if(!(pt=(Cmd *)malloc(sizeof(Cmd)))){
        err_ret("malloc failed");
        return NULL;
    }
    pt->cmd_name="ulimit";
    pt->cmd_usage="ulimit: usage: ulimit [-atfdscmunlviqe]";
    pt->cmd_func=sh_ulimit;
    return pt;
}
