#include <TMCStepper.h>
#include <SoftwareSerial.h>

#define RX_PIN 10  // Pin RX per comunicazione UART con TMC2208
#define TX_PIN 11  // Pin TX per comunicazione UART con TMC2208
#define STEP_PIN 6 // Pin STEP per il controllo del motore
#define DIR_PIN 4  // Pin DIR per il controllo della direzione
#define R_SENSE 0.11f  // Resistenza di sense per il TMC2208

SoftwareSerial TMC2208Serial(RX_PIN, TX_PIN);
TMC2208Stepper driver(&TMC2208Serial, R_SENSE);

const int stepCount = 5000;
bool direction = true;
bool shaft = false;

void setup() {
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    
    Serial.begin(9600);
    TMC2208Serial.begin(9600);
    driver.begin();
    
    if (driver.test_connection()) {
        Serial.println("Connessione TMC2208: OK");
    } else {
        Serial.println("Errore di connessione al TMC2208!");
        while (1);
    }
    
    Serial.print("GCONF: ");
    Serial.println(driver.GCONF(), BIN);

    driver.toff(4); // Abilita lo stepper
    driver.rms_current(1000); // Imposta la corrente RMS a 1A
    driver.microsteps(16); // Imposta i microstep a 16
    driver.pdn_disable(true); // Disabilita PDN per consentire UART
    
    digitalWrite(DIR_PIN, direction);
}

void loop() {
    for (int i = 0; i < stepCount; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(160);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(160);
    }
    
    shaft = !shaft;
    driver.shaft(shaft);
    driver.push(); // Forza l'invio del comando*/

    //direction = !direction;
    //digitalWrite(DIR_PIN, direction);
    delay(500);
}
