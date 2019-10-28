#include "cpu/instr.h"


make_instr_func(iret){
#ifdef IA32_INTR
    uint32_t esp = cpu.esp;
    uint32_t esp_inc = 10;
    cpu.esp += esp_inc;

    OPERAND EFLAGS, CS, EIP;
	EFLAGS.type = CS.type = EIP.type = OPR_MEM;
	EFLAGS.sreg = CS.sreg = EIP.sreg = SREG_SS;
	EFLAGS.data_size = EIP.data_size = 32;
	CS.data_size = 16;
    EIP.addr = esp;
    CS.addr = esp + 4;
    EFLAGS.addr = esp + 6;
    operand_read(&EIP);
    operand_read(&CS);
    operand_read(&EFLAGS);
    cpu.eip = EIP.val ;
    cpu.cs.val = CS.val;
    load_sreg(SREG_CS);
    cpu.eflags.val = EFLAGS.val;
    print_asm_0("iret","",1);
    return 0;
#else
    printf("please implement iret\n"); assert(0);
#endif
}