
#include "pch.h"
#include <iostream>
#include<math.h>

using namespace std;

int n;
int powt = 0;

int main()
{
	setlocale(LC_ALL, "Russian");
	cin >> n;
	if (n > 0 && n <= pow(10,15))
	{
		powt = log10(n) / log10(2) + 1;
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

