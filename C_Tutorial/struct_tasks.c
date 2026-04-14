#include <stdio.h>
#include <string.h>
#include <stdint.h> // Dla typów embedded (uint8_t itp.)

// Symulacja typów dla embedded
typedef struct {
    uint8_t id;
    uint16_t value;
} SensorData;

typedef struct {
    uint32_t address;
    uint8_t data[4];
} Register;

// PROSTE ZADANIA

// Zadanie 1 (Proste): Zdefiniuj strukturę reprezentującą punkt 2D (x, y jako int).
// Utwórz zmienną, zainicjalizuj i wypisz współrzędne.
// struct Point { int x, y; };
// struct Point p = {10, 20};
// printf("Point: (%d, %d)\n", p.x, p.y);

// Zadanie 2 (Proste): Dodaj do struktury Point pole char name[20].
// Zainicjalizuj strukturę i użyj strcpy do ustawienia nazwy.
// struct Point { int x, y; char name[20]; };
// struct Point p = {10, 20, ""};
// strcpy(p.name, "Origin");
// printf("Point %s: (%d, %d)\n", p.name, p.x, p.y);

// Zadanie 3 (Proste): Napisz funkcję, która przyjmuje wskaźnik do Point i zwiększa x o 1.
// void incrementX(struct Point *p) { p->x += 1; }
// struct Point p = {5, 10};
// incrementX(&p);
// printf("New x: %d\n", p.x);

// TRUDNE ZADANIA

// Zadanie 4 (Trudne): Zdefiniuj strukturę Device z polem SensorData i uint8_t status.
// Utwórz tablicę 3 urządzeń, zainicjalizuj i wypisz dane.
// struct Device { SensorData sensor; uint8_t status; };
// struct Device devices[3] = {{{1, 100}, 1}, {{2, 200}, 0}, {{3, 300}, 1}};
// for(int i=0; i<3; i++) printf("Device %d: ID=%d, Value=%d, Status=%d\n", i, devices[i].sensor.id, devices[i].sensor.value, devices[i].status);

// Zadanie 5 (Trudne): Napisz funkcję parsującą dane z UART do struktury Packet (uint8_t start, uint8_t len, uint8_t data[10]).
// Funkcja przyjmuje bufor uint8_t* i len, szuka pakietu zaczynającego się od 0xAA, len jako następny bajt, dane jako kolejne.
// Zwraca wypełnioną strukturę lub pustą jeśli błąd.
// struct Packet { uint8_t start; uint8_t len; uint8_t data[10]; };
// struct Packet parsePacket(uint8_t *buffer, int buf_len) { /* Szukaj 0xAA, len, dane */ }

// Zadanie 6 (Trudne): Zaimplementuj strukturę Register z polem uint32_t address i uint8_t data[4].
// Napisz funkcję writeRegister, która przyjmuje wskaźnik do Register i uint32_t value, zapisuje value jako 4 bajty do data (little-endian).
// void writeRegister(Register *reg, uint32_t value) { /* Rozłóż value na bajty */ }

// Zadanie 7 (Trudne): Utwórz strukturę Config z polami uint8_t mode, uint16_t timeout, char name[16].
// Napisz funkcję saveConfig, która kopiuje dane z jednej Config do drugiej (deep copy dla stringa).
// void saveConfig(Config *dest, const Config *src) { *dest = *src; strcpy(dest->name, src->name); }

// Zadanie 8 (Trudne): Symuluj listę urządzeń: struktura Node { Device device; Node *next; }.
// Napisz funkcję addDevice, która dodaje nowy węzeł na koniec listy (alokacja malloc).
// void addDevice(Node **head, Device d) { /* Znajdź koniec, malloc nowy Node, dodaj */ }

// Zadanie 9 (Trudne): Dla embedded – struktura Timer { uint32_t period; void (*callback)(void); }.
// Napisz funkcję startTimer, która symuluje timer: jeśli period > 0, wywołaj callback.
// void startTimer(Timer *t) { if(t->period > 0) t->callback(); }

// Zadanie 10 (Trudne): Zdefiniuj union DataUnion { uint32_t u32; uint16_t u16[2]; uint8_t u8[4]; }.
// Napisz funkcję, która ustawia u32 i wypisuje jako u8 (symulacja dostępu do rejestrów).
// void setAndPrint(DataUnion *d, uint32_t val) { d->u32 = val; for(int i=0; i<4; i++) printf("%02X ", d->u8[i]); }

// Główna funkcja do testowania
int main() {
    // Odkomentuj testy dla zadań
    // np. struct Point p = {1, 2};
    // printf("(%d, %d)\n", p.x, p.y);

    return 0;
}