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

| **Attività**                                  | **Descrizione**                                                                                                                                | **Stato** |
|-----------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------|----------|
| ESP32 - Modbus Master - RS485 | Verifica della capacità dell’ESP32 di inviare richieste come Master Modbus e ricevere correttamente vari tipi di dati, convertendoli dai registri holding. | COMPLETATO |
| ESP32 - Modbus Slave - RS485 | Verifica della capacità dell’ESP32 di rispondere come Slave Modbus e gestire correttamente i valori dei registri holding. | COMPLETATO |
| Memorizzazione Locale dei Dati | Capacità dell’ESP32 di salvare in modo efficiente diversi tipi di dati provenienti dai registri holding nella memoria locale. | IN CORSO - Creazione file Xls per estrazione dati registrati |
| ESP32 - Modbus Slave | Capacità dell’ESP32 di rispondere alle richieste Modbus da software come ModScan, restituendo dati riconvertiti dai registri holding. | COMPLETATO - da testare |
| Configurazione WiFi | Facilità e successo della configurazione iniziale WiFi tramite captive portal, inclusa la transizione a una nuova rete. | COMPLETATO |
| Comunicazione Indirizzo IP | Comunicazione corretta del nuovo indirizzo IP all’utente dopo la connessione alla nuova rete WiFi. | COMPLETATO |
| Pagina di Configurazione | Completezza e usabilità della pagina di configurazione, inclusa la possibilità di creare, modificare ed eliminare misure. | COMPLETATO PER MODBUS, IN CORSO per ADS |
| Pagina Analytics | Precisione e chiarezza della visualizzazione dati in tempo reale nella pagina analytics in formato testuale. | COMPLETATO |
| Stabilità del Sistema | Stabilità e affidabilità del sistema durante il funzionamento, inclusa la gestione degli errori e dei processi di recupero. | IN CORSO |
| Qualità e Completezza della Documentazione | Qualità e completezza della documentazione, con istruzioni dettagliate, immagini e informazioni utili per la replica o comprensione del prodotto. | IN CORSO |
| Qualità e Completezza della Presentazione | Qualità della presentazione, con contenuti ben strutturati, visual chiari e copertura esaustiva di tutte le funzionalità e l’architettura del prodotto. | DA FARE |
| Qualità della Demo | Efficacia della dimostrazione del prodotto nel mostrare funzionalità, capacità e valore aggiunto, risultando coinvolgente e ben preparata. | DA FARE |
| Design Interfaccia Utente - BONUS | Qualità complessiva del design e dell’esperienza utente dell’interfaccia web, incluse le pagine di configurazione e analytics. | COMPLETATO - possibili ulteriori modifiche se richieste |
| Acquisizione segnali analogici | Acquisizione di tensione, corrente, resistenza, termocoppia e Pt100. | COMPLETATO |
| Impostazioni utente | Possibilità di impostare: | FATTO E TESTATO tutta la sezione |
| | - Ingresso in tensione: inizio scala, fondo scala | COMPLETATO |
| | - Ingresso in corrente: inizio scala, fondo scala | COMPLETATO |
| | - Ingresso termocoppia: tipo di termocoppia | COMPLETATO |
| | - Ingresso RTD (es. Pt100, PT1000): tipo di termoresistenza con relative linearizzazioni applicate | COMPLETATO |
| Lettura via Modbus RTU | Possibilità di leggere ogni grandezza utilizzando il protocollo Modbus RTU. | COMPLETATO |
| Gestione uscite | Ogni uscita analogica/digitale può essere associata a uno degli ingressi, impostare un segnale di allarme o replicare un segnale letto da un ingresso su un’uscita selezionata. | COMPLETATO |
| ESEMPI | - Ingresso digitale: se attivo, attiva l’uscita. | COMPLETATO |
| | - Ingresso analogico: configurazione soglie di allarme (minima o massima). | COMPLETATO |
| | - Esempio: soglia massima 10mA per ingresso 0-20mA, se superata, l’uscita corrispondente si attiva. | COMPLETATO |
| Documentazione software | Creazione di un documento di sintesi con spiegazione dettagliata e codice commentato. | DA FARE: completare report e creare presentazione, durata ~15 min |
| Verifica funzionalità | Test in presenza con esaminatore | Da completare con le nuove funzionalità richieste nell’ultimo incontro. |
| Plus: Ethernet con Modbus TCP/IP | Implementazione del protocollo Ethernet Modbus TCP/IP. (Funzionalità rimossa in accordo con l’esaminatore) |  |
| Integrazione con modulo ADS1115 | Implementazione del modulo ADS1115 per la lettura di segnali analogici. | COMPLETATO |
| Pagina web ADS | Creazione pagina web per la gestione dei segnali letti da ADS, compresa la linearizzazione delle sonde PT100 e PT1000. | COMPLETATO |
| Resource Monitor | Creazione pagina web per la visualizzazione in tempo reale delle risorse utilizzate. | COMPLETATO |


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
| Starting Point           | Creazione Report iniziale, demo video, upload materiale e setup environment e creazione README.md | 2h 15min        |                                                                                                                                                                                                                                                                                                |
| IP Address Communication | Accurate communication of the new IP address to the user after connecting to the new WiFi network. | 4 ore           | Si è notato crash e reboot quando si immette chiave WiFi errata che causa crash e reboot!                                                                                                                                                                                                        |
| IP Address Communication | Fix 1                                                                                              | 5h              | Risoluzione errori però non posso fare sia da AP che da WiFi in 2 diverse quindi quando mi disconnetto da una rete per fare connessione a quella nuova non posso visualizzare messaggio con IP. Non si presenta problema con AP perché ESP32 può fungere sia da WiFi che da AP contemporaneamente                                                                                                                                                                                                        |
| Analytics Page           | The accuracy and clarity of real-time data display on the analytics page in textual format.        | 4.30              |                        ore impiegate: 8.30 -> 13.00   tot: 4.30 ore non funziona: lettura doppia dello stesso registro,  Lettura del valore millseconds: da testare: grafico                                                                                                                                                                                                                                                                                                        |
| Analytics Page           | The accuracy and clarity of real-time data display on the analytics page in textual format.        | 4.00              |                        ore impiegate: 19.30 -> 23.30   tot: 4.00 fix bug precedenti, creazione popup start e stop lettura. ora non funziona: lettura doppia dello stesso registro causa crash sistema,  da testare: grafico                                                                                                           
| Graph Page           |  real-time data display on the graph page         | 1h.00              |                        ore impiegate: 8.30 -> 9.30  
| Ricerca e sviluppo           |  Mobus protocol component and pinout         | 3h              |                        
|  wiznet W5500 e   ENC28J60       |  ricerca         | 4h             | 12.00 -> 16.00 of 30/10/2024
| History Page           | The accuracy and clarity of real-time data display on the analytics page in textual format.        | 2h |  9.30 -> 11.30 of 31/10/2024
| risoluzione watchdog triggered, deadlock problem when same register multiple time, fix crash and rebbot problem|  ricerca         | 24h e 30min             | 1/11/2024 9.00 -> 12.30 AND 14.00 -> 17.00, 2/11/2024 8.00 -> 11.00 AND 14.00 -> 17.00 , 4/11/2024 8.00 -> 11.00 AND 14.00 -> 17.00, 6/11/2024 8.00 -> 14.00 |
| doks usage graph and history page + test |  see the video in the follwing section    |   1h  | 14.00 -> 15.00 of 6/11/2024 
| doks fixed preview problem    | see [Here](./issues/README.md) error detail       |  1h  | 15.00 -> 16.00 of 6/11/2024    
| gant diagram   | in this file at section Diagramma di Gantt per le Attività       |  1h  | 16.00->17 of 6/11/2024   
|  Modulo ENC28J60    | research initial + test with arduino nano       |  3h  | 15.00->18 of 13/11/2024  
|  Fix driver issues Adattatore convertitore da USB a RS485 per w11   |see [Here](./issues/Adattatore%20convertitoreUSBaRS485.md) the detail of this error and the research done       |  11h  |   15.00->18.00 of 19/11/2024 <br> 9.00->11.00; 14.00->18.00 of 20/11/2024 <br> 9.30->12.30 of 21/11/2024 
|  Modbus Slave test and work   | not working yet       |  7h  |   9.00->12.00 AND <br> 13.30->17.30;  of 06/12/2024 <br> 
|  Multiplex   | not working yet       |  10  |   8.00->12.00 AND <br> 13.00->19.00;  of 21/12/2024 <br> 
|  Multiplex   | ho trovato errore: limite  memoria ESP vedi    [link](https://github.com/AlessioTommasi-supsi/ArduinoLibrary/blob/progettosemestreOttimizzaz/model/Esp32_38pin.cpp) se aggiungo qualcosa altro dopo il commento ESP crasha per limite memoria superato!     |  7.30  |   7.30->11.00 AND <br> 14.00->18.00;  of 21/12/2024 POSSIBILI SOLUZIONI passare al chip ESP32-S3 che ha il doppio della memoria integrata pero si devono adattare i pin
|  Multiplex   | fix parziale memoria da mac riesco a fare 2 pin + multithead start and stop + grafico con i valori di tensione letti [video demo](./video/MULTIPLEX.mov) <br> NOTA: <br> da testare se magari e perche non uso memoria dinamica e quindi statica preallocata va fuori range massimo  per far cio successivamente prevedo di implementare pagina con circular progress bar per vedere la memoria utilizzata e libera   |  23h = 7+8+8  |   9.00->11.00 AND <br> 14.00->19.00;  of 22/12/2024 <br> 9.00->11.00 AND <br> 13.00->19.00;  of 23/12/2024 <br> 9.00->11.00 AND <br> 14.00->19.00;  of 24/12/2024  
|  Monitor    | implementazione pagina per monitoraggio di risorse      |  3.15 + 3.30 + 5.30 = 12.15h  |   8.00->11.15 AND <br> 13.30->17.00;  of 26/12/2024 <br>  <br> 13.30->19.00  of 27/12/2024 <br>
|  Multiplex    | ho provato a implementare utilizzando heap ma da ancora sesso problema, crash dopo aggiunta di 2 pin!  inoltre heap risulta utilizzato solo al 50%!!    | 6h |   13.00->19.00 AND <br> 13.30->17.00;  of 26/12/2024 <br> 
|  Multiplex    | risolto errore con static e gestendo add pin in initializepin    | 6.30h |   9.00->11.00 AND <br> 13.30->17.00;  of 28/12/2024 <br> 
|  Multiplex    | risolto errore initializepin  con certi pin da errore perche provo a leggere da risorse che sono utilizzatte per wifi!   | 6.30h |   9.00->11.00 AND <br> 13.30->17.00;  of 29/12/2024 <br> 
|  Multiplex    | DEBUG errore ADC3 - SENSOGuru Meditation Error: Core  1 panic'ed   accade quando compilo ma ho aperto http://192.168.178.144/pinout  perche prova a leggere quando in effetti non ho ancora finito di costruire oggetto!   | 2h |   9.00->11.00  of 28/12/2024  ANCORA DA APPROFONDIRE BENE COME GESTIRE pero siccome e errore che puo accadere solo in fase di boot non e approfondito per ora<br> 
|  Monitor    | GRAFICO stack per ogni singolo thread di registrazione nella pagina monitor!     |  3.15 + 3.30 + 5.30 = 12.15h  |   8.00->11.15 AND <br> 13.30->17.00;  of 26/12/2024 <br>  <br> 13.30->19.00  of 30/12/2024 <br>
|  docs tesi    | creazione documento tesi.tex     |  24h  |      8.00->11.30 AND <br> 13.30->17.300;  of 14/02/2025 <br>  <br> 8.00->11.30 AND <br> 13.30->17.300;  of 15/02/2025 <br>  <br> 8.00->11.30 AND <br> 13.30->17.300;  of 16/02/2025 <br>  <br>8.00->11.30 AND <br> 13.30->17.300;  of 17/02/2025 <br>  <br>
|  docs tesi    | correzione con le modifiche sugerite da Fabio    |  12h  | <br> 13.30->17.30;  of 18/02/2025 <br>  <br> 8.00->11.30 AND <br> 13.30->17.300;  of 19/02/2025 <br>
|  docs tesi    | correzione con le modifiche sugerite da Mirco [link](./Mail_Correzioni_Mirko.pdf) ancora da completare    |  2h  | <br> 8.30->10.30;  of 24/02/2025 <br>  <br> 
|  bugFix presentazione    | debug degli errori che si sono verificati durante la presentazione e fix della maggior parte di essi    |  8h  | <br> 8.30->10.30; AND <br> 13.30->17.30;  of 25/02/2025 <br>  <br> 
|  Edit Pin    | creazione     |  12  | <br> 8.30->11.30; AND <br> 13.30->17.30;  of 26/02/2025 <br>  <br> <br> 10.30->11.30; AND <br> 13.30->16.30;  of 27/02/2025 <br>  <br>
|  Edit Pin    | testing -sono statirilevati bug dovuti ad accesso concorrente delle risorse quando piu pagine attive su /pinout    |  2h  | <br> 8.30->10.30;  of 28/02/2025 <br>  <br> 
|  Edit Pin    | correzione bug accesso concorrente: non acora del tutto fixato ma si pensa di risolvere mettendo mutex in SystemState     |  16h  |  <br> 13.30->17.30;  of 28/02/2025 <br>  <br> <br> 8.30->11.30; AND <br> 13.30->16.30;  of 01/03/2025 <br>  <br> 8.30->11.30; of 02/03/2025<br>  <br> 
|  ADS1115    | creazione sketch ../src/ADS1115     |  6h 30min |  8.30->11.30; AND <br> 13.30->18.30;  of 14/03/2025 <br> 
|  Modbus master view    | fix errore concorrenza che causava crash dispositivo quando piu client connessi     |  8h |  8.30->11.30; AND <br> 13.30->18.30;  of 21/03/2025 
|  Multiser functionality    | organizzazione delle routes tramite pattern decorator per aggiunta e rimozione a run time in base del tipo di utente connesso ancora da comletare tutta la parte relativa alla greazione e gestione dell utente    |  8h |  8.30->11.30; AND <br> 13.30->18.30;  of 21/03/2025 
|  Impostazioni utente    | creazione form per mettere tipo di entrate e uscite da parte dell utente, come richiesto da prof, per ora solo creato html necessito di implementarlo nel progetto    |  8h |  8.30->11.30; AND <br> 13.30->18.30;  of 22/03/2025 
|  Ottimizzazione    | modifica del partizionamento dell esp per dar piu spazio all applicazione, rimozione della funzionalita OTA ora si ha a disposizione 3M per applicativo al posto di 1    |  8h |  8.30->11.30; AND <br> 13.30->18.30;  of 23/03/2025 
|  Ricerca    | linearizzazione delle sonde rtd e delle sonde termo coppie  maggiori info [Qui!](./LINEARIZZAZIONE_SONDE.md)    |  8h |  8.30->11.30; AND <br> 13.30->18.30;  of 24/03/2025 
|  fix errore compatibilita board     |   maggiori info [Qui!](./issues/arduino_espaasynkwebsrv_error.md  )    |  8h |  8.30->11.30; AND <br> 13.30->18.30;  of 25/03/2025 
|  Creazione pagina equivalente a history modbus e pin per ads     |   ha richiesto tempo aggiuntivo a causa di errori legati alla limitata dimensione dei dati trasmissibili dall esp su protocollo http, per aumentare al massimo il numero di dati si e deciso di rimuovere molte parti di css e js dopo estensivi test.    |  16h |   <br> 13.30->18.30;  of 20/06/2025 <br> 13.30->18.30;  of 22/06/2025  <br> 9.30->13.30;  of 22/06/2025  <br> 13.30->18.30;  of 25/06/2025
|  creazione stuttura dati per linearizzazione delle sonde PT100 e PT1000  e integrazione nel progetto   |   tabelle utilizzate [Qui!](./tabelleSonde.pdf  )    |  15h |  8.30->11.30; AND <br> 13.30->18.30;  of 25/03/2025