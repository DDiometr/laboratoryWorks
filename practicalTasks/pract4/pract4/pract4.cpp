
#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	int b;
	int buffer;
	cout << endl << "Введите а ";
	cin >> a;
	cout << endl << "Введите b ";
	cin >> b;

	buffer = a;
	a = b;
	b = buffer;

    cout << endl << "а = " << a << endl; 
	cout << endl << "b = " << b;


	//альтернативный метод


	cout << endl << "Введите а ";
	cin >> a;

	b = a;
	cout << endl << "Введите b ";
	cin >> a;

	cout << endl << "а = " << a << endl;
	cout << endl << "b = " << b;
}

