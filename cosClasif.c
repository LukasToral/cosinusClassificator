#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define M 10
#define N 10

// Algoritmus pro vygenerovani nahodneho floatu ve funkci, pro lepsi citelnost kodu
float randomFloat (float min, float max);

// Funkce pro alokaci a naplněni 1D pole barev
char * allocate1Darray (int m);
void fill1Darray (int m, char **arr);

// Funkce pro alokaci a naplnění 2D float pole
float * allocate2DFloatArray (int m, int n);
void fill2DFloatArray (int m, int n, float **arr);

// Funkce pro aalokaci a naplnění 1D float pole
float * allocate1DFloatArray (int n);
float fill1DFloatArray (int n, float *arr);

// Vraci index s nejvetší cosínovou podobností
int cosine_similarity(float **arr2D, float *arr1D);

int main(void) {
    srand(time(NULL));

    // 2D float pole
    float** arr2Dfloat = allocate2DFloatArray(M, N);
    fill2DFloatArray(M, N, arr2Dfloat);

    // 1D float pole
    float* arr1Dfloat = allocate1DFloatArray(N);
    fill1DFloatArray(N, arr1Dfloat);

    // 1D pole barev
    char** arr = allocate1Darray(M);
    fill1Darray(M,arr);

    // výpis barvy podle vráceného indexu řádku s největší cosinovou podobností
    printf("%s\n", arr[cosine_similarity(arr2Dfloat, arr1Dfloat)]);

    return 0;
}

float randomFloat (float min, float max) {
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * ( max - min ); 
}

float * allocate1DFloatArray (int n) {
    float *arr = (float*) malloc (sizeof(float) * n);
    return arr;
}

float fill1DFloatArray (int n, float *arr) {
    float max = 100;
    float min = -100;
    for (int i = 0; i < n; i++) {
        arr[i] = randomFloat(min, max);
    }
}

float * allocate2DFloatArray (int m, int n) {
    float **arr = malloc(sizeof(float) * m);
    for (int i = 0; i < m; i++) {
        arr[i] = malloc (sizeof(float) * n);
    }

    return arr;
}

void fill2DFloatArray (int m, int n, float **arr) {
    float max = 100;
    float min = -100;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = randomFloat(min, max);
        }
    }
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

int cosine_similarity(float **arr2D, float *arr1D) { // 2D = M * N, 1D = N
    // Vytvoření pole pro uložení hodnot pro každý řádek
    float *similarity = (float*) malloc (sizeof(float) * M);
    int ITBS = 0; // index of the biggest similarity
    float dot = 0.0, denom_a = 0.0, denom_b = 0.0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            dot += arr2D[i][j] * arr1D[j];
            denom_a += arr2D[i][j] * arr2D[i][j];
            denom_b += arr1D[j] * arr1D[j];
            
        }
        similarity[i] = dot / (sqrt(denom_a) * sqrt(denom_b)) ;
    }
    // Najde největší podobnost a vrátí index řádku s největší podobností
    for (int s = 1; s < M; s++) {
        if (similarity[s] > similarity[ITBS]) {
            ITBS = s;
        }      
    }
    return ITBS;
}
