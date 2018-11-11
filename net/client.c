/*
 * @ Description:It's a client program.
 * @ Author:SangYuchen
 * @ Date:2018-11-11
 */

#include "net.h"
#include "apue_err.h"
static void * thr_rtws(void *arg);

pthread_t ntid;

int main(){
    //socket
    int sockfd=Socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(ADDR_PORT);
    client_addr.sin_addr.s_addr=inet_addr(ADDR_IP);

    Connect(sockfd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr));

    printf("Connect OK!\n");

    char buf[MAXLINE];
    int n;
    int err;
    err=pthread_create(&ntid,NULL,thr_rtws,&sockfd);
    if(err!=0)
        err_exit(err,"can't create thread");
    while(1){
        memset(buf,0,sizeof(buf));
        while((n=recv(sockfd,buf,MAXLINE,0))==0);
        fputs(buf,stdout);
    }
    close(sockfd);
    exit(0);
}

static void * thr_rtws(void *arg){
    int n;
    int *sockfd=(int *)arg;
    char buf[MAXLINE];
    while(1){
        memset(buf,0,sizeof(buf));
        fgets(buf,MAXLINE,stdin);
        if(!strcmp(buf,"q\n"))
            exit(0);
        n=strlen(buf);
        if(send(*sockfd,buf,n,0)!=n)
            err_sys("send socket failed");
    }
}
