
#include "pch.h"
#include <iostream>
#include<math.h>

using namespace std;

int calcMethod;
double lenA, lenB, lenC, Ax, Ay, Bx, By, Cx, Cy, p, s;
bool valuesIsCorrect = false;

void input() {
	
	cout << "Выберите вариант входных данных." << endl << " Введите 1 чтобы задать треугольник по длинам сторон." << endl << "Введите 2 чтобы задать треугольник по координатам вершин." << endl;
	cin >> calcMethod;
	switch (calcMethod)
	{
	case 1: 
		{
			cout << "Введите длины сторон по одной в строке." << endl;
			cin >> lenA; cout << endl;
			cin >> lenB; cout << endl;
			cin >> lenC; cout << endl;
		} 
		break;

	case 2: 
		{
			cout << "Введите координа вершин треугольника." << endl << " Координаты вершин вводите по одной вершине на строку, укзывая х и у через пробел" << endl;
			cin >> Ax;  cin >> Ay;
			cin >> Bx;  cin >> By;
			cin >> Cx;  cin >> Cy;
			lenA = sqrt(pow(Bx - Ax, 2) + pow(By - Ay, 2));
			lenB = sqrt(pow(Cx - Bx, 2) + pow(Cy - By, 2));
			lenC = sqrt(pow(Ax - Cx, 2) + pow(Ay - By, 2));
		} 
		break;

	default: 
		{
			
		}
		break;

	}
	
};

void checkValues() {
	bool isTriangle;
	double max;
	max = lenA;


	if (lenB > max)
	{
		max = lenB;
	}

	if (lenC > max)
	{
		max = lenC;
	}

	if (max < lenA + lenB + lenC - max)
	{
		isTriangle = true;
	}

	if ((calcMethod == 1 || calcMethod == 2) && lenA > 0 && lenB > 0 && lenC > 0 && isTriangle)
	{
		valuesIsCorrect = true;
	}
	else
	{
		if (!(calcMethod == 1 || calcMethod == 2)){cout << "При выборе варианта входных данных выбирайте только из предложенных команд(1 и 2)" << endl;}

		if (lenA <= 0) { cout << "Сторона трегольника не может иметь нулевую длину." << endl; }

		if (lenB <= 0) { cout << "Сторона трегольника не может иметь нулевую длину." << endl; }

		if (lenB <= 0) { cout << "Сторона трегольника не может иметь нулевую длину." << endl; }

		if (!isTriangle) { cout << "Такой треугольник не существует." << endl; }

		cout << "Введите данные повторно" << endl;
	}
};

void calculate() {
	p = (lenA + lenB + lenC) / 2;
	s = sqrt(p*(p - lenA)*(p - lenB)*(p - lenC));
};

void output() {
	cout << "S= " << s;
};



int main()
{
	setlocale(LC_ALL, "Russian");
	while (!valuesIsCorrect) {
		input();
		checkValues();
	}
	calculate();
	output();
	return 0;
}

