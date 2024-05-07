# iotProject
iotProject developed in SUPSI Master in Computer science course iot, focus on esp32.
 cioao

### Dependency:
###Prof docs:
https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/establish-serial-connection.html

### VS code extension:
->ESPRESSIFF e estenzione NON HO FINITO DOWNLOAD!
https://www.phippselectronics.com/run-your-first-esp32-program-in-visual-studio-code/


PLATFORM IO:
https://www.youtube.com/watch?v=5edPOlQQKmo

si consiglia di usare windows poiche estensione modbus a pagamento su MacOs!



SETUP ARDUINO IDE:
https://www.youtube.com/watch?v=UuuqnmJIjR0

-> per poter compilare i file nelle sottocartelle devi aggiungerle cone librerie (quindi .zip) all arduino 
    ho creato appositamente cartella library da mettere / sostituire i file zip;
    poi vai su arduino:  Sketch -> include Library e seleziona il file zip -> magari in futuro faccio uno script che automaticamente fa update delle librerie!

NOTA: NON FUNZIONA SEPARAZIONE .H DA .CPP IN QUESTO CASO FAI UN UNICO FILE! PER EVITARE PROBLEMI DI DIPENDENZA CIRCOLARE IMPORTA EMPRE FIGLIO PIU IN BASSO DELLA GERARCHIA!rfaccia c


try to follow to setup webserver: 
https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
