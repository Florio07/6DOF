#include <Arduino.h>
#include <TMCStepper.h>

// Definizione pin
<<<<<<< HEAD
#define STEP_PIN        3   // Pin STEP collegato al TMC2208
#define DIR_PIN        2   // Pin DIR collegato al TMC2208
#define EN_PIN         6   // Pin ENABLE collegato al TMC2208
=======
#define STEP_PIN        6   // Pin STEP collegato al TMC2208
#define EN_PIN        3   // Pin ENABLE collegato al TMC2208
#define DIR_PIN        2   // Pin DIR collegato al TMC2208
>>>>>>> dac9342113415daaef63c7f829dc6ac3265d19b8
#define SW_RX          0   // UART RX Mega2560 -> TX TMC2208
#define SW_TX          1   // UART TX Mega2560 -> RX TMC2208
#define SERIAL_PORT Serial // Porta HardwareSerial per TMC2208
#define DRIVER_ADDRESS 0b00 // Indirizzo del driver (default)
#define R_SENSE 0.11f  // Resistenza di sense per il TMC2208
#define MOTOR_STEPS 5000  // Numero di step prima dell'inversione
#define STEP_DELAY  160   // Microsecondi tra un passo e l'altro

TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);
bool shaft = false;

void setup() {
    pinMode(STEP_PIN, OUTPUT);
<<<<<<< HEAD
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    
    digitalWrite(EN_PIN, LOW); // Abilita il driver
    // Avvio comunicazione con il driver
    SERIAL_PORT.begin(9600); // change to 115200 after testing
    driver.begin();
    
    // Forza la modalità UART
=======
    pinMode(EN_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);

    digitalWrite(EN_PIN, LOW); // Abilita il driver
    
    // Avvio comunicazione con il driver
    SERIAL_PORT.begin(115200); // change to 115200 after testing
    driver.begin();
    delay(100); // Attesa per stabilizzazione
    Serial.begin(115200);
    while(!Serial);
    
    digitalWrite(EN_PIN, HIGH); // Abilita il driver
    // Forza la modalità UART
    driver.IHOLD_IRUN(0x10100); // Assicura che il driver sia attivo
>>>>>>> dac9342113415daaef63c7f829dc6ac3265d19b8
    driver.pdn_disable(true);      // Disabilita il controllo PDN
    driver.mstep_reg_select(true); // Abilita il controllo via registro UART
    
    // Configurazione del driver
    driver.rms_current(1000);
    driver.microsteps(16);
    driver.pwm_autoscale(true);

<<<<<<< HEAD
=======
    driver.GSTAT(0b111); // Reset degli errori
    driver.GCONF(driver.GCONF() | (1 << 0)); // Assicura che la direzione sia controllata via UART

    

    Serial.print("PDN_UART attivato: ");
    Serial.println(driver.pdn_disable() ? "Sì" : "No");

>>>>>>> dac9342113415daaef63c7f829dc6ac3265d19b8
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
<<<<<<< HEAD

    Serial.begin(9600);
    delay(1000);
    digitalWrite(EN_PIN, HIGH); // Abilita il driver
}

void loop() {
=======
    driver.toff(2);

}

void loop() {
    //SERIAL_PORT.write(0x90); // Comando per leggere GSTAT

>>>>>>> dac9342113415daaef63c7f829dc6ac3265d19b8
    for (uint16_t i = 0; i < MOTOR_STEPS; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
    }

<<<<<<< HEAD
    /*shaft = !shaft;
    driver.shaft(shaft);
    driver.push(); // Forza l'invio del comando*/

    digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));

    Serial.print("Cambio direzione: ");
    Serial.println(driver.shaft() ? "Reverse" : "Forward");
=======
    digitalWrite(DIR_PIN, !digitalRead(DIR_PIN)); // Inverte la direzione

    Serial.print("Cambio direzione: ");
    Serial.println(digitalRead(DIR_PIN) ? "Reverse" : "Forward");
>>>>>>> dac9342113415daaef63c7f829dc6ac3265d19b8

    delay(500); // Piccola pausa per stabilità
}
