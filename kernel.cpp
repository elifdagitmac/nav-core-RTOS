#include "kernel.h"

struct TCB *head = NULL;
struct TCB *su_an_calisan = NULL;

void nav_core_init(void) {
    head = NULL;
    su_an_calisan = NULL;
}

void gorev_ekle(struct TCB *eklenecek_gorev_adresi) {
    eklenecek_gorev_adresi->siradaki_gorev = NULL;

    if (head == NULL || eklenecek_gorev_adresi->priority < head->priority) {
        eklenecek_gorev_adresi->siradaki_gorev = head;
        head = eklenecek_gorev_adresi;
    } else {
        struct TCB *tmp = head;
        while (tmp->siradaki_gorev != NULL &&
               tmp->siradaki_gorev->priority <= eklenecek_gorev_adresi->priority) {
            tmp = tmp->siradaki_gorev;
        }
        eklenecek_gorev_adresi->siradaki_gorev = tmp->siradaki_gorev;
        tmp->siradaki_gorev = eklenecek_gorev_adresi;
    }
}

void nav_core_tick(void) {
    struct TCB *tmp = head;
    while (tmp != NULL) {
        if (tmp->delay_ms > 0) {
            tmp->delay_ms--;
        }
        tmp = tmp->siradaki_gorev;
    }
}

void scheduler(void) {
    struct TCB *tmp = head;
    while (tmp != NULL) {
        if (tmp->delay_ms == 0) {
            su_an_calisan = tmp;
            su_an_calisan->gorev_fonksiyonu();
            return;
        }
        tmp = tmp->siradaki_gorev;
    }
}