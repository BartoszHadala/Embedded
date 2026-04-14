#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Dla typów uint8_t itp., często używanych w firmware

// Symulacja typów dla Nordic (np. rejestry)
typedef struct {
    uint8_t status;
    uint16_t data;
} NordicRegister;

// PROSTE ZADANIA

// Zadanie 1 (Proste): Napisz funkcję, która sumuje elementy tablicy int.
// Funkcja powinna przyjmować wskaźnik do tablicy i jej długość, zwracać sumę.
int sum_array(int *arr, int len) {
    // TODO: Zaimplementuj
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += *(arr + i);
    }
    return sum;
}

// Zadanie 2 (Proste): Napisz funkcję, która konwertuje string na liczbę całkowitą (bez użycia atoi).
// Funkcja powinna przyjmować string i zwracać int. Obsłuż znaki '+' i '-'.
int string_to_int(const char *str) {
    int result = 0;
    int sign = 1;  // Domyślnie dodatnie
    if (*str == '-') {
        sign = -1;
        str++;  // Przesuń wskaźnik
    } else if (*str == '+') {
        str++;  // Przesuń wskaźnik
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

// Zadanie 3 (Proste): Napisz funkcję, która sprawdza, czy liczba jest parzysta.
// Funkcja powinna przyjmować int i zwracać 1 jeśli parzysta, 0 jeśli nie.
int is_even(int num) {
    // TODO: Zaimplementuj
    return num % 2 == 0 ? 1 : 0;
}

// Zadanie 4 (Proste): Napisz funkcję, która kopiuje string (bez użycia strcpy).
// Funkcja powinna przyjmować źródło i cel (wskaźniki char), kopiować do '\0'.
void copy_string(char *dest, const char *src) {
    // TODO: Zaimplementuj
    while (*src != '\0')
    {
        *(dest++) = *(src++);
    }
    
}

// TRUDNE ZADANIA

// Zadanie 5 (Trudne): Napisz funkcję sortującą tablicę int metodą bubble sort.
// Funkcja powinna przyjmować wskaźnik do tablicy i długość, sortować w miejscu.
void bubble_sort(int *arr, int len) {
    // TODO: Zaimplementuj
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (arr[j] > arr[j + 1]) {
                int dumpy = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = dumpy;
            }
        }
    }
}

// Zadanie 6 (Trudne): Napisz funkcję parsującą dane z UART (symulacja).
// Funkcja powinna przyjmować bufor uint8_t (dane odebrane), długość, i wyszukiwać pakiet zaczynający się od 0xAA, kończący 0xBB.
// Zwracać wskaźnik do początku pakietu lub NULL jeśli nie znaleziono.
uint8_t* parse_uart_packet(uint8_t *buffer, int len) {
    // TODO: Zaimplementuj
    for (int i = 0; i < len - 1; i++) {
        if (*(buffer + i) == 0xAA) {
            uint8_t * start = buffer + i; 
            for (int j = i + 1; j < len; j++) {
                if (*(buffer + j) == 0xBB) {
                    return start;
                }
            }
        }
    }
    return NULL;
}

// Zadanie 7 (Trudne): Napisz funkcję zarządzającą pamięcią dla struktury NordicRegister.
// Funkcja powinna alokować tablicę struktur, wypełniać przykładowymi danymi, wypisywać i zwalniać pamięć.
// Symuluje zarządzanie rejestrami sprzętowymi.
void manage_registers(int count) {
    
    // TODO: Zaimplementuj alokację, wypełnienie, wypisanie, zwolnienie
}

// Zadanie 8 (Trudne): Napisz funkcję obliczającą prosty CRC (np. CRC-8) dla bufora danych.
// Funkcja powinna przyjmować bufor uint8_t i długość, zwracać uint8_t CRC.
// Użyj wielomianu 0x07 (standardowy dla wielu protokołów).
uint8_t calculate_crc(uint8_t *data, int len) {
    // TODO: Zaimplementuj
    return 0;
}

// Zadanie 9 (Trudne): Napisz funkcję symulującą obsługę timera (interrupt).
// Funkcja powinna przyjmować wskaźnik do zmiennej licznika (int*), zmniejszać ją o 1, jeśli >0.
// Jeśli osiągnie 0, wypisać "Timer expired". Symuluje timer w firmware.
void handle_timer_interrupt(int *timer_counter) {
    // TODO: Zaimplementuj
}

// Zadanie 10 (Trudne): Napisz funkcję optymalizującą zużycie energii (symulacja sleep mode).
// Funkcja powinna przyjmować tablicę uint8_t (dane do przetworzenia), długość, i przetwarzać tylko co drugi element.
// Zwracać sumę przetworzonych elementów. Symuluje oszczędzanie energii w embedded.
int process_energy_efficient(uint8_t *data, int len) {
    // TODO: Zaimplementuj
    return 0;
}

// Główna funkcja do testowania (odkomentuj wywołania)
int main() {
    // Testy prostych zadań
    int arr[] = {1, 2, 3, 4};
    printf("Suma: %d\n", sum_array(arr, 4));

    printf("Konwersja '123': %d\n", string_to_int("123"));

    printf("Czy 4 parzyste: %d\n", is_even(4));

    char dest[20];
    copy_string(dest, "Hello");
    printf("Skopiowany: %s\n", dest);

    // Testy trudnych zadań
    int sort_arr[] = {4, 2, 1, 3};
    bubble_sort(sort_arr, 4);
    printf("Posortowane: ");
    for(int i=0; i<4; i++) printf("%d ", sort_arr[i]);
    printf("\n");

    uint8_t buffer[] = {0x00, 0xAA, 0x01, 0x02, 0xBB, 0x03};
    uint8_t *packet = parse_uart_packet(buffer, 6);
    if(packet) printf("Pakiet znaleziony\n");

    manage_registers(3);

    // uint8_t crc_data[] = {0x01, 0x02, 0x03};
    // printf("CRC: %d\n", calculate_crc(crc_data, 3));

    // int timer = 5;
    // handle_timer_interrupt(&timer);
    // printf("Timer: %d\n", timer);

    // uint8_t energy_data[] = {1, 2, 3, 4, 5, 6};
    // printf("Energia: %d\n", process_energy_efficient(energy_data, 6));

    return 0;
}
