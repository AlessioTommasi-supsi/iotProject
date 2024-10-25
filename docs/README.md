# TSM_IoT - Internet of Things 2024


| Studente        | Tutor           |
| ----------------- | ----------------- |
| Alessio Tommasi | Mirko Gelsomini |

## Anno Accademico

2024 – 2025

## Data

14-10-2024

---

# REPORT:



### Old Evaluation Criteria


| Criteria Name                              | Criteria Description                                                                                                                                                                              | tempo |
| -------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------- |
| ESP32 - Modbus Master - Data Reception     | The ESP32's ability to send Modbus requests to the ESAM E2002 and accurately receive various data types converting them correctly from holding registers.                                         | .     |
| ESP32 - Modbus Master - Local Data Storage | The ESP32's capability to save different data types from holding registers into local storage efficiently.                                                                                        | .     |
| ESP32 - Modbus Slave                       | The ESP32's proficiency in responding to Modbus requests from ModScan software with accurate and reconverted data from holding registers.                                                         | .     |
| WiFi Configuration                         | The ease and success of the initial WiFi setup via a captive portal including the transition to a new network.                                                                                    | .     |
| IP Address Communication                   | Accurate communication of the new IP address to the user after connecting to the new WiFi network.                                                                                                | .     |
| Configuration Page                         | The completeness and usability of the configuration page including the ability to create, edit, and delete measurements.                                                                          | .     |
| Analytics Page                             | The accuracy and clarity of real-time data display on the analytics page in textual format.                                                                                                       | .     |
| System Stability                           | The stability and reliability of the system during normal operation including error handling and recovery processes.                                                                              | .     |
| Documentation Quality and Completeness     | The quality and thoroughness of the documentation providing step-by-step instructions, images, and relevant information for users to replicate or understand the product.                         | .     |
| Presentation Quality and Completeness      | The quality of the presentation including well-structured content, clear visuals, and comprehensive coverage of all relevant aspects of the product such as functionality and architecture.       | .     |
| Demo Quality                               | The effectiveness of the product demonstration in showcasing its features, capabilities, and value proposition, being engaging, well-prepared, and leaving a positive impression on the audience. | .     |
| User Interface Design - BONUS              | The overall design and user experience of the web interface including both the configuration and analytics pages.                                                                                 | .     |

<br>
<br>

## Attività svolte nel precedente corso:


| Criteria Name                              | Criteria Description                                                                                                                                                      | tempo |
| -------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------- |
| ESP32 - Modbus Master -                    | Data Reception	The ESP32's ability to send Modbus requests to the ESAM E2002 and accurately receive various data types converting them correctly from holding registers.  | .     |
| ESP32 - Modbus Master - Local Data Storage | The ESP32's capability to save different data types from holding registers into local storage efficiently.                                                                | .     |
| WiFi Configuration                         | The ease and success of the initial WiFi setup via a captive portal including the transition to a new network.                                                            | .     |
| Configuration Page                         | The completeness and usability of the configuration page including the ability to create, edit, and delete measurements.                                                  | .     |
| System Stability                           | The stability and reliability of the system during normal operation including error handling and recovery processes.                                                      | .     |
| Documentation Quality and Completeness     | The quality and thoroughness of the documentation providing step-by-step instructions, images, and relevant information for users to replicate or understand the product. | .     |

<br>
<br>

## Nuove attivita di progetto:

# ALPHA: Acquisizione Locale di Parametri con Hardware Avanzato

## Descrizione

Il progetto consiste nella realizzazione di un sistema di acquisizione misure basato su un microcontrollore ESP32, con lo scopo di raccogliere dati da sonde di temperatura, segnali analogici e gestire uscite digitali e analogiche. Il sistema dovrà inoltre comunicare con dispositivi esterni tramite il protocollo **Modbus RTU** (RS485) e **Ethernet TCP/IP**, includendo la funzionalità di **datalogging** per la storicizzazione dei dati. Il candidato lavorerà con hardware fornito da un'azienda collaborante e utilizzerà la piattaforma di sviluppo **Arduino IDE**.


## Elettrical schematization of semester project:
![alt text](EsamElettric.jpg)

## Compiti


| Attività                                 | Descrizione                                                                                                                                |
| ------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| **Configurazione sensori di temperatura** | Configurare e integrare sensori di temperatura**PT100**, **PT1000** e **termocoppie** utilizzando moduli come **MAX31865** e **MAX31855**. |
| **Lettura segnali analogici**             | Implementare la lettura di segnali analogici tramite gli ingressi**ADC** dell'ESP32 e eventuali moduli esterni.                            |
| **Gestione uscite digitali e analogiche** | Sviluppare la gestione delle uscite digitali e analogiche tramite l'ESP32.                                                                 |
| **Comunicazione RS485 (Modbus RTU)**      | Integrare la comunicazione**RS485** utilizzando il protocollo **Modbus RTU** per interfacciarsi con altri dispositivi.                     |
| **Server Web (Ethernet TCP/IP)**          | Sviluppare un server**Web** basato su **Ethernet TCP/IP** per il monitoraggio e controllo remoto dei dati acquisiti.                       |
| **Datalogging**                           | Implementare un sistema di**datalogging** per salvare e storicizzare i dati raccolti dai sensori.                                          |
| **Test e validazione**                    | Testare e validare il sistema attraverso simulazioni e test su hardware reale.                                                             |

## Recap Obiettivi

- Creare un sistema completo di acquisizione misure utilizzando l'ESP32.
- Garantire una corretta lettura e gestione delle sonde di temperatura (**PT100**, **PT1000**, **TC**) e segnali analogici.
- Implementare la comunicazione via **Modbus RTU** ed **Ethernet TCP/IP** con un web server integrato.
- Implementare funzionalità di **datalogging** per permettere la storicizzazione dei dati acquisiti.
- Garantire la funzionalità del sistema su hardware reale fornito dall'azienda collaborante.

## Tecnologie

- **Microcontrollore**: ESP32
- **Piattaforma di sviluppo**: Arduino IDE
- **Comunicazione**: RS485 (Modbus RTU), Ethernet TCP/IP
- **Web server**: Librerie per ESP32
- **Sensori**: Moduli MAX31865 (PT100/PT1000), MAX31855 (Termocoppie)
- **Datalogging**: Sistema di memorizzazione dati su SD card o altra memoria persistente
- **Linguaggio di programmazione**: C/C++ (Arduino)

Link alla documentazione Ufficiale: [Link](https://progettistudio.supsi.ch/dettaglio.php?p=C10936)
<br>
<br>

## Attivita che si intendono implementare prossimamente


| Criteria Name            | Criteria Description                                                                               | tempo                                  |
| -------------------------- | ---------------------------------------------------------------------------------------------------- | ---------------------------------------- |
| IP Address Communication | Accurate communication of the new IP address to the user after connecting to the new WiFi network. | inizio: 11.00    fine 14.50  tot 4 ore |
| Analytics Page           | The accuracy and clarity of real-time data display on the analytics page in textual format.        |                                        |

<br>
<br>

## Attivita Completate:

| Attivita                 | Descrizione                                                                                        | Tempo impiegato | Note                                                                                                                                                                                                                                                                                             |
| -------------------------- | ---------------------------------------------------------------------------------------------------- | ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Starting Point           | Creazione Report iniziale, demo video, upload materiale e setup environment e creazione README.md | 2h 15min        |                                                                                                                                                                                                                                                                                                |
| IP Address Communication | Accurate communication of the new IP address to the user after connecting to the new WiFi network. | 4 ore           | Si è notato crash e reboot quando si immette chiave WiFi errata che causa crash e reboot!                                                                                                                                                                                                        |
| IP Address Communication | Fix 1                                                                                              | 5h              | Risoluzione errori però non posso fare sia da AP che da WiFi in 2 diverse quindi quando mi disconnetto da una rete per fare connessione a quella nuova non posso visualizzare messaggio con IP. Non si presenta problema con AP perché ESP32 può fungere sia da WiFi che da AP contemporaneamente                                                                                                                                                                                                        |
| Analytics Page           | The accuracy and clarity of real-time data display on the analytics page in textual format.        | 4.30              |                        ore impiegate: 8.30 -> 13.00   tot: 4.30 ore non funziona: lettura doppia dello stesso registro,  Lettura del valore millseconds: da testare: grafico                                                                                                                                                                                                                                                                                                        |
| Analytics Page           | The accuracy and clarity of real-time data display on the analytics page in textual format.        | 4.00              |                        ore impiegate: 19.30 -> 23.30   tot: 4.00 fix bug precedenti, creazione popup start e stop lettura. ora non funziona: lettura doppia dello stesso registro causa crash sistema,  da testare: grafico                                                                                                           
| Graph Page           |  real-time data display on the graph page         | 1h.00              |                        ore impiegate: 8.30 -> 9.30  
<br>


---

## Demo funzionamento attuale:

<br>
<br>

![Demo Video](./video/InitialPoint.gif)

<br>
<br>

Link al report pdf del report finale anno precedente: [Report](./ReportIotProject.pdf)


## Demo switch wifi:

<br>
<br>

![Demo Video](./video/switch_wifi.gif )

<br>
<br>

---
<br>
<br>

## Demo AnalyticsPage:


<br>

![Demo Video](./video/AnalyticsPage.gif )


   #### RICORDA: non si possono fare 2 volte rec dello stesso registro altrimenti crasha il sistema

    

<br>