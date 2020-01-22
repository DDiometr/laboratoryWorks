#include<iostream>
#include<Windows.h>

enum Status {
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
Game initGame(char userChar) {
	Game tempGame;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempGame.bord[i][j] = ' ';
		}
	}
	int radio = rand() % 50 - 100;
	if (radio < 0)
	{
		tempGame.isUserTurn = false;
	}
	else
	{
		tempGame.isUserTurn = true;
	}
	tempGame.userChar = userChar;
	std::cout << "��� ������: " << userChar << std::endl << std::endl;
	if (userChar = 'x')
	{
		tempGame.botChar = 'o';
	}
	else
	{
		tempGame.botChar = 'x';
	}
	return tempGame;
}
void updateDisplay(const Game game) {
	int counter = 1;
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "  a b c" << std::endl << std::endl;
	for (int i = 1; i <= 5; i++)
	{
		SetConsoleTextAttribute(hConsoleHandle,   FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		if (i%2 == 1)
		{
			std::cout << counter << ' ';
			counter++;
		}
		else
		{
			std::cout << "  ";
		}
		for (int j = 1; j <= 5; j++)
		{
			if (j%2 == 1 && i%2 == 1)
			{
				//�������
				int xPos, yPos;
				switch (i)
				{
				case 1: yPos = 0; break;
				case 3: yPos = 1; break;
				case 5: yPos = 2; break;
				}
				switch (j)
				{
				case 1: xPos = 0; break;
				case 3: xPos = 1; break;
				case 5: xPos = 2; break;
				}
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				std::cout << game.bord[yPos][xPos];
			}
			else
			{
				//�������
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | BACKGROUND_BLUE);
				std::cout << ' ';
			}
		}
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | 0);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void botTurn(Game* game)
 {
	enum lineType
	{
		ROW = 0,
		COLUMN,
		MAIN_DIAG,
		SUB_DIAG
	};
	struct Point
	{
		lineType line;
		int charQuantity = 0;
		int num;
	};
	Point betterLine{ROW};
	int counter = 0;
	bool hasEmpty = false;
	// ������
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game->bord[i][j] == game->userChar)
			{
				counter++;
			}
			if (game->bord[i][j] == ' ')
			{
				hasEmpty = true;
			}
		}
		if (counter > betterLine.charQuantity && counter < 3 && hasEmpty)
		{
			betterLine.charQuantity = counter;
			betterLine.line = ROW;
			betterLine.num = i;
		}
		counter = 0;
		hasEmpty = false;
	}
	// �������
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game->bord[j][i] == game->userChar)
			{
				counter++;
			}
			if (game->bord[j][i] == ' ')
			{
				hasEmpty = true;
			}
		}
		if (counter > betterLine.charQuantity && counter < 3 && hasEmpty)
		{
			betterLine.charQuantity = counter;
			betterLine.line = COLUMN;
			betterLine.num = i;
		}
		counter = 0;
		hasEmpty = false;
	}
	// ������� ���������
	for (int i = 0; i < 3; i++)
	{
		if (game->bord[i][i] == game->userChar)
		{
			counter++;
		}
		if (game->bord[i][i] == ' ')
		{
			hasEmpty = true;
		}
	}
	if (counter > betterLine.charQuantity && counter < 3 && hasEmpty)
	{
		betterLine.charQuantity = counter;
		betterLine.line = MAIN_DIAG;
		betterLine.num = 0;
	}
	counter = 0;
	hasEmpty = false;
	// �������� ���������
	for (int i = 0; i < 3; i++)
	{
		if (game->bord[i][2 - i] == game->userChar && counter < 3)
		{
			counter++;
		}
		if (game->bord[i][2 - i] == ' ')
		{
			hasEmpty = true;
		}
	}
	if (counter > betterLine.charQuantity && counter < 3 && hasEmpty)
	{
		betterLine.charQuantity = counter;
		betterLine.line = SUB_DIAG;
		betterLine.num = 0;	
	}
	counter = 0;
	hasEmpty = false;
	if (betterLine.charQuantity == 0)
	{
		game->bord[1][1] = game->botChar;
	}
	else
	{
		switch (betterLine.line)
		{
		case ROW: {
			for (int j = 0; j < 3; j++)
			{
				if (game->bord[betterLine.num][j] == ' ')
				{
					game->bord[betterLine.num][j] = game->botChar;
					break;
				}
			}
		}break;
		case COLUMN: {
			for (int i = 0; i < 3; i++)
			{
				if (game->bord[i][betterLine.num] == ' ')
				{
					game->bord[i][betterLine.num] = game->botChar;
					break;
				}
			}
		}break;
		case MAIN_DIAG: {
			for (int i = 0; i < 3; i++)
			{
				if (game->bord[i][i] == ' ')
				{
					game->bord[i][i] = game->botChar;
					break;
				}
			}
		}break;
		case SUB_DIAG: {
			for (int i = 0; i < 3; i++)
			{
				if (game->bord[i][i] == ' ')
				{
					game->bord[i][i] = game->botChar;
					break;
				}
			}
		}break;
		default:
			break;
		}
	}
}
void userTurn(Game* game) {
	int x, y = 3, a;
	char b;
	while (true)
	{
		std::cout << "������� ����������(������� ������������ , ����� ��������������)." << std::endl;
		std::cin >> a >> b;
		x = a - 1;
		if (b == 'a')
		{
			y = 0;
		}
		if (b == 'b')
		{
			y = 1;
		}
		if (b == 'c')
		{
			y = 2;
		}
		if (x >= 0 && x <= 2 && y >= 0 && y <= 2 && game->bord[x][y] == ' ')
		{
			game->bord[x][y] = game->userChar;
			break;
		}
		else
		{
			std::cout << "������� ������������ ����������, ��������� ����." << std::endl;
		}
	}
}
bool updateGame(Game* game) {
	if (game->isUserTurn)
	{
		game->isUserTurn = false;
	}
	else
	{
		game->isUserTurn = true;
	}
	//������
	if (game->bord[0][0] == game->bord[0][1] && game->bord[0][0] == game->bord[0][2] && game->bord[0][0] != ' ')
	{
		if (game->bord[0][0] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}
	if (game->bord[1][0] == game->bord[1][1] && game->bord[1][0] == game->bord[1][2] && game->bord[1][0] != ' ')
	{
		if (game->bord[1][0] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}
	if (game->bord[2][0] == game->bord[2][1] && game->bord[2][0] == game->bord[2][2] && game->bord[2][0] != ' ')
	{
		if (game->bord[2][0] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}
	//�������
	if (game->bord[0][0] == game->bord[1][0] && game->bord[0][0] == game->bord[2][0] && game->bord[0][0] != ' ')
	{
		if (game->bord[0][0] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}if (game->bord[0][1] == game->bord[1][1] && game->bord[0][1] == game->bord[2][1] && game->bord[0][1] != ' ')
	{
		if (game->bord[0][1] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}if (game->bord[0][2] == game->bord[1][2] && game->bord[0][2] == game->bord[2][2] && game->bord[0][2] != ' ')
	{
		if (game->bord[0][2] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}
	//������� ���������
	if (game->bord[0][0] == game->bord[1][1] && game->bord[0][0] == game->bord[2][2] && game->bord[0][0] != ' ')
	{
		if (game->bord[0][0] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}
	//�������� ���������
	if (game->bord[0][2] == game->bord[2][2] && game->bord[0][2] == game->bord[2][0] && game->bord[0][2] != ' ')
	{
		if (game->bord[0][2] == game->userChar)
		{
			game->status = USER_WIN;
			return true;
		}
		else
		{
			game->status = BOT_WIN;
			return true;
		}
	}
	int counter = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game->bord[i][j] == ' ')
			{
				counter++;
			}
		}
	}
	if (!counter)
	{
		game->status = NOT_WIN;
		return true;
	}
	else
	{
		return false;
	}
}