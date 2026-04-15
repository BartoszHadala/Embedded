/*
 * ============================================================================
 * CALLBACK & WSKAŹNIKI NA FUNKCJE - ZESTAW ZADAŃ
 * ============================================================================
 * Kompiluj: gcc callback_tasks.c -o callback_tasks
 * Uruchom: ./callback_tasks
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// ============================================================================
// CZĘŚĆ 1: PODSTAWY WSKAŹNIKÓW NA FUNKCJE
// ============================================================================

/*
 * Zadanie 1: Utwórz wskaźnik na funkcję add() i wywołaj przez niego.
 * Funkcja add przyjmuje dwa int i zwraca int.
 */
int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

void task1(void) {
    printf("=== ZADANIE 1 ===\n");
    // TODO: Zadeklaruj wskaźnik na funkcję: int (*ptr)(int, int)
    // TODO: Przypisz do niego funkcję add
    // TODO: Wywołaj przez wskaźnik i wypisz wynik add(5, 3)
    int (*ptr)(int, int) = add;
    printf("add(5, 3) = %d\n", ptr(5, 3));
    printf("\n");
}

/*
 * Zadanie 2: Utwórz tablicę wskaźników na funkcje (add, sub, mul).
 * Wywołaj każdą funkcję z argumentami 10 i 5.
 */
void task2(void) {
    printf("=== ZADANIE 2 ===\n");
    // TODO: Zadeklaruj tablicę: int (*operations[3])(int, int) = {add, sub, mul};
    // TODO: W pętli wywołaj każdą funkcję z (10, 5) i wypisz wyniki
    int (* operations[3])(int, int) = {add, sub, mul};
    for (int i = 0; i < 3; i++) {
        printf("Wynik to %d\n", operations[i](10, 5));
    }
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 2: CALLBACK - PODSTAWY
// ============================================================================

/*
 * Zadanie 3: Napisz funkcję calculate(), która przyjmuje:
 * - dwa int (a, b)
 * - wskaźnik na funkcję operacji (callback)
 * Funkcja wywołuje callback z a i b, zwraca wynik.
 */
int calculate(int a, int b, int (*operation)(int, int)) {
    // TODO: Zaimplementuj
    if (operation == NULL) {
        return 0;
    } else {
        return operation(a, b);
    }
}

void task3(void) {
    printf("=== ZADANIE 3 ===\n");
    // TODO: Wywołaj calculate(10, 5, add) i wypisz wynik
    printf("calculate(10, 5, add) = %d\n", calculate(10, 5, add));
    // TODO: Wywołaj calculate(10, 5, sub) i wypisz wynik
    printf("calculate(10, 5, sub) = %d\n", calculate(10, 5, sub));
    // TODO: Wywołaj calculate(10, 5, mul) i wypisz wynik
    printf("calculate(10, 5, mul) = %d\n", calculate(10, 5, mul));
    printf("\n");
}

/*
 * Zadanie 4: Napisz funkcję forEach(), która iteruje po tablicy int
 * i wywołuje callback dla każdego elementu.
 * Callback przyjmuje int i nic nie zwraca.
 */
void printElement(int x) {
    printf("%d ", x);
}

void doubleElement(int x) {
    printf("%d ", x * 2);
}

void forEach(int *arr, int len, void (*callback)(int)) {
    // TODO: Zaimplementuj - wywołaj callback dla każdego elementu
    if (arr == NULL || callback == NULL || len < 1) {
        return;
    }

    for (int i = 0; i < len; i++) {
        callback(arr[i]);
    }
}

void task4(void) {
    printf("=== ZADANIE 4 ===\n");
    int arr[] = {1, 2, 3, 4, 5};
    // TODO: Wywołaj forEach z printElement
    // TODO: Wywołaj forEach z doubleElement
    int len = sizeof(arr) / sizeof(arr[0]);
    forEach(arr, len, printElement);
    printf("\n");
    forEach(arr, len, doubleElement);
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 3: CALLBACK W EMBEDDED (SYMULACJA)
// ============================================================================

/*
 * Zadanie 5: Symulacja obsługi przycisku z callbackiem.
 * Struktura Button zawiera wskaźnik na funkcję callback.
 * Gdy przycisk jest "naciśnięty", wywołaj callback.
 */
typedef struct {
    uint8_t id;
    uint8_t state;  // 0 = released, 1 = pressed
    void (*onPress)(uint8_t id);  // Callback wywoływany przy naciśnięciu
} Button;

void buttonPressedCallback(uint8_t id) {
    printf("Przycisk %d naciśnięty!\n", id);
}

void Button_Init(Button *btn, uint8_t id, void (*callback)(uint8_t)) {
    // TODO: Zainicjalizuj button - ustaw id, state=0, callback
    if (btn == NULL || callback == NULL) {
        return;
    } else {
        btn->id = id;
        btn->state = 0;
        btn->onPress = callback;
    }
}

void Button_Press(Button *btn) {
    // TODO: Ustaw state=1 i wywołaj callback (jeśli nie NULL)
    if (btn == NULL) {
        return;
    } else {
        btn->state = 1;
        btn->onPress(btn->id);
    }
}

void task5(void) {
    printf("=== ZADANIE 5 ===\n");
    Button btn1;
    // TODO: Zainicjalizuj btn1 z id=1 i callbackiem buttonPressedCallback
    // TODO: Wywołaj Button_Press(&btn1)
    Button_Init(&btn1, 1, buttonPressedCallback);
    Button_Press(&btn1);
    printf("\n");
}

/*
 * Zadanie 6: Symulacja timera z callbackiem.
 * Timer wywołuje callback po "upływie" czasu.
 */
typedef struct {
    uint32_t period_ms;
    uint8_t running;
    void (*onTimeout)(void);
} Timer;

void timerExpiredCallback(void) {
    printf("Timer wygasł!\n");
}

void Timer_Init(Timer *timer, uint32_t period, void (*callback)(void)) {
    // TODO: Zainicjalizuj timer
    if (timer == NULL || period <= 0 || callback == NULL) {
        return;
    } else {
        timer->period_ms = period;
        timer->running = 0;
        timer->onTimeout = callback;
    }
}

void Timer_Start(Timer *timer) {
    // TODO: Ustaw running=1
    if (timer == NULL) {
        return;
    } else {
        timer->running = 1;
    }
}

void Timer_Tick(Timer *timer) {
    // TODO: Jeśli running i callback nie NULL, wywołaj callback
    // (symulacja - w prawdziwym timerze sprawdzałbyś czas)
    if (timer == NULL || timer->running == 0) {
        return;
    } else {
        timer->onTimeout();
    }
}

void task6(void) {
    printf("=== ZADANIE 6 ===\n");
    Timer timer1;
    // TODO: Zainicjalizuj timer z period=1000 i callbackiem
    Timer_Init(&timer1, 1000, timerExpiredCallback);
    // TODO: Uruchom timer i wywołaj Timer_Tick
    Timer_Start(&timer1);
    Timer_Tick(&timer1);
    printf("\n");
}

/*
 * Zadanie 7: Symulacja UART z callbackami dla TX i RX.
 */
typedef struct {
    void (*onTxComplete)(void);
    void (*onRxReceived)(uint8_t data);
} UART_Callbacks;

typedef struct {
    uint8_t id;
    UART_Callbacks callbacks;
} UART_Handle;

void uartTxComplete(void) {
    printf("UART: Transmisja zakończona\n");
}

void uartRxReceived(uint8_t data) {
    printf("UART: Odebrano bajt: 0x%02X ('%c')\n", data, data);
}

void UART_Init(UART_Handle *uart, uint8_t id, void (*txCb)(void), void (*rxCb)(uint8_t)) {
    // TODO: Zainicjalizuj UART z callbackami
    if (uart == NULL || txCb == NULL || rxCb == NULL) {
        return;
    } else {
        uart->id = id;
        uart->callbacks.onTxComplete = txCb;
        uart->callbacks.onRxReceived = rxCb;
    }
}

void UART_SimulateTx(UART_Handle *uart) {
    // TODO: Wywołaj callback TX (jeśli nie NULL)
    if (uart == NULL) {
        return;
    } else {
        uart->callbacks.onTxComplete();
    }
}

void UART_SimulateRx(UART_Handle *uart, uint8_t data) {
    // TODO: Wywołaj callback RX z data (jeśli nie NULL)
    if (uart == NULL) {
        return;
    } else {
        uart->callbacks.onRxReceived(data);
    }
}

void task7(void) {
    printf("=== ZADANIE 7 ===\n");
    UART_Handle uart1;
    // TODO: Zainicjalizuj UART z callbackami
    UART_Init(&uart1, 99, uartTxComplete, uartRxReceived);
    // TODO: Symuluj wysłanie i odebranie danych
    UART_SimulateTx(&uart1);
    UART_SimulateRx(&uart1, 88);
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 4: CALLBACK Z KONTEKSTEM (void *context)
// ============================================================================

/*
 * Zadanie 8: Callback z kontekstem użytkownika.
 * Pozwala przekazać dodatkowe dane do callbacku.
 */
typedef struct {
    char name[20];
    int counter;
} SensorContext;

void sensorCallback(void *context) {
    SensorContext *ctx = (SensorContext *)context;
    ctx->counter++;
    printf("Sensor '%s' - odczyt #%d\n", ctx->name, ctx->counter);
}

typedef struct {
    void (*callback)(void *context);
    void *context;
} Sensor;

void Sensor_Init(Sensor *sensor, void (*cb)(void *), void *ctx) {
    // TODO: Zainicjalizuj sensor z callbackiem i kontekstem
    if (sensor == NULL || cb == NULL || ctx == NULL) {
        return;
    } else {
        sensor->callback = cb;
        sensor->context = ctx;
    }
}

void Sensor_Read(Sensor *sensor) {
    // TODO: Wywołaj callback z kontekstem (jeśli nie NULL)
    if (sensor == NULL) {
        return;
    } else {
        sensor->callback(sensor->context);
    }
}

void task8(void) {
    printf("=== ZADANIE 8 ===\n");
    SensorContext tempCtx = {"Temperatura", 0};
    Sensor tempSensor;
    // TODO: Zainicjalizuj sensor z callbackiem i kontekstem
    Sensor_Init(&tempSensor, sensorCallback, &tempCtx);
    // TODO: Wywołaj Sensor_Read kilka razy
    Sensor_Read(&tempSensor);
    Sensor_Read(&tempSensor);
    Sensor_Read(&tempSensor);
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 5: ZAAWANSOWANE - REJESTRACJA WIELU CALLBACKÓW
// ============================================================================

/*
 * Zadanie 9: System eventów z wieloma callbackami.
 * Pozwala zarejestrować wiele funkcji dla jednego eventu.
 */
#define MAX_CALLBACKS 5

typedef void (*EventCallback)(int eventData);

typedef struct {
    EventCallback callbacks[MAX_CALLBACKS];
    uint8_t count;
} EventSystem;

void EventSystem_Init(EventSystem *es) {
    // TODO: Wyzeruj tablicę callbacków i count
    if (es == NULL) {
        return;
    } else {
        for (int i = 0; i < MAX_CALLBACKS; i++) {
            es->callbacks[i] = NULL;
        }
        es->count = 0;
    }
}

uint8_t EventSystem_Register(EventSystem *es, EventCallback cb) {
    // TODO: Dodaj callback do tablicy (jeśli jest miejsce)
    if (es == NULL || cb == NULL) {
        return 0;
    } else {
        if (es->count >= MAX_CALLBACKS) {
            return 0;
        } else {
            es->callbacks[es->count] = cb;
            es->count++;
        }
    }
    // Zwróć 1 jeśli sukces, 0 jeśli brak miejsca
    return 1;
}

void EventSystem_Trigger(EventSystem *es, int eventData) {
    // TODO: Wywołaj wszystkie zarejestrowane callbacki z eventData
    if (es == NULL) {
        return;
    } else {
        uint8_t len = es->count;
        for (int i = 0; i < len; i++) {
            es->callbacks[i](eventData);
        }

    }
}

void eventHandler1(int data) {
    printf("Handler 1 otrzymał: %d\n", data);
}

void eventHandler2(int data) {
    printf("Handler 2 otrzymał: %d\n", data);
}

void eventHandler3(int data) {
    printf("Handler 3 otrzymał: %d\n", data);
}

void task9(void) {
    printf("=== ZADANIE 9 ===\n");
    EventSystem events;
    // TODO: Zainicjalizuj system
    EventSystem_Init(&events);
    // TODO: Zarejestruj 3 handlery
    EventSystem_Register(&events, eventHandler1);
    EventSystem_Register(&events, eventHandler2);
    EventSystem_Register(&events, eventHandler3);
    // TODO: Wywołaj EventSystem_Trigger z wartością 42
    EventSystem_Trigger(&events, 42);
    printf("\n");
}

/*
 * Zadanie 10: State machine z callbackami.
 * Każdy stan ma swój callback wywoływany przy wejściu.
 */
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_COUNT
} State;

typedef void (*StateHandler)(void);

void onIdleEnter(void) {
    printf("Wejście w stan IDLE\n");
}

void onRunningEnter(void) {
    printf("Wejście w stan RUNNING\n");
}

void onErrorEnter(void) {
    printf("Wejście w stan ERROR!\n");
}

typedef struct {
    State currentState;
    StateHandler handlers[STATE_COUNT];
} StateMachine;

void StateMachine_Init(StateMachine *sm) {
    // TODO: Ustaw currentState na IDLE
    if (sm == NULL) {
        return;
    } else {
        sm->currentState = STATE_IDLE;
    // TODO: Przypisz handlery do tablicy (indeks = stan)
        sm->handlers[STATE_IDLE] = onIdleEnter;
        sm->handlers[STATE_RUNNING] = onRunningEnter;
        sm->handlers[STATE_ERROR] = onErrorEnter;
    }
}

void StateMachine_ChangeState(StateMachine *sm, State newState) {
    // TODO: Zmień stan i wywołaj odpowiedni handler
    if (sm == NULL) {
        return;
    } else {
        sm->currentState = newState;
        sm->handlers[newState]();
    }
}

void task10(void) {
    printf("=== ZADANIE 10 ===\n");
    StateMachine sm;
    // TODO: Zainicjalizuj state machine
    StateMachine_Init(&sm);
    // TODO: Zmień stan na RUNNING, potem ERROR, potem IDLE
    StateMachine_ChangeState(&sm, STATE_RUNNING);
    StateMachine_ChangeState(&sm, STATE_ERROR);
    StateMachine_ChangeState(&sm, STATE_IDLE);
    printf("\n");
}

// ============================================================================
// TESTY
// ============================================================================

void runTests(void) {
    printf("========================================\n");
    printf("CALLBACK & WSKAŹNIKI NA FUNKCJE - TESTY\n");
    printf("========================================\n\n");
    
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    task10();
    
    printf("========================================\n");
    printf("KONIEC TESTÓW\n");
    printf("========================================\n");
}

int main(void) {
    runTests();
    return 0;
}
