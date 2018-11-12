/*
 * @ Description:This is the header file of net.c
 * @ Author:Sangyuchen
 * @ Date:2018-10-11
 */

#ifndef __NET__
#define __NET__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include "apue_log.h"
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>

#define ADDR_IP "127.0.0.1"
#define ADDR_PORT 8888
#define ADDR_SEQ 256
#define SH_PATH "../myshell"

//Daemonize.
void daemonize(const char * cmd);

//Socket wrapper functions.

int Socket(int family, int type, int protocol);
void Listen(int fd, int backlog);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

typedef struct{
    int fd;
    int sockfd;
}Arg;
#endif
