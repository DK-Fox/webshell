/*
 * ****************************************************
 * @ Filename:build_in.h
 * @ Author:syc
 * @ Description:This is the header file requied for the build-in command
 * ***************************************************
 */
#ifndef __BUILD_IN__
#define __BUILD_IN__

typedef struct {
    char *cmd_name;
    char *cmd_usage;
    int (* cmd_func)(char **argv);
}Cmd;

typedef struct{
    Cmd * cmds;

}CmdList;

#endif
