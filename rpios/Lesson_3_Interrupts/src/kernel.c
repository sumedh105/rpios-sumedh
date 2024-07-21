#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"

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

	irq_init_vectors();
	enable_interrupt_controller();
	enable_irq();
	timer_init();

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

	printf("\nSleeping 200 ms...\n");
	timer_sleep(200);

	printf("\nSleeping 200 ms...\n");
	timer_sleep(200);

	printf("\nSleeping 200 ms...\n");
	timer_sleep(200);

	printf("\nSleeping 2 seconds...\n");
	timer_sleep(2000);
	
	printf("\nSleeping 2 seconds...\n");
	timer_sleep(2000);

	printf("\nSleeping 2 seconds...\n");
	timer_sleep(2000);

	printf("\nSleeping 5 seconds...\n");
	timer_sleep(5000);

	printf("\nDONE\n");

	while (1) {
		uart_send(uart_recv());
	}
}
