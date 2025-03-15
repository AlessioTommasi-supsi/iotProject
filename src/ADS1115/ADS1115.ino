/******************************************************
 *
 *
 * GUIDA UTILIZZATA:
 * https://how2electronics.com/how-to-use-ads1115-16-bit-adc-module-with-esp32/
 *
 * LIBRERIE NECESSARIE PER IL CORRETTO FUNZIONAMENTO:
 * https://github.com/adafruit/Adafruit_ADS1X15
 *
 *
 * FUNZIONAMENTO
 * scrivendo da 1 a 7 su seriale si seleziona il canale del multiplexer e si legge da ADS1115
 * titti i canali  AIN0 - AIN3
 * 8 per tornare alla modalità default (tutti i canali) lettura di AIN0 - AIN3
 *******************************************************/

#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
// Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

// Definizione dei pin del multiplexer (collegati all'ESP32)
#define PIN_A 12
#define PIN_B 13
#define PIN_C 14

// Variabile per tenere traccia del canale multiplexer selezionato
// -1 indica lo stato default (modalità "tutti" / default)
int selectedMuxChannel = -1;

// Funzione per impostare i pin del multiplexer in base al canale selezionato
void setMultiplexerChannel(int channel)
{
  switch (channel)
  {
  case 0:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
    break;
  case 1:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
    break;
  case 2:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
    break;
  case 3:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
    break;
  case 4:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
    break;
  case 5:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
    break;
  case 6:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
    break;
  case 7:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
    break;
  default:
    break;
  }
}


void setup(void)
{
  Serial.begin(115200);

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
    while (1)
      ;
  }

  // Configura i pin del multiplexer come output
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);

  

  Serial.println("Sistema pronto.");
  Serial.println("Lettura continua dell'ADS1115 (AIN0 - AIN3) in corso...");
  Serial.println("Per impostare un canale del multiplexer invia:");
  Serial.println("  0-7  => per selezionare il canale specifico (CD405xB).");
  Serial.println("  8    => per tornare al default lettura da tutti i canali.");
}

void printReadFromADS1115(int channel)
{
  int16_t adc;
  float volts;

  adc = ads.readADC_SingleEnded(channel);
  volts = ads.computeVolts(adc);
  Serial.println("");
  Serial.print("AIN");Serial.print(channel);Serial.print(": ");  Serial.print(adc);  Serial.print("  "); Serial.print(volts); Serial.println("V");
  
}

void printAllReadingsFromADS1115()
{
  Serial.println("-------------------------------------------------");
  for (int i = 0; i < 4; i++)
  {
    printReadFromADS1115(i);
  }
  Serial.println("-------------------------------------------------");
}

void loop(void)
{
  
  
  //Controllo se ci sono selezioni del canale di input da seriale
  if (Serial.available()>0)
  {
    String input = Serial.readStringUntil('\n'); // Legge finché non incontra un newline
    input.trim();  // Rimuove spazi e caratteri di newline residui
    int channel = input.toInt();
    if (channel >= 0 && channel <= 7)
    {
      selectedMuxChannel = channel;
      setMultiplexerChannel(selectedMuxChannel);
      Serial.print("Canale selezionato: ");
      Serial.print(selectedMuxChannel);
      Serial.println(" ");
    }
    else if (channel == 8)
    {
      selectedMuxChannel = -1;
      Serial.println("Tutti i canali selezionati.");
    }
    else
    {
      Serial.println("Canale non valido.");
    }
    
    //stampo nuovi sse da seriale ho ricevuto qualcosa
    if(selectedMuxChannel == -1)
    {
      for (size_t i = 0; i < 8; i++)
      {
        Serial.println("Canale: ");Serial.print(i);Serial.println(" ");
        setMultiplexerChannel(i);
        printAllReadingsFromADS1115();
        //delay(1000);
      }
    }else{
      setMultiplexerChannel(selectedMuxChannel);
      printAllReadingsFromADS1115();
    }
  }

  //controllo ogni secondo che sia arrivato qualcosa di nuovo da seriale
  delay(1000);
}
