/*
created by suBardagi
*/

#include "control.h"
#include "adc.h"
#include "board-lib/board.h"
#include "inc/hw_memmap.h"

volatile uint16_t PFC_I_SENSE = 0;
volatile uint16_t PFC_VDC_SENSE = 0;
volatile uint16_t PFC_VAC_SENSE = 0;
volatile uint16_t DAB_IND_I_SENSE = 0;
volatile uint16_t DAB_VOUT_SENSE = 0;
volatile uint16_t DAB_I_OUT_SENSE = 0;

__interrupt void adca1_isr(void)
{
    PFC_I_SENSE = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    PFC_I_SENSE = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
    PFC_I_SENSE = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);

    PFC_I_SENSE = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3);
    PFC_I_SENSE = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4);
    PFC_I_SENSE = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
