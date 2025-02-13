/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(13,INPUT);

  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta
  }
  Serial.println("Inizializzazione porta seriale effettuata!");
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, HIGH);  // ch3 = 1 1 0 
  digitalWrite(13, HIGH);  //corrisponde a s0 gpio 35s1 gpio 36 e s2 gpio 39
  digitalWrite(14, LOW);  // turn the LED on (HIGH is the voltage level)
  
  
  Serial.println("on!");
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("off!");
  delay(1000);                      // wait for a second
}
