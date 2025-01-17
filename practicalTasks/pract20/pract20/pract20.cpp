
#include "pch.h"
#include <iostream>

using namespace std;

void boubleSort(double*, int);
void printArrayD(double*, int);

int main()
{
	int n;
	cin >> n;
	double* arr = new double[n];
	
	for (size_t i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	boubleSort(arr, n);
	printArrayD(arr, n);
}

void boubleSort(double* arr, int len) {
	double buffer;
	int changeCounter = 1;
	for (int i = 0; i < len; i++)
	{
		if (changeCounter > 0)
		{
			changeCounter = 0;
			for (int j = 0; j + 1 < len - i; j++)
			{
				if (arr[j] > arr[j + 1])
				{
 					buffer = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = buffer;
					changeCounter++;
				}
			}
		}
		else
		{
			break;
		}
	}
}

void printArrayD(double* arr, int len) {
	for (int i = 0; i < len ; i++)
	{
		cout << arr[i] << " ";
	}
}