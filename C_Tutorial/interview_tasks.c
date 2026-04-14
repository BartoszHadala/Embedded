/*
 * ============================================================================
 * FIRMWARE INTERN - ZESTAW ZADAŃ REKRUTACYJNYCH
 * ============================================================================
 * Rozwiąż zadania bez podglądania rozwiązań.
 * Skompiluj: gcc interview_tasks.c -o interview -lm
 * Uruchom: ./interview
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// ============================================================================
// CZĘŚĆ 1: OPERACJE BITOWE (bardzo częste na rozmowach!)
// ============================================================================

/*
 * Zadanie 1: Ustaw bit na pozycji n w rejestrze (bez zmiany innych bitów).
 * Przykład: setBit(0b00000000, 3) -> 0b00001000
 */
uint8_t setBit(uint8_t reg, uint8_t n) {
    // TODO: Zaimplementuj
    return reg | (1 << n);
}

/*
 * Zadanie 2: Wyczyść bit na pozycji n w rejestrze.
 * Przykład: clearBit(0b11111111, 3) -> 0b11110111
 */
uint8_t clearBit(uint8_t reg, uint8_t n) {
    // TODO: Zaimplementuj
    return reg &= ~(1 << n);
}

/*
 * Zadanie 3: Przełącz (toggle) bit na pozycji n.
 * Przykład: toggleBit(0b00001000, 3) -> 0b00000000
 */
uint8_t toggleBit(uint8_t reg, uint8_t n) {
    // TODO: Zaimplementuj
    return reg ^= (1 << n);
}

/*
 * Zadanie 4: Sprawdź, czy bit na pozycji n jest ustawiony.
 * Zwróć 1 jeśli tak, 0 jeśli nie.
 */
uint8_t checkBit(uint8_t reg, uint8_t n) {
    // TODO: Zaimplementuj
    if (reg & (1 << n)) return 1;
    else return 0;
}

/*
 * Zadanie 5: Policz liczbę ustawionych bitów (population count).
 * Przykład: countBits(0b10101010) -> 4
 */
uint8_t countBits(uint8_t reg) {
    // TODO: Zaimplementuj
    uint8_t count = 0;
    while (reg > 0) {
        count += (reg & 1);
        reg >>= 1;
    }
    return count;
}

/*
 * Zadanie 6: Odwróć kolejność bitów w bajcie.
 * Przykład: reverseBits(0b11000001) -> 0b10000011
 */
uint8_t reverseBits(uint8_t reg) {
    // TODO: Zaimplementuj
    return 0;
}

// ============================================================================
// CZĘŚĆ 2: WSKAŹNIKI I PAMIĘĆ
// ============================================================================

/*
 * Zadanie 7: Zamień wartości dwóch zmiennych używając wskaźników.
 */
void swap(int *a, int *b) {
    // TODO: Zaimplementuj
    int dummy = *a;
    *a = *b;
    *b = dummy;
}

/*
 * Zadanie 8: Znajdź maksymalną wartość w tablicy.
 * Zwróć wskaźnik do elementu maksymalnego.
 */
int* findMax(int *arr, int len) {
    // TODO: Zaimplementuj
    int maxVal = arr[0];
    int * index;
    for (int i = 1; i < len; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            index = &arr[i];
        }
    }
    return index;
}

/*
 * Zadanie 9: Odwróć tablicę w miejscu (in-place).
 */
void reverseArray(int *arr, int len) {
    // TODO: Zaimplementuj
    int * left = arr;
    int * right = arr + len - 1;
    for (int i = 0; i < len; i++) {
        *(left++) = *(right--);
    }
}

/*
 * Zadanie 10: Sprawdź endianness systemu.
 * Zwróć 1 dla little-endian, 0 dla big-endian.
 */
int checkEndianness(void) {
    // TODO: Zaimplementuj
    return 0;
}

// ============================================================================
// CZĘŚĆ 3: STRUKTURY I EMBEDDED
// ============================================================================

typedef struct {
    uint8_t id;
    uint16_t value;
    uint8_t status;
} SensorData;

/*
 * Zadanie 11: Wypełnij strukturę SensorData danymi.
 * Ustaw: id=1, value=1024, status=0x01
 */
void initSensor(SensorData *sensor) {
    // TODO: Zaimplementuj
}

/*
 * Zadanie 12: Skopiuj dane z jednej struktury do drugiej (deep copy).
 */
void copySensor(SensorData *dest, const SensorData *src) {
    // TODO: Zaimplementuj
}

// ============================================================================
// CZĘŚĆ 4: VOLATILE I REJESTRY (TYPOWE PYTANIA!)
// ============================================================================

/*
 * Zadanie 13: Symulacja odczytu rejestru sprzętowego.
 * Dlaczego używamy volatile? Napisz komentarz wyjaśniający.
 */
volatile uint32_t FAKE_REGISTER = 0x12345678;

uint32_t readRegister(volatile uint32_t *reg) {
    // TODO: Zaimplementuj odczyt rejestru
    // TODO: Napisz komentarz dlaczego volatile jest potrzebne
    return 0;
}

/*
 * Zadanie 14: Ustaw bity 4-7 rejestru na wartość 0xA, nie zmieniając innych.
 * Przykład: setNibble(0x00, 0xA) -> 0xA0
 *           setNibble(0xFF, 0xA) -> 0xAF
 */
uint8_t setNibble(uint8_t reg, uint8_t value) {
    // TODO: Zaimplementuj
    return 0;
}

// ============================================================================
// CZĘŚĆ 5: RING BUFFER (BARDZO WAŻNE W EMBEDDED!)
// ============================================================================

#define RING_BUFFER_SIZE 8

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    uint8_t head;  // Indeks zapisu
    uint8_t tail;  // Indeks odczytu
    uint8_t count; // Liczba elementów
} RingBuffer;

/*
 * Zadanie 15: Zainicjalizuj ring buffer.
 */
void ringBuffer_init(RingBuffer *rb) {
    // TODO: Zaimplementuj
}

/*
 * Zadanie 16: Dodaj element do ring buffera.
 * Zwróć 1 jeśli sukces, 0 jeśli bufor pełny.
 */
uint8_t ringBuffer_put(RingBuffer *rb, uint8_t data) {
    // TODO: Zaimplementuj
    return 0;
}

/*
 * Zadanie 17: Pobierz element z ring buffera.
 * Zwróć 1 jeśli sukces (dane w *data), 0 jeśli bufor pusty.
 */
uint8_t ringBuffer_get(RingBuffer *rb, uint8_t *data) {
    // TODO: Zaimplementuj
    return 0;
}

/*
 * Zadanie 18: Sprawdź, czy ring buffer jest pusty.
 */
uint8_t ringBuffer_isEmpty(RingBuffer *rb) {
    // TODO: Zaimplementuj
    return 1;
}

/*
 * Zadanie 19: Sprawdź, czy ring buffer jest pełny.
 */
uint8_t ringBuffer_isFull(RingBuffer *rb) {
    // TODO: Zaimplementuj
    return 0;
}

// ============================================================================
// CZĘŚĆ 6: PARSOWANIE DANYCH (UART/KOMUNIKACJA)
// ============================================================================

/*
 * Zadanie 20: Parsuj pakiet UART.
 * Format pakietu: [START=0xAA] [LEN] [DATA...] [CHECKSUM] [END=0xBB]
 * Checksum = XOR wszystkich bajtów DATA.
 * Zwróć 1 jeśli pakiet poprawny, 0 jeśli błędny.
 */
uint8_t parsePacket(uint8_t *buffer, uint8_t bufLen, uint8_t *dataOut, uint8_t *dataLen) {
    // TODO: Zaimplementuj
    return 0;
}

/*
 * Zadanie 21: Oblicz prostą sumę kontrolną (XOR wszystkich bajtów).
 */
uint8_t calculateChecksum(uint8_t *data, uint8_t len) {
    // TODO: Zaimplementuj
    return 0;
}

// ============================================================================
// CZĘŚĆ 7: LINKED LIST
// ============================================================================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/*
 * Zadanie 22: Dodaj element na początek listy.
 * Zwróć nowy head.
 */
Node* list_prepend(Node *head, int data) {
    // TODO: Zaimplementuj
    return NULL;
}

/*
 * Zadanie 23: Znajdź element w liście.
 * Zwróć wskaźnik do węzła lub NULL.
 */
Node* list_find(Node *head, int data) {
    // TODO: Zaimplementuj
    return NULL;
}

/*
 * Zadanie 24: Zwolnij całą listę.
 */
void list_free(Node *head) {
    // TODO: Zaimplementuj
}

/*
 * Zadanie 25: Odwróć listę jednokierunkową.
 * Zwróć nowy head.
 */
Node* list_reverse(Node *head) {
    // TODO: Zaimplementuj
    return NULL;
}

// ============================================================================
// CZĘŚĆ 8: PYTANIA TEORETYCZNE (napisz odpowiedzi w komentarzach)
// ============================================================================

/*
 * Pytanie 26: Jaka jest różnica między stack a heap?
 * Odpowiedź: 
 */

/*
 * Pytanie 27: Co to jest memory leak i jak go unikać?
 * Odpowiedź: 
 */

/*
 * Pytanie 28: Kiedy używamy volatile?
 * Odpowiedź: 
 */

/*
 * Pytanie 29: Co to jest race condition?
 * Odpowiedź: 
 */

/*
 * Pytanie 30: Jaka jest różnica między:
 *   const int *p
 *   int *const p
 *   const int *const p
 * Odpowiedź: 
 */

// ============================================================================
// TESTY - odkomentuj po zaimplementowaniu
// ============================================================================

void runTests() {
    printf("=== TESTY OPERACJI BITOWYCH ===\n");
    
    // Test setBit
    printf("setBit(0x00, 3) = 0x%02X (oczekiwane: 0x08): %s\n", 
           setBit(0x00, 3), setBit(0x00, 3) == 0x08 ? "PASS" : "FAIL");
    
    // Test clearBit
    printf("clearBit(0xFF, 3) = 0x%02X (oczekiwane: 0xF7): %s\n",
           clearBit(0xFF, 3), clearBit(0xFF, 3) == 0xF7 ? "PASS" : "FAIL");
    
    // Test toggleBit
    printf("toggleBit(0x08, 3) = 0x%02X (oczekiwane: 0x00): %s\n",
           toggleBit(0x08, 3), toggleBit(0x08, 3) == 0x00 ? "PASS" : "FAIL");
    
    // Test checkBit
    printf("checkBit(0x08, 3) = %d (oczekiwane: 1): %s\n",
           checkBit(0x08, 3), checkBit(0x08, 3) == 1 ? "PASS" : "FAIL");
    
    // Test countBits
    printf("countBits(0xAA) = %d (oczekiwane: 4): %s\n",
           countBits(0xAA), countBits(0xAA) == 4 ? "PASS" : "FAIL");
    
    // Test reverseBits
    printf("reverseBits(0xC1) = 0x%02X (oczekiwane: 0x83): %s\n",
           reverseBits(0xC1), reverseBits(0xC1) == 0x83 ? "PASS" : "FAIL");
    
    printf("\n=== TESTY WSKAŹNIKÓW ===\n");
    
    // Test swap
    int a = 5, b = 10;
    swap(&a, &b);
    printf("swap(5, 10) -> a=%d, b=%d: %s\n", a, b, (a == 10 && b == 5) ? "PASS" : "FAIL");
    
    // Test findMax
    int arr[] = {3, 7, 2, 9, 5};
    int *max = findMax(arr, 5);
    printf("findMax([3,7,2,9,5]) = %d (oczekiwane: 9): %s\n",
           max ? *max : -1, (max && *max == 9) ? "PASS" : "FAIL");
    
    // Test reverseArray
    int arr2[] = {1, 2, 3, 4, 5};
    reverseArray(arr2, 5);
    printf("reverseArray([1,2,3,4,5]) = [%d,%d,%d,%d,%d]: %s\n",
           arr2[0], arr2[1], arr2[2], arr2[3], arr2[4],
           (arr2[0]==5 && arr2[4]==1) ? "PASS" : "FAIL");
    
    // Test endianness
    printf("checkEndianness() = %s\n", checkEndianness() ? "Little-endian" : "Big-endian");
    
    printf("\n=== TESTY RING BUFFER ===\n");
    
    RingBuffer rb;
    ringBuffer_init(&rb);
    printf("isEmpty after init: %s\n", ringBuffer_isEmpty(&rb) ? "PASS" : "FAIL");
    
    ringBuffer_put(&rb, 42);
    printf("isEmpty after put: %s\n", !ringBuffer_isEmpty(&rb) ? "PASS" : "FAIL");
    
    uint8_t data;
    ringBuffer_get(&rb, &data);
    printf("get() = %d (oczekiwane: 42): %s\n", data, data == 42 ? "PASS" : "FAIL");
    printf("isEmpty after get: %s\n", ringBuffer_isEmpty(&rb) ? "PASS" : "FAIL");
    
    printf("\n=== TESTY CHECKSUM ===\n");
    uint8_t testData[] = {0x01, 0x02, 0x03};
    printf("calculateChecksum([0x01,0x02,0x03]) = 0x%02X (oczekiwane: 0x00): %s\n",
           calculateChecksum(testData, 3), calculateChecksum(testData, 3) == 0x00 ? "PASS" : "FAIL");
    
    printf("\n=== KONIEC TESTÓW ===\n");
}

int main() {
    printf("FIRMWARE INTERN - ZADANIA REKRUTACYJNE\n");
    printf("=======================================\n\n");
    
    // Odkomentuj po zaimplementowaniu zadań:
    runTests();
    
    printf("Zaimplementuj funkcje i odkomentuj runTests() w main().\n");
    printf("Powodzenia na rozmowie! 🚀\n");
    
    return 0;
}
