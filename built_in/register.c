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

    //help
    ap->array_append(ap,(ElemType*)help_init());

    //ulimit
    ap->array_append(ap,(ElemType*)ulimit_init());

    //echo
    ap->array_append(ap,(ElemType*)echo_init());

    //export
    ap->array_append(ap,(ElemType*)export_init());

    //set
    ap->array_append(ap,(ElemType*)set_init());

    //unset
    ap->array_append(ap,(ElemType*)unset_init());

    //alias
    ap->array_append(ap,(ElemType*)alias_init());

    //unalias
    ap->array_append(ap,(ElemType*)unalias_init());

    return 0;
}
