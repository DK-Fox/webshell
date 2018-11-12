/*
 * @ Description:Create a server to provide shell service.
 * @ Author:SangYuchen
 * @ Date:2018-11-10
 */

#include "net.h"

static void main_handle(int);
static void sig_pipe(int);
static void * thr_rpws(void *arg);

pthread_t ntid;
pthread_t ptfk;
int flag=0;
int main(){
    //daemon
    //daemonize("server");

    //socket
    int serv_sock = Socket(AF_INET,SOCK_STREAM,0);

    //fill sockaddr_in
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(ADDR_IP);
    serv_addr.sin_port = htons(ADDR_PORT);

    Bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    Listen(serv_sock,ADDR_SEQ);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size =sizeof(clnt_addr);
    int clnt_sock;
    int pid;
    while((clnt_sock=Accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size)) >0){
        if((pid=fork())<0){
            log_sys("fork err");
        }
        if(pid==0){
            close(serv_sock);
            if((pid=fork())<0)
                log_sys("fork err");
            if(pid>0)
                exit(0);
            sleep(1);
            main_handle(clnt_sock);
        }else{
            close(clnt_sock);
            if(waitpid(pid,NULL,0)!=pid)
                log_sys("waitpid error");
        }
    }
    close(serv_sock);

    exit(0);
}

/*
 * Function:Handle new connection.
 */
static void main_handle(int clnt_sock){
    int fd1[2],fd2[2];
    pid_t pid;

    if(signal(SIGPIPE,sig_pipe)==SIG_ERR)
        log_sys("signal failed");

    if(pipe(fd1)<0||pipe(fd2)<0)
        log_sys("pipe failed");

    if((pid=fork())<0){
        log_sys("fork failed");
    }else if(pid>0){
        close(fd1[0]);
        close(fd2[1]);

        //set between client and shell.
        char buf[MAXLINE];
        int n;
        int err;
        Arg arg={fd2[0],clnt_sock};
        err=pthread_create(&ntid,NULL,thr_rpws,&arg);
        if(err!=0)
            log_exit(err,"can't create thread");
        do{
            memset(buf,0,sizeof(buf));
            if((n=recv(clnt_sock,buf,MAXLINE,0)) < 0)
                log_sys("recv failed");
            if(write(fd1[1],buf,n)!=n)
                log_sys("write failed");
        }while(strcmp(buf,"exit\n"));
        close(clnt_sock);
        wait(NULL);
        exit(0);
    }else{
        close(fd1[1]);
        close(fd2[0]);

        //link to parent.
        if(fd1[0]!=STDIN_FILENO){
            if(dup2(fd1[0],STDIN_FILENO)!=STDIN_FILENO)
                log_sys("dup2 failed to stdin");
            close(fd1[0]);
        }

        if(fd2[1]!=STDOUT_FILENO){
            if(dup2(fd2[1],STDOUT_FILENO)!=STDOUT_FILENO)
                log_sys("dup2 failed to stdout");
            if(dup2(fd2[1],STDERR_FILENO)!=STDERR_FILENO)
                log_sys("dup2 failed to stderr");
            close(fd2[1]);
        }

        //run shell.
        if(execl(SH_PATH,"myshell",(char *)0)<0)
            log_sys("execv failed");
        exit(0);
    }
}

static void sig_pipe(int signo){
    printf("SIGPIPE caught\n");
    exit(1);
}

static void * thr_rpws(void *arg){
    int n;
    Arg* argv=(Arg *)arg;
    char buf[MAXLINE];
    while(1){
        memset(buf,0,sizeof(buf));
        if((n=read(argv->fd,buf,MAXLINE))>0){
            if(send(argv->sockfd,buf,n,0)!=n)
                log_sys("send socket failed");
        }
    }
}

