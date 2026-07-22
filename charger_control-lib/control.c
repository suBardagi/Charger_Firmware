/*
created by suBardagi
*/

#include "control.h"
#include "board-lib/board.h"

volatile uint16_t PFC_I_SENSE = 0;
volatile uint16_t PFC_VDC_SENSE = 0;
volatile uint16_t PFC_VAC_SENSE = 0;
volatile uint16_t DAB_IND_I_SENSE = 0;
volatile uint16_t DAB_VOUT_SENSE = 0;
volatile uint16_t DAB_I_OUT_SENSE = 0;

__interrupt void adca1_isr(void)
{
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
