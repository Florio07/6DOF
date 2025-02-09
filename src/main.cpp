#include <Arduino.h>
#include <TMCStepper.h>

// Definizione pin
#define STEP_PIN        3   // Pin STEP collegato al TMC2208
#define SW_RX          19   // UART RX Mega2560 -> TX TMC2208
#define SW_TX          18   // UART TX Mega2560 -> RX TMC2208
#define SERIAL_PORT Serial1 // Porta HardwareSerial per TMC2208
#define DRIVER_ADDRESS 0b00 // Indirizzo del driver (default)
#define R_SENSE 0.11f  // Resistenza di sense per il TMC2208
#define MOTOR_STEPS 5000  // Numero di step prima dell'inversione
#define STEP_DELAY  160   // Microsecondi tra un passo e l'altro

TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);
bool shaft = false;

void setup() {
    Serial.begin(9600);
    delay(1000);

    pinMode(STEP_PIN, OUTPUT);
    
    // Avvio comunicazione con il driver
    SERIAL_PORT.begin(9600); // change to 115200 after testing
    driver.begin();
    
    // Forza la modalità UART
    driver.pdn_disable(true);      // Disabilita il controllo PDN
    driver.mstep_reg_select(true); // Abilita il controllo via registro UART
    
    // Configurazione del driver
    driver.rms_current(1000);
    driver.microsteps(16);
    driver.pwm_autoscale(true);

    // Controllo connessione UART
    Serial.print("Versione driver: ");
    Serial.println(driver.version());

    // Verifica configurazione
    Serial.print("GCONF: ");
    Serial.println(driver.GCONF(), BIN);

    delay(100); // Attesa per stabilizzazione
    driver.shaft(shaft);
    delay(10);
    driver.shaft(shaft);
}

void loop() {
    for (uint16_t i = 0; i < MOTOR_STEPS; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
    }

    shaft = !shaft;
    driver.shaft(shaft);
    driver.push(); // Forza l'invio del comando

    Serial.print("Cambio direzione: ");
    Serial.println(driver.shaft() ? "Reverse" : "Forward");

    delay(500); // Piccola pausa per stabilità
}
