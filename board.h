/* 
created by suBardagi
*/

#ifndef BOARD_H_
#define BOARD_H_

#include "driverlib.h"
#include "device.h"

#define EPWM_CLK_FREQ       100000000U  // System frequency
#define CHARGER_PWM_FREQ    200000U  // PWM frequency
#define PWM_PERIOD_TICKS    (EPWM_CLK_FREQ/(2U*CHARGER_PWM_FREQ))

#define PFC_I_SENSE_CH      ADC_CH_ADCIN0
#define PFC_V_DC_MID_CH     ADC_CH_ADCIN2
#define PFC_V_AC_CH         ADC_CH_ADCIN4

#define DAB_IND_I_SENSE_CH  ADC_CH_ADCIN10
#define DAB_I_OUT_SENSE_CH  ADC_CH_ADCIN1
#define DAB_VOUT_SENSE_CH   ADC_CH_ADCIN6
#define ACQPS_SYS_CLKS  14

void Board_initGPIO(void);
void Board_initPWM(void);
void Board_initADC(void);

#endif /* BOARD_H_ */
