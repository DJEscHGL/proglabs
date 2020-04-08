﻿#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

void Output(double* Arr[], int SIZE, double FT[])
{
	double* qw = FT;
	for (int i = 0; i < SIZE; i++)
	{
		SetConsoleTextAttribute(Terminal, 10 + i);
		for (int j = 0; j < SIZE; j++)
		{
			cout << *(Arr[i] + j) << "*x" << j;
			if (j < SIZE - 1)
				cout << " + ";
		}
		cout << " = " << *qw << endl;
		qw++;
	}
	SetConsoleTextAttribute(Terminal, 7);
}

double *Gauss(double* Arr[], double FT[], int SIZE)
{
	double* x, max;
	int k, index;
	const double EPS = 0.00000000000001;
	x = new double[SIZE];
	k = 0;
	while (k < SIZE)
	{
		max = abs(Arr[k][k]);
		index = k;
		for (int i = k + 1; i < SIZE; i++)
		{
			if (abs(Arr[i][k]) > max)
			{
				max = abs(Arr[i][k]);
				index = i;
			}
		}
		if (max < EPS)
		{
			SetConsoleTextAttribute(Terminal, 9);
			cout << "Решение невозможно, т. к. есть нулевой столбец №" << index << endl;
			cout << "Один из корней равен R";
			SetConsoleTextAttribute(Terminal, 7);
			return 0;
		}
		for (int j = 0; j < SIZE; j++)
			swap(*(Arr[k] + j), *(Arr[index] + j));
		swap(FT[k], FT[index]);
		for (int i = k; i < SIZE; i++)
		{
			double temp = Arr[i][k];
			// Для нулевых пропуск
			if (abs(temp) < EPS)
				continue;
			for (int j = 0; j < SIZE; j++)
				Arr[i][j] = Arr[i][j] / temp;
			FT[i] = FT[i] / temp;
			if (i == k)
				continue;
			for (int j = 0; j < SIZE; j++)
				Arr[i][j] = Arr[i][j] - Arr[k][j];
			FT[i] = FT[i] - FT[k];
		}
		k++;
	}
	// Обратная подстановка
	for (k = SIZE - 1; k >= 0; k--)
	{
		x[k] = FT[k];
		for (int i = 0; i < k; i++)
			FT[i] = FT[i] - Arr[i][k] * x[k];
	}
	return x;
}

int main()
{
	setlocale(0, "");
	int SIZE;
	cout << "SIZE = ";
	cin >> SIZE;
	double** Arr, *FT, *x;
	Arr = new double* [SIZE];
	FT = new double[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		cout << i << " EQUATION = ";
		Arr[i] = new double[SIZE];
		for (int j = 0; j < SIZE; j++)
			cin >> *(Arr[i] + j);
		cout << "FT = ";
		cin >> *(FT + i);
	}
	Output(Arr, SIZE, FT);
	x = Gauss(Arr, FT, SIZE);
	SetConsoleTextAttribute(Terminal, 11);
	for (int i = 0; i < SIZE; i++)
		cout << "x[" << i << "]= " << x[i] << endl;
	SetConsoleTextAttribute(Terminal, 7);
}
