#define BUTTON1 2
#define BUTTON2 3
#define BUZZER 8
#define LED1 9
#define LED2 10

void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON1) == LOW) {
    playChristmas();
  }

  if (digitalRead(BUTTON2) == LOW) {
    playTetris();
  }
}

// 🎄 Canción de Navidad (Jingle Bells, mejor ritmo)
void playChristmas() {
  int melody[] = { 659, 659, 659, 659, 659, 659, 659, 784, 523, 587, 659 };
  int durations[] = { 300, 300, 600, 300, 300, 600, 300, 300, 300, 300, 600 };

  for (int i = 0; i < 11; i++) {
    tone(BUZZER, melody[i]);
    digitalWrite(LED1, HIGH);
    delay(durations[i]);
    noTone(BUZZER);
    digitalWrite(LED1, LOW);
    delay(50);
  }
}

// 🎮 Canción de Tetris (con LED y ritmo más lento)
void playTetris() {
  int melody[] = {
    659, 494, 523, 587, 523, 494, 440,
    440, 523, 659, 587, 523, 494,
    523, 587, 659, 523, 440, 440, 440
  };

  int durations[] = {
    250, 250, 250, 250, 250, 250, 300,
    250, 250, 250, 250, 250, 250,
    250, 250, 250, 250, 300, 250, 300
  };

  for (int i = 0; i < 20; i++) {
    tone(BUZZER, melody[i]);
    digitalWrite(LED2, HIGH);
    delay(durations[i]);
    noTone(BUZZER);
    digitalWrite(LED2, LOW);
    delay(50);
  }
}
