/*
 * @ Description:This is a program of general array.
 * @ Author:SangYuchen
 * @ Date:2018-10-11
 */

#include "general_array.h"

/*
 * @ Function:Get location of element in array.
 * @ Input:ap:array
 *         n:index
 * @ Return:success:location of element
 *          failure:NULL
 */
static ElemType* get_addr(Array* ap,int n){
    //Confirm segment error
    if(n<0||n>=ap->len){
        err_msg("get_addr failed: Segmentation fault");
        return NULL;
    }
    return ap->data+n;
}

/*
 * @ Function:Delete element in array.
 * @ Input:ap:array
 *         n:index
 * @ Return:success:0
 *          failure:-1
 */
static int array_delete(Array* ap,int n){
    ElemType* p;
    int i=0;

    //Get location of element
    if(!(p=ap->get_addr(ap,n))){
        err_msg("get_addr failed");
        return -1;
    }

    //Delete element
    while (n+i!=ap->len-1){
         p[i]=p[i+1];
         i++;
    }
    p[i]=NULL;
    ap->len--;
    return 0;
}

/*
 * @ Function:Clear element in array.
 * @ Input:ap:array
 */
static void clear_array(Array* ap){
    memset(ap->data,0,ap->len*sizeof(ElemType));
    ap->len=0;
}

/*
 * @ Function:Destroy array.
 * @ Input:ap:array
 */
static void destroy_array(Array* ap){
    free(ap->data);
    free(ap);
}

/*
 * @ Function:Insert element into array.
 * @ Input:data:element content
 *         n:index
 * @ Output:ap:array
 * @ Return:success:0
 *          failure:-1
 */
static int array_insert(Array* ap,int n,ElemType data){
    ElemType* p=ap->data;
    int i=ap->len;

    //Confirm segment error
    if(n<0||n>ap->len||ap->len==ap->size){
        err_msg("array_insert failed: Segmentation fault");
        return -1;
    }

    //Insert element
    while(i!=n){
        p[i]=p[i-1];
        i--;
    }
    p[i]=data;
    ap->len++;
    return 0;
}

/*
 * @ Function:Append element into array.
 * @ Input:data:element content
 * @ Output:ap:array
 * @ Return:success:0
 *          failure:-1
 */
static int array_append(Array* ap,ElemType data){
    if(ap->array_insert(ap,ap->len,data)){
        err_msg("array_append failed");
        return -1;
    }
    return 0;
}

/*
 * @ Function:Traverse array.
 * @ Input:f:function to every element
 * @ Output:ap:array
 * @ Return:success:0
 *          failure:-1
 */
static int traverse_array(Array* ap,int(*f)(ElemType*)){
    ElemType* p=ap->data;
    int i;

    //function on every element
    for(i=0;i<ap->len;i++)
        if(f(p[i]))break;
    return i;
}

/*
 * @ Function:Create array.
 * @ Input:size:the size of array
 * @ Return:success:array
 *          failure:NULL
 */
Array* create_array(int size){
    Array *ap;

    //Confirm negative size error
    if(size<=0){
        err_msg("create_array failed: Negative size");
        return NULL;
    }

    //Create array
    if(!(ap=(Array*)malloc(sizeof(Array)))){
        err_ret("malloc failed");
        return NULL;
    }
    if(!(ap->data=(ElemType*)malloc(size*sizeof(ElemType)))){
        free(ap);
        err_ret("malloc failed");
        return NULL;
    }

    //Initialize array
    memset(ap->data,0,size*sizeof(ElemType));
    ap->size=size;
    ap->len=0;
    ap->get_addr=get_addr;
    ap->array_delete=array_delete;
    ap->clear_array=clear_array;
    ap->destroy_array=destroy_array;
    ap->array_insert=array_insert;
    ap->array_append=array_append;
    ap->traverse_array=traverse_array;
    return ap;
}

