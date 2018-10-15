/*
 * @ Description:This is the main program of shell.It can initialize commands, output prompts, and read commands, with built-in commands or external commands to parse.
 * @ Author:SangYuchen
 * @ Date:2018-10-09
 */

#include "main.h"

static int print_pr();
static int readline(PArgc *argc,PArgv * argv);
static int parse_command(Array* cmds,int argc,char **argv);
static int cmd_array_init();
static int external_cmd(int argc,char **argv);
static int user_init();
static int env_init();
static int alias_array_init();
static int var_array_init();

//BUF for reading commands.
char line_buf[MAXLINE];
//Status from executing external command.($?)
int g_status;
//Umask
mode_t umask_mode=DEFAULT_UMASK;
//Command array.
Array* cmds;
//Variable array.
Array* vars;
//Alias array.
Array* aliases;
//Env
char env_hostname[MAXLINE];
char env_pwd[MAXLINE];
char env_home[MAXLINE];
char env_oldpwd[MAXLINE];
char env_username[MAXLINE];

int main(){
    PArgc* pargc=(PArgc*)malloc(sizeof(PArgc));
    PArgv* pargv=(PArgv*)malloc(sizeof(PArgv));

    //Initialize environment.
    env_init();

    //Initialize user informationi.
    user_init();

    //Initialize command array.
    cmd_array_init();

    //Initialize variable array.
    var_array_init();

    //Initialize alias array.
    alias_array_init();
    while(1){
        do
            //Output prompt.
            print_pr();
        //Read a line.
        while(readline(pargc,pargv)==-1);

        //Parse built-in commands.
        if(!parse_command(cmds,*pargc,*pargv))
            continue;

        //Parsing external commands.
        if(external_cmd(*pargc,*pargv)==1)
            err_msg("Command not found");
    }
}

/*
 * @ Function:Print prompt.
 * @ Return:success:0
 *          failure:-1
 */
static int print_pr(){
    //Get hostname;
    char * hostname;
    if(!(hostname=getenv("HOSTNAME")))
        err_sys("getenv failed:HOSTNAME");

    //Get login name.
    char * logname;
    if(!(logname=getenv("USERNAME")))
        err_sys("getenv failed:USERNAME");

    //Get the current path.
    char * path;
    if(!(path=getenv("PWD")))
        err_sys("getenv failed:PWD");

    //Get home dir.
    char * home;
    if(!(home=getenv("HOME")))
        err_sys("getenv failed:HOME");

    //Replace home dir as "~".
    char chpath[MAXLINE];
    if(strstr(path,home)){
        sprintf(chpath,"~%s",path+strlen(home));
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
            if(line_buf[i-1]==' '||line_buf[i-1]=='\t')
                cnt++;
            char *pch=NULL;
            while((pch=strchr(&line_buf[i+1],line_buf[i]))!=NULL && *(pch-1)=='\\');
            if(pch==NULL){
                return -1;
            }else{
                i+=pch-&line_buf[i];
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
 *          not found:1
 */
static int parse_command(Array* cmds,int argc,char **argv){
    int i;
    char cmd_argv0[MAXLINE];

    //Variable.
    if(argc==1&&strchr(argv[0],'='))
        strcpy(cmd_argv0,"set");
    else
        strcpy(cmd_argv0,argv[0]);

    //Traverse built-in command.
    for (i = 0; i < cmds->len && strcmp(((Cmd*)cmds->data[i])->cmd_name,cmd_argv0); i++);
    if(i!=cmds->len){
        Cmd* cur_cmd=(Cmd*)cmds->data[i];
        g_status=cur_cmd->cmd_func(argc,argv,cur_cmd);
        return 0;
    }

    return 1;
}

/*
 * @ Function:Initialize command array.
 * @ Return:success:0
 *          failure:-1
 */
static int cmd_array_init(){
    //Create command array.
    if (!(cmds=create_array(CMD_NUM)))
        err_quit("create_array failed");

    //Register commands.
    cmd_array_register(cmds);

    return 0;
}

/*
 * @ Function:Execute external commands.
 * @ Return:success:0
 *          failure:-1
 *          not found:1
 */
static int external_cmd(int argc,char **argv){
    char path[MAXLINE];
    pid_t pid;

    //Confirm command existence.
    sprintf(path,CMD_DIR"%s",argv[0]);
    if(access(path,F_OK))
        return 1;

    //Execute program in "bin/"
    if((pid=fork())<0){
        err_ret("fork failed");
        return -1;
    }else if(pid>0){
        waitpid(pid,&g_status,0);
        return 0;
    }else{
        if(execv(path,argv)<0){
            err_ret("execv failed");
            return -1;
        }
    }
    return -1;
}

/*
 * @ Function:Initialize user information.
 * @ Return:success:0
 *          failed:-1
 */
static int user_init(){
    char * home;

    if(!(home=getenv("HOME")))
        err_sys("getenv failed:HOME");

    //Change dir.
    if(chdir(home))
        err_sys("chdir failed");

    //Initialize umask.
    umask(umask_mode);

    return 0;
}

/*
 * @ Function:Initialize environment.
 * @ Return:success:0
 *          failure:-1
 */
static int env_init(){
    //Put env for shell.

    //Env:HOSTNAME
    char hostname[HOST_NAME_MAX];
    if(gethostname(hostname,HOST_NAME_MAX-1))
        err_sys("gethostname failed");
    sprintf(env_hostname,"HOSTNAME=%s",hostname);
    if(putenv(env_hostname))
        err_sys("putenv failed:HOSTNAME");

    //Env:USERNAME
    char * username;
    if(!(username=getlogin()))
        err_sys("getlogin failed");
    sprintf(env_username,"USERNAME=%s",username);
    if(putenv(env_username))
        err_sys("putenv failed:USERNAME");

    //Env:HOME
    struct passwd* p_passwd;
    if(!(p_passwd=getpwnam(username)))
        err_sys("getpwnam failed");
    sprintf(env_home,"HOME=%s",p_passwd->pw_dir);
    if(putenv(env_home))
        err_sys("putenv failed:HOME");

    //Env:PWD,OLDPWD
    sprintf(env_pwd,"PWD=%s",p_passwd->pw_dir);
    if(putenv(env_pwd))
        err_sys("putenv failed:PWD");
    sprintf(env_oldpwd,"OLDPWD=%s",p_passwd->pw_dir);
    if(putenv(env_oldpwd))
        err_sys("putenv failed:OLDPWD");

    return 0;
}

/*
 * @ Function:Initialize variable array.
 * @ Return:success:0
 *          failure:-1
 */
static int var_array_init(){
    //Create variable array.
    if (!(vars=create_array(MAXLINE)))
        err_quit("create_array failed");

    return 0;
}

/*
 * @ Function:Initialize alias array.
 * @ Return:success:0
 *          failure:-1
 */
static int alias_array_init(){
    //Create alias array.
    if (!(aliases=create_array(MAXLINE)))
        err_quit("create_array failed");

    return 0;
}

