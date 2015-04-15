#include<iostream>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<cmath>

#define M_PI          3.141592653589793238462643383279502884 /* pi */

//configuration values
#define KMAX 10000
#define N 100
#define MAX 1.0
#define MIN 0.0
#define EPSILON 10e-9

typedef float floatType;
void rewrite(floatType* from, floatType* dest, int size);
void show(floatType** t, int size);
void zero(floatType **t, int size);
void writeToFile(floatType **t, int size);

int main(){
	floatType **t;
	floatType *lastRow;
	floatType h = (MAX - MIN) / (N + 0.0);
	floatType diff;
	floatType temp;
	bool continueLoop = false;
	int i, j, k;

	long startTime = clock();

	t = (floatType**)malloc((N + 1)*sizeof(floatType));
	lastRow = (floatType*)malloc((N + 1)*sizeof(floatType));
	for (i = 0; i <= N; ++i){
		t[i] = (floatType*)malloc((N + 1)*sizeof(floatType));
	}

	zero(t, N + 1);

	for (i = 0; i <= N; ++i) {
		t[i][0] = sin(M_PI * i * h) * sin(M_PI*i*h);
	}
	std::cout << "\n\nBefore loop: \n\n";
	//show(t, N + 1);

	std::cout << "\n\nloop: \n\n";
	for (k = 0; k < KMAX; ++k) {
		diff = 0.0;

		for (i = 1; i < N; ++i) {
			rewrite(t[i - 1], lastRow, N); //not needed +1 because we never update the last column

			for (j = 1; j < N; ++j) {
				temp = t[i][j];
				t[i][j] = (t[i + 1][j] + lastRow[j] + t[i][j + 1] + t[i][j - 1]) / 4.0;
				diff += fabs(temp - t[i][j]);
			}
		}

		if (diff - EPSILON <= 0){
			std::cout << "Desired accuracy reached. " << diff << " iterations: " << k;
			break;
		}
	}
	std::cout << "\n\nAfter loop: \n\n";
	//show(t, N + 1);

	std::cout << "\nThe time passed: " << (clock() - startTime) / 1000.0 << "s\n";
	writeToFile(t, N + 1);

	//freeing memory
	for (int i = 0; i <= N; ++i)
	{
		delete[] t[i];
	}
	delete[] t;
	delete[] lastRow;


	system("pause");
	return 0;
}

void rewrite(floatType* from, floatType* dest, int size){
	for (int i = 0; i < size; ++i){
		dest[i] = from[i];
	}
}

void show(floatType** t, int size){
	std::cout << "\n";
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			std::cout << t[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

void zero(floatType **t, int size){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			t[i][j] = 0.0;
		}
	}
}

void writeToFile(floatType** t, int size){
	std::ofstream file;
	file.open("output.dat", std::ios::out);
	file.clear();
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			file << t[i][j] << "\t";
		}
		file << "\n";
	}
	file.close();
}