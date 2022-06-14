#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

bool gameOver;
const int height = 20, width = 50;
int x, y, fruitX, fruitY, score = 0;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP=0 ,LEFT,RIGHT,UP,DOWN };
eDirection dir;

void setUp() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	
}
void draw() {

	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j==width-1 )
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "f";
			else 
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "SCORE : " << score << endl;

	
}
void input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case '4':
			dir = LEFT;
			break;
		case '8':
			dir = UP;
			break;
		case '2':
			dir = DOWN;
			break;
		case '6':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int tempX, tempY;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}


	switch (dir) {
	case LEFT:
		x--; 
		break; 
	case RIGHT:
		x++;
		break;
	case UP:
		y--;		
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y> height || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY) {

		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}


}




int main() {
		
	setUp();
	while (!gameOver) {
		draw();
		input();
		logic();
		Sleep(10);
	}

	return 0;
}