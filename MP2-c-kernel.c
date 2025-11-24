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

    printf("Enter the vector size: ");
    scanf_s("%d", &vectorSize);

    float* xOne = malloc(vectorSize * sizeof(float));
    float* yOne = malloc(vectorSize * sizeof(float));
    float* xTwo = malloc(vectorSize * sizeof(float));
    float* yTwo = malloc(vectorSize * sizeof(float));
    float* zC = malloc(vectorSize * sizeof(float));
    float* zASM = malloc(vectorSize * sizeof(float));

    float cAvg = 0;
    float asmAvg = 0;
    float cTimes[30];
    float asmTimes[30];

    // inputting the vector elements

    printf("\nEnter the vector elements:\n");
    for (int i = 0; i < vectorSize; i++) {
        //printf("\nElement %d:\n", i);

        //printf("X1[%d] = ", i);
        scanf_s("%f", &xOne[i]);

        //printf("X2[%d] = ", i);
        scanf_s("%f", &xTwo[i]);

        //printf("Y1[%d] = ", i);
        scanf_s("%f", &yOne[i]);

        //printf("Y2[%d] = ", i);
        scanf_s("%f", &yTwo[i]);
    }

    // running the C kernel 30 times
    for (int i = 0; i < 30; i++) {
        // timing the C kernel 
        clock_t beginC = clock();

        c_kernel(xOne, xTwo, yOne, yTwo, zC, vectorSize);

        clock_t endC = clock();
        float timeC = (float)(endC - beginC) / CLOCKS_PER_SEC;

        // printing the first 10 elements of Z (C)
        if (i == 0) {
            printf("\nC Kernel Z[0..9]: ");
            for (int i = 0; i < 10 && i < vectorSize; i++) {
                printf("%.2f, ", zC[i]);
            }
        }
        cTimes[i] = timeC;
        cAvg += timeC;
    }
    cAvg = cAvg / 30;

    // running the ASM kernel 30 times
    for (int i = 0; i < 30; i++) {
        // timing the ASM kernel
        clock_t beginASM = clock();

        asm_kernel(xOne, xTwo, yOne, yTwo, zASM, vectorSize);

        clock_t endASM = clock();
        float timeASM = (float)(endASM - beginASM) / CLOCKS_PER_SEC;

        // printing the first 10 elements of Z (ASM)
        // only printing the first execution result for readability as they are all the same output
        if (i == 0) {
            printf("\nASM Kernel Z[0..9]: ");
            for (int i = 0; i < 10 && i < vectorSize; i++) {
                printf("%.2f, ", zASM[i]);
            }
        }
        asmTimes[i] = timeASM;
        asmAvg += timeASM;
    }
    asmAvg = asmAvg / 30;
    
    printf("\nExecution # |  C Time  | Assembly Time |\n");
    for (int i = 0; i < 30; i++) {
        printf("%11d | %8f | %13f | \n", i+1, cTimes[i], asmTimes[i]);
    }
    printf("\nAverage C kernel time: %f\n", cAvg);
    printf("\nAverage ASM kernel time: %f\n", asmAvg);

    // checking if the ASM kernel is correct
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

    // freeing the memory
    free(xOne);
    free(xTwo);
    free(yOne);
    free(yTwo);
    free(zC);
    free(zASM);

    return 0;
}
