#include <stdio.h>
#include <stdlib.h> // Dla malloc i free

// ZADANIE 6
int mullTwo(int * val);

// ZADANIE 8
int addTwo(int val1, int val2);

int main() {
    // Zadanie 1: Utwórz zmienną całkowitą, wskaźnik do niej, wypisz wartość i adres.
    printf("ZADANIE 1\n");
    int myNum1 = 10;
    int * ptr1 = &myNum1;
    printf("Wartośc zmiennej myNum1 : %d\n", myNum1);
    printf("Wartośc adresu pamięci myNum1 : %p\n", ptr1);

    // Zadanie 2: Użyj dereferencji, aby zmienić wartość zmiennej przez wskaźnik.
    printf("\nZADANIE 2\n");
    *ptr1 = 15;
    printf("Wartośc zmienionej zmiennej myNum1 : %d\n", myNum1);

    // Zadanie 3: Utwórz tablicę int, wskaźnik do pierwszego elementu, iteruj po tablicy używając arytmetyki wskaźników.
    printf("\nZADANIE 3\n");
    int myArr3[] = {1, 2, 3, 4, 5};
    int * ptr3 = myArr3;
    int len3 = sizeof(myArr3) / sizeof(myArr3[0]);
    for (int i = 0; i < len3; i++) {
        printf("myArr3[%d] = %d\n", i, *(ptr3 + i));
    }

    // Zadanie 4: Zmień drugi element tablicy przez wskaźnik.
    printf("\nZADANIE 4\n");
    *(ptr3 + 1) = 99;
    printf("Zmieniony drugi element = %d\n", myArr3[1]);

    // Zadanie 5: Utwórz wskaźnik na wskaźnik (double pointer), wypisz wartość.
    printf("\nZADANIE 5\n");
    int ** ptr5 = &ptr1;
    printf("Wartość wskazująca przez wskaźnik na wskaźnik : %d\n", **ptr5);

    // Zadanie 6: Napisz funkcję, która przyjmuje wskaźnik do int i podwaja jego wartość.
    printf("\nZADANIE 6\n");
    int myNum6 = 5;
    printf("Multiplied 5 * 2 = %d\n" , mullTwo(&myNum6));

    // Zadanie 7: Użyj malloc do alokacji tablicy int o rozmiarze 10, wypełnij ją wartościami, wypisz, zwolnij pamięć.
    printf("\nZADANIE 7\n");
    int * ptr7 = (int *)malloc(10 * sizeof(int));

    if (ptr7 == NULL) {
        printf("Błąd alokacji\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        *(ptr7 + i) = i * 2;
    }

    for (int i = 0; i < 10; i++) {
        printf("Address %p | value %d\n", ptr7 + i, *(ptr7 + i));
    }

    free(ptr7);

    // Zadanie 8: Utwórz wskaźnik do funkcji, która dodaje dwa int.
    printf("\nZADANIE 8\n");
    int (*fun_ptr8)(int, int) = addTwo;
    printf("Dodanie 2 + 4 = %d\n", fun_ptr8(2, 4));

    // Zadanie 9: Użyj wskaźnika void do przechowywania adresu różnych typów (np. int i char).
    printf("\nZADANIE 9\n");
    int char_void9 = 'C';
    int int_void9 = 99;

    void * ptr9;
    ptr9 = &char_void9;
    printf("%c\n", *(char *)ptr9);
    ptr9 = &int_void9;
    printf("%d\n", *(int *)ptr9);

    // Zadanie 10: Symuluj błąd z NULL pointer (sprawdź przed dereferencją).
    printf("\nZADANIE 10\n");
    int * null_ptr10 = NULL;

    if (null_ptr10 == NULL) {
        printf("Wskaźnik jest NULLem\n");
    } else {
        printf("Wartość: %d\n", *null_ptr10);
    }

    return 0;
}

int mullTwo(int * val) {
        return (*val) * 2;
};
int addTwo(int val1, int val2) {
        return val1 + val2;
};