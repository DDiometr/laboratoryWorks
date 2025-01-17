
#include "pch.h"
#include <iostream>

using namespace std;

double a, b, result;
char op = '?';
bool valuesIsCorrect = false;

void input() {
	cout << endl << "Введите выражение" << endl;
	cin >> a >> op >> b;
}

void checkValues() {
	if (op == '+' || op == '-' || op == '*' || op == '/')
	{
		if (op == '/')
		{
			if (b != 0)
			{
				valuesIsCorrect = true;
			}
			else
			{
				cout << "Нельзя делить на ноль. Повторите ввод выражения." << endl;
			}
		}
		else
		{
			valuesIsCorrect = true;
		}
	}
	else
	{
		cout << "Доступны только операции + - * / . Повторите ввод выражения." << endl;
	}
}

void calculate() {
	switch (op)
	{
	case '+': result = a + b; break;
	case '-': result = a - b; break;
	case '*': result = a * b; break;
	case '/': result = a / b; break;
	default:
		break;
	}
}

void output() {
	cout << result;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	while (!valuesIsCorrect)
	{
		input();
		checkValues();
	}
	calculate();
	output();
}

