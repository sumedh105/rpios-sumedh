#include "common.h"
#include "mini_uart.h"
#include "printf.h"

void putc(void *p, char c)
{
	if (c == '\n') {
		uart_send('\r');
	}

	uart_send(c);
}

u32 get_el();

void kernel_main()
{
	uart_init();
	init_printf(0, putc);
	//uart_send_string("Raspberyy PI Bare Metal OS Initializing...\n");
	printf("\nRaspberyy PI Bare Metal OS Initializing...\n");

#if RPI_VERSION == 3
	//uart_send_string("\tBoard: Raspberry PI 3\n");
	printf("\tBoard: Raspberry PI 3\n");
#endif

#if RPI_VERSION == 4
	//uart_send_string("\tBoard: Raspberry PI 4\n");
	printf("\tSumedh's Board: Raspberry PI 4\n");
#endif

	//uart_send_string("\n\nDone\n");
	printf("\n\nDone\n");

	printf("\n Exception level: %d\n", get_el());

	while (1) {
		uart_send(uart_recv());
	}
}
