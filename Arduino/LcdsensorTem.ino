#include <DHT.h>
#include <LiquidCrystal.h>

// Configuración del sensor DHT11
#define DHTPIN 2        // Pin donde está conectado el DATA del DHT11
#define DHTTYPE DHT11   // Tipo de sensor

DHT dht(DHTPIN, DHTTYPE);

// Configuración del LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);  // LCD de 16 columnas x 2 filas
  lcd.print("Iniciando...");
  Serial.println("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leer datos del sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Validar datos
  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Error al leer");
    lcd.setCursor(0, 1);
    lcd.print("sensor DHT11");
    Serial.println("Error al leer sensor DHT11");
  } else {
    // Mostrar en LCD
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humedad: ");
    lcd.print(hum);
    lcd.print("%");

    // Mostrar en consola serial
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" °C | Humedad: ");
    Serial.print(hum);
    Serial.println(" %");
  }

  delay(2000); // Esperar 2 segundos antes de leer de nuevo
}

