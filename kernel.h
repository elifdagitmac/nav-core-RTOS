#pragma once
#include <Arduino.h>

typedef void (*GorevFonksiyonu)(void);

struct TCB {
    uint8_t id;
    uint8_t priority;
    struct TCB *siradaki_gorev;
    uint32_t delay_ms;
    void (*gorev_fonksiyonu)(void);
};

extern struct TCB *head;
extern struct TCB *su_an_calisan;

void nav_core_init(void);
void gorev_ekle(struct TCB *eklenecek_gorev_adresi);
void nav_core_tick(void);
void scheduler(void);