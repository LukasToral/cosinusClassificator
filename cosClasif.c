#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define M 10

// Alokace 1D pole
char * allocate1Darray (int m);
void fill1Darray (int m, char **arr);

int main(void) {
    srand(time(NULL));
    char** arr = allocate1Darray(M);
    fill1Darray(M,arr);

    // Kontrola barev :)
    for (int i = 0; i < M; i++) {
        printf("%s\n", arr[i]);
    }

    return 0;
}

char * allocate1Darray (int m) {
    char **arr;
    arr = (char**)malloc(m * sizeof(char**));
    for (int i = 0; i < m; i++)
        arr[i] = (char*) malloc((7+1) * sizeof(char)); // delka nejdelsi barvy - cervene (7) + 1
    return arr;
}

void fill1Darray (int m, char **arr) {
    int randomNumber;
    for (int i = 0; i < m; i++) {
        randomNumber = rand() % 5; // 0-4
        switch (randomNumber)
        {
        case 0:
            strcpy(arr[i], "cervena");
            break;
        case 1:
            strcpy(arr[i], "zelena");
            break;
        case 2:
            strcpy(arr[i], "modra");
            break;
        case 3:
            strcpy(arr[i], "bila");
            break;
        case 4:
            strcpy(arr[i], "cerna");
            break;
        default:
            break;
        }
    }
}
