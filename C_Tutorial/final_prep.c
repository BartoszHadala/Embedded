/*
 * ============================================================================
 * FIRMWARE INTERN NORDIC - FINALNE ĆWICZENIA PRZED ROZMOWĄ
 * ============================================================================
 * Kompiluj: gcc final_prep.c -o final_prep
 * Uruchom: ./final_prep
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// CZĘŚĆ 1: VOLATILE I ISR (TOP 1 PYTANIE NA ROZMOWIE!)
// ============================================================================

/*
 * Zadanie 1: Wyjaśnij w komentarzu:
 * - Co robi volatile?
 * - Kiedy używamy volatile?
 * - Co się stanie jeśli NIE damy volatile?
 * Odpowiedź:
 * Jest to słowo kluczowe dodawane przez zmienną w celu poinformowania kompilator, żeby
 * nie optymalizował zmiennej, gdyż może być ona używana/zmieniona sprzetową lub poprzez przerwanie.
 * Brak słowa volatile może spowodować, że na zaostrzonym poziomie optymalizacji komplilatora, 
 * usunie on ją całkowicie z programu z racji, że uzna że np. jest nieużywana. Głównie używamy
 * przy flagach, przerwaniań programowych i sprzętowych.
 */

/*
 * Zadanie 2: Symulacja przerwania (ISR).
 * Flaga ustawiana w ISR, odczytywana w main loop.
 * Dlaczego flaga MUSI być volatile?
 */
volatile uint8_t g_buttonPressed = 0;
volatile uint32_t g_tickCounter = 0;

// Symulacja ISR - w prawdziwym firmware to byłoby wywoływane przez sprzęt
void BUTTON_IRQHandler(void) {
    g_buttonPressed = 1;
}

void SYSTICK_IRQHandler(void) {
    g_tickCounter++;
}

void task2(void) {
    printf("=== ZADANIE 2: ISR + VOLATILE ===\n");
    // TODO: Symuluj naciśnięcie przycisku (wywołaj BUTTON_IRQHandler)
    BUTTON_IRQHandler();
    // TODO: W pętli sprawdź flagę g_buttonPressed
    while (1)
    {
        if(g_buttonPressed) {
    // TODO: Jeśli flaga ustawiona - wypisz "Button pressed!", wyzeruj flagę
            printf("Button pressed!\n");
            g_buttonPressed = 0;
            break;
        }
    }
    // TODO: Symuluj 5 ticków (wywołaj SYSTICK_IRQHandler 5 razy)
    for (int i = 0; i < 5; i++) {
        SYSTICK_IRQHandler();
    }
    printf("Wartosć q_tickCounter = %d\n", g_tickCounter);
    // TODO: Wypisz wartość g_tickCounter
    printf("\n");
}

/*
 * Zadanie 3: Dlaczego ten kod jest NIEBEZPIECZNY bez volatile?
 * Napisz komentarz wyjaśniający problem.
 * 
 * Odpowiedź:
 * Zmienne g_dataReady i g_rxData są ustawiane w handlerze przerwania. Czyli de'facto
 * kompilator widzi je jako zainicjalizowane na starcie na zero ale potem już nieużywane.
 * Mimo, że faktycznie przychodzą przerwania i są wykorzystywane kompilator po prostu może je wyrzucić
 * z programu, co np. może nigdy nie wykonać programu z while poolingu, odpytywania flagi.
 */
volatile uint8_t g_dataReady = 0;
volatile uint8_t g_rxData = 0;

void UART_IRQHandler_Sim(uint8_t data) {
    g_rxData = data;
    g_dataReady = 1;
}

void task3(void) {
    printf("=== ZADANIE 3: UART ISR ===\n");
    // TODO: Symuluj odebranie danych UART (wywołaj UART_IRQHandler_Sim z wartością 0x42)
    UART_IRQHandler_Sim(0x42);
    // TODO: Sprawdź g_dataReady, jeśli 1 - wypisz odebrane dane, wyzeruj flagę
    if (g_dataReady) {
        printf("Odebrana dana z UART eq %d\n", g_rxData);
        g_dataReady = 0;
    }
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 2: REJESTRY SPRZĘTOWE (SYMULACJA GPIO)
// ============================================================================

// Symulacja rejestru GPIO (32-bitowy rejestr)
volatile uint32_t GPIO_ODR = 0x00000000;  // Output Data Register
volatile uint32_t GPIO_IDR = 0x00000000;  // Input Data Register

/*
 * Zadanie 4: Napisz funkcje do obsługi GPIO.
 * Ustaw pin, wyczyść pin, toggle pin, odczytaj stan pinu.
 * Pin to numer 0-31.
 */
void GPIO_SetPin(volatile uint32_t *reg, uint8_t pin) {
    // TODO: Ustaw bit na pozycji pin w rejestrze
    *reg |= (1 << pin);
}

void GPIO_ClearPin(volatile uint32_t *reg, uint8_t pin) {
    // TODO: Wyczyść bit na pozycji pin
    *reg &= ~(1 << pin);
}

void GPIO_TogglePin(volatile uint32_t *reg, uint8_t pin) {
    // TODO: Przełącz bit na pozycji pin
    *reg ^= (1 << pin);
}

uint8_t GPIO_ReadPin(volatile uint32_t *reg, uint8_t pin) {
    // TODO: Odczytaj stan bitu na pozycji pin, zwróć 0 lub 1
    return (*reg & (1 << pin)) ? 1 : 0;
}

void task4(void) {
    printf("=== ZADANIE 4: GPIO ===\n");
    // TODO: Ustaw pin 5 (LED)
    GPIO_SetPin(&GPIO_IDR, 5);
    // TODO: Wypisz stan pinu 5
    GPIO_ReadPin(&GPIO_IDR, 5);
    // TODO: Toggle pin 5
    GPIO_TogglePin(&GPIO_IDR, 5);
    // TODO: Wypisz stan pinu 5
    GPIO_ReadPin(&GPIO_IDR, 5);
    // TODO: Wypisz cały rejestr jako hex
    printf("%x", GPIO_IDR);
    printf("\n");
}

/*
 * Zadanie 5: Konfiguracja rejestru - ustaw bity 4-7 na wartość 0xA,
 * nie zmieniając pozostałych bitów (read-modify-write).
 */
void setRegisterField(volatile uint32_t *reg, uint8_t startBit, uint8_t width, uint32_t value) {
    // TODO: Zaimplementuj
    // 1. Utwórz maskę dla pola bitowego (width bitów od startBit)
    uint32_t mask = ((1 << width) - 1) << startBit;
    // 2. Wyczyść pole w rejestrze (reg &= ~maska)
    *reg &= ~mask;
    // 3. Ustaw nową wartość (reg |= (value << startBit) & maska)
    *reg |= (value << startBit) & mask;
}

void task5(void) {
    printf("=== ZADANIE 5: REGISTER FIELD ===\n");
    volatile uint32_t testReg = 0xFF;
    // TODO: Ustaw bity 4-7 na 0xA (width=4, startBit=4, value=0xA)
    // Oczekiwany wynik: 0xAF
    setRegisterField(&testReg, 4, 4, 0xA);
    printf("Register: 0x%02X (oczekiwane: 0xAF)\n", testReg);
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 3: BLE STATE MACHINE
// ============================================================================

typedef enum {
    BLE_DISCONNECTED,
    BLE_ADVERTISING,
    BLE_CONNECTING,
    BLE_CONNECTED,
    BLE_STATE_COUNT
} BLE_State;

typedef enum {
    BLE_EVT_START_ADV,
    BLE_EVT_CONNECT_REQUEST,
    BLE_EVT_CONNECTED,
    BLE_EVT_DISCONNECT,
    BLE_EVT_TIMEOUT
} BLE_Event;

typedef void (*BLE_StateHandler)(void);

typedef struct {
    BLE_State currentState;
    BLE_StateHandler onEnter[BLE_STATE_COUNT];
    BLE_StateHandler onExit[BLE_STATE_COUNT];
} BLE_StateMachine;

/*
 * Zadanie 6: Zaimplementuj handlery stanów BLE.
 */
void onDisconnectedEnter(void) {
    printf("[BLE] Stan: DISCONNECTED\n");
}

void onAdvertisingEnter(void) {
    printf("[BLE] Stan: ADVERTISING - szukam urządzeń...\n");
}

void onConnectingEnter(void) {
    printf("[BLE] Stan: CONNECTING - łączę się...\n");
}

void onConnectedEnter(void) {
    printf("[BLE] Stan: CONNECTED - połączono!\n");
}

void BLE_Init(BLE_StateMachine *sm) {
    // TODO: Ustaw stan początkowy na DISCONNECTED
    if (sm == NULL) {
        return;
    }
    sm->currentState = BLE_DISCONNECTED;
    // TODO: Przypisz handlery onEnter do tablicy (indeks = stan)
    sm->onEnter[sm->currentState] = BLE_EVT_DISCONNECT;
    // TODO: Ustaw onExit na NULL (opcjonalne)
    sm->onExit[sm->currentState] = NULL;
}

void BLE_ChangeState(BLE_StateMachine *sm, BLE_State newState) {
    // TODO: Wywołaj onExit dla obecnego stanu (jeśli nie NULL)
    if (sm == NULL) {
        return;
    } else {
        sm->onExit[sm->currentState]();
    }
    // TODO: Zmień stan
    sm->currentState = newState;
    // TODO: Wywołaj onEnter dla nowego stanu (jeśli nie NULL)
    sm->onEnter[sm->currentState]();
}

/*
 * Zadanie 7: Obsługa eventów BLE.
 * Napisz funkcję, która na podstawie eventu zmienia stan.
 */
void BLE_HandleEvent(BLE_StateMachine *sm, BLE_Event evt) {
    // TODO: Zaimplementuj przejścia stanów:
    // DISCONNECTED + START_ADV       → ADVERTISING
    // ADVERTISING  + CONNECT_REQUEST → CONNECTING
    // ADVERTISING  + TIMEOUT         → DISCONNECTED
    // CONNECTING   + CONNECTED       → CONNECTED
    // CONNECTING   + TIMEOUT         → DISCONNECTED
    // CONNECTED    + DISCONNECT      → DISCONNECTED
    if (sm == NULL) {
        return;
    } else {
        switch (sm->currentState)
        {
            case BLE_DISCONNECTED:
                if (evt == BLE_EVT_START_ADV) {
                    sm->currentState = BLE_ADVERTISING;
                }
                break;
                
            case BLE_ADVERTISING:
                if (evt == BLE_EVT_CONNECT_REQUEST) {
                    sm->currentState = BLE_CONNECTING;
                } else if (evt == BLE_EVT_TIMEOUT) {
                    sm->currentState = BLE_DISCONNECTED;
                }
                break;

            case BLE_CONNECTING:
                if (evt == BLE_EVT_CONNECTED) {
                    sm->currentState = BLE_CONNECTED;
                } else if (evt == BLE_EVT_TIMEOUT) {
                    sm->currentState = BLE_DISCONNECTED;
                }
                break;

            case BLE_CONNECTED:
                if (evt == BLE_EVT_DISCONNECT) {
                    sm->currentState = BLE_DISCONNECTED;
                }
                break;
        
            default:
                break;
        }
    }
}

void task7(void) {
    printf("=== ZADANIE 7: BLE STATE MACHINE ===\n");
    BLE_StateMachine ble;
    BLE_Init(&ble);
    // TODO: Symuluj scenariusz:
    // 1. Start advertising
    BLE_ChangeState(&ble, BLE_EVT_START_ADV);
    // 2. Urządzenie się łączy (connect request)
    BLE_ChangeState(&ble, BLE_EVT_CONNECT_REQUEST);
    // 3. Połączenie nawiązane (connected)
    BLE_ChangeState(&ble, BLE_EVT_CONNECTED);
    // 4. Rozłączenie (disconnect)
    BLE_ChangeState(&ble, BLE_EVT_DISCONNECT);
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 4: RING BUFFER + ISR (KOMBINACJA!)
// ============================================================================

#define UART_BUF_SIZE 16

typedef struct {
    uint8_t buffer[UART_BUF_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} UART_RingBuffer;

/*
 * Zadanie 8: Ring buffer dla UART RX (dane z przerwania).
 */
UART_RingBuffer g_uartRxBuffer;

void UART_RingBuffer_Init(UART_RingBuffer *rb) {
    // TODO: Zainicjalizuj bufor
}

bool UART_RingBuffer_Put(UART_RingBuffer *rb, uint8_t data) {
    // TODO: Dodaj bajt, zwróć true/false
    return false;
}

bool UART_RingBuffer_Get(UART_RingBuffer *rb, uint8_t *data) {
    // TODO: Pobierz bajt, zwróć true/false
    return false;
}

// Symulacja ISR - odbiera bajt i wkłada do ring buffera
void UART_RX_IRQHandler(uint8_t receivedByte) {
    // TODO: Włóż receivedByte do g_uartRxBuffer
}

// Funkcja w main loop - przetwarza dane z buffera
void processUartData(void) {
    // TODO: Pobieraj bajty z g_uartRxBuffer i wypisuj
    // TODO: Wypisz ile bajtów przetworzono
}

void task8(void) {
    printf("=== ZADANIE 8: UART + RING BUFFER ===\n");
    UART_RingBuffer_Init(&g_uartRxBuffer);
    // TODO: Symuluj odebranie "Hello" (bajt po bajcie przez ISR)
    // TODO: Wywołaj processUartData() - powinno wypisać "Hello"
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 5: PARSOWANIE PAKIETU Z CRC
// ============================================================================

/*
 * Zadanie 9: Parsowanie pakietu komunikacyjnego.
 * Format: [START=0xAA] [LEN] [CMD] [DATA...] [CRC] [END=0xBB]
 * CRC = XOR wszystkich bajtów od LEN do ostatniego DATA (włącznie).
 */
typedef struct {
    uint8_t cmd;
    uint8_t data[32];
    uint8_t dataLen;
    bool valid;
} Packet;

uint8_t calculateXorChecksum(uint8_t *data, uint8_t len) {
    // TODO: Oblicz XOR checksum
    return 0;
}

Packet parsePacket(uint8_t *buffer, uint8_t bufLen) {
    // TODO: Zaimplementuj parser:
    // 1. Sprawdź START (0xAA) i END (0xBB)
    // 2. Odczytaj LEN, CMD, DATA
    // 3. Oblicz CRC i porównaj z odebranym
    // 4. Zwróć Packet z valid=true jeśli poprawny
    Packet pkt = {0};
    return pkt;
}

void task9(void) {
    printf("=== ZADANIE 9: PACKET PARSER ===\n");
    // Pakiet: START=0xAA, LEN=3, CMD=0x01, DATA={0x02, 0x03}, CRC=?, END=0xBB
    // CRC = 0x03 ^ 0x01 ^ 0x02 ^ 0x03 = 0x03
    uint8_t testPacket[] = {0xAA, 0x03, 0x01, 0x02, 0x03, 0x03, 0xBB};

    Packet result = parsePacket(testPacket, sizeof(testPacket));
    // TODO: Wypisz czy pakiet poprawny, jaki CMD, jakie dane
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 6: CONST CORRECTNESS (PYTANIE REKRUTACYJNE!)
// ============================================================================

/*
 * Zadanie 10: Wyjaśnij w komentarzu różnicę między:
 *   const int *p        - 
 *   int *const p        - 
 *   const int *const p  - 
 */

/*
 * Zadanie 11: Które z poniższych operacji są legalne? Napisz komentarz.
 */
void task11(void) {
    printf("=== ZADANIE 11: CONST CORRECTNESS ===\n");
    int a = 10, b = 20;

    const int *p1 = &a;
    // *p1 = 30;   // Legalne/Nielegalne? Dlaczego?
    // p1 = &b;    // Legalne/Nielegalne? Dlaczego?

    int *const p2 = &a;
    // *p2 = 30;   // Legalne/Nielegalne? Dlaczego?
    // p2 = &b;    // Legalne/Nielegalne? Dlaczego?

    const int *const p3 = &a;
    // *p3 = 30;   // Legalne/Nielegalne? Dlaczego?
    // p3 = &b;    // Legalne/Nielegalne? Dlaczego?

    printf("a = %d\n", a);
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 7: LINKED LIST - EMBEDDED DEVICE LIST
// ============================================================================

typedef struct BLE_Device {
    uint8_t address[6];     // Adres MAC (6 bajtów)
    int8_t rssi;            // Siła sygnału
    char name[20];
    struct BLE_Device *next;
} BLE_Device;

/*
 * Zadanie 12: Lista zeskanowanych urządzeń BLE.
 */
BLE_Device* BLE_AddDevice(BLE_Device *head, uint8_t addr[6], int8_t rssi, const char *name) {
    // TODO: Alokuj nowy węzeł, wypełnij dane, dodaj na początek listy
    return NULL;
}

BLE_Device* BLE_FindByRSSI(BLE_Device *head, int8_t minRSSI) {
    // TODO: Znajdź pierwsze urządzenie z RSSI >= minRSSI
    return NULL;
}

void BLE_PrintDevices(BLE_Device *head) {
    // TODO: Wypisz wszystkie urządzenia (nazwa, RSSI, adres MAC)
}

void BLE_FreeList(BLE_Device *head) {
    // TODO: Zwolnij całą listę
}

void task12(void) {
    printf("=== ZADANIE 12: BLE DEVICE LIST ===\n");
    BLE_Device *deviceList = NULL;

    uint8_t addr1[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x01};
    uint8_t addr2[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x02};
    uint8_t addr3[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x03};

    // TODO: Dodaj 3 urządzenia
    // TODO: Wypisz listę
    // TODO: Znajdź urządzenie z RSSI >= -60
    // TODO: Zwolnij listę
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 8: MIESZANE - SZYBKIE PYTANIA (ANALIZA KODU)
// ============================================================================

/*
 * Zadanie 13: Co wypisze ten kod? Napisz odpowiedź w komentarzu.
 */
void task13(void) {
    printf("=== ZADANIE 13: ANALIZA KODU ===\n");

    // a) Co wypisze?
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr + 2;
    printf("a) %d\n", *p);       // Odpowiedź:
    printf("a) %d\n", *(p - 1)); // Odpowiedź:
    printf("a) %d\n", p[-2]);    // Odpowiedź:

    // b) Co wypisze?
    uint8_t x = 0xAB;
    printf("b) upper nibble: 0x%X\n", (x >> 4) & 0x0F);  // Odpowiedź:
    printf("b) lower nibble: 0x%X\n", x & 0x0F);          // Odpowiedź:

    // c) Co wypisze? (endianness)
    uint32_t val = 0x01020304;
    uint8_t *bp = (uint8_t *)&val;
    printf("c) first byte: 0x%02X\n", bp[0]);  // Odpowiedź (little-endian):

    printf("\n");
}

/*
 * Zadanie 14: Znajdź BŁĄD w kodzie. Napisz komentarz co jest nie tak.
 */
void task14(void) {
    printf("=== ZADANIE 14: ZNAJDŹ BŁĄD ===\n");

    // Błąd 1:
    // char *str = malloc(5);
    // strcpy(str, "Hello");  // Co jest nie tak?
    // Odpowiedź:

    // Błąd 2:
    // int *p = malloc(sizeof(int));
    // *p = 42;
    // free(p);
    // printf("%d\n", *p);  // Co jest nie tak?
    // Odpowiedź:

    // Błąd 3:
    // void foo() {
    //     int arr[3] = {1, 2, 3};
    //     return arr;  // Co jest nie tak?
    // }
    // Odpowiedź:

    // Błąd 4:
    // volatile uint8_t flag = 0;
    // while (flag = 0) {  // Co jest nie tak?
    //     // czekaj
    // }
    // Odpowiedź:

    printf("Sprawdź odpowiedzi w komentarzach!\n");
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 9: WATCHDOG + TIMER (EMBEDDED COMBO)
// ============================================================================

typedef struct {
    uint32_t timeout;
    uint32_t counter;
    bool enabled;
    void (*onTimeout)(void);
} Watchdog;

/*
 * Zadanie 15: Symulacja watchdog timer.
 * Watchdog resetuje system jeśli nie zostanie "nakarmiony" (kicked) w czasie.
 */
void systemResetCallback(void) {
    printf("[WATCHDOG] SYSTEM RESET! Watchdog nie został nakarmiony!\n");
}

void Watchdog_Init(Watchdog *wdg, uint32_t timeout, void (*callback)(void)) {
    // TODO: Zainicjalizuj watchdog
}

void Watchdog_Start(Watchdog *wdg) {
    // TODO: Ustaw enabled=true, counter=timeout
}

void Watchdog_Kick(Watchdog *wdg) {
    // TODO: Zresetuj counter do timeout (nakarm watchdoga)
}

void Watchdog_Tick(Watchdog *wdg) {
    // TODO: Jeśli enabled, zmniejsz counter
    // TODO: Jeśli counter == 0, wywołaj onTimeout callback
}

void task15(void) {
    printf("=== ZADANIE 15: WATCHDOG ===\n");
    Watchdog wdg;
    Watchdog_Init(&wdg, 5, systemResetCallback);
    Watchdog_Start(&wdg);

    // Symulacja: karmienie co 3 ticki
    // TODO: Tick 3 razy, kick, tick 3 razy, kick
    // TODO: Tick 6 razy BEZ kick → powinien wywołać reset
    printf("\n");
}

// ============================================================================
// CZĘŚĆ 10: PYTANIA TEORETYCZNE (NAPISZ ODPOWIEDZI!)
// ============================================================================

/*
 * Pytanie 16: Czym jest DMA i dlaczego jest ważne w embedded?
 * Odpowiedź:
 */

/*
 * Pytanie 17: Czym jest watchdog timer i do czego służy?
 * Odpowiedź:
 */

/*
 * Pytanie 18: Jaka jest różnica między polling a interrupt?
 * Kiedy użyjesz każdego?
 * Odpowiedź:
 */

/*
 * Pytanie 19: Dlaczego w embedded unikamy malloc/free?
 * Odpowiedź:
 */

/*
 * Pytanie 20: Co to jest race condition? Podaj przykład w embedded.
 * Odpowiedź:
 */

// ============================================================================
// TESTY
// ============================================================================

void runAllTests(void) {
    printf("================================================\n");
    printf("FIRMWARE INTERN NORDIC - FINALNE ĆWICZENIA\n");
    printf("================================================\n\n");

    task2();
    task3();
    task4();
    task5();
    task7();
    task8();
    task9();
    task11();
    task12();
    task13();
    task14();
    task15();

    printf("================================================\n");
    printf("KONIEC - POWODZENIA NA ROZMOWIE! 🚀\n");
    printf("================================================\n");
}

int main(void) {
    runAllTests();
    return 0;
}
