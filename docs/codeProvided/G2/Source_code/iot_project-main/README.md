# Implementation of Modbus Master-Slave communication on ESP32 with E2002BL network analyzer

### Course: Internet of Things (IoT)

### Students:
- Axel Salaris
- Erica Capocello
- Matteo Metaldi
- Roberto Vicario

### Group 2

## Descrizione

As part of the Internet of Things (IoT) course, we developed an integrated system using an ESP32 board and an Esam E2002BL device \cite{3}, a network analyzer. The project involved using the ESP32 in two distinct operational modes: slave mode and master mode. In slave mode, the ESP32 received data requests from a software on the PC, such as Modscan, and responded with the requested information. In master mode, the ESP32 directly queried the E2002BL device to gather the necessary data. One of the main functionalities of the system was the ESP32's ability to create a Wi-Fi network, allowing connection to an existing network. Subsequently, the ESP32 acted as a web server, offering a configuration page that enabled users to view, add, delete, and modify registers in an interactive table. Additionally, the system included a real-time analytics page to monitor the values of a single register. For communication between devices, we used the Modbus RTU protocol, ensuring reliable and efficient data transmission between the system components.

## Requisiti

- ESP32
- Two RS-485 transceiver modules
- [E2002BL](https://esam.biz/prodotto/e2002-bl/?lang=en) network analyser
- Oled Display (optional)

## Installazione e Configurazione
The ESP32’s connected pins to the two RS485s and the display are (Fig. 1):
- RS485 Slave (Serial1)
  - RX: GPIO 32
  - TX: GPIO 33
  - DE: GPIO 27
- RS485 Master (Serial2)
  - RX: GPIO 16
  - TX: GPIO 17
  - DE: GPIO 15
- Oled Display
  - SCK: GPIO 22
  - SDA: GPIO 21


## Endpoints

| Endpoint  | Request type  | Function in code | Description |
| :------------: |:---------:| :-----:| :---------------------------:|
| /setWifi     | POST | handleWifiConfig | Set new Wi-Fi configuration |
| /config      | GET | handleDataPage | Render configuration page |
| /readRegister | GET | handleReadRegister | Read data from network analyzer |
| /addData     | POST | handleAddData | Add new register |
| /deleteData      | POST |  handleDeleteData | Delete a register |
| /updateData | POST | handleUpdateData | Update a register |
| /toggleMaster     | POST | handleToggleMaster | Toggle between master and slave mode |
| /toggleSwap      | POST | handleToggleSwap | Toggle for register swap (MSB-LSB) |
| * | - | handleRoot | Redirect all requests to the DNS server to launch the captive portal |


