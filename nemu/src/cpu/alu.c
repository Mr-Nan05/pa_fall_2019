#include "cpu/cpu.h"



uint32_t data_deal(uint32_t data,size_t data_size)
{
	return sign_ext(data&(0xFFFFFFFF>>(32-data_size)),data_size);
}

uint32_t data_ext(uint32_t data,int n)
{
	if(n==16)
	return 	sign_ext(data&0xFFFF,16);
	else return 	sign_ext(data&0xFF,8);
}

uint32_t forReturn(uint32_t res,int n,size_t data_size)
{
	return res&(0xFFFFFFFF>>(n-data_size));
}

void set_ZF(uint32_t r,size_t s)
{
	r = r &(0xFFFFFFFF>>(32 - s));
	cpu.eflags.ZF = (r==0)?1:0;
}

void set_SF(uint32_t r,size_t s)
{
	r=data_deal(r,s);
	cpu.eflags.SF=sign(r);
}

void set_PF(uint32_t r)
{
	r&=(0xFFFFFFFF>>24);
	int i=0,j=0;
	for(;j<=7;j++)
	{
		i+=r&0x1;
		r>>=1;
	}

	if(i%2==0)
	cpu.eflags.PF=1;
	else
	cpu.eflags.PF=0;
	{
		/* code */
	}
	
}

void set_CF_add(uint32_t result, uint32_t src, size_t data_size)
{
		result=data_deal(result,data_size);
		src = data_deal(src,data_size);
		cpu.eflags.CF = result<src;
}


void set_OF_add(uint32_t r,uint32_t s,uint32_t d,size_t size)
{
		switch(size)
		{
			case 16:
			r = data_ext(r,16);
			s = data_ext(s,16);
			d = data_ext(d,16);
			break;
			case 8:
						r = data_ext(r,8);
						s= data_ext(s,8);
						d = data_ext(d,8);
						break; 
			default:break;
		}

		if(sign(s) == sign(d))
		{
				if(sign(s)!=sign(r))
					cpu.eflags.OF=1;
				else cpu.eflags.OF=0;
		}
		else cpu.eflags.OF=0;
}

void set_CF_adc(uint32_t r,uint32_t s, uint32_t d,size_t size)
{
	r = data_deal(r,size);
	s = data_deal(s,size);
	d  =data_deal(d,size);
	if(d)cpu.eflags.CF=r<=s?1:0;
	else cpu.eflags.CF=r<s?1:0;
}

void set_OF_adc(uint32_t r,uint32_t s,uint32_t d,size_t size)
{
	if(size==16)
	{
		 data_ext(r,16);
			s = data_ext(s,16);
			d = data_ext(d,16);
	}else if(size==8)
	{
		r = data_ext(r,8);
						s= data_ext(s,8);
						d = data_ext(d,8);
	}
if(sign(s)==sign(d))
		cpu.eflags.OF=sign(s)!=sign(r)?1:0;
else  cpu.eflags.OF=0;


}

void set_CF_sub(uint32_t r,uint32_t s,size_t data_size)
{
	s=data_deal(s,data_size);
	cpu.eflags.CF=s?!(r<(~s+1)):0;
}

void set_OF_sub(uint32_t r,uint32_t s,uint32_t d,size_t size)
{
	if(size==16)
	{
			r = data_ext(r,16);
			s = data_ext(s,16);
			d = data_ext(d,16);

	}else if(size == 8)
	{
		r = data_ext(r,8);
						s= data_ext(s,8);
						d = data_ext(d,8);
	}
	if(sign(~s)==sign(d))
	{
		cpu.eflags.OF=(sign(~s)!=sign(r));
	}
	else cpu.eflags.OF=0;
}

//point1
void set_CF_sbb(uint32_t r,uint32_t s,uint32_t d,size_t size)
{
r = data_deal(r,size);
	s = data_deal(s,size);
	d  =data_deal(d,size);
if(s==0)
cpu.eflags.CF=r>d?1:0;
else cpu.eflags.CF=r>=d?1:0;
}

void set_OF_sbb(uint32_t r ,uint32_t s,uint32_t d,size_t size)
{
	if(size==8)
	{
			r = data_ext(r,8);
						s= data_ext(s,8);
						d = data_ext(d,8);

	}
	else if(size ==16)
	{
			r = data_ext(r,16);
			s = data_ext(s,16);
			d = data_ext(d,16);

	}
if(sign(~s)==sign(d))
	cpu.eflags.OF=sign(~s)!=sign(r)?1:0;
else cpu.eflags.OF=0;

}

void set_OF_CF_mul(uint64_t r,uint32_t d,uint32_t res,size_t size)
{
	if(size==8)
		cpu.eflags.CF=cpu.eflags.OF=(((r>>8)|0x00)>0);
	else if(size ==16)
		cpu.eflags.CF=cpu.eflags.OF= (((r>>16)|0x0000)>0);
	else if(size ==32)
	cpu.eflags.CF=cpu.eflags.OF= (((r>>32)|0x00000000)>0);
}

void set_OF_CF_imul(int64_t r,int32_t d,int32_t s,size_t size)
{
	if(size==32)
	cpu.eflags.CF=cpu.eflags.OF=!((((r>>31)^0x1FFFFFFFF)==0)|(((r>>31)|0x000000000)==0));
	else if(size ==16)
	cpu.eflags.CF=cpu.eflags.OF=!((((r>>15)^0x1FFFF)==0)|(((r>>15)|0x00000)==0));
	else if(size==8)
	cpu.eflags.CF=cpu.eflags.OF=!((((r>>7)^0x1FF)==0)|(((r>>7)|0x000)==0));

}

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
uint32_t res=0;
	res=dest+src;
	
	set_CF_add(res,src,data_size);
	set_OF_add(res,src,dest,data_size);
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);	
return forReturn(res,32,data_size);

}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
uint32_t res=0;
	res=dest+src+cpu.eflags.CF;
	
	set_CF_adc(res,src,dest,data_size);
	set_OF_adc(res,src,dest,data_size);
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);	
	return forReturn(res,32,data_size);
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
uint32_t res=0;
res=data_deal(dest,data_size)-data_deal(src,data_size);

set_PF(res);
set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);
	set_OF_sub(res,src,dest,data_size);
	set_CF_sub(res,src,data_size);
	return forReturn(res,64,data_size);
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t res=0;
res=data_deal(dest,data_size)-data_deal(src,data_size+cpu.eflags.CF);
set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);
	set_OF_sbb(res,src,dest,data_size);
	set_CF_sbb(res,src,dest,data_size);

	return forReturn(res,32,data_size);
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
uint64_t res=0;
res = (uint64_t)dest*src;
set_OF_CF_mul(res,dest,src,data_size);
return  (uint64_t)dest*src;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
int64_t res=0;
	res=(int64_t)dest*src;
	set_OF_CF_imul(res,dest,src,data_size);
	return  (uint64_t)dest*src;
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
return (uint32_t)(dest/src);
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
return (uint32_t)(dest/src);
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
return dest%src;
}

int32_t alu_imod(int64_t src, int64_t dest)
{
return dest%src;
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
cpu.eflags.CF=0;
cpu.eflags.OF=0;
set_PF(dest&src);
set_ZF(dest&src,data_size);
set_SF(dest&src,data_size);
return forReturn(dest&src,32,data_size);
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
cpu.eflags.CF=0;
cpu.eflags.OF=0;
set_PF(dest^src);
set_ZF(dest^src,data_size);
set_SF(dest^src,data_size);
return forReturn(dest^src,32,data_size);
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
cpu.eflags.CF=0;
cpu.eflags.OF=0;
set_PF(dest|src);
set_ZF(dest|src,data_size);
set_SF(dest|src,data_size);
return forReturn(dest|src,32,data_size);
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
if(!src)
return dest;
dest=data_deal(dest,data_size);
while(src--)
	{
		cpu.eflags.CF= ((dest&(0x80000000>>(32-data_size)))>0);
		dest*=2;
		set_PF(dest);
		set_SF(dest,data_size);
		set_ZF(dest,data_size);
	}
	return forReturn(dest,32,data_size);
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{

	dest=data_deal(dest,data_size);
	while(src--)
	{
		cpu.eflags.CF= ((dest&0x00000001)>0);
		dest/=2;
		set_PF(dest);
		set_SF(dest,data_size);
		set_ZF(dest,data_size);
	}
return forReturn(dest,32,data_size);
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{

	if(!src)
	return dest;
	dest=data_deal(dest,data_size);
	while(src--)
	{
		cpu.eflags.CF= ((dest&0x00000001)>0);
		if(sign(dest)==1)
		dest = (0x80000000>>(32-data_size))|(dest/2);
		else dest/=2;
		set_PF(dest);
		set_SF(dest,data_size);
		set_ZF(dest,data_size);
	}
	return forReturn(dest,32,data_size);
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
	dest=forReturn(dest,32,data_size);
	while(src--)
	{
		cpu.eflags.CF= ((dest&(0x80000000>>(32-data_size)))>0);
		dest*=2;
		set_PF(dest);
		set_SF(dest,data_size);
		set_ZF(dest,data_size);
	}
	return forReturn(dest,32,data_size);
}
