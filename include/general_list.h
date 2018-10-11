/*
 * @ Description:
 * @ Author:SangYuchen
 * @ Date:2018-10-11
 */
#ifndef __GENERAL_LIST__
#define __GENERAL_LIST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apue_err.h"

typedef void * ElemType;
typedef struct array{
    ElemType *data;
    int size;
    int len;
    ElemType* (*get_addr)(struct array* ap,int n);
    int (*array_delete)(struct array* ap,int n);
    void  (*clear_array) (struct array* ap);
    void  (*destroy_array) (struct array* ap);
    int (*array_insert)(struct array* ap,int n,ElemType data);
    int (*array_append)(struct array* ap,ElemType data);
    int (*get_element)(struct array* ap,int n,ElemType** data);
    int (*traverse_array)(struct array* ap,int(*f)(ElemType*));
}Array;

Array* create_array(int size);

#endif
