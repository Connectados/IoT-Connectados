// Pines
const int fsrPin = A0;       // Pin analógico conectado al sensor FSR
const int ledPin = 13;       // Pin digital del LED

// Umbral de presión (ajusta según tus pruebas)
const int umbral = 1;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // Iniciar comunicación serial
  Serial.println("Sistema iniciado. Esperando presión...");
}

void loop() {
  int lecturaFSR = analogRead(fsrPin);  // Leer el valor del FSR

  // Mostrar en consola el valor leído
  Serial.print("Valor FSR: ");
  Serial.println(lecturaFSR);

  // Si el valor supera el umbral, encender LED
  if (lecturaFSR > umbral) {
    digitalWrite(ledPin, HIGH);
    Serial.println("¡Presión detectada! LED encendido.");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Sin presión. LED apagado.");
  }

  delay(500);  // Esperar medio segundo antes de la próxima lectura
}
