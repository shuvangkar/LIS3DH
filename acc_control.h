#ifndef ACC_CONTROL_H_
#define ACC_CONTROL_H_

#include "Acc.h"

void accSetBuffer(payload_t **pldBuf);

payload_t *getAccdata(payload_t *ptr);

void *readAcc(payload_t *ptr);
void accIsr();


#endif