/*
 * SPDX-FileCopyrightText: 2016-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_log.h"
#include "modbus_params.h" // for modbus parameters structures
#include "mbcontroller.h"
#include "sdkconfig.h"
#include "slave.h"
#include "freertos/queue.h"
#include "display.h"
#include "modbus_master_params.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif


#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK

#define EXAMPLE_ESP_MAXIMUM_RETRY 5
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
#define WIFI_NETWORK_SELECTED BIT2

#define TASKPRIO_MBS_SLAVE 2
#define TASKPRIO_MBS_MASTER 3
#define TASKPRIO_DISPLAY 1


#define MB_PORT_NUM (CONFIG_MB_UART_PORT_NUM)   // Number of UART port used for Modbus connection
#define MB_PORT_NUM (1)   // Number of UART port used for Modbus connection
#define CONFIG_MB_UART_TXD 21
#define CONFIG_MB_UART_RXD 19
#define CONFIG_MB_UART_RTS 4
// #define MB_DEV_SPEED (CONFIG_MB_UART_BAUD_RATE) // The communication speed of the UART
#define MB_DEV_SPEED 9600
// Note: Some pins on target chip cannot be assigned for UART communication.
// See UART documentation for selected board and target to configure pins using Kconfig.

// The number of parameters that intended to be used in the particular control process
// #define MASTER_MAX_CIDS num_device_parameters
#define MASTER_MAX_CIDS num_device_parameters_IoT

// Number of reading of parameters from slave
#define MASTER_MAX_RETRY 10

// Timeout to update cid over Modbus
#define UPDATE_CIDS_TIMEOUT_MS (500)
#define UPDATE_CIDS_TIMEOUT_TICS (UPDATE_CIDS_TIMEOUT_MS / portTICK_PERIOD_MS)

// Timeout between polls
#define POLL_TIMEOUT_MS (1)
#define POLL_TIMEOUT_TICS (POLL_TIMEOUT_MS / portTICK_PERIOD_MS)

#define DEFAULT_SCAN_LIST_SIZE 20

#define PAR_PERMS_READ 0x01
/* FreeRTOS event group to signal when we are connected/disconnected */
static EventGroupHandle_t s_wifi_event_group;
static EventGroupHandle_t s_wifi_event_group_STA;
static const char *TAG_AP = "WiFi SoftAP";
static const char *TAG_STA = "WiFi Sta";
static const char *TAG_MASTER = "MASTER";
static const char *TAG_SERVER = "HTTP WEB SERVER";
char ip_assigned[30];
typedef cJSON* cJSON_GetObjItemCS(const cJSON * const object, const char * const string);
static const char *TAG_WIFI_STA = "wifi station";
static int s_retry_num = 0;
uint16_t number = DEFAULT_SCAN_LIST_SIZE;
wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
uint16_t ap_count = 0;
// Calculate number of parameters in the table
uint16_t num_device_parameters_IoT = 7;
QueueHandle_t holding_reg_queue_mbslave;
QueueHandle_t holding_reg_queue_display;
uint32_t start_time;
uint32_t test_delay = 4000000;
uint8_t enable_timer = 1;
//Defines URI handlers for /data endpoint with GET, POST, and DELETE methods
char user_ssid[32]={0};
char user_password[64]={0};
char connect_net_buffer[1000] = {0};

// SWAP_BEHAVIOUR = 0;
// Swap behaviour

//Handles HTTP GET requests to fetch all data entries
//Constructs a JSON array string of all entries
//Sends the JSON response
char buffer[4096];
esp_err_t data_get_handler(httpd_req_t *req) {
    
    int offset = 0;
    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "[");
    for (int i = 0; i < num_device_parameters_IoT; i++) {
        if(device_parameters_IoT[i].param_type == PARAM_TYPE_FLOAT){
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, 
            "{\"id\":%d,\"name\":\"%s\",\"description\":\"%s\",\"units\":\"%s\","
            "\"slave_id\":%d,\"reg_type\":%d,\"reg_start\":%d,\"reg_size\":%d,"
            "\"data_type\":%d,\"data_size\":%d,\"value\":%.2f,\"instance_offset\":%d,"
            "\"parameter_options\":%d,\"access_mode\":%d}",
            device_parameters_IoT[i].cid, device_parameters_IoT[i].param_key, device_parameters_IoT[i].param_key, device_parameters_IoT[i].param_units,
            device_parameters_IoT[i].mb_slave_addr, device_parameters_IoT[i].mb_param_type, device_parameters_IoT[i].mb_reg_start,
            device_parameters_IoT[i].mb_size, device_parameters_IoT[i].param_type, device_parameters_IoT[i].param_size,
            holding_registers[i].f_value, 0,0,
            device_parameters_IoT[i].access);
        }else{
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, 
            "{\"id\":%d,\"name\":\"%s\",\"description\":\"%s\",\"units\":\"%s\","
            "\"slave_id\":%d,\"reg_type\":%d,\"reg_start\":%d,\"reg_size\":%d,"
            "\"data_type\":%d,\"data_size\":%d,\"value\":%d,\"instance_offset\":%d,"
            "\"parameter_options\":%d,\"access_mode\":%d}",
            device_parameters_IoT[i].cid, device_parameters_IoT[i].param_key, device_parameters_IoT[i].param_key, device_parameters_IoT[i].param_units,
            device_parameters_IoT[i].mb_slave_addr, device_parameters_IoT[i].mb_param_type, device_parameters_IoT[i].mb_reg_start,
            device_parameters_IoT[i].mb_size, device_parameters_IoT[i].param_type, device_parameters_IoT[i].param_size,
            holding_registers[i].u32_value, 0,0,
            device_parameters_IoT[i].access);
        }
        
        if (i < num_device_parameters_IoT - 1) {
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, ",");
        }
    }
    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "]");
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, buffer, strlen(buffer));
    return ESP_OK;
}

//Handles HTTP POST requests to add or update an entry
//Parses the JSON data from the request body
//Checks if the entry exists and updates it; otherwise, adds a new entry
//Responds with a confirmation message
char post_buffer[4096];
esp_err_t data_post_handler(httpd_req_t *req) {
    
    int ret = httpd_req_recv(req, post_buffer, sizeof(post_buffer));
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }
    post_buffer[ret] = '\0';
    cJSON *json = cJSON_Parse(post_buffer);
    if (json == NULL) {
        ESP_LOGE(TAG_SERVER, "Failed to parse JSON");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    mb_parameter_descriptor_t entry = {0};
    char description[100];
    char param_key[100];
    char param_units[100];
    
    // uint32_t instance_offset;

    cJSON_GetObjItemCS *get_object_item = cJSON_GetObjectItemCaseSensitive; // Use the typedef to reference cJSON_GetObjectItemCaseSensitive
    cJSON *id = get_object_item(json, "id");
    cJSON *name = get_object_item(json, "name");
    cJSON *description_json = get_object_item(json, "description");
    cJSON *units = get_object_item(json, "units");
    cJSON *slave_id = get_object_item(json, "slave_id");
    cJSON *reg_type = get_object_item(json, "reg_type");
    cJSON *reg_start = get_object_item(json, "reg_start");
    cJSON *reg_size = get_object_item(json, "reg_size");
    cJSON *data_type = get_object_item(json, "data_type");
    cJSON *data_size = get_object_item(json, "data_size");
    // cJSON *instance_offset_json = get_object_item(json, "instance_offset");
    cJSON *parameter_options = get_object_item(json, "parameter_options");
    cJSON *access_mode = get_object_item(json, "access_mode");

    if (id && cJSON_IsNumber(id)) entry.cid = id->valueint;
    if (name && cJSON_IsString(name)) snprintf(param_key, 100, "%s\0", name->valuestring);
    if (description_json && cJSON_IsString(description_json)) snprintf(description, sizeof(description), "%s\0", description_json->valuestring);
    if (units && cJSON_IsString(units)) snprintf(param_units, 100, "%s\0", units->valuestring);
    if (slave_id && cJSON_IsNumber(slave_id)) entry.mb_slave_addr = slave_id->valueint;
    if (reg_type && cJSON_IsNumber(reg_type)) entry.mb_param_type = reg_type->valueint;
    if (reg_start && cJSON_IsNumber(reg_start)) entry.mb_reg_start = reg_start->valueint;
    if (reg_size && cJSON_IsNumber(reg_size)) entry.mb_size = reg_size->valueint;
    if (data_type && cJSON_IsNumber(data_type)) entry.param_type = data_type->valueint;
    if (data_size && cJSON_IsNumber(data_size)) entry.param_size = data_size->valueint;
    // if (instance_offset_json && cJSON_IsNumber(instance_offset_json)) instance_offset = instance_offset_json->valueint;
    // if (parameter_options && cJSON_IsNumber(parameter_options)) entry.param_opts = parameter_options->valueint;
    if (access_mode && cJSON_IsNumber(access_mode)) entry.access = access_mode->valueint;
    // printf("Slave address %d",slave_id->valueint);
    // printf("Slave address2  %d",entry.mb_slave_addr);
    int index = -1;
    for (int i = 0; i < num_device_parameters_IoT; i++) { // Find if the parameter id already exists
        if (device_parameters_IoT[i].cid == entry.cid) {
            index = i;
            ESP_LOGI(TAG_SERVER, "Updating CID # %d\n", entry.cid);
            edit_device_parameter(device_parameters_IoT,i,num_device_parameters_IoT,param_key,
            param_units,
            entry.mb_slave_addr,
            entry.mb_param_type,
            entry.mb_reg_start,
            entry.mb_size,
            entry.param_type,
            entry.param_size);
            break;
        }
    }
    if (index == -1) {
        add_new_parameter(device_parameters_IoT,
        &num_device_parameters_IoT,
        num_device_parameters_IoT,
        param_key,
        param_units,
        entry.mb_slave_addr,
        entry.mb_param_type,
        entry.mb_reg_start,
        entry.mb_size,
        entry.param_type,
        entry.param_size); 
    }
    httpd_resp_send(req, "Entry saved", HTTPD_RESP_USE_STRLEN);
    cJSON_Delete(json);
    return ESP_OK;
    
}

//Handles HTTP DELETE requests to delete an entry
//Parses the ID from the request body
//Deletes the entry with the specified ID and shifts the remaining entries
//Responds with a confirmation message
esp_err_t data_delete_handler(httpd_req_t *req) {
    char buffer[128];
    int ret = httpd_req_recv(req, buffer, sizeof(buffer));
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }
    buffer[ret] = '\0';
    int id = atoi(buffer);
    delete_device_parameter(device_parameters_IoT,holding_registers,(uint16_t) id,&num_device_parameters_IoT);
    httpd_resp_send(req, "Entry deleted", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

//Defines a handler to serve an HTML page (binary data in flash memory)
//Defines a URI handler for the root /
//Starts the web server and registers the URI handlers
esp_err_t hello_get_handler(httpd_req_t *req) {
    extern const uint8_t index_html_start[] asm("_binary_index_html_start");
    extern const uint8_t index_html_end[] asm("_binary_index_html_end");
    const size_t index_html_size = (index_html_end - index_html_start);
    httpd_resp_send(req, (const char *)index_html_start, index_html_size);
    return ESP_OK;
}



char temp[100];

/* Handler to respond with a list of SSIDs */
esp_err_t ssid_connect_handler(httpd_req_t *req) {

    extern const uint8_t connectme_html_start[] asm("_binary_connectme_html_start");
    extern const uint8_t connectme_html_end[] asm("_binary_connectme_html_end");
    const size_t connectme_html_size = (connectme_html_end - connectme_html_start);
    httpd_resp_send(req, (const char *)connectme_html_start, connectme_html_size);
    return ESP_OK;
}

char resp[2048];
esp_err_t  ssid_get_data_scan_network(httpd_req_t *req) {
    int offset = 0;
    offset += snprintf(resp + offset, sizeof(resp) - offset, "[");
    for (int i = 0; i < ap_count && i < DEFAULT_SCAN_LIST_SIZE; i++) {
        offset += snprintf(resp + offset, sizeof(resp) - offset, 
                           "{\"id\":%d,\"ssid\":\"%s\","
                           "\"rssi\":%d}",
                           i, ap_info[i].ssid, ap_info[i].rssi);
        if (i < ap_count - 1 && i < DEFAULT_SCAN_LIST_SIZE-1) {
            offset += snprintf(resp + offset, sizeof(resp) - offset, ",");
        }
    }
    offset += snprintf(resp + offset, sizeof(resp) - offset, "]");
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, strlen(resp));
    return ESP_OK;
}

esp_err_t  ssid_connect_network(httpd_req_t *req) {

    int ret = httpd_req_recv(req, connect_net_buffer, sizeof(connect_net_buffer));
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }
    connect_net_buffer[ret] = '\0';
    cJSON *json = cJSON_Parse(connect_net_buffer);
    if (json == NULL) {
        ESP_LOGE(TAG_SERVER, "Failed to parse JSON");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    cJSON_GetObjItemCS *get_object_item = cJSON_GetObjectItemCaseSensitive; // Use the typedef to reference cJSON_GetObjectItemCaseSensitive
    cJSON *pass = get_object_item(json, "pass");
    cJSON *ssid = get_object_item(json, "ssid");
    if (pass && cJSON_IsString(pass)) snprintf(user_password, 100, "%s\0", pass->valuestring);
    if (ssid && cJSON_IsString(ssid)) snprintf(user_ssid, 100, "%s\0", ssid->valuestring);
    ESP_LOGI(TAG_AP, "The network %s, and password %s was selected \n\n\n",user_ssid,user_password);
    xEventGroupSetBits(s_wifi_event_group, WIFI_NETWORK_SELECTED);
    httpd_resp_send(req, "Entry saved", HTTPD_RESP_USE_STRLEN);
    cJSON_Delete(json);
    return ESP_OK;
}

httpd_uri_t data_get = {
    .uri = "/data",
    .method = HTTP_GET,
    .handler = data_get_handler,
    .user_ctx = NULL
};

httpd_uri_t data_post = {
    .uri = "/data",
    .method = HTTP_POST,
    .handler = data_post_handler,
    .user_ctx = NULL
};

httpd_uri_t data_delete = {
    .uri = "/data",
    .method = HTTP_DELETE,
    .handler = data_delete_handler,
    .user_ctx = NULL
};

httpd_uri_t hello = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = hello_get_handler,
    .user_ctx = NULL
};

httpd_uri_t connectme = {
    .uri      = "/connect",
    .method   = HTTP_GET,
    .handler  = ssid_connect_handler,
    .user_ctx = NULL
};

httpd_uri_t data_scan_networks = {
    .uri      = "/connect/api/data",
    .method   = HTTP_GET,
    .handler  = ssid_get_data_scan_network,
    .user_ctx = NULL
};

httpd_uri_t connect_network = {
    .uri      = "/connect/api/data",
    .method   = HTTP_POST,
    .handler  = ssid_connect_network,
    .user_ctx = NULL
};

httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &hello);
        httpd_register_uri_handler(server, &data_get);
        httpd_register_uri_handler(server, &data_post);
        httpd_register_uri_handler(server, &data_delete);
        httpd_register_uri_handler(server, &connectme);
        httpd_register_uri_handler(server, &data_scan_networks);
        httpd_register_uri_handler(server, &connect_network);

    }
    return server;
}

//Initializes the ESP32 as a Wi-Fi access point with SSID "ESP32-AP" and password "12345678"
//Configures the Wi-Fi settings and starts the AP
void wifi_init_softap() {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "CONFIGURE ME_group4",
            .password = "12345678",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };
    if (strlen((const char *)wifi_config.ap.password) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();
    ESP_LOGI(TAG_SERVER, "wifi_init_softap finished. SSID:%s password:%s", wifi_config.ap.ssid, wifi_config.ap.password);
}

// Modbus master initialization
static esp_err_t master_init(void)
{
    // Initialize and start Modbus controller
    mb_communication_info_t comm = {
        .port = MB_PORT_NUM,
        .mode = MB_MODE_RTU,
        .baudrate = MB_DEV_SPEED,
        .parity = MB_PARITY_NONE
    };
    void *master_handler = NULL;

    esp_err_t err = mbc_master_init(MB_PORT_SERIAL_MASTER, &master_handler);
    MB_RETURN_ON_FALSE((master_handler != NULL), ESP_ERR_INVALID_STATE, TAG_MASTER,
                       "mb controller initialization fail.");
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG_MASTER,
                       "mb controller initialization fail, returns(0x%x).",
                       (uint32_t)err);
    err = mbc_master_setup((void *)&comm);
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG_MASTER,
                       "mb controller setup fail, returns(0x%x).",
                       (uint32_t)err);

    // Set UART pin numbers
    err = uart_set_pin(MB_PORT_NUM, CONFIG_MB_UART_TXD, CONFIG_MB_UART_RXD,
                       CONFIG_MB_UART_RTS, UART_PIN_NO_CHANGE);
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG_MASTER,
                       "mb serial set pin failure, uart_set_pin() returned (0x%x).", (uint32_t)err);

    err = mbc_master_start();
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG_MASTER,
                       "mb controller start fail, returns(0x%x).",
                       (uint32_t)err);

    // Set driver mode to Half Duplex
    err = uart_set_mode(MB_PORT_NUM, UART_MODE_RS485_HALF_DUPLEX);
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG_MASTER,
                       "mb serial set mode failure, uart_set_mode() returned (0x%x).", (uint32_t)err);

    vTaskDelay(5);

    err = mbc_master_set_descriptor(&device_parameters_IoT[0], num_device_parameters_IoT);
    MB_RETURN_ON_FALSE((err == ESP_OK), ESP_ERR_INVALID_STATE, TAG_MASTER,"mb controller set descriptor fail, returns(0x%x).",(uint32_t)err);
    ESP_LOGI(TAG_MASTER, "Modbus master stack initialized...");

    start_time = micros();

    return err;
}

// User operation function to read slave values and check alarm
static void master_operation_func(void *arg)
{
    esp_err_t err = ESP_OK;
    // float value = 0;
    const mb_parameter_descriptor_t *param_descriptor = NULL;
    print_current_descriptor_values(holding_registers,device_parameters_IoT,num_device_parameters_IoT);
    param_value_t temp_param_value;
    // Read all found characteristics from slave(s)
    for (uint16_t cid = 0; (err != ESP_ERR_NOT_FOUND) && cid < num_device_parameters_IoT; cid++)
    {
        
        // Get data from parameters description table
        // and use this information to fill the characteristics description table registered on the Modbus API
        // The obtained values are saved temporary into a temporal location () and afterwards stored into a holding buffer array  (holding_registers)
        err = mbc_master_get_cid_info(cid, &param_descriptor); // Return the description according the cid number
        if ((err != ESP_ERR_NOT_FOUND) && (param_descriptor != NULL))
        {
            void *temp_data_ptr = master_get_param_data_custom(param_descriptor,&temp_param_value); // get pointer to temp_param_value acording to data type
            assert(temp_data_ptr);
            uint8_t type = 0;     
            err = mbc_master_get_parameter(cid, (char *)param_descriptor->param_key, (uint8_t *)temp_data_ptr, &type); // Generates the tx and reads from Modbus slave device, data is stored into value
            // Handle answer from slave
            if (err == ESP_OK)
            {                 
                if ((param_descriptor->mb_param_type == MB_PARAM_HOLDING)) change_value_param_register(holding_registers,cid,param_descriptor->param_type,temp_data_ptr);            
            }
            else
            {
                ESP_LOGE(TAG_MASTER, "Characteristic #%d (%s) read fail, err = 0x%x (%s).",param_descriptor->cid,(char *)param_descriptor->param_key,(int)err,(char *)esp_err_to_name(err));
            }
            vTaskDelay(POLL_TIMEOUT_TICS); // timeout between polls
        }
    }
    xQueueSend(holding_reg_queue_display, (void*)&holding_reg_params , (TickType_t)5);
    xQueueSend(holding_reg_queue_mbslave, (void*)&holding_reg_params , (TickType_t)5);
    vTaskDelay(UPDATE_CIDS_TIMEOUT_TICS);

}

/* Initialize Wi-Fi as sta and set scan method */
static void wifi_scan(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    
}
static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG_STA, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group_STA, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG_STA,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        sprintf(ip_assigned,IPSTR, IP2STR(&event->ip_info.ip));
        // sprintf(buffer_label1,"V : %3.3f V",voltage);
        // ESP_LOGI(TAG_STA, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        print_display(ip_assigned,100,0,0);
        
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group_STA, WIFI_CONNECTED_BIT);
    }
}

void connect_me_operation(void) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    // Initialize wifi STA
    ESP_LOGI(TAG_WIFI_STA, "ESP_WIFI_MODE_STA");
    // init_wifi_sta();

    // wifi scan
    wifi_scan();

    // wifi AP mode
    wifi_init_softap();


    // Start the web server
    httpd_handle_t server = start_webserver();
    s_wifi_event_group_STA = xEventGroupCreate();
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));
    wifi_config_t wifi_config = {
        .sta = {
            .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };
    EventBits_t events_wifi = xEventGroupWaitBits(s_wifi_event_group, WIFI_NETWORK_SELECTED, true, false, portMAX_DELAY);
    if(events_wifi & WIFI_NETWORK_SELECTED){
        ESP_LOGI(TAG_STA,"Event received: Password and SSID are added to the STA settings");
        memcpy(wifi_config.sta.ssid, user_ssid, sizeof(user_ssid));
        memcpy(wifi_config.sta.password, user_password, sizeof(user_password));
        // wifi STA mode

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
        ESP_ERROR_CHECK(esp_wifi_start() );
        ESP_LOGI(TAG_STA, "wifi_init_sta finished");
        vTaskDelay(1000);
    }
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group_STA,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG_STA, "connected to ap SSID:%s password:%s",
                 user_ssid, user_password);
                //  wifi_connected=1;
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG_STA, "Failed to connect to SSID:%s, password:%s",
                 user_ssid, user_password);
    } else {
        ESP_LOGE(TAG_STA, "UNEXPECTED EVENT");
    }

    printf("\nconnected, ip assigned by DHCP server: %s",ip_assigned);
}



// Task executed by the RTOS

void task_modbus_slave(void *arg){
    while(1){
        slave_loop();
    }
    vTaskDelete(NULL);
}

void task_modbus_master(void *arg){
    while(1){
        master_operation_func(NULL);
    }
    vTaskDelete(NULL);
}

// void task_print_display(void *args){
//     holding_reg_params_t modbus_data;
//     init_display();
//     while (1)   
//     {
//         xQueueReceive(holding_reg_queue_display, (void*)&modbus_data , (TickType_t)10000 );
//         // print_display((float) modbus_data.holding_data0,(float) modbus_data.holding_data1, (float) modbus_data.holding_data2, (float)modbus_data.holding_data4);
//     }
// }

void app_main(void)
{
    // Initialization of device peripheral and objects
    // ESP_ERROR_CHECK(slave_init());
    holding_reg_queue_display = xQueueCreate(1, sizeof(holding_reg_params_t)); 
    holding_reg_queue_mbslave = xQueueCreate(1, sizeof(holding_reg_params_t));
    s_wifi_event_group = xEventGroupCreate();
    vTaskDelay(pdMS_TO_TICKS(100));
    init_display();
    connect_me_operation();
    vTaskDelay(pdMS_TO_TICKS(100));
    slave_init();
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_ERROR_CHECK(master_init());
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGI('main', "Start modbus test...");
    vTaskDelay(pdMS_TO_TICKS(100));

    xTaskCreatePinnedToCore(task_modbus_master,       "modbusMaster",       4096, NULL, TASKPRIO_MBS_MASTER,      NULL, 1);
    // xTaskCreatePinnedToCore(task_print_display,     "printDisplay",     4096, NULL, TASKPRIO_DISPLAY,    NULL, 1);
    xTaskCreatePinnedToCore(task_modbus_slave,     "modbusSlave",     4096, NULL, TASKPRIO_MBS_SLAVE,    NULL, 1);


}
