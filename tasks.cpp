#include "tasks.h"

// --- TCB Objects ---
struct TCB radar_gorevi;
struct TCB motor_gorevi;
struct TCB monitor_gorevi;

// --- Servo Objects ---
Servo dumenServosu;
Servo radarServosu;

// --- Global Status Variables ---
volatile float mesafe          = 50.0;
volatile bool engel_durumu     = false;
int mevcutAci                  = 90;
int adimYonu                   = 3;
unsigned long sonServoHareketi = 0;

// --- Interrupt-Based Echo Variables ---
volatile unsigned long echo_baslangic = 0;
volatile unsigned long echo_sure      = 0;
volatile bool olcum_hazir             = false;

// =================================================================
// INTERRUPT FUNCTION — ECHO PIN (Pin 2, runs in the background)
// =================================================================
void echoPinKesmeFonksiyonu() {
    if (digitalRead(ECHO_PIN) == HIGH) {
        echo_baslangic = micros();         // Rising edge: measurement started
    } else {
        echo_sure   = micros() - echo_baslangic; // Falling edge: time calculated
        olcum_hazir = true;
    }
}

// =================================================================
// TASK 1 — RADAR SCAN (Priority: 1)
// =================================================================
void Task_RadarScan(void) {

    // If there's no obstacle, make a windshield wiper movement
    if (!engel_durumu) {
        if (millis() - sonServoHareketi >= 30) {
            sonServoHareketi = millis();
            mevcutAci += adimYonu;
            if (mevcutAci >= 150 || mevcutAci <= 30) {
                adimYonu = -adimYonu;
            }
            radarServosu.write(mevcutAci);
        }
    }
    // If there's an obstacle, the radar stays locked at that angle, the measurement continues.

    // --- Ultrasonic Triggering (non-blocking) ---
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // The signal was sent. The echo response is caught by the interrupt in the background.

    // --- Read the measurement coming from the interrupt ---
    if (olcum_hazir) {
        mesafe      = (echo_sure / 2.0) * 0.0343;
        olcum_hazir = false;
    }

    engel_durumu = (mesafe > 0.0 && mesafe < 20.0);

    radar_gorevi.delay_ms = 40;
}

// =================================================================
// TASK 2 — MOTOR CONTROL (Priority: 2)
// =================================================================
void Task_MotorControl(void) {
    digitalWrite(MOTOR_INPUT1_PIN, LOW);
    digitalWrite(MOTOR_INPUT2_PIN, HIGH);
    motor_gorevi.delay_ms = 30;
}

// =================================================================
// TASK 3 — SYSTEM MONITOR (Priority: 3)
// =================================================================
void Task_SystemMonitor(void) {
    static unsigned long son_ekran_zamani = 0;

    if (millis() - son_ekran_zamani >= 1000) {
        son_ekran_zamani = millis();

        Serial.println(F("-------- NAV-CORE STATUS --------"));
        Serial.print(F("Sistem Zamani : ")); Serial.print(millis());  Serial.println(F(" ms"));
        Serial.print(F("Mesafe        : ")); Serial.print(mesafe);    Serial.println(F(" cm"));
        Serial.print(F("Radar Acisi   : ")); Serial.print(mevcutAci); Serial.println(F(" deg"));
        Serial.print(F("Engel Durumu  : ")); Serial.println(engel_durumu ? F("(!)(TEHLIKE)(!)") : F("(GUVENLI)"));
        Serial.println(F("---------------------------------"));
    }

    monitor_gorevi.delay_ms = 1000;
}
