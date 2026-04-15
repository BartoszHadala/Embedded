#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>

/** Forward declaration */
typedef struct Event Event;

/** Funkcja wskaźnikowa obsługi zdarzenia
 * 
 * @param event wskaźnik na strukturę zdarzenia
 * @param scheduledTime czas w jakim zdarzenie jest zaplanowane
 * @param context dodatkowe informacje dodane do zdarzenia
 */
typedef void (* OnEventHandler)(Event * event, uint64_t scheduledTime, void * context);

/** Deklaracja struktury deskryptora zdarzenia */
struct Event {
    bool isScheduled;
    uint64_t scheduledTime;
    uint64_t interval;
    OnEventHandler onEvent;
    void * context;
};

/** Inicjalizacja zdarzenia
 * 
 * Ta funkcja powinna czyścić wszystkie informacje odnośnie wszystkich zdarzeń
 */
void EVENT_MANAGER_INIT(void);

/** Rejestracja zdarzeń
 * 
 * @param event wskaźnik na deskryptor struktury zdarzenia
 * @param onEvent funkcja wskaźnikowa wywoływana podczas zdarzenia
 * @param context opcjonalny wskaźnik przekazywany do zdarzenia (NULL jeśli nieużywany)
 * @return true jeśli zdarzenie zostało zarejestrowane, w innym przypadku false
 */
bool EVENT_MANAGER_RegisterEvent(Event * event, OnEventHandler onEvent, void * context);

/** Wyrejestrowanie zdarzenia
 * 
 * @param event wskaźnik na deskryptor struktury zdarzenia
 */
void EVENT_MANEGER_UnregisterEvent(Event * event);

/** Planowanie zdarzeń
 * 
 * @param event wskaźnik na deskryptor struktury zdarzenia
 * @param time czas w jakim zdarzenie powinno się uruchomić
 * @param interval interwał powtarzania w ms (0 = jednorazowe)
 * @return true jeśli zdarzenie zostało zaplanowane, w innym przypadku false
 */
bool EVENT_MANAGER_ScheduleEvent(Event * event, uint64_t time, uint64_t interval);

/** Obsługa zdarzeń. Ta funkcja powinna być wywołana w głównej pętli programu
 * 
 * @param currentTime aktualny czas
 */
void EVENT_MANAGER_Process(uint64_t currentTime);

#endif