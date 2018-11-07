/*
 * @ Description:This is a program for create a daemon.
 * @ From:APUE
 * @ Date:2018-11-08
 */

#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "apue_err.h"
#include <sys/stat.h>

void daemonize(const char * cmd){
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit rl;

    //Clear file creation mask.
    umask(0);

    //Get maxinum number of file description.
    if(getrlimit(RLIMIT_NOFILE,&rl)<0){
        err_quit("%s:can't get file limit",cmd);
    }

    //Become a session leader to lose controlling TTY.
    if((pid=fork())<0)
        err_quit("%s:can't fork",cmd);
    else if(pid!=0){
        exit(0);
    }
    setsid();

    //Ensure future opens won't allocate TTYs.
    if((pid=fork())<0)
        err_quit("%s:can't fork",cmd);
    else if(pid!=0)
        exit(0);

    //Change directory to the root
    if(chdir("/")<0)
        err_quit("%s:can't change the directory to /",cmd);

    //Close all open file description.
    if(rl.rlim_max==RLIM_INFINITY)
        rl.rlim_max=1024;
    for(i=0;i<rl.rlim_max;i++)
        close(i);

    //Attach file description 0,1, and 2 to /dev/null.
    fd0=open("/dev/null",O_RDWR);
    fd1=dup(0);
    fd2=dup(0);

    //Initialize the logfile.
    openlog(cmd,LOG_CONS,LOG_DAEMON);
    if(fd0!=0||fd1!=1||fd2!=2){
        syslog(LOG_ERR,"unexpected file descriptors %d %d %d",fd0,fd1,fd2);
        exit(1);
    }
}
