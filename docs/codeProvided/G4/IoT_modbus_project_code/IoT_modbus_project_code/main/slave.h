#include <stdio.h>
#include <stdint.h>
#include "esp_err.h"
#include "mbcontroller.h"       // for mbcontroller defines and api

extern QueueHandle_t holding_reg_queue_mbslave;

void setup_reg_data(void);

void slave_init(void);

void slave_loop(void);