
#include "pch.h"
#include <iostream>
#include<math.h>

using namespace std;

double eps = pow(10, -10);
int n, powt = 0;


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите число: ";
	cin >> n;
	if (n > 0 && n <= pow(10,15))
	{
		powt = log10(n) / log10(2) + 1;
		if (powt)
		{

		}
		cout << powt;
	}
	else
	{
		if (n == 0)
		{
			powt = 0;
			cout << powt;
		}
		else
		{
			cout << "Ошибка." << endl;
		}
		
	}
}

