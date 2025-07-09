| Studente        | Tutor           |
| ----------------- | ----------------- |
| Alessio Tommasi | Mirko Gelsomini |

## Anno Accademico

2024 – 2025


---



<br>
<br>


# ALPHA: Acquisizione Locale di Parametri con Hardware Avanzato

## Descrizione

Il progetto consiste nella realizzazione di un sistema di acquisizione misure basato su un microcontrollore ESP32, con lo scopo di raccogliere dati da sonde di temperatura, segnali analogici e gestire uscite digitali e analogiche. Il sistema dovrà inoltre comunicare con dispositivi esterni tramite il protocollo **Modbus RTU** (RS485) e **Ethernet TCP/IP**, includendo la funzionalità di **datalogging** per la storicizzazione dei dati. Il candidato lavorerà con hardware fornito da un'azienda collaborante e utilizzerà la piattaforma di sviluppo **Arduino IDE**.



<br><br><br><br><br>

---

# Compiti Tesi

| **Categoria** | **Attività** | **Descrizione** | **Stato** |
| :--- | :--- | :--- | :--- |
| **Comunicazione e Protocolli** | ESP32 - Modbus Master (RS485) | Verifica della capacità dell’ESP32 di inviare richieste come Master Modbus e ricevere correttamente vari tipi di dati, convertendoli dai registri holding. | COMPLETATO |
| | ESP32 - Modbus Slave (RS485) | Verifica della capacità dell’ESP32 di rispondere come Slave Modbus e gestire correttamente i valori dei registri holding. | COMPLETATO |
| | ESP32 - Modbus Slave (Test) | Capacità dell’ESP32 di rispondere alle richieste Modbus da software come ModScan, restituendo dati riconvertiti dai registri holding. | COMPLETATO - da testare |
| | Lettura via Modbus RTU | Possibilità di leggere ogni grandezza utilizzando il protocollo Modbus RTU. | COMPLETATO |
| | Configurazione WiFi | Facilità e successo della configurazione iniziale WiFi tramite captive portal, inclusa la transizione a una nuova rete. | COMPLETATO |
| | Comunicazione Indirizzo IP | Comunicazione corretta del nuovo indirizzo IP all’utente dopo la connessione alla nuova rete WiFi. | COMPLETATO |
| | ~~Plus: Ethernet con Modbus TCP/IP~~ | ~~Implementazione del protocollo Ethernet Modbus TCP/IP.~~ | *Funzionalità rimossa in accordo con l’esaminatore* |
| **Acquisizione e Gestione Dati** | Acquisizione segnali analogici | Acquisizione di tensione, corrente, resistenza, termocoppia e Pt100. | COMPLETATO |
| | Integrazione con modulo ADS1115 | Implementazione del modulo ADS1115 per la lettura di segnali analogici. | COMPLETATO |
| | Impostazioni utente | Possibilità di impostare: Ingresso in tensione (inizio/fondo scala), Ingresso in corrente (inizio/fondo scala), Ingresso termocoppia (tipo), Ingresso RTD (Pt100/PT1000 con linearizzazioni). | FATTO E TESTATO |
| | Gestione Uscite | Ogni uscita analogica/digitale può essere associata a uno degli ingressi, impostare un segnale di allarme o replicare un segnale letto da un ingresso su un’uscita selezionata. | COMPLETATO |
| | Esempi Gestione Uscite | - Ingresso digitale: se attivo, attiva l’uscita.<br>- Ingresso analogico: configurazione soglie di allarme (min/max).<br>- Esempio: soglia massima 10mA per ingresso 0-20mA, se superata, l’uscita si attiva. | COMPLETATO |
| | Memorizzazione Locale dei Dati | Capacità dell’ESP32 di salvare in modo efficiente diversi tipi di dati provenienti dai registri holding nella memoria locale. | IN CORSO - Creazione file Xls per estrazione dati registrati |
| **Interfaccia Web e UX** | Pagina di Configurazione | Completezza e usabilità della pagina di configurazione, inclusa la possibilità di creare, modificare ed eliminare misure. | COMPLETATO PER MODBUS, IN CORSO per ADS |
| | Pagina Analytics | Precisione e chiarezza della visualizzazione dati in tempo reale nella pagina analytics in formato testuale. | COMPLETATO |
| | Pagina web ADS | Creazione pagina web per la gestione dei segnali letti da ADS, compresa la linearizzazione delle sonde PT100 e PT1000. | COMPLETATO |
| | Resource Monitor | Creazione pagina web per la visualizzazione in tempo reale delle risorse utilizzate. | COMPLETATO |
| | Design Interfaccia Utente (BONUS) | Qualità complessiva del design e dell’esperienza utente dell’interfaccia web, incluse le pagine di configurazione e analytics. | COMPLETATO - possibili ulteriori modifiche se richieste |
| **Sistema e Stabilità** | Stabilità del Sistema | Stabilità e affidabilità del sistema durante il funzionamento, inclusa la gestione degli errori e dei processi di recupero. | IN CORSO |
| | Verifica funzionalità | Test in presenza con esaminatore. | Da completare con le nuove funzionalità richieste nell’ultimo incontro. |
| **Documentazione e Presentazione** | Qualità e Completezza della Documentazione | Qualità e completezza della documentazione, con istruzioni dettagliate, immagini e informazioni utili per la replica o comprensione del prodotto. | IN CORSO |
| | Documentazione software | Creazione di un documento di sintesi con spiegazione dettagliata e codice commentato. | DA FARE: completare report e creare presentazione, durata ~15 min |
| | Qualità e Completezza della Presentazione | Qualità della presentazione, con contenuti ben strutturati, visual chiari e copertura esaustiva di tutte le funzionalità e l’architettura del prodotto. | DA FARE |
| | Qualità della Demo | Efficacia della dimostrazione del prodotto nel mostrare funzionalità, capacità e valore aggiunto, risultando coinvolgente e ben preparata. | DA FARE |


## Recap Obiettivi

- Creare un sistema completo di acquisizione misure utilizzando l'ESP32.
- Garantire una corretta lettura e gestione delle sonde di temperatura (**PT100**, **PT1000**, **TC**) e segnali analogici.
- Implementare la comunicazione via **Modbus RTU** ed **Ethernet TCP/IP** con un web server integrato.
- Implementare funzionalità di **datalogging** per permettere la storicizzazione dei dati acquisiti.
- Garantire la funzionalità del sistema su hardware reale fornito dall'azienda collaborante.

## Tecnologie

- **Microcontrollore**: ESP32 38 pin
- **Piattaforma di sviluppo**: Arduino IDE, ESP Dev Module, Espressif 3.0.7 board for ESP32
- **Comunicazione**: RS485 (Modbus RTU), Wifi 
- **Sensori**: Moduli MAX31865 (PT100/PT1000), MAX31855 (Termocoppie)
- **Linguaggio di programmazione**: C/C++ (Arduino)

Link alla documentazione Ufficiale: [Link](https://progettistudio.supsi.ch/dettaglio.php?p=C10936)
<br>
<br>
                                                                                                                                                     

<br>
<br>

## Attivita Svolte:

| Attivita                 | Descrizione                                                                                        | Tempo impiegato | Note                                                                                                                                                                                                                                                                                             |
| -------------------------- | ---------------------------------------------------------------------------------------------------- | ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Punto di Partenza        | Creazione del report iniziale, video demo, caricamento del materiale, configurazione dell'ambiente e creazione del file README.md | 2h 15min        |                                                                                                                                                                                                                                                                                                |
| Comunicazione Indirizzo IP | Comunicazione accurata del nuovo indirizzo IP all'utente dopo la connessione alla nuova rete WiFi.   | 4 ore           | Si è notato crash e reboot quando si immette chiave WiFi errata che causa crash e reboot!                                                                                                                                                                                                        |
| Comunicazione Indirizzo IP | Correzione 1                                                                                       | 5h              | Risoluzione errori però non posso fare sia da AP che da WiFi in 2 diverse quindi quando mi disconnetto da una rete per fare connessione a quella nuova non posso visualizzare messaggio con IP. Non si presenta problema con AP perché ESP32 può fungere sia da WiFi che da AP contemporaneamente                                                                                                                                                                                                        |
| Pagina Analytics         | Accuratezza e chiarezza della visualizzazione dei dati in tempo reale sulla pagina analytics in formato testuale. | 4.30              |                        ore impiegate: 8.30 -> 13.00   tot: 4.30 ore non funziona: lettura doppia dello stesso registro,  Lettura del valore millseconds: da testare: grafico                                                                                                                                                                                                                                                                                                        |
| Pagina Analytics         | Accuratezza e chiarezza della visualizzazione dei dati in tempo reale sulla pagina analytics in formato testuale. | 4.00              |                        ore impiegate: 19.30 -> 23.30   tot: 4.00 fix bug precedenti, creazione popup start e stop lettura. ora non funziona: lettura doppia dello stesso registro causa crash sistema,  da testare: grafico                                                                                                           
| Pagina Grafico           | Visualizzazione dei dati in tempo reale sulla pagina del grafico.                                    | 1h.00             |                        ore impiegate: 8.30 -> 9.30  
| Ricerca e sviluppo       | Componente del protocollo Modbus e pinout.                                                         | 3h                |                        
|  Wiznet W5500 e ENC28J60   | Ricerca.                                                                                           | 4h                | 12.00 -> 16.00 of 30/10/2024
| Pagina Cronologia        | Accuratezza e chiarezza della visualizzazione dei dati storici sulla pagina della cronologia.        | 2h                |  9.30 -> 11.30 of 31/10/2024
| Risoluzione problemi     | Risoluzione di problemi legati a watchdog, deadlock con letture multiple dello stesso registro, crash e riavvii anomali. | 24h e 30min       | 1/11/2024 9.00 -> 12.30 AND 14.00 -> 17.00, 2/11/2024 8.00 -> 11.00 AND 14.00 -> 17.00 , 4/11/2024 8.00 -> 11.00 AND 14.00 -> 17.00, 6/11/2024 8.00 -> 14.00 |
| Documentazione Grafico e Cronologia | Vedere il video nella sezione seguente.                                                    | 1h                | 14.00 -> 15.00 of 6/11/2024 
| Correzione Anteprima Documentazione | Vedere i dettagli dell'errore [qui](./issues/README.md).                                   | 1h                | 15.00 -> 16.00 of 6/11/2024    
| Diagramma di Gantt       | Creazione del diagramma di Gantt per le attività.                                                  | 1h                | 16.00->17 of 6/11/2024   
| Modulo ENC28J60          | Ricerca iniziale e test con Arduino Nano.                                                          | 3h                | 15.00->18 of 13/11/2024  
| Correzione Driver Adattatore USB-RS485 | Dettagli sull'errore e sulla ricerca effettuata disponibili [qui](./issues/Adattatore%20convertitoreUSBaRS485.md). | 11h               |   15.00->18.00 of 19/11/2024 <br> 9.00->11.00; 14.00->18.00 of 20/11/2024 <br> 9.30->12.30 of 21/11/2024 
| Test Modbus Slave        | Test e sviluppo della funzionalità Modbus Slave (non ancora funzionante).                          | 7h                |   9.00->12.00 AND <br> 13.30->17.30;  of 06/12/2024 <br> 
| Multiplexer              | Sviluppo funzionalità Multiplexer (non ancora funzionante).                                        | 10h               |   8.00->12.00 AND <br> 13.00->19.00;  of 21/12/2024 <br> 
| Multiplexer              | Trovato errore: limite di memoria dell'ESP. Vedi [link](https://github.com/AlessioTommasi-supsi/ArduinoLibrary/blob/progettosemestreOttimizzaz/model/Esp32_38pin.cpp). L'aggiunta di codice dopo il commento causa un crash per superamento del limite di memoria. | 7.30h             |   7.30->11.00 AND <br> 14.00->18.00;  of 21/12/2024 POSSIBILI SOLUZIONI passare al chip ESP32-S3 che ha il doppio della memoria integrata pero si devono adattare i pin
| Multiplexer              | Correzione parziale del problema di memoria. Da Mac riesco a gestire 2 pin + multithreading (start/stop) + grafico con i valori di tensione letti. [Video demo](./video/MULTIPLEX.mov) <br> NOTA: <br> Da testare se il problema è dovuto all'uso di memoria statica invece che dinamica. Prevedo di implementare una pagina con una circular progress bar per monitorare la memoria utilizzata e libera. | 23h = 7+8+8       |   9.00->11.00 AND <br> 14.00->19.00;  of 22/12/2024 <br> 9.00->11.00 AND <br> 13.00->19.00;  of 23/12/2024 <br> 9.00->11.00 AND <br> 14.00->19.00;  of 24/12/2024  
| Monitor                  | Implementazione della pagina per il monitoraggio delle risorse.                                    | 12.15h            |   8.00->11.15 AND <br> 13.30->17.00;  of 26/12/2024 <br>  <br> 13.30->19.00  of 27/12/2024 <br>
| Multiplexer              | Tentativo di implementazione con heap, ma il problema di crash dopo l'aggiunta di 2 pin persiste. L'heap risulta utilizzato solo al 50%. | 6h                |   13.00->19.00 AND <br> 13.30->17.00;  of 26/12/2024 <br> 
| Multiplexer              | Risolto errore con `static` e gestendo l'aggiunta dei pin in `initializePin`.                      | 6.30h             |   9.00->11.00 AND <br> 13.30->17.00;  of 28/12/2024 <br> 
| Multiplexer              | Risolto errore in `initializePin`: alcuni pin davano errore perché tentavano di leggere da risorse utilizzate dal WiFi. | 6.30h             |   9.00->11.00 AND <br> 13.30->17.00;  of 29/12/2024 <br> 
| Multiplexer              | DEBUG: Errore "Guru Meditation Error: Core 1 panic'ed (ADC3)" si verifica durante la compilazione se la pagina `http://192.168.178.144/pinout` è aperta, perché il sistema tenta di leggere l'oggetto prima che sia completamente costruito. | 2h                |   9.00->11.00  of 28/12/2024  ANCORA DA APPROFONDIRE BENE COME GESTIRE pero siccome e errore che puo accadere solo in fase di boot non e approfondito per ora<br> 
| Monitor                  | Implementazione del grafico dello stack per ogni singolo thread di registrazione nella pagina di monitoraggio. | 12.15h            |   8.00->11.15 AND <br> 13.30->17.00;  of 26/12/2024 <br>  <br> 13.30->19.00  of 30/12/2024 <br>
| Documentazione Tesi      | Creazione del documento `tesi.tex`.                                                                | 24h               |      8.00->11.30 AND <br> 13.30->17.300;  of 14/02/2025 <br>  <br> 8.00->11.30 AND <br> 13.30->17.300;  of 15/02/2025 <br>  <br> 8.00->11.30 AND <br> 13.30->17.300;  of 16/02/2025 <br>  <br>8.00->11.30 AND <br> 13.30->17.300;  of 17/02/2025 <br>  <br>
| Documentazione Tesi      | Correzione con le modifiche suggerite da Fabio.                                                    | 12h               | <br> 13.30->17.30;  of 18/02/2025 <br>  <br> 8.00->11.30 AND <br> 13.30->17.300;  of 19/02/2025 <br>
| Documentazione Tesi      | Correzione con le modifiche suggerite da Mirko [link](./Mail_Correzioni_Mirko.pdf) (ancora da completare). | 2h                | <br> 8.30->10.30;  of 24/02/2025 <br>  <br> 
| Correzione Bug Presentazione | Debug e fix della maggior parte degli errori riscontrati durante la presentazione.               | 8h                | <br> 8.30->10.30; AND <br> 13.30->17.30;  of 25/02/2025 <br>  <br> 
| Modifica Pin             | Creazione della funzionalità di modifica dei pin.                                                  | 12h               | <br> 8.30->11.30; AND <br> 13.30->17.30;  of 26/02/2025 <br>  <br> <br> 10.30->11.30; AND <br> 13.30->16.30;  of 27/02/2025 <br>  <br>
| Modifica Pin             | Testing: rilevati bug dovuti ad accesso concorrente delle risorse quando più pagine sono attive su `/pinout`. | 2h                | <br> 8.30->10.30;  of 28/02/2025 <br>  <br> 
| Modifica Pin             | Correzione del bug di accesso concorrente (non ancora del tutto risolto). Si prevede di utilizzare un mutex in `SystemState`. | 16h               |  <br> 13.30->17.30;  of 28/02/2025 <br>  <br> <br> 8.30->11.30; AND <br> 13.30->16.30;  of 01/03/2025 <br>  <br> 8.30->11.30; of 02/03/2025<br>  <br> 
| ADS1115                  | Creazione dello sketch `../src/ADS1115`.                                                           | 6h 30min          |  8.30->11.30; AND <br> 13.30->18.30;  of 14/03/2025 <br> 
| Vista Modbus Master      | Correzione di un errore di concorrenza che causava il crash del dispositivo con più client connessi. | 8h                |  8.30->11.30; AND <br> 13.30->18.30;  of 21/03/2025 
| Funzionalità Multi-utente | Organizzazione delle route tramite il pattern Decorator per l'aggiunta e la rimozione a runtime in base al tipo di utente connesso (parte di creazione e gestione utente da completare). | 8h                |  8.30->11.30; AND <br> 13.30->18.30;  of 21/03/2025 
| Impostazioni Utente      | Creazione del form per la configurazione dei tipi di ingressi e uscite da parte dell'utente, come richiesto dal professore (solo HTML, da implementare nel progetto). | 8h                |  8.30->11.30; AND <br> 13.30->18.30;  of 22/03/2025 
| Ottimizzazione           | Modifica del partizionamento dell'ESP per aumentare lo spazio per l'applicazione. Rimossa la funzionalità OTA, ora si hanno 3MB disponibili invece di 1MB. | 8h                |  8.30->11.30; AND <br> 13.30->18.30;  of 23/03/2025 
| Ricerca                  | Linearizzazione delle sonde RTD e termocoppie. Maggiori info [qui](./LINEARIZZAZIONE_SONDE.md).     | 8h                |  8.30->11.30; AND <br> 13.30->18.30;  of 24/03/2025 
| Correzione Compatibilità Scheda | Maggiori info [qui](./issues/arduino_espaasynkwebsrv_error.md).                               | 8h                |  8.30->11.30; AND <br> 13.30->18.30;  of 25/03/2025 
| Creazione Pagina ADS     | Creazione di una pagina equivalente a "History" per Modbus e pin per ADS. Ha richiesto tempo aggiuntivo a causa di errori legati alla limitata dimensione dei dati trasmissibili dall'ESP su protocollo HTTP. Per massimizzare i dati, si è deciso di rimuovere parti di CSS e JS dopo test estensivi. | 16h               |   <br> 13.30->18.30;  of 20/06/2025 <br> 13.30->18.30;  of 22/06/2025  <br> 9.30->13.30;  of 22/06/2025  <br> 13.30->18.30;  of 25/06/2025
| Struttura Dati Sonde     | Creazione della struttura dati per la linearizzazione delle sonde PT100 e PT1000 e integrazione nel progetto. Tabelle utilizzate [qui](./tabelleSonde.pdf). | 15h               |  8.30->11.30; AND <br> 13.30->18.30;  of 25/03/2025