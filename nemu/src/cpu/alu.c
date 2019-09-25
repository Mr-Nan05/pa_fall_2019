#include "cpu/cpu.h"

void set_CF_add(uint32_t result,uint32_t src,size_t data_size){
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.CF=result<src;
}

void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size) {
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(src)==sign(dest)){
		if(sign(src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}
	else{
		cpu.eflags.OF=0;
	}
}

void set_CF_adc(uint32_t result,uint32_t src,uint32_t dest,size_t data_size) {
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	if(dest!=0)
		cpu.eflags.CF= result<=src;
	if(dest==0)
		cpu.eflags.CF= result<src;
}

void set_OF_adc(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(src)==sign(dest)){
		if(sign(src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}
	else
	{
		cpu.eflags.OF=0;
	}
}

void set_CF_sub(uint32_t result,uint32_t src,size_t data_size){
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(src != 0)
		cpu.eflags.CF=!(result<(~src+1));
	else
		cpu.eflags.CF=0;
}

void set_OF_sub(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(~src)==sign(dest)){
		if(sign(~src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}
	else
		cpu.eflags.OF=0;
}

void set_CF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	
	if(src!=0)
		cpu.eflags.CF= (result>=dest);
	else
		cpu.eflags.CF= result>dest;
	
}

void set_OF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(~src)==sign(dest)){
		if(sign(~src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}
	else
		cpu.eflags.OF=0;
}

void set_OF_CF_mul(uint64_t result,uint32_t dest,uint32_t res,size_t data_size){
	switch(data_size)
	{
		case 8: cpu.eflags.CF=cpu.eflags.OF= (((result>>8)|0x00)>0);
				break;
		case 16: cpu.eflags.CF=cpu.eflags.OF= (((result>>16)|0x0000)>0);
				 break;
		case 32: cpu.eflags.CF=cpu.eflags.OF= (((result>>32)|0x00000000)>0);
				 break;
	}
}

void set_OF_CF_imul(int64_t result,int32_t dest,int32_t src,size_t data_size){
	switch(data_size)
	{
		case 8: cpu.eflags.CF=cpu.eflags.OF=!((((result>>7)^0x1FF)==0)|(((result>>7)|0x000)==0));
				break;
		case 16: cpu.eflags.CF=cpu.eflags.OF=!((((result>>15)^0x1FFFF)==0)|(((result>>15)|0x00000)==0));
				break;
		case 32: cpu.eflags.CF=cpu.eflags.OF=!((((result>>31)^0x1FFFFFFFF)==0)|(((result>>31)|0x000000000)==0));
				break;
	}
}

void set_ZF(uint32_t result,size_t data_size) {
	result=result&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF = (result==0);
}

void set_SF(uint32_t result,size_t data_size) {
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);
}

void set_PF(uint32_t result)
{
	result=result &(0xFFFFFFFF>>24);
	int temp=0;
	for(int i=0;i<8;i++)
	{
		temp+=result&0x1;
		result=result>>1;
	}

	if(temp%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;
}
 	
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=dest+src;
	
	set_CF_add(res,src,data_size);
	set_OF_add(res,src,dest,data_size);
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);	

	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=dest+src+cpu.eflags.CF;

	set_CF_adc(res,src,dest,data_size);
	set_OF_adc(res,src,dest,data_size);
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}


uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size)-sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);
	set_OF_sub(res,src,dest,data_size);
	set_CF_sub(res,src,data_size);

    return res&(0xFFFFFFFF>>(64-data_size));
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size)-(sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size)+cpu.eflags.CF);

	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);
	set_OF_sbb(res,src,dest,data_size);
	set_CF_sbb(res,src,dest,data_size);
	
	return res&(0xFFFFFFFF>>(32-data_size));
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
	uint64_t res=0;
	res = (uint64_t)dest*src;
	set_OF_CF_mul(res,dest,src,data_size);
	return res;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
	int64_t res=0;
	res=(int64_t)dest*src;
	set_OF_CF_imul(res,dest,src,data_size);
	return res;
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
	uint32_t res=0;
	res=dest/src;
	return res;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
	int32_t res=0;
	res=dest/src;
	return res;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	return dest%src;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	return dest%src;
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res = dest & src;

	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res = dest^src;

	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	res = dest | src;

	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {

	uint32_t res=0;
	if(src==0)
		return dest;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	while(src--)
	{
		cpu.eflags.CF= ((dest&(0x80000000>>(32-data_size)))>0);
		dest*=2;
		res=dest;
		set_PF(res);
		set_SF(res,data_size);
		set_ZF(res,data_size);
	}
	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	while(src--)
	{
		cpu.eflags.CF= ((dest&0x00000001)>0);
		dest/=2;
		res=dest;
		set_PF(res);
		set_SF(res,data_size);
		set_ZF(res,data_size);
	}
	return res&(0xFFFFFFFF>>(32-data_size)); 
}


uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	
	if(src==0)
		return dest;
	dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	while(src--)
	{
		cpu.eflags.CF= ((dest&0x00000001)>0);
		if(sign(dest)==1)
			dest = (0x80000000>>(32-data_size))|(dest/2);
		else
			dest=dest/2;
		res=dest;
		set_PF(res);
		set_SF(res,data_size);
		set_ZF(res,data_size);
	}

	return res&(0xFFFFFFFF>>(32-data_size)); 
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	while(src--)
	{
		cpu.eflags.CF= ((dest&(0x80000000>>(32-data_size)))>0);
		dest*=2;
		res=dest;
		set_PF(res);
		set_SF(res,data_size);
		set_ZF(res,data_size);
	}
	return res&(0xFFFFFFFF>>(32-data_size));
}

uint32_t alu_neg(uint32_t src,size_t data_size){
	
	uint32_t res=0;
	if(src==0)
		cpu.eflags.CF=0;
	else
		cpu.eflags.CF=1;

	res=~src+1;

	set_OF_add(res,(~src),1,data_size);
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);

	return res&(0xFFFFFFFF>>(32-data_size));
}

