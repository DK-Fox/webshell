/*
 * @ Description:This is the main program of the shell
 * @ Author:SangYuchen
 * @ Date:2018-10-09
 */

#include "main.h"

static int print_pr();
static int readline(PArgc *argc,PArgv * argv);
static int parse_command(Array* cmds,int argc,char **argv);
static int cmd_array_init(Array** ap);

char line_buf[MAXLINE];

int main(){
    PArgc* pargc=(PArgc*)malloc(sizeof(PArgc));
    PArgv* pargv=(PArgv*)malloc(sizeof(PArgv));
    Array* cmds;
    cmd_array_init(&cmds);
    while(1){
        do
            print_pr();
        while(readline(pargc,pargv)==-1);
        parse_command(cmds,*pargc,*pargv);
        //external_cmd();
    }
    exit(0);
}

/*
 * Print prompt.
 */
static int print_pr(){
    char hostname[HOST_NAME_MAX];
    if(gethostname(hostname,HOST_NAME_MAX-1)!=0)
        err_sys("gethostname failed");

    char * logname=getlogin();
    if(logname==NULL)
        err_sys("getlogin failed");

    char * path=getcwd(NULL,0);
    if(path==NULL)
        err_sys("getcwd failed");

    printf("%s@%s:%s$ ",logname,hostname,path);
    return 0;
}

static int readline(PArgc *argc,PArgv * argv){
    fgets(line_buf, MAXLINE, stdin);
    if(line_buf[0]=='\n')
        return -1;
    int length=strlen(line_buf);
    line_buf[length-1]='\0';
    int cnt=0;
    for(int i=0;i<length-1;i++){
        if(strchr("\"\'",line_buf[i])!=NULL && line_buf[i-1]!='\\'){
            char *pch=NULL;
            while((pch=strchr(&line_buf[i+1],line_buf[i]))!=NULL && *(pch-1)=='\\');
            if(pch==NULL){
                return -1;
            }else{
                i+=pch-&line_buf[i];
                cnt++;
                continue;
            }
        }

        if(line_buf[i]==' '||line_buf[i]=='\t')
            line_buf[i]='\0';

        if(line_buf[i-1]=='\0' && line_buf[i]!=' ' && line_buf[i]!='\t')
            cnt++;
    }
    *argc=cnt;
    *argv=(PArgv)malloc(cnt*sizeof(*argv));
    cnt=0;
    for(int i=0;i<length;i++){
        if(line_buf[i]!='\0' && line_buf[i-1]=='\0'){
            (*argv)[cnt++]=&line_buf[i];
        }
    }
    return 0;
}

static int parse_command(Array* cmds,int argc,char **argv){
    int i;
    for (i = 0; i < cmds->len && strcmp(((Cmd*)cmds->data[i])->cmd_name,argv[0]); i++);
    if(i!=cmds->len){
        Cmd* cur_cmd=(Cmd*)cmds->data[i];
        cur_cmd->cmd_func(argc,argv,cur_cmd);
    }

    if(!strcmp(argv[0],"exit"))
        exit(0);

    return 0;
}

static int cmd_array_init(Array** ap){
    if (!(*ap=create_array(CMD_NUM)))
        err_quit("create_array failed");
    cmd_array_register(*ap);
    return 0;
}
