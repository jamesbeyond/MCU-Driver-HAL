#include "serial_api.h"

serial_t my_uart;

int main()
{
    serial_t *serial = &my_uart;
    serial_init(serial, CONSOLE_TX, CONSOLE_RX);
    serial_baud(serial, 115200);

    const char str[] = "Hello world!\n";
    for (unsigned int i = 0; i < sizeof(str); ++i) {
        serial_putc(serial, str[i]);
    }

    while(1){}
}