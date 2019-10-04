
#include "pch.h"
#include <iostream>
#include<random>

using namespace std;
int rdNum, fg;
bool wantToContinue = true;

int main()
{
	setlocale(LC_ALL, "Russian");
	random_device rad;
	rdNum = rad() % 100;
	while (wantToContinue)
	{
		wantToContinue = false;

		cout << endl << "Компьютер загадал целое число от 0 до 100 включительно." << endl << " У вас есть пять попыток чтобы угадать его. " << endl << "После кажной попытки компьютер будет давать вам подсказку." << endl;

		for (int i = 0; i < 5; i++)
		{
			cin >> fg;
			

			if (i == 4 && fg != rdNum)
			{
				cout << "Вы проиграли. Компьютер загадал " << rdNum << endl;
			}
			else
			{
				if (fg > rdNum)
				{
					cout << "Загаданное число меньше." << endl;
				}
				else
				{
					if (fg < rdNum)
					{
						cout << "Загаданное число больше" << endl;
					}
					if (fg == rdNum)
					{
						cout << "Вы угадали" << endl;
					}
				}
			}
		}


		cout << "Хотите сыгать заново(1 - да, 0  - нет)" << endl;
		cin >> wantToContinue; 
	}
}

