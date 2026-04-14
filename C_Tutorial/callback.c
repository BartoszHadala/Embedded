#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int execute(int a, int b, int(*callback)(int, int));

int main() {

    // Jak zadelkarować wskaźnik funkcyjny?
        // typ_wartości_zwracanej_przez_funkcję (nazwa_wskaźnika_funkcyjnego) (typ_argumentu_1, typ_argumentu_2, ...)
        int a = 2, b = 4;
        printf("Wezwanie add daje wynik: %d\n", execute(a, b, add));
        printf("Wezwanie sub daje wynik: %d\n", execute(a, b, sub));
        printf("Wezwanie mul daje wynik: %d\n", execute(a, b, mul));

    return 0;
}

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int execute(int a, int b, int(*callback)(int, int)) {
    if (callback == NULL) {
        return 0;
    } else {
        return callback(a, b);
    }
}
    

