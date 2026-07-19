/*
created by suBardagi
*/

#include "board.h"
#include "epwm.h"
#include "inc/hw_memmap.h"
#include "sysctl.h"
#include "adc.h"
#include "driverlib.h"

void Board_initGPIO(void)
{
    // ePWM routing
    GPIO_setPinConfig(GPIO_0_EPWM1_A);
    GPIO_setPinConfig(GPIO_1_EPWM1_B);
    GPIO_setPinConfig(GPIO_2_EPWM2_A);
    GPIO_setPinConfig(GPIO_3_EPWM2_B);
    GPIO_setPinConfig(GPIO_4_EPWM3_A);
    GPIO_setPinConfig(GPIO_5_EPWM3_B);
    GPIO_setPinConfig(GPIO_6_EPWM4_A);
    GPIO_setPinConfig(GPIO_7_EPWM4_B);
    GPIO_setPinConfig(GPIO_8_EPWM5_A);
    GPIO_setPinConfig(GPIO_9_EPWM5_B);
    GPIO_setPinConfig(GPIO_10_EPWM6_A);
    GPIO_setPinConfig(GPIO_11_EPWM6_B);

    // CAN routing
    GPIO_setPinConfig(GPIO_12_CANB_TX);
    GPIO_setPinConfig(GPIO_13_CANB_RX);

    // UART routing
    GPIO_setPinConfig(GPIO_16_SCIA_TX);
    GPIO_setPinConfig(GPIO_17_SCIA_RX);

    // Relay drive
    GPIO_setPinConfig(GPIO_22_GPIO22);
    GPIO_setDirectionMode(22, GPIO_DIR_MODE_OUT);
    GPIO_writePin(22, 0);

    // Fan drive
    GPIO_setPinConfig(GPIO_23_GPIO23);
    GPIO_setDirectionMode(23, GPIO_DIR_MODE_OUT);
    GPIO_writePin(23, 0);
}

void Board_initADC(void)
{
    // ADC reference
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);
    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);

    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_2_0);
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);

    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(1000);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, PFC_I_SENSE_CH, ACQPS_SYS_CLKS);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, PFC_V_DC_MID_CH, ACQPS_SYS_CLKS);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA, PFC_V_AC_CH, ACQPS_SYS_CLKS);

    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER2);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
}

void Board_initEPWM(void)
{
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC); // freezing ePWMs

    // Time-base submodule
    EPWM_setTimeBasePeriod(EPWM6_BASE, PWM_PERIOD_TICKS);
    EPWM_setTimeBaseCounterMode(EPWM6_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setClockPrescaler(EPWM6_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_disablePhaseShiftLoad(EPWM6_BASE);
    EPWM_setPhaseShift(EPWM6_BASE, 0U);
    EPWM_setSyncOutPulseMode(EPWM6_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    EPWM_setCounterCompareValue(EPWM6_BASE, EPWM_COUNTER_COMPARE_A, (PWM_PERIOD_TICKS/2U));

    EPWM_setActionQualifierAction(EPWM6_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM6_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
}

void Board_init(void){
    Board_initGPIO();
    Board_initEPWM();
    Board_initADC();
}