#include <WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// =======================
// WIFI
// =======================

const char* ssid = "TU_INTERNET";
const char* password = "TU_CONTRASEÑA";

// =======================
// THINGSPEAK
// =======================

unsigned long channelID = TU_CHANNEL_ID;
const char* writeAPIKey = "TU_API_KEY";

WiFiClient client;

// =======================
// ADS1115
// =======================

Adafruit_ADS1115 ads;

// =======================
// CONFIG SENSOR
// =======================

const float LINE_VOLTAGE = 110.0;

const float SENSOR_MAX_CURRENT = 30.0;
const float SENSOR_MAX_VOLTAGE = 1.0;

const int SAMPLES = 500;

float offset = 0;

// =======================
// TARIFA CFE
// =======================

// Precio aproximado por kWh en MXN
const float COST_PER_KWH = 1.2;

// =======================

void setup() {

  Serial.begin(115200);

  // I2C
  Wire.begin(21, 22);

  // ADS1115
  if (!ads.begin(0x4B)) {

    Serial.println("ADS1115 no detectado");

    while (1);
  }

  ads.setGain(GAIN_ONE);

  // WIFI
  WiFi.begin(ssid, password);

  Serial.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");

  // THINGSPEAK
  ThingSpeak.begin(client);

  Serial.println("Sistema iniciado");
}

void loop() {

  float sumSq = 0;

  // =======================
  // LECTURA RMS
  // =======================

  for (int i = 0; i < SAMPLES; i++) {

    int16_t raw = ads.readADC_SingleEnded(0);

    // Conversión a volts
    float volts = raw * 0.125e-3;

    // Eliminación de offset DC
    offset += (volts - offset) * 0.0005;

    float centered = volts - offset;

    sumSq += centered * centered;
  }

  // Voltaje RMS del sensor
  float sensorVrms = sqrt(sumSq / SAMPLES);

  // Corriente RMS
  float current = (sensorVrms / SENSOR_MAX_VOLTAGE)
                  * SENSOR_MAX_CURRENT;

  // Filtro de ruido
  if (current < 0.02) {

    current = 0;
  }

  // Potencia en watts
  float power = current * LINE_VOLTAGE;

  // =======================
  // CONSUMO Y COSTOS
  // =======================

  // Consumo en kWh por hora
  float kwhPerHour = power / 1000.0;

  // Costo por hora
  float costPerHour = kwhPerHour * COST_PER_KWH;

  // Costo mensual estimado
  // suponiendo 24h al día durante 30 días
  float costPerMonth = costPerHour * 24.0 * 30.0;

  // =======================
  // SERIAL
  // =======================

  Serial.print("Corriente: ");
  Serial.print(current, 3);
  Serial.print(" A");

  Serial.print(" | Potencia: ");
  Serial.print(power, 1);
  Serial.print(" W");

  Serial.print(" | Costo 1h: $");
  Serial.print(costPerHour, 4);
  Serial.print(" MXN");

  Serial.print(" | Costo mes: $");
  Serial.print(costPerMonth, 2);
  Serial.println(" MXN");

  // =======================
  // THINGSPEAK
  // =======================

  ThingSpeak.setField(1, current);
  ThingSpeak.setField(2, power);
  ThingSpeak.setField(3, costPerHour);
  ThingSpeak.setField(4, costPerMonth);

  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {

    Serial.println("Datos enviados a ThingSpeak");
  }
  else {    

    Serial.print("Error ThingSpeak: ");
    Serial.println(response);
  }

  // ThingSpeak requiere mínimo 15 segundos
  delay(15000);
}
