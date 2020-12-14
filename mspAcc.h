#ifndef ACC_LIS3DH_H_
#define ACC_LIS3DH_H_

#include <msp430.h>
#include "mspSPI.h"
#include "acc_driver.h"
#include "acc_control.h"
//#include "mspSerial.h"


uint8_t is_connected();
void acc_begin(void);
void acc_fifo_begin(void);
void acc_clear_fifo(void);
uint8_t acc_get_fifo_status(void);
void en_acc_int(void);
void print_acc_xyx(uint8_t *buffer6);


void acc_fifoStartRec(void);

unsigned int acc_readRawAccelX(void);
unsigned int acc_readRawAccelX(void);
unsigned int acc_readRawAccelX(void);

#endif /* ACC_LIS3DH_H_ */
