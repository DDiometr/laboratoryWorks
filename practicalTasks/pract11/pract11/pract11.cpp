
#include "pch.h"
#include <iostream>

using namespace std;

int n, result = 1;

int main()
{
	setlocale(LC_ALL, "Russian");
	cin >> n;
	if (n > 0)
	{
		for (int i = 1; i <= n; i++)
		{
			result *= i; // result = result * i
		}
		cout << result;
	}
	else
	{
		cout << "Факториал - функция которая определена только для положительных чисел.";
	}
	
}

