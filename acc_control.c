#include "acc_control.h"

uint8_t ptrIndex=0;

uint8_t xyzBuffer[6];


void accIsr()
{
    payload_t *headPtr = (payload_t*)ramQHead();
    readAcc(headPtr);
}


void *readAcc(payload_t *ptr)
{    
    payload_t *curentHead = ptr;
    uint8_t i = 0;
    do
    {
        acc_get_xyz(xyzBuffer);
        curentHead -> x[ptrIndex] = xyzBuffer[1];
        curentHead -> y[ptrIndex] = xyzBuffer[3];
        curentHead -> z[ptrIndex] = xyzBuffer[5];
        ptrIndex++;
        if( ptrIndex >= SAMPLE_IN_PACKET)
        {
            curentHead =  ramQUpdateHead();
            ptrIndex = 0;
        }
    }while(++i <ACC_MAX_POINT);
}
