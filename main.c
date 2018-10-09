/*
 * ******************************************************
 * @ Filename:main.c
 * @ Author:syc
 * @ Description:This is the main program of the shell
 * ******************************************************
 */

#include "main.h"

char line_buf[MAXLINE];

int main(){
    printf("My webshell starts ...\n");

    PArgc * pargc=(PArgc*)malloc(sizeof(Pargc));
    PArgv * pargv=(PArgv*)malloc(sizeof(PArgv));

    //while(1){
        print_pr();
        readline(pargc,pargv);
        //parse_command();
        //external_cmd();
    //}
    exit(0);
}

/*
 * Print prompt.
 */
int print_pr(){
    char hostname[HOST_NAME_MAX];
    if(gethostname(hostname,HOST_NAME_MAX-1)!=0)
        err_sys("gethostname failed")

    char * logname=getlogin();
    if(logname==NULL)
        err_sys("getlogin failed");

    char * path=getcwd(NULL,0);
    if(path==NULL)
        err_sys("getcwd failed");

    printf("%s@%s:%s$ ",logname,hostname,path);
    return 0;
}

int readline(PArgc *argc,PArgv * argv){
    fgets(&line_buf, MAXLINE, stdin);
    int cnt=0;
    int length=strlen(line_buf);
    for(int i=0;i<length;i++){
        if(strch("\"\'<\(\{\[",line_buf[i])!=NULL && line_buf[i-1]!='\\'){
            while((char * pch=strch(&line_buf[i+1],line_buf[i]))!=NULL && *(pch-1)=='\\');
            if(pch==NULL){
                ;
                return -1;
            }else{
                i+=pch-&line_buf[i];
                cnt++;
                continue;
            }
        }

        if(line_buf[i]==' '||line_buf[i]=='\t')
            line_buf[i]='\0';

        if(line_buf[i-1]==' '||line_buf[i]=='\t')
            cnt++;
    }
    *argc=cnt;
    *argv=(Pargv)malloc(cnt*sizeof(*Pargv));
    for(int i=0,cnt=0;i<length;i++){
        if(line_buf[i]!='\0',line_buf[i-1]=='\0'){
            (*argv)[cnt++]=&line_buf[i];
        }
    }
    return 0;
}




