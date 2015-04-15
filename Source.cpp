#define _USE_MATH_DEFINES // for M_PI

#include<iostream>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<cmath>

//configuration values
#define KMAX 50000
#define N 100
#define MAX 1.0
#define MIN 0.0
#define EPSILON 1e-6

typedef double floatType;
void rewrite(floatType* from, floatType* dest, int size);
void show(floatType** t, int size);
void zero(floatType **t, int size);
void zero(floatType *t, int size);
void writeToFile(floatType **t, int size);

int main(){
	floatType **t;
	floatType *lastRow;
	floatType h = (MAX - MIN) / (N + 0.0);
	floatType diff;
	floatType lastValue;
	floatType leftTemp;
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
		t[i][0] = sin(M_PI * i * h) * sin(M_PI * i * h);
	}
	std::cout << "\n\nBefore loop: \n\n";
	//show(t, N + 1);

	
	std::cout << "\n\nloop: \n\n";
	for (k = 0; k < KMAX; ++k) {
		diff = 0.0;

		zero(lastRow, N + 1);
		for (i = 1; i < N; ++i) {
			//rewrite(t[i - 1], lastRow, N); //not needed +1 because we never update the last column
			lastRow[0] = t[i][0];

			for (j = 1; j < N; ++j) {
				lastValue = t[i][j];
				t[i][j] = (t[i + 1][j] + lastRow[j] + t[i][j + 1] + lastRow[j-1]) / 4.0;
				lastRow[j] = lastValue;
				diff += fabs(lastValue - t[i][j]);
			}
		}
		//show(t, N);
		if (diff < EPSILON){
			std::cout << "Desired accuracy reached. " << diff << " iterations: " << k;
			break;
		}
	}
	std::cout << "\n\nAfter loop: \n\n" << diff;
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
	std::cout << "\n";
	for (int i = 0; i < size; ++i){
		std::cout << from[i] << "\t";
		dest[i] = from[i];
	}
}

void show(floatType** t, int size){
	std::cout << "\n";
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			//std::cout << t[i][j] << "\t";
			printf("%.6f\t", t[i][j]);
		}
		std::cout << "\n";
	}
}

void zero(floatType *t, int size){
	for (int i = 0; i < size; ++i){
		t[i] = 0.0;
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
