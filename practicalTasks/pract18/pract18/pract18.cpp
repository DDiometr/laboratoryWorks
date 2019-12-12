

#include "pch.h"
#include <iostream>
#include <ctime>

using namespace std;


int main()
{
	int min = 101, max = -101;
	srand(static_cast<int>(time(0)));
	int arr[20];
	
	for (int i = 0; i < 20; i++)
	{
		arr[i] = (rand() % 201) - 100;
		cout << arr[i] << " ";
	}
	
	for (int i = 0; i < 20; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	cout << endl << min << endl << max;
}

