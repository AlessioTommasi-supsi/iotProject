#ifndef PINTYPE_H
#define PINTYPE_H

enum class PinType {
    ANALOGIC, // Pin per segnali analogici generici
    DIGITAL,  // Pin per segnali digitali generici (HIGH/LOW)
    VIN,      // Ingresso di alimentazione
    VOUT,     // Uscita di alimentazione
    GND,      // Massa (ground)
    EN,       // Enable, tipicamente usato per attivare o disattivare parti del circuito
    ADC,      // Analog-to-Digital Converter, converte segnali analogici in digitali
    DAC,      // Digital-to-Analog Converter, converte segnali digitali in analogici
    PWM,      // Pulse Width Modulation, usato per generare segnali PWM
    TOUCH,    // Pin capacitivo per rilevamento del tocco
    UART,     // Universal Asynchronous Receiver-Transmitter, comunicazione seriale asincrona
    SPI,      // Serial Peripheral Interface, protocollo di comunicazione seriale sincrona
    I2C,      // Inter-Integrated Circuit, protocollo di comunicazione seriale sincrona per corto raggio
    UNKNOWN,   // Tipo di pin sconosciuto


    SIZE      // restituisce la dimensione dell'enum deve essere sempre l'ultimo elemento
};

#endif // PINTYPE_H
