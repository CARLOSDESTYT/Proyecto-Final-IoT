# Proyecto-Final-IoT
#Monitor Inteligente de Consumo Eléctrico con ESP32 + ADS1115 + ThingSpeak

Proyecto IoT para medir corriente, potencia eléctrica y costo estimado de consumo en tiempo real utilizando un ESP32, un sensor SCT-013 y la plataforma ThingSpeak.

---

#Vista General

Este sistema permite:

- Medir corriente AC en tiempo real
- Calcular potencia eléctrica
- Estimar costo por hora y mensual
- Enviar datos a ThingSpeak
- Monitorear desde cualquier lugar
- Crear dashboards IoT
  
---
#¿Cómo funciona?

El sensor SCT-013 detecta la corriente consumida por un aparato eléctrico.
El ADS1115 convierte la señal analógica a digital con alta precisión.
El ESP32 procesa los datos:

1. Calcula corriente RMS
2. Calcula potencia eléctrica
3. Estima costo energético
4. Envía datos a ThingSpeak mediante WiFi

---

#Componentes Utilizados

| Componente | Cantidad |
|---|---|
| ESP32 DevKit | 1 |
| ADS1115 | 1 |
| Sensor SCT-013-030 | 1 |
| Protoboard | 1 |
| Resistencias (si aplica) | Varias |
| Cables Dupont | Varios |
| Fuente USB para ESP32 | 1 |
| WiFi | 1 |

---

#Arquitectura del Sistema

```text
┌─────────────────┐
│ Aparato eléctrico │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ SCT-013 Sensor  │
└────────┬────────┘
         │ Señal AC
         ▼
┌─────────────────┐
│ ADS1115 ADC     │
└────────┬────────┘
         │ I2C
         ▼
┌─────────────────┐
│ ESP32           │
│ - RMS           │
│ - Potencia      │
│ - Costos        │
└────────┬────────┘
         │ WiFi
         ▼
┌─────────────────┐
│ ThingSpeak      │
└─────────────────┘
```

---

#Conexiones

## ADS1115 → ESP32

| ADS1115 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## SCT-013 → ADS1115

| SCT-013 | ADS1115 |
|---|---|
| Señal | A0 |
| GND | GND |

---

#Variables Calculadas

El sistema calcula:

## Corriente RMS

```math
I = \frac{V_{RMS}}{V_{MAX}} \times I_{MAX}
```

---

## Potencia

```math
P = V \times I
```

---

## Costo eléctrico

```math
Costo = \left(\frac{P}{1000}\right) \times t \times tarifa
```

---

#Plataforma IoT

Se utilizó:

- ThingSpeak
- WiFi del ESP32
- Dashboard en la nube

---

#Datos enviados a ThingSpeak

| Campo | Variable |
|---|---|
| Field 1 | Corriente |
| Field 2 | Potencia |
| Field 3 | Costo por hora |
| Field 4 | Costo mensual |

---

#Instalación

## 1. Instalar Arduino IDE

Descargar:

https://www.arduino.cc/en/software

---

## 2. Instalar librerías

Instalar desde el Library Manager:

- ThingSpeak
- Adafruit ADS1X15
- WiFi

---

## 3. Configurar ESP32

Agregar boards ESP32:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

---

## 4. Configurar WiFi

Editar:

```cpp
const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";
```

---

## 5. Configurar ThingSpeak

Editar:

```cpp
unsigned long channelID = TU_CHANNEL_ID;
const char* writeAPIKey = "TU_API_KEY";
```

---

#Resultados

Ejemplo de salida serial:

```text
Corriente: 0.523 A | Potencia: 57.5 W | Costo 1h: $0.0690 MXN | Costo mes: $49.68 MXN
```

---

#Posibles Mejoras

- Pantalla OLED
- Dashboard web personalizado
- Integración con Home Assistant
- Alertas por Telegram
- Base de datos propia
- Medición de múltiples líneas
- Relés inteligentes
- IA para predicción de consumo

---

#Seguridad

Este proyecto trabaja con corriente AC.

RECOMENDACIONES:

- No manipular cables energizados
- Usar aislamiento adecuado
- Verificar conexiones antes de energizar
- Realizar pruebas con supervisión

---

#Tecnologías Utilizadas

- C++
- Arduino IDE
- ESP32
- ThingSpeak
- ADS1115
- IoT
- I2C

---

#Proyecto

Puedes usar este proyecto para:

- Casas inteligentes
- Monitoreo energético
- Automatización
- Educación
- IoT
- Control de consumo eléctrico

---

#Fotos

<img width="2560" height="1275" alt="image" src="https://github.com/user-attachments/assets/541f9932-929f-4002-bc22-683e209b79d2" />
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/ade5d8bf-cd23-492a-9f7c-4fa87ab1172b" />
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/b37599e2-b950-4b19-a929-98562e9a8963" />
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/ad258df2-c4f8-4a47-be86-1b5b333fd548" />
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/35b2155e-4cae-4c7c-b7ce-5406fa5ce52f" />
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/b4490d20-fcd2-4057-a388-4eceaab9dfaf" />
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/fd956f32-46c8-404a-8c37-80a78c6ef3ec" />
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/8f048ec0-1825-441f-93d7-cce4b1e084de" />
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/a59b73bf-ddb8-4009-b111-0f65ce6ef4ea" />
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/0a405b13-bbea-46aa-aa50-db4379126a0f" />
<img width="900" height="1600" alt="image" src="https://github.com/user-attachments/assets/397d9d60-6c9a-4f8e-a45a-2c62572b1adb" />
```
