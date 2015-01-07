#ifndef DUINO_TWI_H
#define DUINO_TWI_H

#define TWI_BUFFER_SIZE 32
#define TWI_TWBR 0x0C // TWI Bit Rate reg setting

#define TRUE 1
#define FALSE 0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

typedef union {
	uint8_t all;
	struct {
		uint8_t is_slave:1;
		uint8_t is_busy:1;
		uint8_t rest:6;
	}; 
} TWI_status_type;

extern TWI_status_type TWI_status; // first bit is 1 if busy, 0 if ready to transmit, second bit is 1 if slave, 0 if master

// Common Functions
#define TWI_is_busy() (TWI_status.is_busy)
#define TWI_is_master() (! TWI_status.is_slave)
#define TWI_is_slave() (TWI_statis.is_slave)
uint8_t TWI_state(void);

// Master functions
// Will block until finished
void TWI_master_init(void);
uint8_t TWI_write_bytes(uint8_t address, uint8_t *data, uint8_t data_len);
uint8_t TWI_read_bytes(uint8_t address, uint8_t *buffer, uint8_t num_bytes);
uint8_t TWI_read_bytes_from_command(uint8_t address, uint8_t command, uint8_t *buffer, uint8_t num_bytes);

// Slave functions
// non-blocking
void TWI_slave_init(uint8_t address);
void TWI_write_response(uint8_t *data, uint8_t data_len);
void TWI_set_command_callback(uint8_t command, uint8_t (*callback)(uint8_t *data, uint8_t data_len));

ISR (TWI_vect);

#endif
