#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    int * data;     // wskaźnik do pamięci na listę
    int numItems;   // mówi ile jest elementów listy
    int size;       // 
} List;

void addToList(List *myList, int item);

int main() {

    List myList;
    int amount;

    myList.numItems = 0;
    myList.size = 10;
    myList.data = malloc(myList.size * sizeof(int));

    if (myList.data == NULL) {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }

    amount = 44;
    for (int i = 0; i < amount; i++) {
        addToList(&myList, i + 1);
    }

    for (int i = 0; i < myList.numItems; i++) {
        printf("%d ", myList.data[i]);
    }

    free(myList.data);
    myList.data = NULL;

    return 0;
}

void addToList(List *myList, int item) {

}