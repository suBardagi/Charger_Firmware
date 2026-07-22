/*
created by suBardagi
*/

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "driverlib.h"
#include "device.h"

extern volatile uint16_t PFC_I_SENSE;
extern volatile uint16_t PFC_VDC_SENSE;
extern volatile uint16_t PFC_VAC_SENSE;
extern volatile uint16_t DAB_IND_I_SENSE;
extern volatile uint16_t DAB_VOUT_SENSE;
extern volatile uint16_t DAB_I_OUT_SENSE;

__interrupt void adca1_isr(void);

#endif
