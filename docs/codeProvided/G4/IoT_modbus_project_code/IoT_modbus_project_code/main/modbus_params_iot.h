/*
 * SPDX-FileCopyrightText: 2016-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*=====================================================================================
 * Description:
 *   The Modbus parameter structures used to define Modbus instances that
 *   can be addressed by Modbus protocol. Define these structures per your needs in
 *   your application. Below is just an example of possible parameters.
 *====================================================================================*/
#ifndef _DEVICE_PARAMS_IOT
#define _DEVICE_PARAMS_IOT

#include <stdint.h>

// This file defines structure of modbus parameters which reflect correspond modbus address space
// for each modbus register type (coils, discreet inputs, holding registers, input registers)
#pragma pack(push, 1)
typedef struct
{
    uint8_t discrete_input0:1;
    uint8_t discrete_input1:1;
    uint8_t discrete_input2:1;
    uint8_t discrete_input3:1;
    uint8_t discrete_input4:1;
    uint8_t discrete_input5:1;
    uint8_t discrete_input6:1;
    uint8_t discrete_input7:1;
} discrete_reg_params_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t coils_port0; // 0
    uint8_t coils_port1; // 2
    uint8_t coils_port2; // 4
    uint8_t coils_port3; // 6
    uint8_t coils_port4; // 8
    uint8_t coils_port5; // 10
    uint8_t coils_port6; // 12
    uint8_t coils_port7; // 14
} coil_reg_params_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    float input_data0; // 0
    float input_data1; // 2
    float input_data2; // 4
    float input_data3; // 6
    float input_data4; // 8
    float input_data5; // 10
    float input_data6; // 12
    float input_data7; // 14
} input_reg_params_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    float holding_data0;
    float holding_data1;
    float holding_data2;
    float holding_data3;
    float holding_data4;
    float holding_data5;
    float holding_data6;
    float holding_data7;
} holding_reg_params_t;
#pragma pack(pop)

extern holding_reg_params_t holding_reg_params_iot;
extern input_reg_params_t input_reg_params_iot;
extern coil_reg_params_t coil_reg_params_iot;
extern discrete_reg_params_t discrete_reg_params_iot;

#endif // !defined(_DEVICE_PARAMS_IOT)
