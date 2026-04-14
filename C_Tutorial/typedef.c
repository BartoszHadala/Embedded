#include <stdio.h>

typedef float Temperature;

typedef struct {
    char brand[30];
    int year;
} Car;


int main() {

    // Typedef pozwala na stworzenie aliasu istniejącego typu.
    Temperature today = 25.5;
    Car auto1 = {"Ford", 1999};

    return 0;
}