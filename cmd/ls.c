/*
 * @ Description:This is the command "ls".
 * @ Author: SangYuchen
 * @ Date:2018-10-29
 */
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue_err.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc,char *argv[]){
    //ls
    DIR *dp;
    struct stat* buf=(struct stat*)malloc(sizeof(struct stat));
    struct dirent *dirp;
    struct passwd *ptr;
    struct group *pgr;
    struct tm * pt;
    char *file_buf[MAXLINE];

    //Get filenames.
    if((dp=opendir(getenv("PWD")))==NULL)
        err_sys("can't open %s",getenv("PWD"));
    int i=0;
    while((dirp=readdir(dp))!=NULL){
        file_buf[i]=(char*)malloc(sizeof(dirp->d_name));
        strcpy(file_buf[i++],dirp->d_name);
    }

    //Sort by name.
    int len=i;
    int j;
    char *tmp;
    for(i=0;i<len-1;i++){
        int min=i;
        for(j=i+1;j<len;j++){
            if(strcmp(file_buf[j],file_buf[min])<0){
                min=j;
            }
        }
        tmp=file_buf[i];
        file_buf[i]=file_buf[min];
        file_buf[min]=tmp;
    }

    //Print some message.
    for(i=0;i<len;i++){
        if(stat(file_buf[i],buf)<0){
            err_ret("stat error");
            continue;
        }
        //mode
        if(S_ISREG(buf->st_mode))
            printf("-");
        else if (S_ISDIR(buf->st_mode))
            printf("d");
        else if (S_ISCHR(buf->st_mode))
            printf("c");
        else if (S_ISBLK(buf->st_mode))
            printf("b");
        else if (S_ISFIFO(buf->st_mode))
            printf("f");
        else if (S_ISLNK(buf->st_mode))
            printf("l");
        else
            printf("*");

        //RWX
        char rwx[3]="rwx";
        for(int i=8;i>=0;i--){
            if(buf->st_mode & (1<<i))
                printf("%c",rwx[2-i%3]);
            else
                printf("-");
        }
        printf("%2ld ",buf->st_nlink);
        ptr=getpwuid(buf->st_uid);
        printf("%s ",ptr->pw_name);
        pgr=getgrgid(ptr->pw_gid);
        printf("%s ",pgr->gr_name);
        char size_buf[MAXLINE];
        if(buf->st_size>1024){
            sprintf(size_buf,"%3ldK",buf->st_size/1024);
        }
        printf("%s ",size_buf);
        pt=gmtime(&buf->st_atime);
        char time_buf[MAXLINE];
        strftime(time_buf,MAXLINE,"%b %d %R",pt);
        printf("%s ",time_buf);
        printf("%s\n",file_buf[i]);
    }
    //close.
    for(i=0;i<len;i++){
        free(file_buf[i]);
    }
    free(buf);
    closedir(dp);
    exit(0);
}

