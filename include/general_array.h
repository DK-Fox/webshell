/*
 * @ Description:This is the header file for general_array.c
 * @ Author:SangYuchen
 * @ Date:2018-10-11
 */
#ifndef __GENERAL_ARRAY__
#define __GENERAL_ARRAY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apue_err.h"

typedef void * ElemType;
typedef struct array{
    ElemType *data;//Element array
    int size;//Size of array
    int len;//Number of elements

    //Array method
    ElemType* (*get_addr)(struct array* ap,int n);
    int (*array_delete)(struct array* ap,int n);
    void  (*clear_array) (struct array* ap);
    void  (*destroy_array) (struct array* ap);
    int (*array_insert)(struct array* ap,int n,ElemType data);
    int (*array_append)(struct array* ap,ElemType data);
    int (*traverse_array)(struct array* ap,int(*f)(ElemType*));
}Array;

Array* create_array(int size);

#endif
