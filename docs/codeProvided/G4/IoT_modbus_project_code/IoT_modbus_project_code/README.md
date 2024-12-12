# ESP32 Modbus Master Project

This project is an ESP32-based Modbus Master implementation using the ESP-IDF framework. It communicates with Modbus devices, handles various FreeRTOS tasks, and includes additional functionality such as WiFi configuration and web server setup.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Project Structure](#project-structure)
- [Setup](#setup)
- [Building and Flashing](#building-and-flashing)
- [Configuration](#configuration)
- [Usage](#usage)
- [License](#license)
- [Contributing](#contributing)

## Prerequisites

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) installed
- VS Code (optional, but recommended for development)
- Git installed

## Project Structure


## Setup

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/your-repo-name.git
    cd your-repo-name
    ```

2. **Set up the ESP-IDF environment**:
    ```sh
    . $HOME/esp/esp-idf/export.sh
    ```

## Building and Flashing

1. **Build the project**:
    ```sh
    idf.py build
    ```

2. **Flash the project to your ESP32**:
    ```sh
    idf.py flash
    ```

3. **Monitor the output**:
    ```sh
    idf.py monitor
    ```

## Configuration

- The `sdkconfig` file contains all the project-specific configuration settings. This file is included in the repository to ensure consistent configuration across different environments.

- **Modbus Configuration**:
    - UART Port: Defined by `MB_PORT_NUM`
    - UART TX Pin: Defined by `CONFIG_MB_UART_TXD`
    - UART RX Pin: Defined by `CONFIG_MB_UART_RXD`
    - UART RTS Pin: Defined by `CONFIG_MB_UART_RTS`
    - Baud Rate: Defined by `MB_DEV_SPEED`

## Usage

After flashing the firmware, the ESP32 will initialize as a Modbus master, configure the UART interface, and start the FreeRTOS tasks to manage communication and other functionalities. Monitor the output using `idf.py monitor` to see log messages and debug information.

## License

This project is licensed under the Apache License 2.0. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

---

This project was developed using the ESP-IDF framework and is designed to provide robust Modbus communication capabilities for ESP32-based systems.

For more information, please refer to the official [ESP-IDF documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html).
