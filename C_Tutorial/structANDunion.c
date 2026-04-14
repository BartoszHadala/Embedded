#include <stdio.h>
#include <string.h>

struct myStructure {
    int myNum;
    char myLetter;
    char myString[30];
};

    struct Owner
    {
        char firstName[30];
        char lastName[30];
    };

    struct Car
    {
        char brand[30];
        int year;
        struct Owner owner;
    };

void updateYear(struct Car *c, int y);

int main() {

    // Struktura to sposób grupowania powiązanych danych w jednym miejscu
    // W przeciwieństwie do tablic może zawierać różne typy danych

    struct myStructure s1;
    s1.myNum = 13;
    s1.myLetter = 'B';
    strcpy(s1.myString, "Some text"); // <- w przypadku C, do stringów trzeba użyć strcpy

    // Prostrzy sposób przypisania
    struct myStructure s2 = {12, 'C', "Some text2"};
    
    printf("myNum eq %d\n", s1.myNum);
    printf("myLetter eq %c\n", s1.myLetter);
    printf("myString eq %s\n", s1.myString);

    // Kopiowanie stuktur
    struct myStructure s3;
    s3 = s2;

    // Struktury zagnieżdżone i wskaźniki

    // * Uniknięcie kopiowania dużych danych
    // * Możliwość zmiany wartości wewnątrz funkcji
    // * Pozwala na tworzenie struktury dynamicznie zarządzanej w pamięci

    struct Owner person = {"John", "Doe"};
    struct Car car1 = {"Toyota", 2018, person};

    updateYear(&car1, 2022);

    struct Car * ptr = &car1;

    // Dereferencja do pola strutury wskazywanej przez wskaźnik korzysta z -> zamiast .
    printf("Car: %s (%d)\n", car1.brand, ptr->year);
    printf("Owner: %s %s\n", car1.owner.firstName, car1.owner.lastName);  

    // Padding oznacza, że kompilator czasami dodaje puste przestrzenie w strukturze w celu zachowania
    // popranwości ułożenia danych i przyśpieszenia działania, dlatego ważne jest ułożenie
    // danych w strukturze!

    // Union

    // W przypadku union wszystkie jej elementy dzielą tą samą pamięć
    // Można korzystać tylko z jednej jej wartości w jednym momencie

    union myUnion
    {
        int myNum;
        char myLetter;
        char myString[30];
    };

    union myUnion u1;
    u1.myNum = 90; // -> union wskazuje na int
    u1.myLetter = 90; // -> union wskazuje na char

    // Rozmiar union to rozmiar największego elementu

    return 0;
}

void updateYear(struct Car *c, int y) {
    c->year = y;
}