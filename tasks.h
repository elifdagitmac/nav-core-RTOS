#pragma once
#include <Arduino.h>
#include <Servo.h>
#include "kernel.h"

// =================================================================
// PIN SETTINGS
// =================================================================

// --- Ultrasonic Sensor ---
#define TRIG_PIN            11   // Mavi kablo
#define ECHO_PIN             2   // Gri kablo (interrupt-capable)

// --- L293D Motor Driver ---
#define MOTOR_INPUT1_PIN     5   // Yeşil kablo
#define MOTOR_INPUT2_PIN     4   // Turuncu kablo

// --- Servo Pins ---
#define DUMEN_PIN            9   // Üst servo, yeşil sinyal
#define RADAR_PIN           10   // Alt servo, turuncu sinyal

// =================================================================
// TCB OBJECTS
// =================================================================
extern struct TCB radar_gorevi;
extern struct TCB motor_gorevi;
extern struct TCB monitor_gorevi;

// =================================================================
// SERVO OBJECTS
// =================================================================
extern Servo dumenServosu;
extern Servo radarServosu;

// =================================================================
// GLOBAL STATUS VARIABLES
// =================================================================
extern volatile float mesafe;
extern volatile bool engel_durumu;
extern int mevcutAci;
extern int adimYonu;
extern unsigned long sonServoHareketi;

// --- Interrupt-Based Echo Measurement ---
extern volatile unsigned long echo_baslangic;
extern volatile unsigned long echo_sure;
extern volatile bool olcum_hazir;

// =================================================================
// TASK & INTERRUPT FUNCTION PROTOTYPES
// =================================================================
void echoPinKesmeFonksiyonu(void);
void Task_RadarScan(void);
void Task_MotorControl(void);
void Task_SystemMonitor(void);
