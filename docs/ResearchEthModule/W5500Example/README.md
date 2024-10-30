# W5500 Example for ESP32

This document is a research of how to use the W5500 Ethernet module with an ESP32 microcontroller.

## Product Link
You can purchase the W5500 Ethernet module from Amazon using the following link: [AZDelivery Internet Ethernet Module](https://www.amazon.it/AZDelivery-Internet-Ethernet-Microcontrollore-Arduino/dp/B07CYVRMPL/ref=sr_1_1_sspa?__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2Z777ZTMA9WNM&dib=eyJ2IjoiMSJ9.t0emCGrjs3b0FK9PMOyi_ouXIrakJ3c-wuHPS5U-MGNF_8SGKqs5AETm0zsqGgmDjb0IdLinvMW9KG8LrJFumU4vS1pD8M8Zfr7FaOFhOyJXBOcBGrQ_2C8_DnQMi9BdMDaNFotrn2cfXk_gUNV4abShkFSix9p62f-Yr4UOZpOFmWoZ96_9Y2Y01yNT9zHaEL_vLy9vXm0rdJzbf7eifqzxLLYFtT-MTzlJ88v7wz4ZcTqYTp-ZnJaExr4fAHBXu-7KIIZUlelRo-MSgVCFd_Xjqq3fchlptvnb-sraMAI.iJ8dAC3i4mNmT05ZPq1r5xENAgEikI6zPMAhKVmLIi4&dib_tag=se&keywords=W5500&qid=1730288356&sprefix=w5500%2Caps%2C171&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1).

## Requirements
- ESP32 microcontroller
- W5500 Ethernet module
- Jumper wires
- Breadboard (optional)

## Wiring
Connect the W5500 module to the ESP32 as follows:
- **W5500** | **ESP32**
- VCC      | 3.3V
- GND      | GND
- MISO     | MISO (GPIO19)
- MOSI     | MOSI (GPIO23)
- SCK      | SCK (GPIO18)
- CS       | GPIO5
- RST      | GPIO4

## Code Example for W5500 not Testedfx
```cpp
#include <SPI.h>
#include <Ethernet.h>

// MAC address for the Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Initialize the Ethernet client library
EthernetClient client;

void setup() {
    // Start the Ethernet connection
    Ethernet.begin(mac); // Use DHCP to obtain an IP address

    //without DHCP:
    //Ethernet.begin(mac, IPAddress(192, 168, 1, 177)); // Use a static IP address

    // Check for Ethernet hardware present
    
    while (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.");
        delay(1); 
        Ethernet.begin(mac); // Retry to initialize the Ethernet shield
    }
    

    // Check for Ethernet connection
    if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("Ethernet cable is not connected.");
    }

    Serial.begin(9600);
    Serial.println("Ethernet initialized.");
    Serial.print("IP: ");
    Serial.println(Ethernet.localIP());
}

void loop() {
    // Check if Ethernet cable is connected
    if (Ethernet.linkStatus() == LinkON) {
        Serial.println("Ethernet cable is connected.");
    } else {
        Serial.println("Ethernet cable is not connected.");
    }
    
    delay(2000);
}
```

## References
- [ESP32 Documentation](https://esp32.com/viewtopic.php?t=26828)
- [W5500 Datasheet](https://docs.wiznet.io/img/products/w5500/W5500_ds_v110e.pdf)

- [Guide 1 ](https://mischianti.org/esp32-ethernet-w5500-with-plain-http-and-ssl-https/)

- [Guide 2 Git repo](https://github.com/BOlaerts/ESPHome-W5500-Ethernet-on-ESP32-boards/blob/main/README.md)

    - has different vesion of product w5500: [link](https://www.amazon.it/USR-ES1-W5500-Chip-Ethernet-Converter/dp/B07RGLN436/ref=sr_1_6?__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2Z777ZTMA9WNM&dib=eyJ2IjoiMSJ9.t0emCGrjs3b0FK9PMOyi_ouXIrakJ3c-wuHPS5U-MGNF_8SGKqs5AETm0zsqGgmDjb0IdLinvMW9KG8LrJFumU4vS1pD8M8Zfr7FaOFhOyJXBOcBGrQ_2C8_DnQMi9BdMDaNFotrn2cfXk_gUNV4abShkFSix9p62f-Yr4UOZpOFmWoZ96_9Y2Y01yNT9zHaEL_vLy9vXm0rdJzbf7eifqzxLLYFtT-MTzlJ88v7wz4ZcTqYTp-ZnJaExr4fAHBXu-7KIIZUlelRo-MSgVCFd_Xjqq3fchlptvnb-sraMAI.iJ8dAC3i4mNmT05ZPq1r5xENAgEikI6zPMAhKVmLIi4&dib_tag=se&keywords=W5500&qid=1730289561&sprefix=w5500%2Caps%2C171&sr=8-6)


- [Guide 3 Github repo](https://github.com/iafilius/ESP32_W5500_Ethernet_NTP_deepsleep_demo/tree/master)  <-in future will follow this guide and Guide 1

## Issues
- The W5500 module may not work with some ESP32 boards. If you encounter any issues, try using a different ESP32 board or W5500 module.
<br>
it seems more appropriate to use the w5500 with Arduino boards, as it is more compatible with them.

see this issue: [link](https://forum.arduino.cc/t/esp32-w5500-not-working/985120/2)