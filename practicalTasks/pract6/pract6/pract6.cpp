
#include "pch.h"
#include <iostream>
#include<math.h>

using namespace std;

double a, b, c, x1, x2 = 0, D;

void output() {
	if (x2 == 0)
	{
		cout << endl << "x = " << x1 << endl;
	}
	else
	{
		cout << endl << "х1 = " << x1 << endl << "х2 = " << x2 << endl;
	};
};

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << endl << "Уравнение вида ax^2 + bx + c = 0";
	cout << endl << "Введите a ";
	cin >> a;
	cout << "Введите b ";
	cin >> b;
	cout << "Введите c ";
	cin >> c;


  /*1 1 1 дискриминант                         |  х1 = (-b + sqrt(b^2 - 4ac))/ 2a, х2 = (-b + sqrt(b^2 - 4ac))/ 2a
	1 1 0 вынос за скобки                      |  x1 = 0 , x2 = -b/a
	1 0 1 перенос с за равно и нахождение х12  |  x1 = sqrt(-c/a), x2 = -sqrt(-c/a)
	1 0 0 x = 0                                |  х1 = 0
	0 1 1 линейное уравнение                   |  x1 = -c/b
	0 1 0 х = 0                                |  x1 = 0
	0 0 1 х = с                                |  нет корней
	0 0 0 должна быть хотябы одна переменная   |  нет корней*/

	
	if (a && b && c)
	{
		// дискриминант
		D = pow(b, 2) - 4 * a * c;

		if (D < 0)
		{
			cout << endl << "Нет корней в области действительных чисел";
		}
		else
		{
			x1 = (-b + sqrt(D)) / (2 * a);
			x2 = (-b - sqrt(D)) / (2 * a);
			output();
		};
		
	}
	else
	{
		if (a && b && !c)
		{
			//за скобки
			x1 = 0;
			x2 = -b / a;
			output();
		}
		else
		{
			if (a && !b && c)
			{
				//корень с переносом
				if (-c/a < 0)
				{
					cout << endl << "Нет корней в области действительных чисел";
				}
				else
				{
					x1 = sqrt(-c / a);
					x2 = -sqrt(-c / a);
					output();
				};
				
			}
			else
			{
				if ((a && !b && !c) || (!a && b && !c))
				{
					//х = 0
					x1 = 0;
					output();
				}
				else
				{
					if (!a && b && c)
					{
						//линейное уравнение
						x1 = -c / b;
						output();
					}
					else
					{
						if (!a && !b && c)  // 0*x^2 + 0*x + 0 = 0
						{
							//бесконечно много корней
							cout << endl << "Уравнение не имеет корней";
						}
						else
						{
							if (!a && !b && !c)
							{
								cout << endl << "Уравнение имеет бесконечно много корней";
							}
						}
					}

					
				}

				
			};

			
		};

		
	}

	

	return 0;
}

