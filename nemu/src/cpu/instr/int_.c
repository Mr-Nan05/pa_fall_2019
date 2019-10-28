#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_){
#ifdef IA32_INTR 
     OPERAND imm;
     imm.type = OPR_IMM;
     imm.sreg = SREG_CS;
     imm.data_size = 8;
     imm.addr = eip + 1;
     operand_read(&imm);

     uint8_t intr_no = imm.val;

     print_asm_1("int", "", 2, &imm);
     raise_sw_intr(intr_no);
     return 0;
#else
      printf("please implement int\n"); assert(0);
#endif
}