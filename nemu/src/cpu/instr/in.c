#include "cpu/instr.h"
#include "device/port_io.h"

uint32_t get_date(size_t size)
{
    uint16_t port_addr=cpu.edx & 0xFFFF;
    size_t data_len= size;
    uint32_t data= pio_read(port_addr,data_len);
    return data;
}

make_instr_func(in_b){
#ifdef HAS_DEVICE_SERIAL
    cpu.eax=get_date(1);
    return 1;
#else
    printf("please implement in\n");assert(0);
#endif
}

make_instr_func(in_v){
#ifdef HAS_DEVICE_SERIAL
    cpu.eax=get_data(data_size/8);
    return 1;
#else
    printf("please implement in\n");assert(0);
#endif
}