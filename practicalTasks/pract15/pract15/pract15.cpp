

#include "pch.h"
#include <iostream>

using namespace std;

void insert(int pos, int num);
int arr[5];

int main()
{
	int n, current;
	
	for (int i = 5; i > 0; i--)
	{
		arr[i] = 150000;
	}


	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> current;
		for (int k = 0; k < 5; k++)
		{
			if (current < arr[i])
			{
				insert(i, current);
				break;
			}
		}
		
		
		for (int i = 5; i > 0; i--)
		{
			cout << arr[i];
		}
		cout << endl;
	}
}

void insert(int pos, int num) {
	arr[pos] = num;
}

