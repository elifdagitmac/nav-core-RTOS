#include <Arduino.h>
#include <Servo.h>
#include "kernel.h"
#include "tasks.h"

void setup() {
    Serial.begin(9600);
    nav_core_init();

    // --- Starting Servo ---
    dumenServosu.attach(DUMEN_PIN);
    dumenServosu.write(90);

    radarServosu.attach(RADAR_PIN);
    radarServosu.write(90);

    // --- RTOS Task Definitions ---
    radar_gorevi.id               = 1;
    radar_gorevi.priority         = 1;
    radar_gorevi.delay_ms         = 0;
    radar_gorevi.gorev_fonksiyonu = Task_RadarScan;

    motor_gorevi.id               = 2;
    motor_gorevi.priority         = 2;
    motor_gorevi.delay_ms         = 0;
    motor_gorevi.gorev_fonksiyonu = Task_MotorControl;

    monitor_gorevi.id               = 3;
    monitor_gorevi.priority         = 3;
    monitor_gorevi.delay_ms         = 0;
    monitor_gorevi.gorev_fonksiyonu = Task_SystemMonitor;

    gorev_ekle(&radar_gorevi);
    gorev_ekle(&motor_gorevi);
    gorev_ekle(&monitor_gorevi);

    // --- Pin Configuration ---
    pinMode(TRIG_PIN,         OUTPUT);
    pinMode(ECHO_PIN,         INPUT);
    pinMode(MOTOR_INPUT1_PIN, OUTPUT);
    pinMode(MOTOR_INPUT2_PIN, OUTPUT);

    // --- Echo Interrupt Connection ---
    // CHANGE: catches both the rising and falling edges (needed for timing)
    attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoPinKesmeFonksiyonu, CHANGE);

    Serial.println(F("NAV-CORE: Baslatma Tamamlandi."));
}

void loop() {
    nav_core_tick();
    scheduler();
    delay(1);
}
