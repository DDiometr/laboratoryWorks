
#include "pch.h"
#include <iostream>
#include<math.h>

using namespace std;


double myPow(int a, int b) {
	double buffer = a;
	
	
	
	
	int i = abs(b);
	while (true)
	{
		
		if (i == 1)
		{
			return buffer;
		}
		if (i == 0)
		{
			return 1;
		}
		buffer *= buffer;

		i--;
	}
		
	
	
	
	
};

int main()
{
	int num, expUs;
	cin >> num;
	cin >> expUs;
	cout << myPow(num, expUs);
	return 0;
}

