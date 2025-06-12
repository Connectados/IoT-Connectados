const int pinLDR = A0;     // Pin donde está conectado el sensor
const int pinLED = 13;     // Pin del LED
const int pinLED2 = 12;     // Pin del 2do LED

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  Serial.begin(9600);      // Solo si quieres ver el valor por Serial
}

void loop() {
  int luz = analogRead(pinLDR); // Valor entre 0 (oscuro) y 1023 (mucha luz)

  Serial.println(luz);          // Opcional: para ver en el monitor serial

  if (luz < 500) {              // Ajusta este umbral si quieres
    digitalWrite(pinLED, HIGH); // Enciende el LED en oscuridad
    digitalWrite(pinLED2, HIGH); // Enciende el LED en oscuridad

  } else {
    digitalWrite(pinLED, LOW);  // Apaga el LED si hay luz
    digitalWrite(pinLED2, LOW); // Enciende el LED en oscuridad

  }

  delay(100);  // pequeña pausa para estabilidad
}
