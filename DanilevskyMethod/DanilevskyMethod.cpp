#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

using namespace std;
#define N 7

int main()
{
	setlocale(LC_CTYPE, "Rus");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
							  //double A[5][5] = { {0,0,0,0,0},
							  //{ 0,6.59, 1.26, 0.81, 1.195 },
							  //{ 0,1.26, 3.83, 1.3, 0.16 },
							  //{ 0,0.81, 1.3, 5.77, 2.1 },
							  //{ 0,1.195, 0.16, 2.1, 5.77 } };
	double D[5][5]; // вспомагательная матрица для хранения предыдущего результата умножения матриц
	double A[N][N] = { 0 }; // исходная матрица
	int n; // размер матрицы
	double M[N - 1][N][N]; // матрица М
	double inverseM[N - 1][N][N]; // матрица обратная M
	double multiplyMatrix[N][N]; // вспомагательная матрица для умножения
	do
	{
		cout << "Введите число уравнений системы: ";
		while (!(cin >> n) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибка ввода! Повторите ввод" << endl;
		}
		if (N < n)
			cout << "Слишком большое число уравнений. Повторите ввод\n";
	} while (N < n);
	cout << "Введите систему.\n" << "После ввода елемента [ряд][столбец]\nзаданой матрицы нажмите Enter\nдля перехода к следующему елементу системы:" << endl;
	for (int i = 1; i <= n; i++) {
		cout << "Столбец " << i << ":\n";
		for (int j = 1; j <= n; j++) {
			cout << "Елемент [" << i << "][" << j << "]: ";
			while (!(cin >> A[i][j]) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Повторите ввод" << endl;
				cout << "Елемент [" << i << "][" << j << "]: ";
			}
		}
	}
	cout << "Ваша матрица А или D0:\n\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout.width(7);
			cout << A[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int k = 1; k <= n - 1; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (n - i == k) {
					if (j != i) {
						M[k][i][j] = -A[i + 1][j] / A[i + 1][i];
					}
					else {
						M[k][i][j] = 1 / A[i + 1][i];
					}
				}
				else {
					if (i == j) {
						M[k][i][j] = 1;
					}
					else {
						M[k][i][j] = 0;
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (n - i == k) {
					inverseM[k][i][j] = A[i + 1][j];
				}
				else {
					if (i == j) {
						inverseM[k][i][j] = 1;
					}
					else {
						inverseM[k][i][j] = 0;
					}
				}
			}
		}
		cout << "M" << k << " :" << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout.width(10);
				cout << M[k][i][j];
			}
			cout << endl;
		}
		cout << "обратная к M" << k << " :" << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout.width(10);
				cout << inverseM[k][i][j];
			}
			cout << endl;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				multiplyMatrix[i][j] = 0;
				for (int p = 1; p <= n; p++) {
					multiplyMatrix[i][j] += (inverseM[k][i][p] * A[p][j]);
					D[i][j] = multiplyMatrix[i][j];
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				multiplyMatrix[i][j] = 0;
				for (int p = 1; p <= n; p++) {
					multiplyMatrix[i][j] += (D[i][p] * M[k][p][j]);
					A[i][j] = multiplyMatrix[i][j];
					if (fabs(A[i][j]) < 0.000000001)
						A[i][j] = 0;
				}
			}
		}
		cout << "D" << k << " = M[" << k << "]* D" << k - 1 << " * M[" << k << "]^-1:\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout.width(15);
				cout << A[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}