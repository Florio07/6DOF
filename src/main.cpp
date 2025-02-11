#include <TMCStepper.h>

// Definizioni dei pin
#define RX_PIN  19    // RX di Arduino collegato al TX del driver
#define TX_PIN  18    // TX di Arduino collegato al RX del driver
#define STEP_PIN 3    // Pin di Step (D3)

// Parametri motore
#define MAX_STEPS 5000  // Numero di passi prima di invertire la direzione

// Impostazioni del driver
#define SERIAL_PORT Serial2  // UART per la comunicazione con il TMC2208
TMC2208Stepper driver(&SERIAL_PORT, 0.11);  // Inizializzazione driver

// Variabili di controllo
unsigned long stepCount = 0;
bool reverseDirection = false;

void setup() {
  // Seriali
  Serial.begin(115200);
  SERIAL_PORT.begin(115200);  // Comunicazione con il driver

  // Configurazione pin
  pinMode(STEP_PIN, OUTPUT);

  // Inizializzazione driver TMC2208
  driver.begin();
  driver.toff(4);            // Abilita il driver
  driver.rms_current(1000);  // Imposta corrente a 1A RMS
  driver.microsteps(16);     // Imposta micropassi a 16
  driver.pwm_autoscale(true);  // Abilita modalità stealthChop
  
  // Imposta direzione iniziale
  driver.shaft(reverseDirection);  
}

void loop() {
  // Se abbiamo raggiunto 5000 passi, invertiamo la direzione via UART
  if (stepCount >= MAX_STEPS) {
    reverseDirection = !reverseDirection;   // Cambia direzione
    driver.shaft(reverseDirection);         // Invia il comando al driver
    stepCount = 0;                           // Reset contatore passi
    delay(500);                              // Piccola pausa per stabilità
  }

  // Esegue un passo
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(1000);

  // Incrementa il contatore passi
  stepCount++;
}
