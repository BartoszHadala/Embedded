#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "event_manager.h"

// Symulacja zapalania diody i wciskania przycisku
void onLedBlink(Event *event, uint64_t scheduledTime, void *context);
void onButtonClick(Event *event, uint64_t scheduledTime, void *context);

int main() {

    // 1. Inicjalizacja
    EVENT_MANAGER_INIT();

    // 2. Stworzenie zdarzeń
    Event ledEvent;
    Event sensorEvent;

    // 3. Rejestracja zdarzeń z callbackami
    EVENT_MANAGER_RegisterEvent(&ledEvent, onLedBlink, NULL);
    EVENT_MANAGER_RegisterEvent(&sensorEvent, onButtonClick, NULL);

    // 4. Zaplanuj zdarzenia
    EVENT_MANAGER_ScheduleEvent(&ledEvent, 1000, 1000);   // co 1000ms (cykliczne)
    EVENT_MANAGER_ScheduleEvent(&sensorEvent, 500, 0);    // jednorazowe w 500ms

    // Main Loop
    for (uint64_t time = 0; time <= 10000; time += 100) {
        printf("--- Czas: %" PRIu64 " ms ---\n", time);
        EVENT_MANAGER_Process(time);
    }

    return 0;
}

void onLedBlink(Event *event, uint64_t scheduledTime, void *context) {
    printf("[%" PRIu64 " ms] Zapalono diodę LED!\n", scheduledTime);
}

void onButtonClick(Event *event, uint64_t scheduledTime, void *context) {
    printf("[%" PRIu64 " ms] Wciśnięto przycisk!\n", scheduledTime);
}

