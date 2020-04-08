#include<iostream>
#include<string>
#include"console.h";
#include<conio.h>
#include<ctime>
using namespace std;
#define consoleWidth 40
#define consoleHeight 25
int z = 100;
int score = 0;
enum class Trangthai
{
	UP,DOWN,LEFT,RIGHT
};
struct Toado
{
	int x, y;
};
struct Snake
{
	Toado dot[1000];
	int n;
	Trangthai tt;
}snake;
struct f
{
	int x, y;
};
struct Food
{
	f food[1];
}k;
void khoitao(Snake &snake, Food &k)
{
	snake.dot[0].x = 5;
	snake.dot[0].y = 5;
	snake.n = 3;
	snake.tt = Trangthai::DOWN;
	k.food[0].x = 10;
	k.food[0].y = 10;
}
void in(Snake snake, Food k)
{
	for(int i = 1; i < 34;i++)
	clrscr();
	for (int i = 0; i < consoleHeight; i++)
	{
		TextColor(11);
		gotoXY(consoleWidth, i);

		putchar(179);
	}
	gotoXY(consoleWidth + 1, 5);
	TextColor(6);
	cout << "	SCORE : " << score;
	gotoXY(consoleWidth + 1, 20);
	TextColor(11);
	cout << "   0 : +2 pits || M +10 pits ";
	gotoXY(consoleWidth + 1, 21);

	cout << "   y/Y = Yes || n/N = NO ";
	for (int i = 0; i < snake.n; i++)
	{
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		TextColor(14);
		putchar('o');
	}
}
void dotcon(Snake& snake)
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.dot[i] = snake.dot[i - 1];
	}
}
int  xuly(Snake& snake, Food& k)
{
	static int i = 1;
	if (snake.n == 3 || snake.dot[0].x != k.food[0].x || snake.dot[0].y != k.food[0].y)
	{
		gotoXY(k.food[0].x, k.food[0].y);
		TextColor(11);
		if (i == 5)
		{
			z = 50;
			TextColor(9);
			putchar('M');
		}
		else putchar('O');
	}
	// An
	if (snake.dot[0].x == k.food[0].x && snake.dot[0].y == k.food[0].y)
	{
		if (i == 5)

		{
			snake.n += 4;
			score += 10;
		}
		else
		{
			snake.n++;
			score += 2;
		}
	}
	// Thay doi x,y thuc an 
	if (snake.n > 3 && snake.dot[0].x == k.food[0].x && snake.dot[0].y == k.food[0].y)
	{
		srand((int)time(0));
		int a = rand() % 39;
		int b = rand() % 11 + 10;
		k.food[0].x = a;
		k.food[0].y = b;
		if (i == 5)
		{
			z = 100;
			i = 1;
		}
		else
			i++;

	}
	if (snake.dot[0].x < 0 || snake.dot[0].x >= consoleWidth || snake.dot[0].y < 0 || snake.dot[0].y >= consoleHeight)
		return -1;
	for (int i = 1; i < snake.n; i++)
	{
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
		{
			return -1;
		}
	}
}
	
void control(Snake& snake)
{
	dotcon(snake);
	if (_kbhit())
	{
		char phim = _getch();
		if (snake.tt == Trangthai::DOWN && (phim == 'w' || phim == 'W'))
		snake.tt = Trangthai::DOWN;
		else if (snake.tt == Trangthai::UP && (phim == 'S' || phim == 's'))
		snake.tt = Trangthai::UP;
		else if (snake.tt == Trangthai::LEFT && (phim == 'D' || phim == 'd'))
		snake.tt = Trangthai::LEFT;
		else if (snake.tt == Trangthai::RIGHT && (phim == 'a' || phim == 'A'))
		snake.tt = Trangthai::RIGHT;
		else if (phim == 'a' || phim == 'A')
			snake.tt = Trangthai::LEFT;
		else	if (phim == 's' || phim == 'S')
			snake.tt = Trangthai::DOWN;
		else	if (phim == 'D' || phim == 'd')
			snake.tt = Trangthai::RIGHT;
		else		if (phim == 'w' || phim == 'W')
			snake.tt = Trangthai::UP;
	}
	if (snake.tt == Trangthai::DOWN)
		snake.dot[0].y++;
	else if (snake.tt == Trangthai::RIGHT)
		snake.dot[0].x++;
	else if (snake.tt == Trangthai::LEFT)
		snake.dot[0].x--;
	else if (snake.tt == Trangthai::UP)
		snake.dot[0].y--;
}
int main()
{
	score = 0;
	int m = 0;
	khoitao(snake,k);
	while (1)
	{
		clrscr();
		control(snake);
		in(snake,k);
		// dieu khien 
		
		m = xuly(snake, k);
		if (m == -1)
		{
			gotoXY(consoleWidth + 1, 6);
			TextColor(11);
			cout << "	LOSE !! TRY ? ";
			while (1)
			{
				

				
					char key = _getch();
					if (key == 'y' || key == 'Y')
						return main();
					else if (key == 'n' || key == 'N')
						return 0;
				
			}
		}
		Sleep(z);
	}
} 