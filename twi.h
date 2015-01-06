#ifndef I2C_H
#define I2C_H

#define TWI_BUFFER_SIZE 32
#define TWI_TWBR 0x0C // TWI Bit Rate reg setting

#define TRUE 1
#define FALSE 0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

extern uint8_t TWI_status; // first bit is 1 if busy, 0 if ready to transmit, second bit is 1 if master, 0 if slave

// Common Functions
uint8_t TWI_busy(void);
uint8_t TWI_is_master(void);
uint8_t TWI_is_slave(void);
uint8_t TWI_status(void);

// Master functions
// Will block until finished
void TWI_master_init(void);
uint8_t TWI_write_bytes(uint8_t address, uint8_t *data, uint8_t data_len);
uint8_t TWI_read_bytes(uint8_t address, uint8_t *buffer, uint8_t num_bytes);
uint8_t TWI_read_bytes_from_command(uint8_t address, uint8_t command, uint8_t *buffer, uint8_t num_bytes);

// Slave functions
// non-blocking
void TWI_slave_init(uint8_t address);
uint8_t TWI_write_response(uint8_t *data, uint8_t data_len);
uint8_t TWI_set_command_interrupt(uint8_t command, uint8_t (*callback)(uint8_t *data, uint8_t data_len));

ISR (TWI_vect);

/****************************************************************************
  TWI State codes
****************************************************************************/
// General TWI Master staus codes                      
#define TWI_START                  0x08  // START has been transmitted  
#define TWI_REP_START              0x10  // Repeated START has been transmitted
#define TWI_ARB_LOST               0x38  // Arbitration lost

// TWI Master Transmitter staus codes                      
#define TWI_MTX_ADR_ACK            0x18  // SLA+W has been tramsmitted and ACK received
#define TWI_MTX_ADR_NACK           0x20  // SLA+W has been tramsmitted and NACK received 
#define TWI_MTX_DATA_ACK           0x28  // Data byte has been tramsmitted and ACK received
#define TWI_MTX_DATA_NACK          0x30  // Data byte has been tramsmitted and NACK received 

// TWI Master Receiver staus codes  
#define TWI_MRX_ADR_ACK            0x40  // SLA+R has been tramsmitted and ACK received
#define TWI_MRX_ADR_NACK           0x48  // SLA+R has been tramsmitted and NACK received
#define TWI_MRX_DATA_ACK           0x50  // Data byte has been received and ACK tramsmitted
#define TWI_MRX_DATA_NACK          0x58  // Data byte has been received and NACK tramsmitted

// TWI Slave Transmitter staus codes
#define TWI_STX_ADR_ACK            0xA8  // Own SLA+R has been received; ACK has been returned
#define TWI_STX_ADR_ACK_M_ARB_LOST 0xB0  // Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
#define TWI_STX_DATA_ACK           0xB8  // Data byte in TWDR has been transmitted; ACK has been received
#define TWI_STX_DATA_NACK          0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received
#define TWI_STX_DATA_ACK_LAST_BYTE 0xC8  // Last data byte in TWDR has been transmitted (TWEA = 0); ACK has been received

// TWI Slave Receiver staus codes
#define TWI_SRX_ADR_ACK            0x60  // Own SLA+W has been received ACK has been returned
#define TWI_SRX_ADR_ACK_M_ARB_LOST 0x68  // Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
#define TWI_SRX_GEN_ACK            0x70  // General call address has been received; ACK has been returned
#define TWI_SRX_GEN_ACK_M_ARB_LOST 0x78  // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
#define TWI_SRX_ADR_DATA_ACK       0x80  // Previously addressed with own SLA+W; data has been received; ACK has been returned
#define TWI_SRX_ADR_DATA_NACK      0x88  // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
#define TWI_SRX_GEN_DATA_ACK       0x90  // Previously addressed with general call; data has been received; ACK has been returned
#define TWI_SRX_GEN_DATA_NACK      0x98  // Previously addressed with general call; data has been received; NOT ACK has been returned
#define TWI_SRX_STOP_RESTART       0xA0  // A STOP condition or repeated START condition has been received while still addressed as Slave

// TWI Miscellaneous status codes
#define TWI_NO_STATE               0xF8  // No relevant state information available; TWINT = 0
#define TWI_BUS_ERROR              0x00  // Bus error due to an illegal START or STOP condition

#endif
