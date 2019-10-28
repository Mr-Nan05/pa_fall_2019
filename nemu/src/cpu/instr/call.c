#include "cpu/instr.h"

make_instr_func(call_near)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip+1;
    operand_read(&rel);
    int offset = sign_ext(rel.val,data_size);

    uint32_t esp_de = data_size/8;
    cpu.esp-= esp_de;
    uint32_t esp = cpu.esp;

    uint32_t val = 0;
    val = eip+1+data_size/8;

    OPERAND opr;
    opr.type = OPR_MEM;
    opr.sreg = SREG_SS;
    opr.addr = esp;
    opr.data_size = data_size;
    opr.val = val;
    operand_write(&opr);

    print_asm_1("call","",2,&rel);
    cpu.eip += offset;

    return 1 + data_size/8;
}

make_instr_func(call_near_indirect){
    int len = 1;
    opr_src.data_size = data_size;
    len+= modrm_rm(eip+1,&opr_src);
    operand_read(&opr_src);

    uint32_t esp_de = data_size/8;
    cpu.esp-= esp_de;
    uint32_t esp=cpu.esp;

    uint32_t val=0;
    val=eip+len;
    OPERAND opr;
    opr.type = OPR_MEM;
    opr.sreg = SREG_SS;
    opr.addr = esp;
    opr.data_size = data_size;
    opr.val = val;
    operand_write(&opr);

    cpu.eip = opr_src.val;
    
    return 0;
}