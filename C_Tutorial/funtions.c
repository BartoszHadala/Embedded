#include <stdio.h>

// Definicja funkcji powinna być umieszczona na górze 
int add(int a, int b);
void greetingMorning();
void greetingEvening();
void greet(void (*func)()); // argumentem jest wskaźnik na funkcję, która nic nie zwraca i nie ma argumentów
int addNumbers(int a, int b);
void calculate(int (*callback)(int, int), int x, int y);

int main() {

    // wskaźnik na funkcję
    int (*ptr)(int a, int b) = add;
    printf("Wynik dodawnia 2 + 4 eq %d\n", ptr(2, 4));

    // Callback function jest funkcją przekazaną jako argument do innej funcji

    // przekazanie funkcji do innej funkcji jako argument - callback
    greet(greetingMorning);
    greet(greetingEvening);
    printf("Wynik addNumbers(5, 3): %d\n", addNumbers(5, 3));

    // Przykład użycia calculate z callbackiem
    calculate(addNumbers, 5, 3);

    return 0;
}

// Deklaracja funkcji powinna być umieszczona na dole
int add(int a, int b) {
    return a + b;
}

void greetingMorning() {
    printf("Good morning!\n");
}

void greetingEvening() {
    printf("Good morning!\n");
}

void greet(void (*func)()) {
    func();
}

int addNumbers(int a, int b) {
    return a + b;
}

void calculate(int (*callback)(int, int), int x, int y) {
    callback(x, y);
}