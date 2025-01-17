

#include "pch.h"
#include <iostream>

using namespace std;

double moveCalc(double a, double b, double c) {
	return a + b * c + 1/2*-9.8*c*c;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double x0; //выберем вещественный тип для всех трёх переменных
	double v0; //по причине того что ускорение свободного падения дано 
	double t;  //с точностью до 1 знака после запятой (ответ должен быть с точностью до одного знака после запятой)

	double result;
	bool errorlessVelosity;
	bool errorlessHeight;
	bool errorlessTime;
	cout << endl << "Введите высоту на которой тело находилось в начальный момент времени(м) "; cin >> x0;
	cout << endl << "Введите начальную скорость тела(м/с) "; cin >> v0;
	cout << endl << "Введите сколько времени длилось падение(с) "; cin >> t;

	
	do
	{

		if (v0 > 0) {
			cout << "Данная программа рассчитывает только движение тел которые в указанный промежуток времени находились в свободном падении, поэтому начальная скорость не может быть положительной."
			<< endl << "Введите значение начальной скорости повторно";
			errorlessVelosity = false;
			cout << endl << "Введите начальную скорость тела(м/с) "; cin >> v0;
		}
		else
		{
			errorlessVelosity = true;
		};

		if (x0 < 0) {
			cout << "Данная программа рассчитывает только движение тел которые в указанный промежуток времени находились в свободном падении, поэтому начальная высота не может быть меньше нуля."
			<< endl << "Введите значение начальной высоты повторно";
			errorlessHeight = false;
			cout << endl << "Введите высоту на которой тело находилось в начальный момент времени(м) "; cin >> x0;
		}
		else
		{
			errorlessHeight = true;
		};

		if (t < 0) {
			cout << "Время - неотрицательная величина."
				<< endl << "Введите значение времени";
			errorlessTime = false;
			cout << endl << "Введите сколько времени длилось падение(с) "; cin >> t;
		}
		else
		{
			errorlessTime = true;
		};
	} while (!errorlessVelosity || !errorlessHeight || !errorlessTime); {}

	

	result = moveCalc(x0, v0, t);

	if (result < 0) {
		cout << endl << 
		"Предупреждение: тело падало не весь заданный промежуток времени, пролетев " << x0 << " метров, оно ударилось о поверхность.";
	}
	else
	{
		cout << result;
	};
	system("PAUSE");
}

