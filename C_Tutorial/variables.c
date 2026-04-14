#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {

    // Deklarując zmienną musimy podać typ i nazwę.
    int myNum = 10;            /* 2 lub 4 bytes */ 
    float myFloat = 10.25;     /* 4 bytes */
    float myDouble = 3e8;    /* 8 bytes */
    char myChar = 'B';         /* 1 bytes */
    char myString[] = "Ja";    

    // Zmienne mogą zawierać kwalifikator znaku i długości: unsigned/signed short/long

    // Dodanie zmiennej const spowoduje, że nie będzie możliwości zmiany wartości zmiennej
    const int notChangable = 5;

    printf("%d\n", myNum);
    printf("%.2f\n", myFloat);  // notacja z kropką pozwala wskazać precyzję po przecinku
    printf("%lf\n", myDouble);
    printf("%c\n", myChar);
    printf("%s\n", myString);


    // Można deklarować wiele zmiennych tego samego typu jednocześnie
    int a, b, c;
    a = b = c = 50;

    // Sizeof pozwala sprawdzić przechowywany rozmiar w pamięci,
    // %zu - przeznaczone do zmiennej typu size_t
    printf("%zu\n", sizeof(myNum));

    // Write length here
    int length = 2;
    // Write width here
    int width = 4;
    // Write area here (length * width)
    int area = length * width;
    // Print area here
    printf("Area is eq %d\n", area);


    // Jawna konwersja typów:
    int num1 = 5;
    int num2 = 2;
    float sum = (float) num1 / num2; // -> 2.500000

    // Aby korzystać z zmiennych typu bool należy zaimplementować bibliotekę <stdbool.h>
    bool isProgrammingFun = true;

    // Tablice
    int myTab[] = {25, 50, 75, 100}; // sizeof -> 4 elementy * 4 bajty
    int myTab2[2];
    myTab2[0] = 25; myTab2[1] = 50;

    size_t myTabLen = sizeof(myTab) / sizeof(myTab[0]);
    printf("Długość tablicy myTab wynosi %zu\n", myTabLen);

    for (int i = 0; i < myTabLen; i++) {
        printf("%d ",myTab[i]);
    }

    // Znalezenie najmniejszej wartości z tablicy
    int ages[] = {20, 22, 18, 35, 48, 26, 87, 70};
    size_t agesLen = sizeof(ages) / sizeof(ages[0]);
    int lowestVal = ages[0];
    for (int i = 1; i < agesLen; i++) {
        if (ages[i] < lowestVal) {
            lowestVal = ages[i];
        }
    }
    printf("\nLowest val eq %d\n", lowestVal);

    // Praca ze stringami wymaga dodania biblioteki <string.h>
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("%zu\n", strlen(alphabet)); // 26 -> nie uwzlędni /'0'
    printf("%zu\n", sizeof(alphabet)); // 27 -> uwzględni /'0'

    char str1[20] = "Hello ";
    char str2[] = "World!";
    strcat(str1, str2);     // Konkatynacja stringów
    printf("%s\n", str1);

    char str11[20] = "Hello ";
    char str22[20];
    strcpy(str22, str11);     // Kopiowanie stringów
    printf("%s\n", str22);

    char str111[20] = "Hello ";
    char str222[20] = "Hello ";
    printf("%d\n" ,strcmp(str222, str111));     // Kopiowanie stringów


    return 0;
}