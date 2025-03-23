# Requisiti Minimi della TESI

Di seguito l'elenco delle funzionalità che il sistema deve implementare:

1. **Acquisizione dei segnali analogici**
   - Tensione
   - Corrente
   - Resistenza
   - Termocoppia
   - Pt100

2. **Impostazione dei parametri da parte dell'utente**
   - **Ingresso in Tensione:**
     - Inizio scala
     - Fondo scala
   - **Ingresso in Corrente:**
     - Inizio scala
     - Fondo scala
   - **Ingresso in Termocoppia:**
     - Selezione del tipo di termocoppia
   - **Ingresso RTD (es. Pt100):**
     - Selezione del tipo di termo resistenza

3. **Lettura delle grandezze tramite Modbus RTU**
   - Il sistema deve essere in grado di leggere ogni grandezza acquisita utilizzando il protocollo Modbus RTU.

4. **Interrogazione di dispositivi tramite Modbus RTU**
   - Funzionalità come Modbus RTU master per interrogare un altro dispositivo.
   - Rilettura dei parametri tramite:
     - Interfaccia web
     - Comunicazione seriale in modalità Modbus RTU slave

5. **Gestione delle uscite analogiche**
   - Ogni uscita analogica deve poter essere associata a uno degli ingressi analogici.
   - Esempio: Mappare un ingresso 0–10V a una uscita analogica 0–10V.
   - Prevedere tutte le opzioni configurabili per la gestione delle uscite.

6. **Gestione delle uscite digitali**
   - Ogni uscita digitale può essere associata a ingressi analogici o digitali.
     - **Ingresso Digitale:**
       - Funzionalità applicata "se ingresso attivo allora uscita attiva".
     - **Ingresso Analogico:**
       - Configurare l’uscita digitale come una sorta di allarme.
       - Esempio: 
         - L'utente imposta una soglia di allarme (minima o massima) per un ingresso analogico, ad esempio:
           - Lettura di una corrente 0–20 mA.
           - Impostazione di una soglia massima a 10 mA.
         - Quando il valore dell'ingresso supera i 10 mA, l'uscita corrispondente viene attivata (chiusa).

7. **Documentazione del Software**
   - Redazione di un documento di sintesi che spieghi il funzionamento dell'intero software.
   - Il codice dovrà essere opportunamente commentato per facilitare la comprensione.

8. **Verifica delle funzionalità**
   - Esecuzione di step di verifica per controllare tutte le funzionalità implementate.
   - Spiegazione dettagliata del software da presentare prima della sessione d’esame.

9. **Plus: Implementazione Ethernet**
   - Aggiungere il supporto per il protocollo Modbus TCP/IP.


---

## Da chiarire con il Professore:

-  **Mobus master**: cosa ce che non funzionava, ultima volta che ci siamo sentiti aveva accennato ad un errore nella gestione degli interi

- **Impostazione Parametri**: come devono essere impostati i parametri pagina web??

- **Lettura delle grandezze tramite Modbus RTU**: interia questo dovrebbeessere gia in gradodi farlo tramite /modbusMaster
    -   NEED TO FIX accesso concorrente come fatto per PINOUT.

- **Documentazione del Software**: Sara presente il file UML.mdj per architettura in generale poi pensavo di commentare tutti i file.h come fatto per il file a questo link: [ADS1115](../src/ADS1115/ADS1115.ino) chedi se va bene o se si necessitano di ulteriori documentazioni.

- **test**: come si svolgeranno i test? ho visto ADUnit test ma andrebbero ad appesantire ulteriormente il programma.

- **Gestione delle uscite analogiche**: Ho capito bene: io ho un segnle in ingresso e lo voglio REPLICARE via SW sulle uscite digitali?  cosa si intene per opzioni configurabili per la gestione delle uscite

- **Gestione delle uscite Digitali**:
o piu probabile: attiva nel senzo che ci collegereo un led o un buzzer cosi vedo se il segnale è arrivto a esp o lancio erroriin base a quelli definiti da utente.




    /*
    TEST AD 
    3.3V  su cn2  dal pin 1.2 
    macchina a stati e leggere valore che restituisce AD
    prima con macchina a stati staccata.

    -Multipl

    MACCHINA A STATI

    interroga con un dalay ogni canale dopo delay secondi

    ONLINE
    */

    













Tutti i canali selezionati.
Canale: 
0 
-------------------------------------------------

AIN0: -16  -0.00V

AIN1: 5700  1.07V

AIN2: 5712  1.07V

AIN3: 5710  1.07V
-------------------------------------------------
Canale: 
1 
-------------------------------------------------

AIN0: 13358  2.50V

AIN1: 5712  1.07V

AIN2: 5692  1.07V

AIN3: 5697  1.07V
-------------------------------------------------
Canale: 
2 
-------------------------------------------------

AIN0: -2946  -0.55V

AIN1: -2846  -0.53V

AIN2: -2645  -0.50V

AIN3: -2645  -0.50V
-------------------------------------------------
Canale: 
3 
-------------------------------------------------

AIN0: 7840  1.47V

AIN1: 5666  1.06V
