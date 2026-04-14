#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // Proces rezerwacji pamięci nazwany jest alokacją pamięci
    // Wyróżniamy pamięć statyczną i dynamiczną

    // Pamięć statyczna jest znana przed startem programu
    // Pamięć dynamiczna można ustawiać w czasie trwania systemu

    int * ptr1, * ptr2;
    ptr1 = malloc(sizeof(*ptr1));    
    ptr2 = calloc(1, sizeof(*ptr2)); // lepsza wersja umożliwia podanie ilości

    // Odczytywanie zalokowanej dynamicznej pamięci
    int * ptr = calloc(4, sizeof(int));
    *ptr = 2;
    ptr[1] = 4;

    printf("%d %d", ptr[0], ptr[1]);

    // Zalokowane miejsce w pamięci nie ma określonego typu
    int * ptr3 = malloc(4);
    char * ptr33 = (char *)ptr3;
    ptr3[0] = 1684234849; // 0x64636261
    printf("%d is %c %c %c %c", *ptr3, ptr33[0], ptr33[1], ptr33[2], ptr33[3]);
    // na tej podstawie stwierdzam, że PC używa little-endian

    // Relokowanie pamięci
    int * w1 = realloc(ptr1, 6 * sizeof(* ptr1));
    if (w1 == NULL) {
        printf("Failed. Unable to resize memory.");
    }

    free(ptr1);

    // Dobrą praktyką jest wskazanien a NULL po skończeniu korzystania ze wskaźnika, 
    // aby jego przyszłe zachowanie nie wpłynęło na program

    int * w;
    w = malloc(sizeof(*w));
    if (w == NULL) {
        printf("Unable to allocate memory");
        return 1;
    }
    *w = 20;
    printf("Integer value: %d\n", *w);
    free(w);
    w = NULL;

    // Alokowanie sturktur / tablica struktur

    typedef struct
    {
        char brand[50];
        int year;
    } Car;

    Car * cars = (Car *)malloc(3 * sizeof(Car));
    if ( cars == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    strcpy(cars[0].brand, "Honda");
    cars[0].year = 2020;
    strcpy(cars[1].brand, "BMW");
    cars[1].year = 2018;
    strcpy(cars[2].brand, "Volvo");
    cars[2].year = 2023;

    for (int i = 0; i < 3; i++) {
        printf("Brand: %s | Year: %d\n", cars[i].brand, cars[i].year);
    }

    free(cars);
    cars = NULL;

    return 0;
}