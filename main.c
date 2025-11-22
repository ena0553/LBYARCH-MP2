#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

extern void asmhello();
int main(int argc, char* argv[]) {
	clock_t begin = clock();

	int vectorSize;
	
	scanf_s("%d", &vectorSize);
	vectorSize = vectorSize * 4

	printf("%d\n", vectorSize);
	("\n");

	float *xOne = malloc(vectorSize * sizeof(float));
	float *yOne = malloc(vectorSize * sizeof(float));
	float *xTwo = malloc(vectorSize * sizeof(float));
	float *yTwo = malloc(vectorSize * sizeof(float));
	float *z = malloc(vectorSize * sizeof(float));
	for (int i = 0; i < vectorSize; i++) {
		scanf_s("%f", &xOne[i]);
		scanf_s("%f", &xTwo[i]);
		scanf_s("%f", &yOne[i]);
		scanf_s("%f", &yTwo[i]);

		z[i] = sqrt(pow(xTwo[i] - xOne[i], 2) + pow(yTwo[i] - yOne[i], 2));
	}
	
	printf("The first 10 elements of Z are: ");
	for (int i = 0; i < 10; i++) {
		printf("%.2f, ", z[i]);
	}

	// asmhello();


	printf("\ndone");
	clock_t end = clock();

	float time_spent = (float)(end - begin);
	printf("\n%f", time_spent/CLOCKS_PER_SEC);
	
	return 0;
}