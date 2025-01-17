#include "pch.h"
#include <iostream>

using namespace std;

double BMI(double weight, double height);
void printBMI(double BMI);

int main()
{
	double weight, height;
	cin >> weight >> height;
	printBMI(BMI(weight, height/100));
}


double BMI(double weight, double height) {
	return weight / (height * height);
}

void printBMI(double BMI) {
	if (BMI < 18.5)
	{
		cout << "Underweight";
		return;
	}
	if (BMI < 25)
	{
		cout << "Normal";
		return;
	}if (BMI < 30)
	{
		cout << "Overweight";
		return;
	}if (BMI >= 30 )
	{
		cout << "Obesity";
		return;
	}
}