#include <LiquidCrystal.h>

// LCD RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pines del sensor ultrasónico
#define TRIG_PIN 3
#define ECHO_PIN 4

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Sensor Ultrasónico");
  delay(2000);
  lcd.clear();
}

void loop() {
  long duracion;
  float distancia;

  // Disparo ultrasónico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Mide el tiempo del eco
  duracion = pulseIn(ECHO_PIN, HIGH);

  // Calcula la distancia en cm
  distancia = duracion * 0.034 / 2;

  // Mostrar en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  lcd.setCursor(0, 1);
  lcd.print(distancia);
  lcd.print(" cm");

  // También en consola serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(500);
}
