#include "Acc.h"

void acc_begin(void)
{
    //Enable ACC port and set to high
    ACC_PORT_SET();
    ACC_DISABLE();

    //Enable Axis and Data Rate
#if defined(LOW_POWER_MODE)
    acc_write_register(LIS3DH_CTRL_REG1,
                       LIS3DH_DATA_RATE     |
                       LIS3DH_ENA_LOW_POW_MODE |
                       LIS3DH_ENABLE_Z_AXIS |
                       LIS3DH_ENABLE_Y_AXIS |
                       LIS3DH_ENABLE_X_AXIS );
    //setting accelerometer range
    acc_write_register(LIS3DH_CTRL_REG4, BLOCK_DATA_UPDATE | HIGH_RES_DISABLE);

#else
    acc_write_register(LIS3DH_CTRL_REG1,
                           LIS3DH_DATA_RATE     |
                           LIS3DH_ENABLE_Z_AXIS |
                           LIS3DH_ENABLE_Y_AXIS |
                           LIS3DH_ENABLE_X_AXIS );
    //setting accelerometer range
    acc_write_register(LIS3DH_CTRL_REG4, BLOCK_DATA_UPDATE | HIGH_RES_ENABLE);
#endif
    //setting interrupt
    acc_write_register(LIS3DH_CTRL_REG3, ENABLE_INTERRUPTS_ON_INT1);
    //setting accelerometer range
}

void acc_fifo_begin(void)
{
    uint8_t response;
    response = acc_read_register(LIS3DH_CTRL_REG5);
    acc_write_register(LIS3DH_CTRL_REG5, (response & ~LIS3DH_SET_FIFO_ENA_STATUS) | LIS3DH_SET_FIFO_ENA_STATUS );
    acc_write_register(LIS3DH_FIFO_CTRL_REG, FIFO_BUFFER_MODE  |
                                             TRIG_INT_ON_INT1  );
}

unsigned int acc_readRawAccelX(void){
    return acc_read_register16(LIS3DH_OUT_X_L,2);
}

unsigned int acc_readRawAccelY(void){
    return acc_read_register16(LIS3DH_OUT_Y_L,2);
}
unsigned int acc_readRawAccelZ(void){
    return acc_read_register16(LIS3DH_OUT_Z_L,2);
}
uint8_t acc_get_fifo_status(void)
{
  return  acc_read_register(LIS3DH_FIFO_SRC_REG);
}

void acc_clear_fifo(void)
{
    uint8_t buffer[6];
    while( (acc_get_fifo_status() & 0x20 ) == 0 )
    {
        acc_get_xyz(buffer);
    }
}

void acc_fifoStartRec(void)
{
    uint8_t response;
    response = acc_read_register(LIS3DH_FIFO_CTRL_REG);
    acc_write_register(LIS3DH_FIFO_CTRL_REG, response & 0x3F);
    response = acc_read_register(LIS3DH_FIFO_CTRL_REG);
    acc_write_register(LIS3DH_FIFO_CTRL_REG, (response & 0x3F)| FIFO_BUFFER_MODE);
}


void en_acc_int(void)
{
    P2DIR &= ~(ACC_INT1_PIN | ACC_INT2_PIN);            // set INT1 & INT2 as input
    P2OUT &=  ~(ACC_INT1_PIN | ACC_INT2_PIN);           // set INT1 & INT2 pulled high
    P2REN |=  (ACC_INT1_PIN | ACC_INT2_PIN);              //
    P2IES &=  ~(ACC_INT1_PIN | ACC_INT2_PIN);           // set INT1 & INT2 on falling edge
    P2IFG &= ~(ACC_INT1_PIN | ACC_INT2_PIN);            // clear interrupt on INT1 and IN2
    P2IE  |=  (ACC_INT1_PIN | ACC_INT2_PIN);              // enable INT1 & INT2 on Port2
    _EINT();                            // Enable interrupts (set GIE in SR)
}