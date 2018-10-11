/*
 * @ Description:
 * @ Author:SangYuchen
 * @ Date:2018-10-11
 */

#include "general_list.h"

static ElemType* get_addr(Array* ap,int n){
    if(n<0||n>=ap->len){
        err_msg("get_addr failed: Segmentation fault");
        return NULL;
    }
    return ap->data+n;
}

static int array_delete(Array* ap,int n){
    ElemType* p;
    int i=0;
    if(!(p=ap->get_addr(ap,n))){
        err_msg("get_addr failed");
        return -1;
    }
    while (n+i!=ap->len-1){
         p[i]=p[i+1];
         i++;
    }
    p[i]=NULL;
    ap->len--;
    return 0;
}

static void clear_array(Array* ap){
    memset(ap->data,0,ap->len*sizeof(ElemType));
    ap->len=0;
}

static void destroy_array(Array* ap){
    free(ap->data);
    free(ap);
}

static int array_insert(Array* ap,int n,ElemType data){
    ElemType* p=ap->data;
    int i=ap->len;
    if(n<0||n>ap->len||ap->len==ap->size){
        err_msg("array_insert failed: Segmentation fault");
        return -1;
    }
    while(i!=n){
        p[i]=p[i-1];
        i--;
    }
    p[i]=data;
    ap->len++;
    return 0;
}

static int array_append(Array* ap,ElemType data){
    if(ap->array_insert(ap,ap->len,data)){
        err_msg("array_append failed");
        return -1;
    }
    return 0;
}

static int get_element(Array* ap,int n,ElemType** data){
    ElemType* p;
    if(!(p=ap->get_addr(ap,n))){
        err_msg("get_element failed");
        return -1;
    }
    *data=*p;
    return 0;
}

static int traverse_array(Array* ap,int(*f)(ElemType*)){
    ElemType* p=ap->data;
    int i;
    for(i=0;i<ap->len;i++)
        if(f(p[i]))return i+1;
    return 0;
}

Array* create_array(int size){
    Array *ap;
    if(size<=0){
        err_msg("create_array failed: Negative size");
        return NULL;
    }
    if(!(ap=(Array*)malloc(sizeof(Array)))){
        err_ret("malloc failed");
        return NULL;
    }
    if(!(ap->data=(ElemType*)malloc(size*sizeof(ElemType)))){
        free(ap);
        err_ret("malloc failed");
        return NULL;
    }
    memset(ap->data,0,size*sizeof(ElemType));
    ap->size=size;
    ap->len=0;
    ap->get_addr=get_addr;
    ap->array_delete=array_delete;
    ap->clear_array=clear_array;
    ap->destroy_array=destroy_array;
    ap->array_insert=array_insert;
    ap->array_append=array_append;
    ap->get_element=get_element;
    ap->traverse_array=traverse_array;
    return ap;
}

