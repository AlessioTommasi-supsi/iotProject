#include "Pin.h"
#include <cstring>

// Costruttore
Pin::Pin(uint8_t num, PinType t, uint8_t input, const char *n, uint16_t volt)
    : number(num), type(t), voltage(volt), isInput(input), recordingTask(NULL)
{
    // Crea il mutex
    mutex = xSemaphoreCreateMutex();
    if (mutex == NULL) {
        Serial.println("Failed to create mutex for Pin " + String(num));
    }
    
    strncpy(note, n, sizeof(note));
    note[sizeof(note) - 1] = '\0';

    if (number != static_cast<uint8_t>(-1))
    {
        pinMode(number, input ? INPUT : OUTPUT);
    }
}

// Distruttore
Pin::~Pin() {
    if (mutex != NULL) {
        vSemaphoreDelete(mutex);
    }
}

// Copy constructor
Pin::Pin(const Pin& other) {
    mutex = xSemaphoreCreateMutex();
    if (mutex == NULL) {
        Serial.println("Failed to create mutex in copy constructor");
    }
    
    if (xSemaphoreTake(other.mutex, portMAX_DELAY) == pdTRUE) {
        number = other.number;
        type = other.type;
        voltage = other.voltage;
        isInput = other.isInput;
        stackSize = other.stackSize;
        timeToRecord = other.timeToRecord;
        valuesVoltage = other.valuesVoltage;
        recordingTask = other.recordingTask;
        strncpy(note, other.note, sizeof(note));
        note[sizeof(note) - 1] = '\0';
        xSemaphoreGive(other.mutex);
    }
}

// Assignment operator
Pin& Pin::operator=(const Pin& other) {
    if (this != &other) {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE && 
            xSemaphoreTake(other.mutex, portMAX_DELAY) == pdTRUE) {
            number = other.number;
            type = other.type;
            voltage = other.voltage;
            isInput = other.isInput;
            stackSize = other.stackSize;
            timeToRecord = other.timeToRecord;
            valuesVoltage = other.valuesVoltage;
            recordingTask = other.recordingTask;
            strncpy(note, other.note, sizeof(note));
            note[sizeof(note) - 1] = '\0';
            xSemaphoreGive(other.mutex);
            xSemaphoreGive(mutex);
        }
    }
    return *this;
}

// Equality operator
bool Pin::operator==(const Pin& other) const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE && 
        xSemaphoreTake(other.mutex, portMAX_DELAY) == pdTRUE) {
        bool result = (number == other.number);
        xSemaphoreGive(other.mutex);
        xSemaphoreGive(mutex);
        return result;
    }
    return false;
}

// Getter e Setter thread-safe
uint8_t Pin::getNumber() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        uint8_t result = number;
        xSemaphoreGive(mutex);
        return result;
    }
    return 0;
}

void Pin::setNumber(uint8_t num) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        number = num;
        xSemaphoreGive(mutex);
    }
}

PinType Pin::getPinType() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        PinType result = type;
        xSemaphoreGive(mutex);
        return result;
    }
    return PinType::UNKNOWN;
}

void Pin::setPinType(PinType t) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        type = t;
        xSemaphoreGive(mutex);
    }
}

uint16_t Pin::getVoltage() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        uint16_t result = voltage;
        xSemaphoreGive(mutex);
        return result;
    }
    return 0;
}

void Pin::setVoltage(uint16_t volt) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        voltage = volt;
        xSemaphoreGive(mutex);
    }
}

bool Pin::getIsInput() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        bool result = isInput;
        xSemaphoreGive(mutex);
        return result;
    }
    return true;
}

void Pin::setIsInput(bool input) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        isInput = input;
        xSemaphoreGive(mutex);
    }
}

void Pin::getNote(char* buffer, size_t bufferSize) const {
    if (buffer && bufferSize > 0 && xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        strncpy(buffer, note, bufferSize);
        buffer[bufferSize - 1] = '\0';
        xSemaphoreGive(mutex);
    }
}

void Pin::setNote(const char *newNote) {
    if (newNote && xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        strncpy(note, newNote, sizeof(note));
        note[sizeof(note) - 1] = '\0';
        xSemaphoreGive(mutex);
    }
}

size_t Pin::getStackSize() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        size_t result = stackSize;
        xSemaphoreGive(mutex);
        return result;
    }
    return 10000;
}

void Pin::setStackSize(size_t size) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        stackSize = size;
        xSemaphoreGive(mutex);
    }
}

size_t Pin::getTimeToRecord() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        size_t result = timeToRecord;
        xSemaphoreGive(mutex);
        return result;
    }
    return 1000;
}

void Pin::setTimeToRecord(size_t time) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        timeToRecord = time;
        xSemaphoreGive(mutex);
    }
}

TaskHandle_t Pin::getRecordingTask() const {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        TaskHandle_t result = recordingTask;
        xSemaphoreGive(mutex);
        return result;
    }
    return NULL;
}

// Imposta la modalità del pin
void Pin::setMode(uint8_t mode)
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        isInput = mode == INPUT;
        if (number != static_cast<uint8_t>(-1))
        {
            pinMode(number, mode);
        }
        xSemaphoreGive(mutex);
    }
}

// Scrive sul pin
bool Pin::write(bool goHigh)
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        isInput = false;
        voltage = goHigh ? 3300 : 0;
        if (number != static_cast<uint8_t>(-1)) {
            pinMode(number, OUTPUT);
            digitalWrite(number, goHigh ? HIGH : LOW);
        }
        xSemaphoreGive(mutex);
        return true;
    }
    return false;
}

void Pin::setType(String type)
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        this->type = StringToPinType(type);
        xSemaphoreGive(mutex);
    }
}

String Pin::getType() const
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        String result = pinTypeToString(this->type);
        xSemaphoreGive(mutex);
        return result;
    }
    return "UNKNOWN";
}

// Conversione tipo pin in stringa
String Pin::pinTypeToString(PinType type)
{
    switch (type)
    {
    case PinType::ANALOGIC:
        return "ANALOGIC";
    case PinType::DIGITAL:
        return "DIGITAL";
    case PinType::VIN:
        return "VIN";
    case PinType::VOUT:
        return "VOUT";
    case PinType::GND:
        return "GND";
    case PinType::EN:
        return "EN";
    case PinType::ADC:
        return "ADC";
    case PinType::DAC:
        return "DAC";
    case PinType::PWM:
        return "PWM";
    case PinType::TOUCH:
        return "TOUCH";
    case PinType::UART:
        return "UART";
    case PinType::SPI:
        return "SPI";
    case PinType::I2C:
        return "I2C";
    default:
        return "UNKNOWN";
    }
}

// Conversione stringa in tipo pin
PinType Pin::StringToPinType(String type)
{
    if (type == "ANALOGIC")
        return PinType::ANALOGIC;
    if (type == "DIGITAL")
        return PinType::DIGITAL;
    if (type == "VIN")
        return PinType::VIN;
    if (type == "VOUT")
        return PinType::VOUT;
    if (type == "GND")
        return PinType::GND;
    if (type == "EN")
        return PinType::EN;
    if (type == "ADC")
        return PinType::ADC;
    if (type == "DAC")
        return PinType::DAC;
    if (type == "PWM")
        return PinType::PWM;
    if (type == "TOUCH")
        return PinType::TOUCH;
    if (type == "UART")
        return PinType::UART;
    if (type == "SPI")
        return PinType::SPI;
    if (type == "I2C")
        return PinType::I2C;
    return PinType::UNKNOWN;
}

// Legge il valore del pin
uint16_t Pin::read()
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        uint16_t result = voltage;
        if (isInput)
        {
            result = (type == PinType::ANALOGIC) ? analogRead(number) * (3300.0 / 4095.0)
                                                 : digitalRead(number) * 1000;
        }
        voltage = result;
        xSemaphoreGive(mutex);
        return result;
    }
    return 0;
}

// Funzione per registrare valori dal pin
void Pin::recordingFunction()
{
    const size_t MAX_VALUES = 100; // Limite massimo valori per evitare overflow
    unsigned long lastCleanup = millis();
    const unsigned long CLEANUP_INTERVAL = 30000; // Pulizia ogni 30 secondi
    
    try {
        while (true) {
            // Verifica heap ogni ciclo
            size_t freeHeap = ESP.getFreeHeap();
            if (freeHeap < 4096) { // Se heap < 4KB, ferma recording
                Serial.println("WARNING: Low memory, stopping recording for pin " + String(number));
                break;
            }
            
            uint16_t value = read();
            Serial.println("Recording value for pin " + String(number) + ": " + String(value));
            
            if (xSemaphoreTake(mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
                // Limita il numero di valori per evitare overflow
                if (valuesVoltage.size() >= MAX_VALUES) {
                    valuesVoltage.erase(valuesVoltage.begin(), valuesVoltage.begin() + 10); // Rimuovi i primi 10
                }
                
                valuesVoltage.push_back(value);
                xSemaphoreGive(mutex);
                
                // Pulizia periodica per liberare memoria
                unsigned long currentTime = millis();
                if (currentTime - lastCleanup > CLEANUP_INTERVAL) {
                    if (valuesVoltage.size() > 50) {
                        valuesVoltage.erase(valuesVoltage.begin(), valuesVoltage.begin() + 25);
                    }
                    lastCleanup = currentTime;
                }
            }
            
            // Usa vTaskDelay invece di delay per task FreeRTOS
            vTaskDelay(pdMS_TO_TICKS(timeToRecord));
        }
    } catch (...) {
        Serial.println("Exception in recording function for pin " + String(number));
    }
    
    // Auto-cleanup del task
    if (xSemaphoreTake(mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
        recordingTask = NULL;
        xSemaphoreGive(mutex);
    }
    
    vTaskDelete(NULL); // Termina se stesso
}

// Inizia la registrazione con protezioni anti-crash
void Pin::startRecording(int milliseconds)
{
    // Controlli preliminari per prevenire crash
    if (milliseconds < 500) {
        milliseconds = 500; // Minimo 500ms per evitare sovraccarico
    }
    
    // Verifica heap disponibile
    size_t freeHeap = ESP.getFreeHeap();
    if (freeHeap < 8192) { // Minimo 8KB liberi
        Serial.println("ERROR: Heap insufficiente per recording pin " + String(number) + ". Free: " + String(freeHeap));
        return;
    }
    
    if (xSemaphoreTake(mutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
        // Se c'è già un task attivo, fermalo prima
        if (recordingTask != NULL) {
            Serial.println("Stopping existing recording task for pin " + String(number));
            vTaskDelete(recordingTask);
            recordingTask = NULL;
            vTaskDelay(pdMS_TO_TICKS(100)); // Aspetta che il task sia completamente terminato
        }
        
        timeToRecord = milliseconds;
        
        // Riduce lo stack size per ESP32 Core 3.0.7
        size_t taskStackSize = 2048; // Ridotto da 4096 per risparmiare memoria
        
        // Crea il task con priorità bassa e core specifico
        BaseType_t result = xTaskCreatePinnedToCore(
            [](void *parameter) {
                Pin *pin = static_cast<Pin *>(parameter);
                pin->recordingFunction();
            },
            ("PinRec" + String(number)).c_str(), // Nome task più corto
            taskStackSize,
            this,
            1, // Priorità bassa
            &recordingTask,
            0  // Core 0 per bilanciare il carico
        );
        
        if (result != pdPASS) {
            Serial.println("ERROR: Failed to create recording task for pin " + String(number));
            recordingTask = NULL;
        } else {
            Serial.println("Recording started for pin " + String(number) + " (interval: " + String(milliseconds) + "ms)");
        }
        
        xSemaphoreGive(mutex);
    } else {
        Serial.println("ERROR: Cannot acquire mutex for pin " + String(number));
    }
}

// Ferma la registrazione con pulizia sicura
void Pin::stopRecording()
{
    if (xSemaphoreTake(mutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
        if (recordingTask != NULL) {
            Serial.println("Stopping recording for pin " + String(number));
            
            // Termina il task in modo sicuro
            vTaskDelete(recordingTask);
            recordingTask = NULL;
            
            // Aspetta che il task sia completamente terminato
            vTaskDelay(pdMS_TO_TICKS(100));
            
            Serial.println("Recording stopped for pin " + String(number));
        }
        xSemaphoreGive(mutex);
    } else {
        Serial.println("ERROR: Cannot acquire mutex to stop recording for pin " + String(number));
    }
}

// Ottiene i valori registrati
std::vector<float> Pin::getValuesVoltage()
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        std::vector<float> copyValues(valuesVoltage.begin(), valuesVoltage.end());
        xSemaphoreGive(mutex);
        return copyValues;
    }
    return std::vector<float>();
}

// Dimensione stack usato
size_t Pin::getUsedStackInWords()
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        size_t size = valuesVoltage.size() * sizeof(valuesVoltage[0]) / 4;
        xSemaphoreGive(mutex);
        return size;
    }
    return 0;
}

// Dimensione stack totale
size_t Pin::getStackSizeInWords()
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        size_t result = stackSize;
        xSemaphoreGive(mutex);
        return result;
    }
    return 10000;
}

// Ritorna descrizione del pin
String Pin::toString() const
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        String result = "Pin number: " + String(number) +
                        ", Type: " + pinTypeToString(type) +
                        ", Voltage: " + String(voltage / 1000.0, 3) + " V" +
                        ", Input: " + (isInput ? "Yes" : "No") +
                        ", Note: " + String(note);
        xSemaphoreGive(mutex);
        return result;
    }
    return "Pin access error";
}

// Add methods for editing and deleting values with locks
void Pin::editValue(int index, float value)
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        if (index >= 0 && index < valuesVoltage.size())
        {
            valuesVoltage[index] = value;
        }
        xSemaphoreGive(mutex);
    }
}

void Pin::deleteValue(int index)
{
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        if (index >= 0 && index < valuesVoltage.size())
        {
            valuesVoltage.erase(valuesVoltage.begin() + index);
        }
        xSemaphoreGive(mutex);
    }
}
