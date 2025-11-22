#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

extern void asm_kernel(float* x1, float* x2, float* y1, float* y2, float* z, int n);

void c_kernel(float* x1, float* x2, float* y1, float* y2, float* z, int n) {
    for (int i = 0; i < n; i++) {
        float dx = x2[i] - x1[i];
        float dy = y2[i] - y1[i];
        z[i] = sqrtf(dx * dx + dy * dy);
    }
}

int main(int argc, char* argv[]) {

    int vectorSize;

    printf("Enter the vector size (number of elements per vector): ");
    scanf_s("%d", &vectorSize);
    vectorSize = vectorSize * 4; 

    printf("Total vector size = %d\n", vectorSize);

    float* xOne = malloc(vectorSize * sizeof(float));
    float* yOne = malloc(vectorSize * sizeof(float));
    float* xTwo = malloc(vectorSize * sizeof(float));
    float* yTwo = malloc(vectorSize * sizeof(float));
    float* zC = malloc(vectorSize * sizeof(float));
    float* zASM = malloc(vectorSize * sizeof(float));

 
    printf("\nenter the vector elements.\n");
    for (int i = 0; i < vectorSize; i++) {
        printf("\nElement %d:\n", i + 1);

        printf("X1[%d] = ", i + 1);
        scanf_s("%f", &xOne[i]);

        printf("X2[%d] = ", i + 1);
        scanf_s("%f", &xTwo[i]);

        printf("Y1[%d] = ", i + 1);
        scanf_s("%f", &yOne[i]);

        printf("Y2[%d] = ", i + 1);
        scanf_s("%f", &yTwo[i]);
    }


    clock_t beginC = clock();

    c_kernel(xOne, xTwo, yOne, yTwo, zC, vectorSize);

    clock_t endC = clock();
    float timeC = (float)(endC - beginC) / CLOCKS_PER_SEC;


    printf("\nC Kernel Z[0..9]: ");
    for (int i = 0; i < 10 && i < vectorSize; i++) printf("%.2f, ", zC[i]);
    printf("\nC Time: %f seconds\n", timeC);

    clock_t beginASM = clock();

    asm_kernel(xOne, xTwo, yOne, yTwo, zASM, vectorSize);

    clock_t endASM = clock();
    float timeASM = (float)(endASM - beginASM) / CLOCKS_PER_SEC;

    printf("\nASM Kernel Z[0..9]: ");
    for (int i = 0; i < 10 && i < vectorSize; i++) printf("%.2f, ", zASM[i]);
    printf("\nASM Time: %f seconds\n", timeASM);

    int correct = 1;
    for (int i = 0; i < vectorSize; i++) {
        if (fabs(zC[i] - zASM[i]) > 0.0001f) {
            correct = 0;
            break;
        }
    }

    if (correct)
        printf("\nASM kernel output is CORRECT.\n");
    else
        printf("\nASM kernel output is WRONG.\n");


    free(xOne);
    free(xTwo);
    free(yOne);
    free(yTwo);
    free(zC);
    free(zASM);

    return 0;
}
