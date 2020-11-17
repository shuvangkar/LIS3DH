#include "acc_control.h"

uint8_t pIndex=0;

uint8_t xyzBuffer[6];


void accIsr()
{
    payload_t *headPtr = (payload_t*)ramQHead();
    readAcc(headPtr);
}

uint8_t pIndex = 0;

void *readAcc(payload_t *ptr)
{    
    payload_t *curentHead = ptr;
    uint8_t i = 0;
    do
    {
        acc_get_xyz(xyzBuffer);
        curentHead -> x[pIndex] = xyzBuffer[1];
        curentHead -> y[pIndex] = xyzBuffer[3];
        curentHead -> z[pIndex] = xyzBuffer[5];
        pIndex++;
        if( pIndex >= SAMPLE_IN_PACKET)
        {
            curentHead =  ramQUpdateHead();
            pIndex = 0;
        }
    }while(++i <ACC_MAX_POINT);
}