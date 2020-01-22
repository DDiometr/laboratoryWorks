#include<iostream>

#include<time.h>


enum Status{
   PLAY,            // Игра продолжается
   USER_WIN,        // Игрок победил
   BOT_WIN,         // Бот победил
   NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
};

struct Game {
	char bord[3][3];  // Игровое поле
	bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
	char userChar;    // Символ которым играет пользователь
	char botChar;     // Символ которым играет бот
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
		std::cout << "Игрок победил" << std::endl;
	}
	if (game1.status == BOT_WIN)
	{
		std::cout << "Бот победил" << std::endl;
	}
	if (game1.status == NOT_WIN)
	{
		std::cout << "Ничья" << std::endl;
	}
	
	system("PAUSE");
}