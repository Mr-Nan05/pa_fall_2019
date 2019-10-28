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

//make_instr_impl_2op(mov, c, r, l)
//make_instr_impl_2op(mov, r, c, l)
//make_instr_impl_2op(mov, rm, s, w)


make_instr_func(mov_c2r_l) {

	OPERAND src, dest;

	dest.data_size = 32;

	src.data_size = 32;



	modrm_c_r(eip + 1, &src, &dest);

	operand_read(&src);

	//printf("dest addr: %d\n", dest.addr);

	dest.val = src.val;

	operand_write(&dest);

	//printf("here2\n");

	return 2;

}



make_instr_func(mov_r2c_l) {

	OPERAND src, dest;

	src.data_size = 32;

	dest.data_size = 32;



	modrm_c_r(eip + 1, &dest, &src);

	operand_read(&src);

	dest.val = src.val;

	operand_write(&dest);

	//load_sreg(dest.addr);

	return 2;

}



make_instr_func(mov_rm2s_w) {

	OPERAND rm, s;

	rm.data_size = s.data_size = 16;



	modrm_rm_s(eip + 1, &rm, &s);

	operand_read(&rm);

	s.val = rm.val;

	operand_write(&s);

	load_sreg(s.addr);

	return 2;

}
make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
        return len;
}
