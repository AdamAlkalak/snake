#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define UP 72  // Up Arrow 
#define DOWN 80 // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77  // Right Arrow 
#define ESC 27  // Escape Key
#define STARTSIZE 20 //Set the snake start size
#define ZERO 0

struct Point
{
	int x;
	int y;
};

typedef struct Point Point;

void gotoxy(int y, int x);
int getKey();
void printSharps();
int selfIntersect(Point snake[], int len);
Point randomFruits();
int wallHit(Point snake[], int len);

void main()
{
	while (1)
	{
		char direction = ZERO, lastDirection = RIGHT;
		int x = 40, y = 12, playerChoice = -1, pLength = STARTSIZE / 2, sLength = 1, c;  // x for coulmn and y for line 
		Point snake[STARTSIZE], p, fruit;

		srand(time(NULL));

		p.x = 40;
		p.y = 12;

		while (playerChoice == -1)//start menu
		{
			printf("Hello and welcome to SNAKE!\nPlease choose your level:\n");
			printf("0. Exit\n1. Basic level\n2. Intermidiate level\n3. Advanced level\n");
			scanf("%d", &playerChoice);

			if (playerChoice < 0 || playerChoice > 3)
			{
				printf("Invalid choice, please try again\n");
				playerChoice = -1;
			}
			if (playerChoice == 0)
			{
				printf("Good bye!");
				break;
			}
		}

		if (playerChoice == 0)
			break;

		system("cls"); //clears the screen

		printSharps(); //prints the borders

		fruit = randomFruits();
		gotoxy(fruit.x, fruit.y);
		printf("$");

		gotoxy(x, y);// start from the middle of the screen

		direction = RIGHT;// the direction is Right untill an arrow hit

		while (direction != ESC)
		{
			Sleep(150);// sleeps for a second before continuing to the next command

			lastDirection = direction;

			if (_kbhit()) //only if any key was hit
				direction = getKey();  // change direction	// make a move in current direction if no change

			if (direction != ESC && direction != RIGHT && direction != LEFT && direction != UP && direction != DOWN)
				direction = lastDirection; //checks that only arrows and esc got hit.

			switch (direction)
			{
			case RIGHT:
				p.x++;
				break;
			case DOWN:
				p.y++;
				break;
			case LEFT:
				p.x--;
				break;
			case UP:
				p.y--;
				break;
			}

			gotoxy(p.x, p.y);
			printf("@");

			c = wallHit(snake, sLength); //checks if the snake hit a wall
			if (c == 1)
				direction = ESC;

			if (snake[0].x == fruit.x && snake[0].y == fruit.y) //checks if the snakes head ate a fruit, and then generated another fruit
			{
				fruit = randomFruits();
				gotoxy(fruit.x, fruit.y);
				printf("$");
				sLength++;
				pLength++;
			}

			if (pLength == STARTSIZE)//winning massage if the sanke lenght is 20
			{
				system("cls");
				printf("####################\n");
				printf("YOU WIN! :)\n");
				printf("####################\n");
				direction = ESC;
			}

			if (sLength < pLength) //prints the snake according to STARTSIZE
			{
				for (int i = sLength - 1; i >= 0; i--)
					snake[i + 1] = snake[i];
				snake[0] = p;
				sLength++;
			}

			else
			{
				gotoxy(snake[pLength - 1].x, snake[pLength - 1].y); //moves the head and delete the tail
				printf(" ");
				for (int i = pLength - 2; i >= 0; i--)
					snake[i + 1] = snake[i];
				snake[0] = p;
			}

			if (selfIntersect(snake, sLength))//checks if the snake ate itself
			{
				system("cls");
				printf("####################\n");
				printf("SELF INTERSECTION\n");
				printf("####################\n");
				direction = ESC;
			}
		}
		Sleep(2000);//after showing the suitable massage, sleeps for 2 sec and then clears the screen.
		system("cls");
		playerChoice = -1;
	}
}
// This function moves the cursor to the line y and column x.
// (0,0) is the upper left corner of the screen.
void gotoxy(int y, int x)
{
	printf("\x1b[%d;%df", x + 1, y + 1);
}

// This function gets keyCodes for special keys such as arrows , escape and others
// It returns the Key code such as 72 for arrow up, 27 for Escape... 
int getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}

int selfIntersect(Point snake[], int len)//this function checks for self intersection
{
	if (len >= 4)
		for (int i = 4; i < len; i++)
			if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
				return 1;
	return 0;
}

void printSharps()//this function prints the borders
{
	for (int i = 0; i < 75; i++)
		printf("#");
	printf("\n");
	for (int i = 0; i < 25; i++)
	{
		printf("#");
		for (int j = 0; j < 73; j++)
			printf(" ");
		printf("#\n");
	}
	for (int i = 0; i < 75; i++)
		printf("#");
	printf("\n");
}

Point randomFruits()//generates random fruit location
{
	Point fruit;

	fruit.x = 1 + rand() % 74;
	fruit.y = 1 + rand() % 24;

	return fruit;
}

int wallHit(Point snake[], int len)//checks if the snake hit a wall
{
	if (snake[0].x == 74 || snake[0].x == 0 || snake[0].y == 0 || snake[0].y == 25)
	{
		system("cls");
		printf("####################\n");
		printf("Wall hit! Game over\n");
		printf("####################\n");
		return 1;
	}
	return 0;
}
