# ENC28J60 Example

This example demonstrates how to use the ENC28J60 Ethernet module with your ESP32 project.
## Requirements

- ESP32 board
- ENC28J60 Ethernet module
- Ethernet library for ENC28J60
- Jumper wires

## Installation

1. Connect the ENC28J60 module to your ESP32 board as follows:

    ![alt text](wifilan_esp32_enc_sch.jpg)

2. Install the Ethernet library for ENC28J60:
    - Open the Arduino IDE.
    - Go to `Sketch` > `Include Library` > `Manage Libraries`.
    - Search for `UIPEthernet` and install it.

## Usage

1. Open the Arduino IDE.
2. Go to `File` > `Examples` > `UIPEthernet` > `WebServer`.




## References



- [ENC28J60 Module on Amazon](https://www.amazon.it/AZDelivery-ENC28J60-Internet-Ethernet-Arduino/dp/B07D8SV85Q/ref=sr_1_1_sspa?__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=BLBM0SCXP19A&dib=eyJ2IjoiMSJ9.vQdgSXCCHNioofOgClbgQmZHe6P7pulu16ZJ6d4qBnlWWQiBnmgmSPVqaM6LiasQTmGk5IxwicRWMSJabS-kvp-9TJMnv88Sn77sCGPmJ3Cg6c7THSK3sYiBfDOjeIvDgoyD6TF8R-gjgSlsvjqBiMGVx3aFB37vr-j8MW0Nsip9GnqXUpvfePV9UC8_Gv0kcfBDe9LmScgbHzqdeR8ros4Tv7M1nO3aM1KT8J-CnnoRjPtrewIDNMVZz01zwRby_OsWhxB_HPqbbLK0CJvA4G_EPZx3Cnf-TBK2e5UWOkk.kALmlXn7c587n9ZETEfvmgi1-Q7jHS6riNZA5sz0Oj4&dib_tag=se&keywords=ENC28J60&qid=1730290515&sprefix=enc28j60%2Caps%2C167&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1)

- [UIPEthernet Library](https://github.com/UIPEthernet/UIPEthernet)
- [ENC28J60 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/39662c.pdf)

- [Guide 1](https://wicard.net/wifi-lan-esp32-enc28j60/)

- [Guide 2](https://www.geeetech.com/wiki/index.php/Arduino_ENC28J60_Ethernet_Module?srsltid=AfmBOooNwTSsF875Sab-oIlZ7RBNq-Mw6ssF1RasmwL76pf9URoLGKuE)

- [Guide 3](https://mischianti.org/esp32-ethernet-enc28j60-with-plain-http-and-ssl-https/)

## Code Example for ENC28J60 Module not Testedfx

```cpp

#include <SPI.h>
#include <UIPEthernet.h>  // Include la libreria per ENC28J60

// Imposta il MAC address (puoi usarne uno a tua scelta)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Imposta un indirizzo IP statico (opzionale se usi DHCP)
IPAddress ip(192, 168, 1, 177);

EthernetClient client;

void setup() {
  Serial.begin(115200);

  // Avvia Ethernet con IP statico
  Ethernet.begin(mac, ip);
  
  // Oppure, per usare DHCP
  // if (Ethernet.begin(mac) == 0) {
  //   Serial.println("Errore: impossibile ottenere IP con DHCP");
  //   Ethernet.begin(mac, ip);  // Riprova con IP statico
  // }

  Serial.print("Indirizzo IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Verifica se il cavo Ethernet è collegato
  if (Ethernet.linkStatus() == LinkON) {
    Serial.println("Cavo Ethernet collegato.");
  } else {
    Serial.println("Cavo Ethernet non collegato.");
  }
  
  delay(2000);
}
    
```

## Notes
 questo modulo non ha modulo TCP/IP integrato, quindi è necessario utilizzare una libreria esterna come UIPEthernet per gestire la connessione Ethernet.

 cio influisce sulle prestazioni della connessione rispetto ai moduli Ethernet con modulo TCP/IP integrato come il W5500.

 inoltre Esp32 se ha carico gia eccessivo di lavoro come nel nostro caso questo modulo e sconsigliato perche richiede molte risorse di sistema.