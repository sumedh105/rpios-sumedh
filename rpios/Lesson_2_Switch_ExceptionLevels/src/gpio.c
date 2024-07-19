#include "gpio.h"

void gpio_pin_set_func(u8 pinNumber, GpioFunc func) {
	// 3 is the no of bits occupied by each GPIO pin in a register. This means
	// there can be 10 GPIO pins accomodated in each reg.
	u8 bitStart = (pinNumber * 3) % 30;

	// 10 is the no of GPIO pins in each register.
	u8 reg = pinNumber / 10;

	u32 selector = REGS_GPIO->func_select[reg];
	selector &= ~(0x7 << bitStart);
	selector |= (func << bitStart);

	REGS_GPIO->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pinNumber) {
	// 16 is the no of GPIO pins in each register.
	u8 reg = pinNumber / 16;

	// 2 is the no of bits occupied by each GPIO pin in a register. This
	// means there can be 16 GPIO pins accomodated in ecah reg.
	u8 bitStart = (pinNumber * 2) % 32;

	u32 selector = REGS_GPIO->pup_pdn_cntrl_reg[reg];

	// Switch off the 14th and 15th GPIO pins. This means, switch off the bits
	// 28-31 in the selected register.
	//selector = selector & 0x0FFFFFFF; 
	
	//The below logic would set the corresponding bits to 0. For example,
	//in case of pinNumber 14, the bits 28-29 would be set to 0. In case of
	//pinNumber 15, the bits 30-31 would be set to 0.
	selector = selector & ~(0x3 << bitStart); 

	REGS_GPIO->pup_pdn_cntrl_reg[reg] = selector;
}


