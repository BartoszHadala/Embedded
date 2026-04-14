#include <stdio.h>

int main() {

    // Po stworzeniu zmiennej i przypisaniu jej dotaje ona swoje miejsce w pamięci komputera
    // Odwołanie się do miejsca w pamięci odbywa się poprzez referencję &
    int myAge = 43;
    printf("%p\n", &myAge);

    return 0;
}