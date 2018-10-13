/*
 * @ Description:Register built-in commands.
 * @ Author: SangYuchen
 * @ Date:2018-10-11
 */

#include "built_in.h"

/*
 * @ Function:Register commands.
 * @ Output:ap:command array after initializing
 * @ Return:success:0
 *          failure:-1
 */
int cmd_array_register(Array* ap){
    //pwd
    ap->array_append(ap,(ElemType*)pwd_init());

    //exit
    ap->array_append(ap,(ElemType*)exit_init());

    //cd
    ap->array_append(ap,(ElemType*)cd_init());

    //umask
    ap->array_append(ap,(ElemType*)umask_init());

    return 0;
}
