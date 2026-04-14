#include <stdio.h>

int main() {

    // Wskaźnik to zmienna, która przechowuje adrs pamięci innej zmiennej

    // Jeżeli wskazujemy na int to przesuwamy się o 4 bajty, w przypadku char przesywany się o 1 bajt

    int myAge = 22;
    int * ptr = &myAge;

    printf("Value: %d\n", myAge);
    printf("Memory addr: %p\n", ptr);
    printf("Dereference: %d\n", *ptr);

    // Wypisanie pamięci adresów tablicy
    int myNums[] = {1, 2, 3, 4};
    size_t len = sizeof(myNums) / sizeof(myNums[0]);
    for (int i = 0; i < len; i++) {
        printf("Mem addr of %d : %p\n", myNums[i], &myNums[i]); // -> zwiększa się o 4 bajty
    }

    // Iteracja po elementach tablicy za pomocą wskaźników
    int * ptr2 = myNums;
    for (int i = 0; i < len; i++) {
        printf("%d:", *(ptr2 + i));
    }
    printf("\n");

    // Zmiana elementu tablicy za pomocą wskaźnika
    *(ptr + 1) = 10;

    // Wskaźnik na wskaźnik
    int myNum3 = 10;        // val
    int * ptr3 = &myNum3;   // ptr to val
    int ** pptr3 = &ptr3;   // ptr to ptr

    printf("myNum = %d\n", myNum3);
    printf("*ptr = %d\n", *ptr3);
    printf("**pptr = %d\n", **pptr3);

    return 0;
}