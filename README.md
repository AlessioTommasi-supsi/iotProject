# iotProject
iotProject developed in SUPSI Master in Computer Science course IoT, focusing on ESP32, ESAM, and Modbus Protocol.

### Dependency:
If you are on a Windows environment, install `iotProject/driver/CP210x_Universal_Windows_Driver`.

### SETUP ARDUINO IDE:

To compile the files in the subfolders, you need to add them as libraries (i.e., .zip files) to the Arduino IDE.
I have specifically created a library folder to place/replace the zip files;
For proper compilation, you need to import all the zip folders in /Library:


Da bpard manager assicuratu di avere installato la seguente versione delle board: esp32 by Espressif Systems 3.0.7 le versioni successive danno problemi con libreria webserver vedi dettagli nella cartella issues!

versione di arduino ide da utilizzare: 2.3.4



![alt text](image/Library.png)

### Electrical Schematic:

![alt text](image/schema_elettrico.jpeg)

### UML Diagram:

![alt text](image/uml.png)

## State Machine: 
![alt text](image/state_machine.png)



## Elettrical schematization of semester project:
![alt text](docs/EsamElettric.jpg)


## Dispositivo utilizzato in fase di sviluppo:
![alt text](image/ESP32-DOIT-DEV-KIT-v1-pinout-mischianti.png)

## Pinout proposti per slave Modbus

file che si e utilizzato per testare slave: [Qui](src/SLAVE_EXAMPLE/modbusSlave2/modbusSlave2.ino)


![alt text](image/SlavePinout.png)


Secondo me non funzionantew perche ho devkit V1 e non altri tipi di ESP!


## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0). You are free to use, share, and adapt the work for non-commercial purposes, provided that you give appropriate credit to the original author(s) and do not use the material for commercial purposes.

Full license text: [Creative Commons CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/)

