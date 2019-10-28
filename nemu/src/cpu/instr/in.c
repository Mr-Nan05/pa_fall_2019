#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b){
#ifdef HAS_DEVICE_SERIAL
   uint16_t port = cpu.edx & 0xffff;
   cpu.eax = (cpu.eax & 0xffffff00) + pio_read(port, 1);
   return 1;
#else
    printf("please implement in\n");assert(0);
#endif
}

make_instr_func(in_v){
#ifdef HAS_DEVICE_SERIAL

    uint16_t port = cpu.edx & 0xffff;
    if(data_size == 16){
    cpu.eax = (cpu.eax & 0xffff0000) + pio_read(port, 2);
    }
    else if(data_size == 32){
    cpu.eax = pio_read(port, 4);
    }

    return 1;
#else
    printf("please implement in\n");assert(0);
#endif
}