#include <iostream>
using namespace std;

#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstring>
#include <time.h>
#include <random>

#define WIDTH 40
#define HEIGHT 20
#define BODY 'O'
#define APPLE '*'

enum class Direction
{
	up,
	right,
	down,
	left
};
struct Point
{
	int x;
	int y;
};

#pragma region GlobalVariable

vector<Point> snake = {
	Point{ WIDTH / 2 + 2, HEIGHT / 2 },
	Point{ WIDTH / 2 + 1, HEIGHT / 2 },
	Point{ WIDTH / 2, HEIGHT / 2 },
	Point{ WIDTH / 2 - 1, HEIGHT / 2 },
	Point{ WIDTH / 2 - 2, HEIGHT / 2 }
};
Direction direction = Direction::right;
Point apple;
int score = 0;
int speed = 300;
Point prevTail;
#pragma endregion

#pragma region Prototype
void gotoxy(int, int);
void drawSnake();
void drawSnakePart(Point);
void ShowConsoleCursor(bool);
void move();
void drawHeadnTail();
void genApple();
bool isHitWall();
bool isBiteItself();
bool isAteApple();
void growing();
void displayScore();
void showEndMenu();
void startGame();
void resetSnake();
void showStartMenu();
void drawBox();
#pragma endregion

int main()
{
	showStartMenu();
	return 0;
}
void drawSnake()
{
	for (size_t i = 0; i < snake.size(); i++)
		drawSnakePart(snake[i]);
}
void drawSnakePart(Point p)
{
	gotoxy(p.x, p.y);
	cout << BODY;
}

void drawBox()
{
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	gotoxy(0, HEIGHT);
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << '|';
	}
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(WIDTH, i);
		cout << '|';
	}
} 

void displayScore()
{
	gotoxy(WIDTH + 5, 2);
	cout << "Diem so: " << score;
}
void showEndMenu()
{
	gotoxy(0, 0);
	char option;
	do
	{
		system("cls");
		cout << "Ket thuc tro choi!" << endl;
		cout << "Diem so: " << score << endl;
		cout << "Ban co muon choi lai khong ([y]/[n]): ";
		cin >> option;
		option = tolower(option);
	} while (option != 'y' && option != 'n');
	if (option == 'y')
	{
		resetSnake();
		startGame();
	}
	else if (option == 'n')
		exit(1);
}
void startGame()
{
	system("cls");
	ShowConsoleCursor(false);
	drawBox();
	drawSnake();
	genApple();
	displayScore();
	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			ch = tolower(ch);
			if (ch == 'a' && direction != Direction::right)
				direction = Direction::left;
			else if (ch == 'w' && direction != Direction::down)
				direction = Direction::up;
			else if (ch == 's' && direction != Direction::up)
				direction = Direction::down;
			else if (ch == 'd' && direction != Direction::left)
				direction = Direction::right;
			else if (ch == 'q')
			{
				showEndMenu();
				break;
			}
		}
		move();
		drawHeadnTail();
		if (isAteApple())
		{
			score++;
			displayScore();
			growing();
			genApple();
		}
		if (isBiteItself())
		{
			ShowConsoleCursor(true);
			showEndMenu();
			break;
		}
		if (isHitWall())
		{
			ShowConsoleCursor(true);
			showEndMenu();
			break;
		}
		Sleep(speed);
	}
}
void resetSnake()
{
	score = 0;
	direction = Direction::right;
	snake = {
		Point{ WIDTH / 2 + 2, HEIGHT / 2 },
		Point{ WIDTH / 2 + 1, HEIGHT / 2 },
		Point{ WIDTH / 2, HEIGHT / 2 },
		Point{ WIDTH / 2 - 1, HEIGHT / 2 },
		Point{ WIDTH / 2 - 2, HEIGHT / 2 }
	};
}
void showStartMenu()
{
	int option=0;
	while (option != 1 && option != 2)
	{
		system("cls");
		cout << "Chao mung ban da den voi game Ran san moi!" << endl;
		cout << "Lua chon:" << endl;
		cout << "1. Bat dau" << endl;
		cout << "2. Thoat" << endl;
		cout << "Nhap lua chon: ";
		cin >> option;
	};
	if (option == 1)
	{
		system("cls");
		int t = 0;
		while (t< 1 || t >5)
		{
			system("cls");
			cout << "Chon cap do (1 - 5): ";
			cin >> t;
		};
		speed = 600 - t * 100;
		system("cls");
		cout << "Meo: Trong khi choi game, ban co the nhan 'q' de thoat" << endl;
		gotoxy(0, 3);
		cout << "Ready!";
		Sleep(1000);
		for (size_t i = 3; i > 0; i--)
		{
			gotoxy(0, 3);
			cout << i << "         ";
			Sleep(1000);
		}
		gotoxy(0, 3);
		cout << "GO!";
		Sleep(1000);
		startGame();
	}
	else if (option == 2)
		exit(1);
}
void move()
{
	prevTail = snake.back();
	for (size_t i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];
	if (direction == Direction::up)
		snake[0].y -= 1;
	else if (direction == Direction::down)
		snake[0].y += 1;
	else if (direction == Direction::left)
		snake[0].x -= 1;
	else if (direction == Direction::right)
		snake[0].x += 1;
}
void drawHeadnTail()
{
	gotoxy(snake[0].x, snake[0].y);
	cout << BODY;
	gotoxy(prevTail.x, prevTail.y);
	cout << ' '; 
}
void genApple()
{
	srand(time(0));
	int x = rand() % (WIDTH - 1) + 1;
	int y = rand() % (HEIGHT - 1) + 1;
	apple = {
		x,
		y,
	};
	gotoxy(x, y);
	cout << APPLE;
}
bool isHitWall()
{
	return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}
bool isBiteItself()
{
	Point head = snake[0];
	for (size_t i = 1; i < snake.size(); i++)
		if (head.x == snake[i].x && head.y == snake[i].y)
			return true;
	return false;
}
bool isAteApple()
{
	return snake[0].x == apple.x && snake[0].y == apple.y;
}
void growing()
{
	snake.push_back(prevTail);
}

#pragma region ConsoleFunction

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}