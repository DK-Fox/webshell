/*
 * @ Description:Socket wrapper functions.
 * @ From:UNP
 * @ Date:2018-11-11
 */

#include "net.h"

int Socket(int family, int type, int protocol){
        int n;

        if ( (n = socket(family, type, protocol)) < 0)
            log_sys("socket error");
        return(n);
}

void Listen(int fd, int backlog){
    char *ptr;

    /*4can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        log_sys("listen error");
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen){
        if (bind(fd, sa, salen) < 0)
                    log_sys("bind error");
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen){
        if (connect(fd, sa, salen) < 0)
                    log_sys("connect error");
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr){
    int n;

again:
    if ( (n = accept(fd, sa, salenptr)) < 0) {
        if (errno == ECONNABORTED)
            goto again;
        else
            log_sys("accept error");
    }
    return(n);
}

