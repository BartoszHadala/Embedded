#include <stdio.h>
#include <stdbool.h>

int main() {

    int time = 16;
    bool isMorning = time < 16;
    bool isDay = time < 18;

    // I
    if (isMorning) {
        printf("Good morning.");
    } else if (isDay) {
        printf("Good day.");
    } else {
        printf("Good evening");
    }
    
    // II
    (time < 18) ? printf("Good day.") : printf("Good evening.");


    return 0;
}