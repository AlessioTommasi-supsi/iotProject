/*
 * SPDX-FileCopyrightText: 2016-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// FreeModbus Slave Example ESP32

#include <stdio.h>
#include <stdint.h>
#include "esp_err.h"
#include "mbcontroller.h"       // for mbcontroller defines and api
#include "modbus_params_iot.h"      // for modbus parameters structures
#include "esp_log.h"            // for log_write
#include "sdkconfig.h"
#include "slave.h"
#include "modbus_master_params.h"


#define CONFIG_MB_UART_TXD 23
#define CONFIG_MB_UART_RXD 22
#define CONFIG_MB_UART_RTS 18

#define MB_PORT_NUM     (2)   // Number of UART port used for Modbus connection
#define MB_SLAVE_ADDR   1     // The address of device in Modbus network
#define MB_DEV_SPEED    (9600)  // The communication speed of the UART

// Note: Some pins on target chip cannot be assigned for UART communication.
// Please refer to documentation for selected board and target to configure pins using Kconfig.

// Defines below are used to define register start address for each type of Modbus registers

#define MB_REG_DISCRETE_INPUT_START         (0x0000)
#define MB_REG_COILS_START                  (0x0000)
#define MB_REG_INPUT_START                  (0x0000)
#define MB_REG_HOLDING_START                (0x0000)

#define MB_PAR_INFO_GET_TOUT                (10) // Timeout for get parameter info
#define MB_CHAN_DATA_MAX_VAL                (6)
#define MB_CHAN_DATA_OFFSET                 (0.2f)
#define MB_READ_MASK                        (MB_EVENT_INPUT_REG_RD \
                                                | MB_EVENT_HOLDING_REG_RD \
                                                | MB_EVENT_DISCRETE_RD \
                                                | MB_EVENT_COILS_RD)
#define MB_WRITE_MASK                       (MB_EVENT_HOLDING_REG_WR \
                                                | MB_EVENT_COILS_WR)
#define MB_READ_WRITE_MASK                  (MB_READ_MASK | MB_WRITE_MASK)

static const char *TAG = "SLAVE_TEST";

static portMUX_TYPE param_lock = portMUX_INITIALIZER_UNLOCKED;

mb_param_info_t reg_info; // keeps the Modbus registers access information
mb_communication_info_t comm_info; // Modbus communication parameters
mb_register_area_descriptor_t reg_area; // Modbus register area descriptor structure

// Set register values into known state
void setup_reg_data(void)
{
    //INPUT STATUS
    // discrete_reg_params.discrete_input0 = 0x50; // 0
    // discrete_reg_params.discrete_input1 = 0x51; // 2
    // discrete_reg_params.discrete_input2 = 0x52; // 4
    // discrete_reg_params.discrete_input3 = 0x53; // 6
    // discrete_reg_params.discrete_input4 = 0x54; // 8
    // discrete_reg_params.discrete_input5 = 0x55; // 10
    // discrete_reg_params.discrete_input6 = 0x56; // 12
    // discrete_reg_params.discrete_input7 = 0x57; // 14

    //HOLDING REGISTER
    holding_reg_params_iot.holding_data0 = 1.34; // 0
    holding_reg_params_iot.holding_data1 = 2.56; // 2
    holding_reg_params_iot.holding_data2 = 3.78; // 4
    holding_reg_params_iot.holding_data3 = 4.90; // 6
    holding_reg_params_iot.holding_data4 = 5.67; // 8
    holding_reg_params_iot.holding_data5 = 6.56; // 10
    holding_reg_params_iot.holding_data6 = 7.67; // 12
    holding_reg_params_iot.holding_data7 = 8.88; // 14

    // //COILS STATUS
    // coil_reg_params.coils_port0 = 0x60; // 0
    // coil_reg_params.coils_port1 = 0x61; // 2
    // coil_reg_params.coils_port2 = 0x62; // 4
    // coil_reg_params.coils_port3 = 0x63; // 6
    // coil_reg_params.coils_port4 = 0x64; // 8
    // coil_reg_params.coils_port5 = 0x65; // 10
    // coil_reg_params.coils_port6 = 0x66; // 12
    // coil_reg_params.coils_port7 = 0x67; // 14

    // //INPUT REGISTER
    // input_reg_params.input_data0 = 1.12; // 0
    // input_reg_params.input_data1 = 2.34; // 2
    // input_reg_params.input_data2 = 3.56; // 4
    // input_reg_params.input_data3 = 4.78; // 6
    // input_reg_params.input_data4 = 4.56; // 8
    // input_reg_params.input_data5 = 2.88; // 10
    // input_reg_params.input_data6 = 3.12; // 12
    // input_reg_params.input_data7 = 4.44; // 14
}

// An example application of Modbus slave. It is based on freemodbus stack.
// See deviceparams.h file for more information about assigned Modbus parameters.
// These parameters can be accessed from main application and also can be changed
// by external Modbus master host.
void slave_init(void)
{
    //mb_param_info_t reg_info; // keeps the Modbus registers access information
    //mb_communication_info_t comm_info; // Modbus communication parameters
    //mb_register_area_descriptor_t reg_area; // Modbus register area descriptor structure

    // Set UART log level
    esp_log_level_set(TAG, ESP_LOG_INFO);
    void* mbc_slave_handler = NULL;

    ESP_ERROR_CHECK(mbc_slave_init(MB_PORT_SERIAL_SLAVE, &mbc_slave_handler)); // Initialization of Modbus controller

    // Setup communication parameters and start stack
#if CONFIG_MB_COMM_MODE_ASCII
    comm_info.mode = MB_MODE_ASCII,
#elif CONFIG_MB_COMM_MODE_RTU
    comm_info.mode = MB_MODE_RTU,
#endif
    comm_info.slave_addr = MB_SLAVE_ADDR;
    comm_info.port = MB_PORT_NUM;
    comm_info.baudrate = MB_DEV_SPEED;
    comm_info.parity = MB_PARITY_NONE;
    ESP_ERROR_CHECK(mbc_slave_setup((void*)&comm_info));

    // The code below initializes Modbus register area descriptors
    // for Modbus Holding Registers, Input Registers, Coils and Discrete Inputs
    // Initialization should be done for each supported Modbus register area according to register map.
    // When external master trying to access the register in the area that is not initialized
    // by mbc_slave_set_descriptor() API call then Modbus stack
    // will send exception response for this register area.



/*--------------------------------------------REGISTER MAP--------------------------------------------*/

    // Initialization of Holding Registers area0
    reg_area.type = MB_PARAM_HOLDING; // Set type of register area
    reg_area.start_offset = MB_REG_HOLDING_START; // Offset of register area in Modbus protocol
    reg_area.address = (void*)&holding_registers[0]; // Set pointer to storage instance
    reg_area.size = sizeof(holding_registers);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));


    // Initialization of Input Registers area0
    reg_area.type = MB_PARAM_INPUT;
    reg_area.start_offset = MB_REG_INPUT_START;
    reg_area.address = (void*)&input_reg_params_iot.input_data0;
    reg_area.size = sizeof(input_reg_params_iot);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));


    // Initialization of Coils register area
    reg_area.type = MB_PARAM_COIL;
    reg_area.start_offset = MB_REG_COILS_START;
    reg_area.address = (void*)&coil_reg_params_iot;
    reg_area.size = sizeof(coil_reg_params_iot);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));


    // Initialization of Discrete Inputs register area
    reg_area.type = MB_PARAM_DISCRETE;
    reg_area.start_offset = MB_REG_DISCRETE_INPUT_START;
    reg_area.address = (void*)&discrete_reg_params_iot;
    reg_area.size = sizeof(discrete_reg_params_iot);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));

/*----------------------------------------------------------------------------------------------------*/


    // setup_reg_data(); // Set values into known state

    // Starts of modbus controller and stack
    ESP_ERROR_CHECK(mbc_slave_start());

    // Set UART pin numbers
    ESP_ERROR_CHECK(uart_set_pin(MB_PORT_NUM, CONFIG_MB_UART_TXD,
                            CONFIG_MB_UART_RXD, CONFIG_MB_UART_RTS,
                            UART_PIN_NO_CHANGE));

    // Set UART driver mode to Half Duplex
    ESP_ERROR_CHECK(uart_set_mode(MB_PORT_NUM, UART_MODE_RS485_HALF_DUPLEX));

    ESP_LOGI(TAG, "Modbus slave stack initialized.");
    ESP_LOGI(TAG, "Start modbus test...");

}

void slave_loop(void){
    
        // Check for read/write events of Modbus master for certain events
        // xQueueReceive(holding_reg_queue_mbslave, (void*)&holding_reg_params_iot , (TickType_t)10000 );
        mb_event_group_t event = mbc_slave_check_event(MB_READ_WRITE_MASK);
        const char* rw_str = (event & MB_READ_MASK) ? "READ" : "WRITE";
        
        // ESP_LOGI(TAG,"Voltaje coming from the queue %f",holding_reg_params_iot.holding_data0);
        

        // Filter events and process them accordingly
        if(event & (MB_EVENT_HOLDING_REG_WR | MB_EVENT_HOLDING_REG_RD)) {
            // Get parameter information from parameter queue
            ESP_ERROR_CHECK(mbc_slave_get_param_info(&reg_info, MB_PAR_INFO_GET_TOUT));
            ESP_LOGI(TAG, "HOLDING %s (%u us), ADDR:%u, TYPE:%u, INST_ADDR:0x%.4x, SIZE:%u",
                    rw_str,
                    (uint32_t)reg_info.time_stamp,
                    (uint32_t)reg_info.mb_offset,
                    (uint32_t)reg_info.type,
                    (uint32_t)reg_info.address,
                    (uint32_t)reg_info.size);
        } else if (event & MB_EVENT_INPUT_REG_RD) {
            ESP_ERROR_CHECK(mbc_slave_get_param_info(&reg_info, MB_PAR_INFO_GET_TOUT));
            ESP_LOGI(TAG, "INPUT READ (%u us), ADDR:%u, TYPE:%u, INST_ADDR:0x%.4x, SIZE:%u",
                    (uint32_t)reg_info.time_stamp,
                    (uint32_t)reg_info.mb_offset,
                    (uint32_t)reg_info.type,
                    (uint32_t)reg_info.address,
                    (uint32_t)reg_info.size);
        } else if (event & MB_EVENT_DISCRETE_RD) {
            ESP_ERROR_CHECK(mbc_slave_get_param_info(&reg_info, MB_PAR_INFO_GET_TOUT));
            ESP_LOGI(TAG, "DISCRETE READ (%u us): ADDR:%u, TYPE:%u, INST_ADDR:0x%.4x, SIZE:%u",
                    (uint32_t)reg_info.time_stamp,
                    (uint32_t)reg_info.mb_offset,
                    (uint32_t)reg_info.type,
                    (uint32_t)reg_info.address,
                    (uint32_t)reg_info.size);
        } else if (event & (MB_EVENT_COILS_RD | MB_EVENT_COILS_WR)) {
            ESP_ERROR_CHECK(mbc_slave_get_param_info(&reg_info, MB_PAR_INFO_GET_TOUT));
            ESP_LOGI(TAG, "COILS %s (%u us), ADDR:%u, TYPE:%u, INST_ADDR:0x%.4x, SIZE:%u",
                    rw_str,
                    (uint32_t)reg_info.time_stamp,
                    (uint32_t)reg_info.mb_offset,
                    (uint32_t)reg_info.type,
                    (uint32_t)reg_info.address,
                    (uint32_t)reg_info.size);
        }
}



