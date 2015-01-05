#ifndef I2C_H
#define I2C_H

//All commands return 0 for success, 1 for failure

// Master functions
uint8_t write_bytes(uint8_t address, uint8_t *bytes);
uint8_t read_bytes(uint8_t address, uint8_t *buffer, int num_bytes);
uint8_t read_bytes_from_command(uint8_t address, uint8_t *bytes, uint8_t *buffer, int num_bytes);

// Slave functions
uint8_t register_interrupt(uint8_t command, uint8_t (*callback)(uint8_t *data));

// parts of commands
uint8_t begin_transmission(uint8_t address);
uint8_t write_byte(uint8_t byte);
uint8_t read_byte(uint8_t *byte);
uint8_t end_transmission();

#endif
