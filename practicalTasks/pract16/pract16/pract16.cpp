

#include "pch.h"
#include <iostream>

using namespace std;
void factorization(int num);
void insert(int num);

struct numDivider
{
	int numDivider;
	int quantity;
};

const int ARR_SIZE = 1000000;

numDivider arr[ARR_SIZE] = {0};


int endPos = 0;
int main()
{
	int n;
	cin >> n;
	
	factorization(n);

	for (int i = 0; i <= endPos; i++)
	{
		if (arr[i].numDivider == 0)
		{
			break;
		}
		else
		{
			if (arr[i+1].numDivider == 0)
			{
				cout << arr[i].numDivider; 
				if (arr[i].quantity != 1)
				{
					cout << "^" << arr[i].quantity;
				}
			}
			else
			{
				cout << arr[i].numDivider;
				if (arr[i].quantity != 1)
				{
					cout << "^" << arr[i].quantity;
				}
				cout << " * ";
			}		
		}		
	}
}

void factorization(int num) {
	int n = num;
	for (int i = 2; i <= n;)
	{
		if (num%i == 0)
		{
			if (num / i == 1)
			{
				insert(i);
				break;
			}
			else
			{
				num /= i;
				insert(i);
			}
		}
		else
		{
			i++;
		}
	}
}

void insert(int num) {
	for (int i = 0; i < ARR_SIZE; i++)
	{
		
		if (arr[i].numDivider == 0)
		{
			endPos = i;
			break;
		}
		
	}


	bool presentFlag;
	for (int i = 0; i <= endPos; i++)
	{
		if (num == arr[i].numDivider)
		{
			arr[i].quantity++;
			//cout << num;
			presentFlag = true;
			break;
		}
		else
		{
			presentFlag = false;
		}
	}
	if (!presentFlag)
	{
		arr[endPos].numDivider = num;
		arr[endPos].quantity = 1;
		//cout << num;
	}
	
	
}