#ifndef _MODBUS_MASTER_PARAMS
#define _MODBUS_MASTER_PARAMS

#include "mbcontroller.h"


/* This data type take a different data type according the specs on the descriptors table */
typedef union  
{
    float f_value;
    uint8_t u8_value;
    uint16_t u16_value;
    uint32_t u32_value;
    // char str_value[100];
}param_value_t;




typedef struct 
{
    param_value_t       value;              /* Data type is defined during execution and depends on param_type value */

}parameter_frontend_desc;

enum
{
    MB_DEVICE_ADDR1 = 1 // Only one slave device used for the test (add other slave addresses here)

};

enum
{
    MODB_SLAVE_ID_ADDR1 = 1, // Only one slave device used for the test (add other slave addresses here)
    MODB_SLAVE_ID_ADDR2,
    MODB_SLAVE_ID_ADDR3
};

// Enumeration of all supported CIDs for device (used in parameter definition table)
enum
{
    CID_HOLD_DATA_0  = 0,
    CID_HOLD_DATA_1,
    CID_HOLD_DATA_2,
    CID_HOLD_DATA_3,
    CID_HOLD_DATA_4,
    CID_HOLD_DATA_5
};

esp_err_t add_new_parameter(mb_parameter_descriptor_t* mdb_descriptor,uint16_t* counter,uint16_t cid, const char* param_key,const char*  param_units,uint8_t mb_slave_addr,mb_param_type_t mb_param_type,uint16_t mb_reg_start,
uint16_t  mb_size,mb_descr_type_t param_type,mb_descr_size_t param_size);

esp_err_t edit_device_parameter(mb_parameter_descriptor_t* mdb_descriptor,uint16_t counter, uint16_t total_param_num, const char* param_key,const char*  param_units,uint8_t mb_slave_addr,mb_param_type_t mb_param_type,uint16_t mb_reg_start,
uint16_t  mb_size,mb_descr_type_t param_type,mb_descr_size_t param_size);

esp_err_t delete_device_parameter(mb_parameter_descriptor_t* mdb_descriptor,param_value_t* data_registers,uint16_t cid,uint16_t *total_param_num);

void *master_get_param_data_custom(const mb_parameter_descriptor_t *param_descriptor,param_value_t *temp_param_value);

void swap_float_value(void * data_ptr);

void change_value_param_register(param_value_t* data_registers,uint16_t cid,mb_descr_type_t param_type,void* value);

void print_current_descriptor_values(param_value_t* holding_data_registers, mb_parameter_descriptor_t* device_param_table,uint16_t num_params);


// Useful custom functions

uint32_t IRAM_ATTR micros();
void IRAM_ATTR delayMicroseconds(uint32_t us);

extern mb_parameter_descriptor_t device_parameters_IoT[100];
extern param_value_t holding_registers[100];

// extern uint8_t SWAP_BEHAVIOUR = 1;
extern uint8_t SWAP_BEHAVIOUR;

#endif