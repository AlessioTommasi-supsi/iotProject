#include "modbus_master_params.h"
#include "esp_timer.h"
uint8_t SWAP_BEHAVIOUR = 0;

static const char *TAG = "MASTER";

// The macro to get offset for parameter in the appropriate structure
#define HOLD_OFFSET(field) ((uint16_t)(offsetof(holding_reg_params_t, field) + 1))

#define STR(fieldname) ((const char *)(fieldname))
// Options can be used as bit masks or parameter limits
#define OPTS(min_val, max_val, step_val)                   \
    {                                                      \
        .opt1 = min_val, .opt2 = max_val, .opt3 = step_val \
    }
// Enumeration of modbus device addresses accessed by master device

mb_parameter_descriptor_t device_parameters_IoT[100] = {
    // { CID, Param Name, Units, Modbus Slave Addr, Modbus Reg Type, Reg Start, Reg Size, Instance Offset, Data Type, Data Size, Parameter Options, Access Mode}
    {
        0,  // CID 
        STR("Voltage Phase 1"), //Param Name
        STR("V"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        123,
        2, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_FLOAT, //Data Type
        4, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },
    {
        1,  // CID 
        STR("Temperature"), //Param Name
        STR("C"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        157,
        2, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_FLOAT, //Data Type
        4, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },
    {
        2,  // CID 
        STR("Frequency"), //Param Name
        STR("Hz"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        121,
        2, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_FLOAT, //Data Type
        4, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },
    {
        3,  // CID 
        STR("Active power Phase 1"), //Param Name
        STR("W"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        129,
        2, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_FLOAT, //Data Type
        4, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },
    {
        4,  // CID 
        STR("Peak value 1"), //Param Name
        STR("V"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        159,
        2, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_FLOAT, //Data Type
        4, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },
    {
        5,  // CID 
        STR("Total harmonic distortion V1"), //Param Name
        STR("%"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        171,
        2, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_FLOAT, //Data Type
        4, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },
    {
        6,  // CID 
        STR(" 3 phase connection"), //Param Name
        STR("#"),//Units
        MODB_SLAVE_ID_ADDR1,  //Modbus Slave Addr
        MB_PARAM_HOLDING,  //Modbus Reg Type
        // 0x100, //Reg
        347,
        1, //Reg Size
        0,// Instance Offset
        PARAM_TYPE_U16, //Data Type
        2, //Data Size - in bytes
        OPTS(0, 0, 0), //Parameter Options
        PAR_PERMS_READ //Access Mode
    },    
    };


param_value_t holding_registers[100] = {0};


esp_err_t delete_device_parameter(mb_parameter_descriptor_t* mdb_descriptor,param_value_t* data_registers,uint16_t cid,uint16_t *total_param_num){
    if(*total_param_num < 1) {
        return ESP_FAIL;
    }
    for (int i = 0; i < (*total_param_num); i++) {
        if (mdb_descriptor[i].cid == cid) {
            for (int j = i; j < (*total_param_num) - 1; j++) {
                mdb_descriptor[j] = mdb_descriptor[j+1];
                mdb_descriptor[j].cid--;
                data_registers[j] = data_registers[j+1];
            }
            (*total_param_num)--;
            break;
        }
    }
    return ESP_OK;
}

esp_err_t edit_device_parameter(mb_parameter_descriptor_t* mdb_descriptor,uint16_t counter, uint16_t total_param_num, const char* param_key,const char*  param_units,uint8_t mb_slave_addr,mb_param_type_t mb_param_type,uint16_t mb_reg_start,
uint16_t  mb_size,mb_descr_type_t param_type,mb_descr_size_t param_size){
    
    mdb_descriptor[counter].cid = counter;
    mdb_descriptor[counter].param_key = NULL;
    mdb_descriptor[counter].param_units = NULL;
    mdb_descriptor[counter].param_key = strdup(param_key);
    mdb_descriptor[counter].param_units = strdup(param_units);
    mdb_descriptor[counter].mb_slave_addr = mb_slave_addr;
    mdb_descriptor[counter].mb_param_type = mb_param_type;
    mdb_descriptor[counter].mb_reg_start = mb_reg_start;
    mdb_descriptor[counter].mb_size = mb_size;
    mdb_descriptor[counter].param_type = param_type;
    mdb_descriptor[counter].param_size = param_size;
    // mdb_descriptor[counter].param_opts = OPTS(0, 0, 0); //Parameter Options
    mdb_descriptor[counter].access = PAR_PERMS_READ;
    printf("Device parameter descriptor was modified\n");
    printf("CID: %d\n", mdb_descriptor[counter].cid);
    printf("Parameter Key: %s+\n", mdb_descriptor[counter].param_key);
    printf("Parameter Units: %s+\n", mdb_descriptor[counter].param_units);
    printf("Modbus Slave Address: %d\n", mdb_descriptor[counter].mb_slave_addr);
    printf("Modbus Parameter Type: %d\n", mdb_descriptor[counter].mb_param_type);
    printf("Modbus Register Start: %d\n", mdb_descriptor[counter].mb_reg_start);
    printf("Modbus Register Size: %d\n", mdb_descriptor[counter].mb_size);
    printf("Parameter Type: %d\n", mdb_descriptor[counter].param_type);
    printf("Parameter Size: %d\n", mdb_descriptor[counter].param_size);
    printf("---------------------------------\n");

    esp_err_t err = mbc_master_set_descriptor(&mdb_descriptor[0], total_param_num);
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG,
                        "mb controller set descriptor fail, returns(0x%x).",
                        (uint32_t)err);
    return err;
}


esp_err_t add_new_parameter(mb_parameter_descriptor_t* mdb_descriptor,uint16_t* counter,uint16_t cid, const char* param_key,const char*  param_units,uint8_t mb_slave_addr,mb_param_type_t mb_param_type,uint16_t mb_reg_start,
uint16_t  mb_size,mb_descr_type_t param_type,mb_descr_size_t param_size)
{

    mdb_descriptor[*counter].cid = cid;
    mdb_descriptor[*counter].param_key = NULL;
    mdb_descriptor[*counter].param_units = NULL;
    mdb_descriptor[*counter].param_key = strdup(param_key);
    mdb_descriptor[*counter].param_units = strdup(param_units);
    mdb_descriptor[*counter].mb_slave_addr = mb_slave_addr;
    mdb_descriptor[*counter].mb_param_type = mb_param_type;
    mdb_descriptor[*counter].mb_reg_start = mb_reg_start;
    mdb_descriptor[*counter].mb_size = mb_size;
    mdb_descriptor[*counter].param_type = param_type;
    mdb_descriptor[*counter].param_size = param_size;
    // mdb_descriptor[*counter].param_opts = OPTS(0, 0, 0); //Parameter Options
    mdb_descriptor[*counter].access = PAR_PERMS_READ;
    (*counter)++;

    esp_err_t err = mbc_master_set_descriptor(&mdb_descriptor[0], (*counter));
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG,
                        "mb controller set descriptor fail, returns(0x%x).",
                        (uint32_t)err);
    vTaskDelay(10);

    return err;
}

void *master_get_param_data_custom(const mb_parameter_descriptor_t *param_descriptor,param_value_t *temp_param_value){
    assert(temp_param_value != NULL);
    void *instance_ptr = NULL;
    if(param_descriptor->param_type == PARAM_TYPE_U16)
    {
        instance_ptr = (void *)&temp_param_value->u16_value;
    }
    else if (param_descriptor->param_type == PARAM_TYPE_FLOAT)
    {
        instance_ptr = (void *)&temp_param_value->f_value;
    }
    // else if (param_descriptor->param_type == PARAM_TYPE_ASCII)
    // {
    //     instance_ptr = (void *)&temp_param_value->str_value;
    // }
    else{
        instance_ptr = NULL;
    }
    return instance_ptr;
}

void swap_float_value(void * data_ptr){


    uint32_t uint_value = 0;
    uint_value = *(uint32_t *)data_ptr;
    if(SWAP_BEHAVIOUR){
        uint_value = (((uint_value) << 16) & 0xFFFF0000)  | ((uint_value) >> 16 & 0x0000FFFF);
    }
    memcpy(data_ptr, &uint_value, sizeof(float)); // Copy the bit pattern from uint32_t to float

}


void change_value_param_register(param_value_t* data_registers,uint16_t cid,mb_descr_type_t param_type,void* value){
    switch (param_type)
        {
        case PARAM_TYPE_U16:
            data_registers[cid].u8_value = *(uint16_t *)value;
            break;

        case PARAM_TYPE_FLOAT:
            swap_float_value(value);
            data_registers[cid].f_value = *(float *)value;
            break;

        // case PARAM_TYPE_ASCII:
        //     strncpy(data_registers[cid].str_value,(char*)value,sizeof(data_registers[cid].str_value) - 1);
        //     break;
        
        default:
            break;
        }
}

void print_current_descriptor_values(param_value_t* holding_data_registers, mb_parameter_descriptor_t* device_param_table,uint16_t num_params){
    for (uint16_t cid = 0; cid < num_params; cid++){
        
        if (device_param_table[cid].param_type == PARAM_TYPE_FLOAT)
        {
            ESP_LOGI(TAG, "Characteristic holding float #%d %s (%s) value = %f read successful.",device_param_table[cid].cid,(char *)device_param_table[cid].param_key,(char *)device_param_table[cid].param_units,holding_data_registers[cid].f_value);
        }else{
            ESP_LOGI(TAG, "Characteristic holding #%d %s (%s) value = %x read successful.",device_param_table[cid].cid,(char *)device_param_table[cid].param_key,(char *)device_param_table[cid].param_units,holding_data_registers[cid].u32_value);
        }
    }
    printf("\n");
}


uint32_t IRAM_ATTR micros(){
    return (uint32_t) (esp_timer_get_time());
}
void IRAM_ATTR delayMicroseconds(uint32_t us)
{
    uint32_t m = micros();
    if(us){
        uint32_t e = (m + us);
        if(m > e){ //overflow
            while(micros() > e){
                asm volatile ("nop");
            }
        }
        while(micros() < e){
            asm volatile ("nop");
        }
    }
}