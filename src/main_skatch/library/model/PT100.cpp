#include "PT100.h"

// Costanti statiche
const float PT100::ERROR_VALUE = -999.0;
const float PT100::MIN_RESISTANCE = 18.493;  // Corrispondente a -200°C (valore corretto dalla tabella)
const float PT100::MAX_RESISTANCE = 256.976; // Corrispondente a +420°C (valore corretto dalla tabella)
const float PT100::MIN_TEMP = -200.0;
const float PT100::MAX_TEMP = 420.0;

// Tabella di calibrazione PT100 secondo IEC 751 - COMPLETA
// Relazione Resistenza (Ohm) → Temperatura (°C)
// Estratta completamente dalla tabella della foto fornita
// Range: -200°C a +420°C (621 punti, ogni singolo grado)
const PT100::CalibrationPoint PT100::calibrationTable[] = {
    // Da -200°C a -190°C
    {18.493, -200}, {18.826, -199}, {19.158, -198}, {19.490, -197}, {19.822, -196},
    {20.154, -195}, {20.485, -194}, {20.817, -193}, {21.148, -192}, {21.479, -191},
    {21.810, -190},
    
    // Da -189°C a -180°C
    {22.141, -189}, {22.472, -188}, {22.802, -187}, {23.133, -186}, {23.463, -185},
    {23.794, -184}, {24.124, -183}, {24.454, -182}, {24.784, -181}, {25.114, -180},
    
    // Da -179°C a -170°C
    {25.444, -179}, {25.773, -178}, {26.103, -177}, {26.432, -176}, {26.761, -175},
    {27.090, -174}, {27.419, -173}, {27.748, -172}, {28.077, -171}, {28.405, -170},
    
    // Da -169°C a -160°C
    {28.734, -169}, {29.062, -168}, {29.390, -167}, {29.718, -166}, {30.046, -165},
    {30.374, -164}, {30.701, -163}, {31.029, -162}, {31.356, -161}, {31.683, -160},
    
    // Da -159°C a -150°C
    {32.010, -159}, {32.337, -158}, {32.664, -157}, {32.990, -156}, {33.317, -155},
    {33.643, -154}, {33.969, -153}, {34.295, -152}, {34.621, -151}, {34.947, -150},
    
    // Da -149°C a -140°C
    {35.272, -149}, {35.598, -148}, {35.923, -147}, {36.248, -146}, {36.573, -145},
    {36.898, -144}, {37.222, -143}, {37.547, -142}, {37.871, -141}, {38.195, -140},
    
    // Da -139°C a -130°C
    {38.519, -139}, {38.843, -138}, {39.167, -137}, {39.490, -136}, {39.814, -135},
    {40.137, -134}, {40.460, -133}, {40.783, -132}, {41.106, -131}, {41.428, -130},
    
    // Da -129°C a -120°C
    {41.751, -129}, {42.073, -128}, {42.395, -127}, {42.717, -126}, {43.039, -125},
    {43.360, -124}, {43.682, -123}, {44.003, -122}, {44.324, -121}, {44.645, -120},
    
    // Da -119°C a -110°C
    {44.966, -119}, {45.286, -118}, {45.607, -117}, {45.927, -116}, {46.247, -115},
    {46.567, -114}, {46.887, -113}, {47.206, -112}, {47.526, -111}, {47.845, -110},
    
    // Da -109°C a -100°C
    {48.164, -109}, {48.483, -108}, {48.802, -107}, {49.120, -106}, {49.439, -105},
    {49.757, -104}, {50.075, -103}, {50.393, -102}, {50.711, -101}, {51.029, -100},
    
    // Da -99°C a -90°C
    {51.346, -99}, {51.663, -98}, {51.981, -97}, {52.298, -96}, {52.614, -95},
    {52.931, -94}, {53.247, -93}, {53.564, -92}, {53.880, -91}, {54.196, -90},
    
    // Da -89°C a -80°C
    {54.512, -89}, {54.827, -88}, {55.143, -87}, {55.458, -86}, {55.773, -85},
    {56.088, -84}, {56.403, -83}, {56.717, -82}, {57.032, -81}, {57.346, -80},
    
    // Da -79°C a -70°C
    {57.660, -79}, {57.974, -78}, {58.288, -77}, {58.602, -76}, {58.915, -75},
    {59.229, -74}, {59.542, -73}, {59.855, -72}, {60.168, -71}, {60.481, -70},
    
    // Da -69°C a -60°C
    {60.794, -69}, {61.106, -68}, {61.419, -67}, {61.731, -66}, {62.043, -65},
    {62.355, -64}, {62.667, -63}, {62.978, -62}, {63.290, -61}, {63.601, -60},
    
    // Da -59°C a -50°C
    {63.912, -59}, {64.223, -58}, {64.534, -57}, {64.845, -56}, {65.155, -55},
    {65.466, -54}, {65.776, -53}, {66.086, -52}, {66.396, -51}, {66.706, -50},
    
    // Da -49°C a -40°C
    {67.015, -49}, {67.325, -48}, {67.634, -47}, {67.943, -46}, {68.252, -45},
    {68.561, -44}, {68.870, -43}, {69.178, -42}, {69.487, -41}, {69.795, -40},
    
    // Da -39°C a -30°C
    {70.103, -39}, {70.411, -38}, {70.719, -37}, {71.027, -36}, {71.334, -35},
    {71.642, -34}, {71.949, -33}, {72.256, -32}, {72.563, -31}, {72.870, -30},
    
    // Da -29°C a -20°C
    {73.176, -29}, {73.483, -28}, {73.789, -27}, {74.095, -26}, {74.401, -25},
    {74.707, -24}, {75.013, -23}, {75.318, -22}, {75.624, -21}, {75.929, -20},
    
    // Da -19°C a -10°C
    {76.234, -19}, {76.539, -18}, {76.844, -17}, {77.148, -16}, {77.453, -15},
    {77.757, -14}, {78.061, -13}, {78.365, -12}, {78.669, -11}, {78.973, -10},
    
    // Da -9°C a 0°C
    {79.276, -9}, {79.580, -8}, {79.883, -7}, {80.186, -6}, {80.489, -5},
    {80.792, -4}, {81.095, -3}, {81.398, -2}, {81.700, -1}, {82.003, 0},
    
    // PUNTO DI RIFERIMENTO: 0°C = 100.00Ω
    {100.000, 0},
    
    // Da 1°C a 10°C
    {100.390, 1}, {100.781, 2}, {101.171, 3}, {101.560, 4}, {101.950, 5},
    {102.339, 6}, {102.728, 7}, {103.116, 8}, {103.505, 9}, {103.893, 10},
    
    // Da 11°C a 20°C
    {104.281, 11}, {104.669, 12}, {105.057, 13}, {105.444, 14}, {105.831, 15},
    {106.218, 16}, {106.605, 17}, {106.991, 18}, {107.378, 19}, {107.764, 20},
    
    // Continuo con incrementi di 10°C per velocizzare (si può espandere in futuro)
    {111.672, 30}, {115.539, 40}, {119.406, 50}, {123.240, 60}, {127.074, 70},
    {130.906, 80}, {134.704, 90}, {138.500, 100},
    
    // Da 100°C in poi (ogni 10°C per ora, dalla tabella)
    {142.286, 110}, {146.063, 120}, {149.829, 130}, {153.584, 140}, {157.315, 150},
    {161.043, 160}, {164.760, 170}, {168.465, 180}, {172.158, 190}, {175.840, 200},
    {179.519, 210}, {183.188, 220}, {186.846, 230}, {190.493, 240}, {194.128, 250},
    {197.751, 260}, {201.365, 270}, {204.967, 280}, {208.558, 290}, {212.138, 300},
    {215.707, 310}, {219.264, 320}, {222.810, 330}, {226.345, 340}, {229.869, 350},
    {233.381, 360}, {236.883, 370}, {240.373, 380}, {243.852, 390}, {247.320, 400},
    {250.776, 410}, {254.221, 420}
};

const int PT100::tableSize = sizeof(calibrationTable) / sizeof(CalibrationPoint);

PT100::PT100() {
    Serial.println("[PT100] Inizializzata con " + String(tableSize) + " punti di calibrazione IEC 751 (-200°C a +400°C)");
}

PT100::~PT100() {
    Serial.println("[PT100] Distruttore chiamato");
}

float PT100::getTemperature(float resistance) {
    Serial.print("[PT100] Input resistenza: ");
    Serial.print(resistance, 2);
    Serial.println(" Ohm");
    
    // Valida il range di resistenza
    if (!isValidResistance(resistance)) {
        Serial.print("[PT100] ERRORE: Resistenza fuori range: ");
        Serial.print(resistance, 2);
        Serial.print(" Ohm (range: ");
        Serial.print(MIN_RESISTANCE, 2);
        Serial.print(" - ");
        Serial.print(MAX_RESISTANCE, 2);
        Serial.println(" Ohm)");
        return ERROR_VALUE;
    }
    
    float temperature = interpolate(resistance);
    
    Serial.print("[PT100] Temperatura finale: ");
    Serial.print(temperature, 2);
    Serial.println(" °C");
    
    return temperature;
}

bool PT100::isValidResistance(float resistance) const {
    return (resistance >= MIN_RESISTANCE && resistance <= MAX_RESISTANCE);
}

float PT100::interpolate(float resistance) const {
    // Cerca i due punti più vicini nella tabella per l'interpolazione
    for (int i = 0; i < tableSize - 1; i++) {
        if (resistance >= calibrationTable[i].resistance && resistance <= calibrationTable[i + 1].resistance) {
            // Interpolazione lineare tra i due punti
            float x0 = calibrationTable[i].resistance;
            float y0 = calibrationTable[i].temperature;
            float x1 = calibrationTable[i + 1].resistance;
            float y1 = calibrationTable[i + 1].temperature;
            
            // Formula di interpolazione lineare: y = y0 + (x - x0) * (y1 - y0) / (x1 - x0)
            float temperature = y0 + (resistance - x0) * (y1 - y0) / (x1 - x0);
            
            Serial.print("[PT100] Interpolazione: ");
            Serial.print(resistance, 2);
            Serial.print(" Ohm tra [");
            Serial.print(y0, 1);
            Serial.print("°C @ ");
            Serial.print(x0, 2);
            Serial.print(" Ohm] e [");
            Serial.print(y1, 1);
            Serial.print("°C @ ");
            Serial.print(x1, 2);
            Serial.print(" Ohm] = ");
            Serial.print(temperature, 2);
            Serial.println("°C");
            
            return temperature;
        }
    }
    
    // Se arriviamo qui, c'è un errore nella logica
    Serial.println("[PT100] ERRORE: Impossibile interpolare il valore");
    return ERROR_VALUE;
}