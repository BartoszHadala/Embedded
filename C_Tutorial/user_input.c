#include <stdio.h>

int main() {

    int myNum;
    printf("Type a number: ");
    scanf("%d", &myNum);
    getchar(); // Consume the newline left by scanf
    printf("Your number eq %d\n", myNum);

    char firstName[30];
    printf("Type a first name: ");
    scanf("%s", firstName); // <-- zablica jest sama w sobie wskaźnikie, nie trzeba przekazywać przez referencję
    getchar(); // Consume the newline left by scanf
    printf("Your first name eq %s\n", firstName);

    char fullName[30];
    printf("Type your full name: ");
    fgets(fullName, sizeof(fullName), stdin);
    printf("Hello %s\n", fullName);
}