#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(out_b){
#ifdef HAS_DEVICE_SERIAL
    uint16_t port = cpu.edx & 0xffff;
    uint8_t data = cpu.eax & 0xff;
    pio_write(port, 1, data);
    return 1;
#else
    printf("please implement out\n");assert(0);
#endif
}

make_instr_func(out_v){
#ifdef HAS_DEVICE_SERIAL
    uint16_t port = cpu.edx & 0xffff;
    if(data_size == 16){
        uint16_t data = cpu.eax & 0xffff;
        pio_write(port, 2, data);
    }
    else if(data_size == 32){
        uint32_t data = cpu.eax;
        pio_write(port, 4, data);
    }
    return 1;
#else
    printf("please implement out\n");assert(0);
#endif
}