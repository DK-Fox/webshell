/*
 * @ Description:
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include "build_in.h"

int cmd_array_register(Array* ap){
    ap->array_append(ap,(ElemType*)pwd_init());
    return 0;
}
