#pragma once
#include <Arduino.h>
#include <Servo.h>
#include "kernel.h"

// =================================================================
// PIN TANIMLAMALARI
// =================================================================

// --- Ultrasonik Sensör ---
#define TRIG_PIN            11   // Mavi kablo
#define ECHO_PIN             2   // Gri kablo (interrupt-capable)

// --- L293D Motor Sürücü ---
#define MOTOR_INPUT1_PIN     5   // Yeşil kablo
#define MOTOR_INPUT2_PIN     4   // Turuncu kablo

// --- Servo Pinleri ---
#define DUMEN_PIN            9   // Üst servo, yeşil sinyal
#define RADAR_PIN           10   // Alt servo, turuncu sinyal

// =================================================================
// TCB NESNELERİ
// =================================================================
extern struct TCB radar_gorevi;
extern struct TCB motor_gorevi;
extern struct TCB monitor_gorevi;

// =================================================================
// SERVO NESNELERİ
// =================================================================
extern Servo dumenServosu;
extern Servo radarServosu;

// =================================================================
// GLOBAL DURUM DEĞİŞKENLERİ
// =================================================================
extern volatile float mesafe;
extern volatile bool engel_durumu;
extern int mevcutAci;
extern int adimYonu;
extern unsigned long sonServoHareketi;

// --- Interrupt Tabanlı Echo Ölçümü ---
extern volatile unsigned long echo_baslangic;
extern volatile unsigned long echo_sure;
extern volatile bool olcum_hazir;

// =================================================================
// GÖREV & INTERRUPT FONKSİYON PROTOTİPLERİ
// =================================================================
void echoPinKesmeFonksiyonu(void);
void Task_RadarScan(void);
void Task_MotorControl(void);
void Task_SystemMonitor(void);