

#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	int b;
	cout << endl << "Введите а: ";
	cin >> a;
	cout << endl << "Введите b: ";
	cin >> b;

    cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	while(b == 0)
	{
		cout << "Ошибка, нельзя делить на отрицательное число" << endl << "Введите b: ";
		cin >> b;
	}
	cout << "a / b = " << a / b << endl;
}

