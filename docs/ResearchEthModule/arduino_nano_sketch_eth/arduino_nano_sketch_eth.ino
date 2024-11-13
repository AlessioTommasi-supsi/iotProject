#include <UIPEthernet.h>  // Libreria per ENC28J60

// Imposta il MAC address unico per il modulo Ethernet (puoi modificarlo)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Indirizzo IP statico (modifica in base alla tua rete)
IPAddress ip(192, 168, 178, 124);

// Porta del server web
EthernetServer server(80);

void setup() {
  Serial.begin(9600);

  // Inizializza Ethernet con IP statico
  Ethernet.begin(mac, ip);
  delay(1000);  // Attendi per la connessione

  // Avvia il server
  server.begin();
  Serial.print("Server avviato. Vai su http://");
  Serial.print(ip);
  Serial.println(" per accedere.");
}

void loop() {
  // Attendi client in arrivo
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Client connesso");
    // Invia una risposta al client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>Modulo ENC28J60 - Server Web Arduino Nano</h1>");
    client.println("<p>Funziona!</p>");
    client.println("</html>");

    delay(1); // Attendi per inviare i dati
    client.stop(); // Chiudi la connessione
    Serial.println("Client disconnesso");
  }
}
