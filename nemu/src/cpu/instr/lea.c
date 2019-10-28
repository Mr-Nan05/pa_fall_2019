#include "cpu/instr.h"

make_instr_func(lea){

    int len = 1;
    opr_dest.data_size = data_size;
    len += modrm_r_rm(eip+1,&opr_dest,&opr_src);
    opr_dest.val = opr_src.addr;
    operand_write(&opr_dest);

    return len;
}