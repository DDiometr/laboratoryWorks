
#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int var1 = 3; 
	int var2 = -3.99; 
	double var3 = 3; 
	double var4 = 3.14; 
    cout << endl 
		<< var1 << endl //нормальный вывод
		<< var2 << endl //вывод 3 так как переменная типа int не хранит дробную часть
		<< var3 << endl //нормальный вывод
		<< var4 << endl ;//нормальный вывод
}


