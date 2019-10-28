#include "cpu/instr.h"

make_instr_func(jmp_near) {
        OPERAND rel;
        rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

	int offset = sign_ext(rel.val, data_size);
	print_asm_1("jmp", "", 2, &rel);

	cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(jmp_short_){
        OPERAND rel;
        rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
        rel.data_size = 8;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, rel.data_size);

        print_asm_1("jmp", "", 2, &rel);

        cpu.eip += offset;
        return 1 + rel.data_size / 8;
}

make_instr_func(jmp_near_indirect){
        int len = 1;
        opr_src.data_size = data_size;
        len += modrm_rm(eip+1,&opr_src);
        operand_read(&opr_src);

        print_asm_1("jmp", "", 2, &opr_src);

        cpu.eip = opr_src.val;

        return 0;
}


make_instr_func(jmp_far_imm){        
#ifdef IA32_SEG    
        int len = 1;
        OPERAND ptr1, ptr2;
        ptr1.data_size = 16;
        ptr2.data_size = data_size;
        ptr1.type = ptr2.type = OPR_IMM;
        ptr1.sreg = ptr2.sreg = SREG_CS;
        ptr2.addr = eip + 1;
        ptr1.addr = eip + 1 + data_size/8;

        print_asm_2("ljmp","",2,&ptr1,&ptr2);

        operand_read(&ptr1);
        operand_read(&ptr2);
        len += 2 + data_size/8;
        
        cpu.eip = ptr2.val;
        cpu.segReg[SREG_CS].val = ptr1.val;
        load_sreg(SREG_CS);

        return 0;
#else
        printf("please implement ljmp\n");assert(0);
#endif
}
