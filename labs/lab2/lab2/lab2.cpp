#include "pch.h"
#include <iostream>
#include<math.h>
#include<iomanip>

using namespace std;

int main()
{
	double a, b, h, result, startX, endX, min, max, epsilon = 0.000000000001;
	cin >> a >> b >> h >> startX >> endX;
	min = 2;
	max = 0;
	for (double i = startX; round(i*10)/10 <= round(endX*10)/10; i += h)
	{
		if (i < a || fabs(a - i) < epsilon)
		{
			result = pow(i, 2) + sin(i);
			if (result > max)
			{
				max = result;
			}
			if (result < min)
			{
				min = result;
			}
			cout << setw(7) << i << setw(10) << result << endl;
			continue;
		}
		if (a < i && i < b)
		{
			result = cos(pow(i, 2));
			if (result > max)
			{
				max = result;
			}
			if (result < min)
			{
				min = result;
			}
			cout << setw(7) << i << setw(10) << result << endl;
			continue;
		}
		if (i >= b)
		{
			result = log(i) / log(2);
			if (result > max)
			{
				max = result;
			}
			if (result < min)
			{
				min = result;
			}
			cout << setw(7) << i << setw(10) << result << endl;
			continue;
		}
	}
	cout << endl;
	cout << "Max: " << max << endl;
	cout << "Min: " << min << endl;
}

