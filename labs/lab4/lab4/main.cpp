#include<iostream>

#include<time.h>


enum Status{
   PLAY,            // ���� ������������
   USER_WIN,        // ����� �������
   BOT_WIN,         // ��� �������
   NOT_WIN          // �����. ���������� ���, �� � �� ���� ��� ��������� ������
};

struct Game {
	char bord[3][3];  // ������� ����
	bool isUserTurn;  // ��� ���. ���� ������������, �� isUserTurn = true
	char userChar;    // ������ ������� ������ ������������
	char botChar;     // ������ ������� ������ ���
	Status status;
};

#include<Header.h>

int main() {
	setlocale(LC_ALL, "Russian");
	Game game1 = initGame('x');
	Game* ptr = &game1;
	while (!updateGame(ptr)) {
		updateDisplay(game1);
		if (game1.isUserTurn)
		{
			userTurn(ptr);
		}
		else
		{
			botTurn(ptr);
		}
		system("cls");
	};
	if (game1.status == USER_WIN)
	{
		std::cout << "����� �������" << std::endl;
	}
	if (game1.status == BOT_WIN)
	{
		std::cout << "��� �������" << std::endl;
	}
	if (game1.status == NOT_WIN)
	{
		std::cout << "�����" << std::endl;
	}
	
	system("PAUSE");
}