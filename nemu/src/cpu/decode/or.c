#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    if(opr_src.data_size==8 && opr_dest.data_size== data_size)
    {
        opr_src.val = sign_ext(opr_src.val,8);
    }
    opr_dest.val=alu_or(opr_src.val,opr_dest.val,opr_dest.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(or,r,rm,b)
make_instr_impl_2op(or,r,rm,v)
make_instr_impl_2op(or,rm,r,b)
make_instr_impl_2op(or,rm,r,v)
make_instr_impl_2op(or,i,a,b)
make_instr_impl_2op(or,i,a,v)

make_instr_impl_2op(or,i,rm,b)
make_instr_impl_2op(or,i,rm,v)
make_instr_impl_2op(or,i,rm,bv)