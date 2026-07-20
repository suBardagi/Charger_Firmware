/*
created by suBardagi
*/

#ifndef PID_H
#define PID_H

#include "device.h"
#include "driverlib.h"

typedef struct{
    float Kp;
    float Kd;
    float Ki;
    float integral;
    float prev_error;
    float prev_prev_error;
     uint8_t step_count;
    uint8_t started;

    // limits for the PID
    float integral_max;
    float integral_min;
    float output_max;
    float output_min;

    float dt;

    uint8_t use_limits;
    uint8_t use_dt;

    float deriv_filter_alpha;
    float derivative_filtered;
} PID_controller;

void pid_init(PID_controller *pid, float Kp, float Ki, float Kd, uint8_t use_limits, uint8_t use_dt, ...);

float pid_compute(PID_controller *pid, float set, float measurement);

#endif
