#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    clock_t begin = clock();
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("2e28.txt", "w");

    fprintf(fptr, "268435456\n");
    
    // 2^22 = 4194304
    // 2^26 = 67108864
    // 2^30 = 1073741824

    for(int i = 0 ; i < (268435456 * 4) ; i++){
        float x = ((float)rand() / RAND_MAX) * 100.0f;
        fprintf(fptr, "%.2f\n", x);
    }
    

    // Close the file
    fclose(fptr); 
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time spent: %f", time_spent);
    return 0;
}