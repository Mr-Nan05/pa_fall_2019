#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    if(opr_src.data_size==8 && (opr_dest.data_size==16||opr_dest.data_size==32)){
        opr_src.val = sign_ext(opr_src.val,8);
    }
    opr_dest.val=alu_sub(opr_src.val,opr_dest.val,opr_dest.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(sub,r,rm,b)
make_instr_impl_2op(sub,r,rm,v)
make_instr_impl_2op(sub,rm,r,b)
make_instr_impl_2op(sub,rm,r,v)
make_instr_impl_2op(sub,i,a,b)
make_instr_impl_2op(sub,i,a,v)

make_instr_impl_2op(sub,i,rm,b)
make_instr_impl_2op(sub,i,rm,v)
make_instr_impl_2op(sub,i,rm,bv)

