#include "utils.h"
#include "printf.h"
#include "entry.h"
#include "peripherals/irq.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "timer.h"

const char entry_error_messages[16][32] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",
	"ERROR_INVALID_EL1t",

	"SYNC_INVALID_EL1h",
	"IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",
	"ERROR_INVALID_EL1h",

	"SYNC_INVALID_EL0_64",
	"IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",
	"ERROR_INVALID_EL0_64",

	"SYNC_INVALID_EL0_32",
	"IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",
	"ERROR_INVALID_EL0_32",
};

void show_invalid_entry_message(u32 type, u64 esr, u64 address)
{
	printf("ERROR CAUGHT: %s - %d, ESR: %x, Address: %x\n", entry_error_messages[type], type, esr, address);
}

void enable_interrupt_controller()
{
	//REGS_IRQ->irq0_enable_0 = AUX_IRQ | SYS_TIMER_IRQ_1;
	REGS_IRQ->irq0_enable_0 = SYS_TIMER_IRQ_1 | SYS_TIMER_IRQ_3;
}

void handle_irq()
{
	u32 irq;

	irq = REGS_IRQ->irq0_pending_0;

	//printf("Sumedh W. Jambekar in handle_irq() and irq: %x\n", irq);
	while (irq) {
		//printf("Sumedh W. Jambekar in handle_irq() and in outer while loop\n");
		if (irq & AUX_IRQ) {
			//printf("Sumedh W. Jambekar in handle_irq() and in outer while loop and in inner if condition\n");
			irq &= ~AUX_IRQ;

			while ((REGS_AUX->mu_iir & 4) == 4) {
				printf("Sumedh W. Jambekar in handle_irq() and in outer while loop and in inner if condition and in inner while loop\n");
				printf("UART Recv: ");
				uart_send(uart_recv());
				printf("\n");
			}	
		}

		//printf("Sumedh W. Jambekar in handle_irq() and in outer while loop and (irq & SYS_TIMER_IRQ_1): %x\n", (irq & SYS_TIMER_IRQ_1));
		if (irq & SYS_TIMER_IRQ_1) {
			irq &= ~SYS_TIMER_IRQ_1;

			//printf("Calling handle_timer_1()\n");
			handle_timer_1();
		}

		//printf("Sumedh W. Jambekar in handle_irq() and in outer while loop and (irq & SYS_TIMER_IRQ_3): %x\n", (irq & SYS_TIMER_IRQ_3));
		if (irq & SYS_TIMER_IRQ_3) {
			irq &= ~SYS_TIMER_IRQ_3;

			//printf("Calling handle_timer_3()\n");
			handle_timer_3();
		}

		//printf("irq:%x\n", irq);
	}
}
