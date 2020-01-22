#include<libbmp.h>
#include<iostream>

using namespace std;
int bitPos = 7;
int bytePos;
char text[20000] = { 0 };
bool stop = false;

void insertBit(char bit) {
	text[bytePos] |= bit << bitPos;
	bitPos--;
	if (bitPos<0)
	{
		bitPos = 7;
		bytePos++;
	}
	if (bytePos == 1000)
	{
		stop = true;
	}
}

int main(){
	BmpImg img1;
	img1.read("pic6.bmp");
	//ключ 00r 00b 00g 10r 10b 10g 01r 01b
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < img1.get_height(); i++)
	{
		if (!stop)
		{
			for (int j = 0; j < img1.get_width(); j++) 
			{
				insertBit(img1.red_at(j, i)&1);
				insertBit(img1.blue_at(j, i)&1);
				insertBit(img1.green_at(j, i)&1);
			}
		}
	}
	cout << text<< endl;
	system("PAUSE");
}