
#define RX_PIN_SLAVE 32
#define TX_PIN_SLAVE 33
#define DE_PIN_SLAVE 27

void setup() {
  Serial.begin(9600);

  
  // Inizializza i pin come output
  pinMode(RX_PIN_SLAVE, OUTPUT);
  pinMode(TX_PIN_SLAVE, OUTPUT);
  pinMode(DE_PIN_SLAVE, OUTPUT);
}

void loop() {
  // Accende i LED
  Serial.println("Accendo i LED");
  digitalWrite(RX_PIN_SLAVE, HIGH);
  digitalWrite(TX_PIN_SLAVE, HIGH);
  digitalWrite(DE_PIN_SLAVE, HIGH);
  delay(1000); // Attende per 1 secondo

  // Spegne i LED
  Serial.println("Spegno i LED");
  digitalWrite(RX_PIN_SLAVE, LOW);
  digitalWrite(TX_PIN_SLAVE, LOW);
  digitalWrite(DE_PIN_SLAVE, LOW);
  delay(1000); // Attende per 1 secondo
}
