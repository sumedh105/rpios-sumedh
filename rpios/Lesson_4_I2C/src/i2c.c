#include "gpio.h"
#include "peripherals/i2c.h"
#include "i2c.h"
#include "printf.h"

#define I2C_SPEED 100000

void i2c_init()
{
	gpio_pin_set_func(2, GFAlt0);
	gpio_pin_set_func(3, GFAlt0);
	gpio_pin_enable(2);
	gpio_pin_enable(3);

	I2CRegs->clock_divider = CORE_CLOCK_SPEED / I2C_SPEED;
}

i2c_status i2c_recv(u8 address, u8 *buffer, u32 size)
{
	int count = 0;

	I2CRegs->slave_address = address;
	I2CRegs->control = C_CLEAR;
	I2CRegs->status = S_CLKT | S_ERR | S_DONE;
	I2CRegs->data_length = size;
	I2CRegs->control = C_I2CEN | C_ST | C_READ;

	while (!(I2CRegs->status & S_DONE)) {
		while (I2CRegs->status & S_RXD) {
			*buffer++ = I2CRegs->data_fifo & 0xFF;
			count++;
		}
	}

	while (count < size && I2CRegs->status & S_RXD) {
		*buffer++ = I2CRegs->data_fifo & 0xFF;
		count++;
	}

	reg32 status = I2CRegs->status;

	I2CRegs->status = S_DONE;

	if (status & S_ERR) {
		return I2C_ACK_ERROR;
	} else if (status & S_CLKT) {
		return I2C_CLOCK_TIMEOUT;
	} else if (count < size) {
		return I2C_DATA_LOSS;
	}	

	return I2C_SUCCESS;
}

i2c_status i2c_send(u8 address, u8 *buffer, u32 size)
{
	int count = 0;

	I2CRegs->slave_address = address;
	I2CRegs->control = C_CLEAR;
	I2CRegs->status = S_CLKT | S_ERR | S_DONE;
	I2CRegs->data_length = size;
	I2CRegs->control = C_I2CEN | C_ST;
	
	while (!(I2CRegs->status & S_DONE)) {
		while (count < size && I2CRegs->status & S_TXD) {
			I2CRegs->data_fifo = *buffer++;
			count++;
		}
	}

	reg32 status = I2CRegs->status;

	I2CRegs->status = S_DONE;

	if (status & S_ERR) {
		return I2C_ACK_ERROR;
	} else if (status & S_CLKT) {
		return I2C_CLOCK_TIMEOUT;
	} else if (count < size) {
		return I2C_DATA_LOSS;
	}	

	return I2C_SUCCESS;
}


