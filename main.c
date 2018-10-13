/*
 * @ Description:This is the main program of shell.It can initialize commands, output prompts, and read commands, with built-in commands or external commands to parse.
 * @ Author:SangYuchen
 * @ Date:2018-10-09
 */

#include "main.h"

static int print_pr();
static int readline(PArgc *argc,PArgv * argv);
static int parse_command(Array* cmds,int argc,char **argv);
static int cmd_array_init(Array** ap);

//BUF for reading commands.
char line_buf[MAXLINE];
//Umask
mode_t umask_mode=DEFAULT_UMASK;

int main(){
    PArgc* pargc=(PArgc*)malloc(sizeof(PArgc));
    PArgv* pargv=(PArgv*)malloc(sizeof(PArgv));
    Array* cmds;

    //Initialize umask
    umask(umask_mode);
    //Initialize command array.
    cmd_array_init(&cmds);
    while(1){
        do
            //Output prompt.
            print_pr();
        //Read a line.
        while(readline(pargc,pargv)==-1);
        //Parse built-in commands.
        parse_command(cmds,*pargc,*pargv);
        //Parsing external commands.
        //external_cmd();
    }
}

/*
 * @ Function:Print prompt.
 * @ Return:success:0
 *          failure:-1
 */
static int print_pr(){
    //Get host name.
    char hostname[HOST_NAME_MAX];
    if(gethostname(hostname,HOST_NAME_MAX-1))
        err_sys("gethostname failed");

    //Get login name.
    char * logname;
    if(!(logname=getlogin()))
        err_sys("getlogin failed");

    //Get the current path.
    char * path;
    if(!(path=getcwd(NULL,0)))
        err_sys("getcwd failed");

    //Get user information.
    struct passwd* p_passwd;
    if(!(p_passwd=getpwnam(logname)))
        err_ret("getpwnam failed");

    //Replace home dir as "~".
    char chpath[MAXLINE];
    if(strstr(path,p_passwd->pw_dir)){
        sprintf(chpath,"~%s",path+strlen(p_passwd->pw_dir));
    }else
        sprintf(chpath,"%s",path);

    //Output prompt.
    printf(F_L_RED"%s@%s"F_WHITE":"F_L_BLUE"%s"F_WHITE"$ ",logname,hostname,chpath);

    return 0;
}

/*
 * @ Function:Read a line and parse the line as "argc","argv".
 * @ Output:argc:number of parameter
 *          argv:all parameter
 * @ Return:success:0
 *          failure:-1
 */
static int readline(PArgc *argc,PArgv * argv){
    //Read a line.
    fgets(line_buf, MAXLINE, stdin);
    //If only enter, return to -1.
    if(line_buf[0]=='\n')
        return -1;
    //Deal with the end of '\n'.
    int length=strlen(line_buf);
    line_buf[length-1]='\0';

    int cnt=0;
    for(int i=0;i<length-1;i++){
        //Deal with quote.
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

        //Split strings.
        if(line_buf[i]==' '||line_buf[i]=='\t')
            line_buf[i]='\0';
        if(line_buf[i-1]=='\0' && line_buf[i]!=' ' && line_buf[i]!='\t')
            cnt++;
    }

    //Convert to 'argc','argv'.
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

/*
 * @ Function:Parse built-in commands.
 * @ Input:cmds:command array
 *         argc:number of parameter
 *         argv:all parameter
 * @ Return:success:0
 *          failure:-1
 */
static int parse_command(Array* cmds,int argc,char **argv){
    int i;
    //Traverse built-in command.
    for (i = 0; i < cmds->len && strcmp(((Cmd*)cmds->data[i])->cmd_name,argv[0]); i++);
    if(i!=cmds->len){
        Cmd* cur_cmd=(Cmd*)cmds->data[i];
        cur_cmd->cmd_func(argc,argv,cur_cmd);
    }

    return 0;
}

/*
 * @ Function:Initialize command array.
 * @ Output:ap:command array after initializing
 * @ Return:success:0
 *          failure:-1
 */
static int cmd_array_init(Array** ap){
    //Create command array.
    if (!(*ap=create_array(CMD_NUM)))
        err_quit("create_array failed");

    //Register commands.
    cmd_array_register(*ap);

    return 0;
}
