
## Issues Related to the Board

Link to Goodnotes: [Qui](https://web.goodnotes.com/s/MFs1q0628At8S2OhyxoSrB#page-4)

### Errore:

![Error Image](image.png)

### Alimentazione Testata:

#### 5V Non Funzionante

Alimentatore info:
![5V Info](image-1.png)

**Nota:** Il LED non si accende con solo questa alimentazione.

#### 19V Non Funzionante

Alimentatore info:
![19V Info](image-3.png)

Board state:
![Board State](image-2.png)

Serial monitor:
![Serial Monitor](image-4.png)

#### 24V: Alimentatore 19V in Serie ad Alimentatore 5V

Nessuna differenza rispetto a 19V. Devo ancora testare se 24V effettivi con multimetro.

### Note

Se stacco ESP, carico programma e poi metto ESP su board, il programma è caricato correttamente ma in base al codice che carico ottengo errori modbus:

- INVALID_QUERY
- DEVICE NOT CONNECTED
- MODBUS TIMEOUT

### Board Voltage Monitor

#### Non Sulla Board

##### Da Serial Monitor:

- Pin number: 32, Type: 6, Voltage: 0.000 V, Input: Yes, Note: ADC4, TOUCH9
- Pin number: 33, Type: 6, Voltage: 0.000 V, Input: Yes, Note: ADC5, TOUCH8
- Pin number: 19, Type: 11, Voltage: 0.000 V, Input: Yes, Note: VSPI MISO
- Pin number: 25, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 18, Type: 11, Voltage: 3.300 V, Input: Yes, Note: VSPI CLK or input digital
- Pin number: 26, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 5, Type: 8, Voltage: 3.300 V, Input: Yes, Note: input digital VSPI CS0, PWM
- Pin number: 27, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 17, Type: 10, Voltage: 3.300 V, Input: Yes, Note: UART RXD1
- Pin number: 14, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 16, Type: 10, Voltage: 3.300 V, Input: Yes, Note: UART TXD2
- Pin number: 12, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 4, Type: 6, Voltage: 3.300 V, Input: Yes, Note: ADC10, TOUCH0
- Pin number: 0, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 13, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 2, Type: 6, Voltage: 3.300 V, Input: No, Note: ADC2 is in use by Wi-Fi. Please see [ADC Limitations](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations) for more info
- Pin number: 9, Type: 1, Voltage: 3.300 V, Input: Yes, Note: SD D2
- Pin number: 10, Type: 1, Voltage: 3.300 V, Input: Yes, Note: SD D3
- Pin number: 8, Type: 1, Voltage: 3.300 V, Input: Yes, Note: SD2 SPIWP HS1 DATA 1
- Pin number: 11, Type: 1, Voltage: 3.300 V, Input: Yes, Note: SPICS0 CMD
- Pin number: 7, Type: 1, Voltage: 3.300 V, Input: Yes, Note: SD0 SPIQ HS1 DATA 0
- Pin number: 6, Type: 1, Voltage: 3.300 V, Input: Yes, Note: segnale di clock temporizzato

##### Dopo Qualche Secondo di Lettura: Da Pagina Web:

[PDF](Pinout_not_attached.pdf)

Come si può notare, dei pin sono differenti.

#### Sulla Board:

**Nota:** Con 19V risulta collegato a Wi-Fi ma non mi fa accedere da internet. L'indirizzo IP è corretto!
![Wi-Fi Connection](image-5.png)

Board scollegata da alimentazione ESP connesso live sulla board:
[Pinout](Pinout_onBoardNoAlimentation.pdf)

Board con alimentazione 19V da tester ESP connesso live sulla board:
[Board Connessa Alimentazione](BoardCOnnessaALIMENTAZIONE.pdf)

### Found

Su pin 13 -- tutti quelli ingressi digitali -- trovato 5V all'avvio che magari causavano crash del sistema poiché all'avvio ESP tenta di tirare a 0 tutti i pin ma non ce la fa.

### Pin da Evitare:

Flash e altri scopi speciali:

- GPIO6 – GPIO11: Riservati alla memoria flash; non usarli.
- GPIO34 – GPIO39: Solo input; non usabili come output.

Pin con funzioni bootstrap/speciali:

Alcuni pin influenzano il processo di boot o sono usati per la programmazione seriale (come GPIO0, GPIO2, GPIO15, TX/RX). Usarli in modo improprio può interferire con l’avvio o la comunicazione, specialmente se risiedono su schede con collegamenti particolari (es. LED integrati, sensori).

Ad esempio, GPIO0, GPIO2, GPIO15 sono “strap pins” che determinano la modalità di avvio. Assicurati di non forzarli in stati contrari ai requisiti di boot mentre il chip si avvia.

### Pin Generalmente Sicuri per I/O Digitali

Puoi considerare i seguenti GPIO per funzioni di input e output, purché tu segua eventuali precauzioni legate al boot:

- GPIO4, GPIO5: Buoni per output e input generali.
- GPIO12 – GPIO19: Generalmente sicuri; ad eccezione di particolari condizioni (es. GPIO12 può influenzare la tensione di alimentazione in alcune configurazioni, ma in molti casi è utilizzabile).
- GPIO21 – GPIO23: Spesso usati per I2C, ma liberi per I/O generali se non serve comunicazione I2C.
- GPIO25 – GPIO27: Generalmente liberi.
- GPIO32, GPIO33: Liberi per I/O.
