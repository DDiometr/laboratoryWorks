
#include "pch.h"
#include <iostream>
#include<math.h>

using namespace std;


double lenA = 1, lenB = 1, lenC = 1;


bool input() {
	int calcMethod;
	double  Ax, Ay, Bx, By, Cx, Cy;
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
		return true;
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
		return true;
	}
	break;
	default: {
		return false;
	}break;
	}
	
};

bool checkValues() {
	
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

	if (!(max > lenA + lenB + lenC - max) && lenA > 0 && lenB > 0 && lenC > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
};

double calculate() {
	double p, s;
	p = (lenA + lenB + lenC) / 2;
	s = sqrt(p*(p - lenA)*(p - lenB)*(p - lenC));
	return s;
};

void output(double s) {
	cout << "S= " << s;
};



int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Справка должна быть здесь";
	input();
	if (checkValues())
	{
		output(calculate());
	}
	else
	{
		cout << "Введены неправильные данные , см. Справку";
	}
	return 0;
}

