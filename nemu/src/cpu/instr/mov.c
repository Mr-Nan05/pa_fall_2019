#include "cpu/instr.h"

static void instr_execute_2op()
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
	make_instr_impl_2op(mov, r, rm, v)
		make_instr_impl_2op(mov, rm, r, b)
			make_instr_impl_2op(mov, rm, r, v)
				make_instr_impl_2op(mov, i, rm, b)
					make_instr_impl_2op(mov, i, rm, v)
						make_instr_impl_2op(mov, i, r, b)
							make_instr_impl_2op(mov, i, r, v)
								make_instr_impl_2op(mov, a, o, b)
									make_instr_impl_2op(mov, a, o, v)
										make_instr_impl_2op(mov, o, a, b)
											make_instr_impl_2op(mov, o, a, v)

												make_instr_func(mov_c2r_l)
{

	MODRM modrm;
	opr_src.data_size = 32;
	opr_dest.data_size = 32;

	modrm.val = instr_fetch(eip + 1, 1);
	opr_src.type = OPR_CREG;
	opr_src.addr = modrm.reg_opcode;

	int len = 1 + modrm_rm(eip + 1, &opr_dest);

	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);

	return len;
}

make_instr_func(mov_r2c_l)
{
	opr_src.data_size = opr_dest.data_size = 32;

	int len = 1 + modrm_rm(eip + 1, &opr_src);

	MODRM modrm;
	modrm.val = instr_fetch(eip + 1, 1);
	opr_dest.type = OPR_CREG;
	opr_dest.addr = modrm.reg_opcode;

	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);

	return len;
}

make_instr_func(mov_rm2s_w)
{
	opr_src.data_size = opr_dest.data_size = 16;

	int len = 1 + modrm_rm(eip + 1, &opr_src);

	MODRM modrm;
	modrm.val = instr_fetch(eip + 1, 1);
	opr_dest.type = OPR_SREG;
	opr_dest.addr = modrm.reg_opcode;

	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
	load_sreg(opr_dest.addr);

	return len;
}

make_instr_func(mov_zrm82r_v)
{
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	int len = 1 + modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l)
{
	OPERAND r, rm;
	r.data_size = 32;
	rm.data_size = 16;
	int len = 1 + modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_srm82r_v)
{
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	int len = 1 + modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	r.val = sign_ext(rm.val, 8);
	operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_srm162r_l)
{
	OPERAND r, rm;
	r.data_size = 32;
	rm.data_size = 16;
	int len = 1 + modrm_r_rm(eip + 1, &r, &rm);
	operand_read(&rm);
	r.val = sign_ext(rm.val, 16);
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}
