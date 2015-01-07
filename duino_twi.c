#include "duino_twi.h"

TWI_status_type TWI_status = {0}; // Not ready to transmit, currently a slave

static uint8_t TWI_master_buffer[TWI_BUFFER_SIZE];
static uint8_t TWI_slave_buffer[TWI_BUFFER_SIZE];
static uint8_t TWI_msg_size;
static uint8_t TWI_state;
static void (*TWI_callbacks)(uint8_t *data, uint8_t data_len)[255];

uint8_t TWI_get_state() {
	while (TWI_is_busy());
	return TWI_state;
}

void TWI_master_init() {
	TWI_status.is_slave = 0;
	/* etc */
}

uint8_t TWI_write_bytes(uint8_t address, uint8_t *data, uint8_t data_len) {
	if (TWI_is_slave()) {
		/* fail */
	}
	TWI_master_buffer[0] = address << 1 | 0;
	int i;
	for (i = 1; i < data_len; ++i) {
		TWI_master_buffer[i] = data[i - 1]
	}
	TWI_msg_size = data_len + 1;
	/* set up for transmitting */
	return TWI_get_state();
}

uint8_t TWI_read_bytes(uint8_t address, uint8_t *buffer, uint8_t num_bytes) {
	if (TWI_is_slave()) {
		/* fail */
	}
	TWI_master_buffer[0] = address << 1 | 1;
	TWI_msg_size = num_bytes;
	/* set up for transmitting */
	uint8_t state = TWI_get_state();
	if (/* state is success */) {
		int i;
		for (i = 1; i < num_bytes; ++i) {
			buffer[i - 1] = TWI_master_buffer[i];
		}
	}
	return state;
}

uint8_t TWI_read_bytes_from_command(uint8_t address, uint8_t command, uint8_t *buffer, uint8_t num_bytes) {
	/* figure out how to send repeated start, rest should be similar to write_bytes and read_bytes */
}

void TWI_slave_init() {
	TWI_status.is_slave = 1;
	/* etc */
}

void TWI_write_response(uint8_t *data, uint8_t data_len) {
	TWI_msg_size = data_len;
	int i;
	for (i = 0; i < data_len; ++i) {
		TWI_slave_buffer[i] = data[i];
	}
}

void TWI_set_command_callback(uint8_t command, void (*callback)(uint8_t *data, uint8_t data_len)) {
	TWI_callbacks[command] = callback;
}

ISR (TWI_vect) {
	switch (TWSR) {
		/* huge list of cases */
	}
}
