/*
Title: Assignment - 4
Author: Priscilla Lo
Objective: To program a Battleship game that allows for a human user to play against an AI or watch two AIs playing against each other.
Using an abstract class and multiple derived classes for the different types of ships. (note: to test game, you can see the locations of the
opponent's ships by commenting out line 123)
*/

#include "Boat.h"
#include <Windows.h>

//Global variables counting number of ships sank by each player
int HITS1 = 0;
int HITS2 = 0;

enum State { MainMenu, Play, AI, Quit };

void gotoXY(int x, int y);
void drawBoard(int player);
void guess(int x, int y, int player, Boat &ship);
bool collision(Boat &ship1, Boat &ship);

void main()
{
	//State change variables
	State current = State::MainMenu;
	int select = 0;

	//Gameplay variables
	int ok = 0;
	int turn = 1;
	int guessX = 0;
	int guessY = 0;

	srand(time(NULL));

	while (true)
	{
		//Player1 variables (need to be declared in here to create new after deleted, such as when changing states)
		AircraftCarrier *AC1 = new AircraftCarrier();
		Battleship *B1 = new Battleship();
		Submarine *S1 = new Submarine();
		Cruiser *C1 = new Cruiser();
		Destroyer *D1 = new Destroyer();

		//Player2 variables
		AircraftCarrier *AC2 = new AircraftCarrier();
		Battleship *B2 = new Battleship();
		Submarine *S2 = new Submarine();
		Cruiser *C2 = new Cruiser();
		Destroyer *D2 = new Destroyer();

		if (current == State::MainMenu)
		{
			system("CLS");

			cout << endl << "                            ~ B A T T L E S H I P ~" << endl;
			cout << "------------------------------------------------------------------------------------" << endl;/*art adapted and modified from http://ascii.co.uk/art/titanic */
			cout << "         _ .....Hit me I dare you......" << endl;
			cout << "        / " << (char)92 << endl;
			cout << "    __/    " << (char)92 << "_" << endl;
			cout << "   /_  -  " << (char)92 << "  " << (char)92 << "                      ,:',:`,:' ........Oh yeah, yes I will...HA!" << endl;
			cout << "  / / /     " << (char)92 << " " << (char)92 << "                  __||_||_||_||___" << endl;
			cout << " |    |     / |             ____[" << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << (char)34 << "]___" << endl;
			cout << " /   /     " << (char)92 << "   " << (char)92 << "            " << (char)92 << " " << (char)34 << " " << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << (char)39 << "  /"  << endl;
			cout << " ~~^~^~~^~~^~^~^~~^~^~^~~^~~^~^~^^~^~^~^~^~^~^~^~~^~^~^~^~~^~^~~^~^~^~^~~^~^~^~^~^~" << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "        [1] - Play Against AI       [2] - Watch AI vs AI       [3] - Quit" << endl;
			cin >> select;
		}
		if (current == State::Play || select == 1)
		{
			system("CLS");

			//PLAYER 1 (AI)
			gotoXY(3, 1);
			cout << "REIGNING";
			gotoXY(1, 2);
			cout  << "AI CHAMPION" << endl;
			gotoXY(15, 1); //label axes of board
			cout << "0123456789";
			for (int i = 0; i < 10; i++)
			{
				gotoXY(14, (i+2));
				cout << i;
			}

			drawBoard(1);

			//generating ships for opponent
			AC1->setPlayer(1);
			AC1->generateShip();
			AC1->drawShip();

			B1->setPlayer(1);
			do
			{
				B1->generateShip();
			} while (collision(*AC1, *B1) == true); //make sure not colliding with previously generated ship
			B1->drawShip();

			S1->setPlayer(1);
			do
			{
			S1->generateShip();
			} while (collision(*AC1, *S1) == true || collision(*B1, *S1) == true);
			S1->drawShip();

			C1->setPlayer(1);
			do
			{
			C1->generateShip();
			} while (collision(*AC1, *C1) == true || collision(*B1, *C1) == true || collision(*S1, *C1) == true);
			C1->drawShip();

			D1->setPlayer(1);
			do
			{
			D1->generateShip();
			} while (collision(*AC1, *D1) == true || collision(*B1, *D1) == true || collision(*S1, *D1) == true || collision(*C1, *D1) == true);
			D1->drawShip();

			drawBoard(1); //to hide player 1 (opposing player) ships

			//line of separation
			gotoXY(0, 13);
			cout << "-----------------------------------------------------" << endl;

			//PLAYER 2 (bottom board, YOU)
			gotoXY(4, 15);
			cout << "LOWLY";
			gotoXY(1, 16);
			cout << "HUMAN NOOB";
			gotoXY(15, 14); //label axes of board
			cout << "0123456789";
			for (int i = 0; i < 10; i++)
			{
				gotoXY(14, (i + 15));
				cout << i;
			}
			drawBoard(2);

			//generating your ships
			AC2->setPlayer(2);
			AC2->generateShip();
			AC2->drawShip();

			B2->setPlayer(2);
			do
			{
				B2->generateShip();
			} while (collision(*AC2, *B2) == true); //make sure not colliding with previously generated ship
			B2->drawShip();

			S2->setPlayer(2);
			do
			{
				S2->generateShip();
			} while (collision(*AC2, *S2) == true || collision(*B2, *S2) == true);
			S2->drawShip();

			C2->setPlayer(2);
			do
			{
				C2->generateShip();
			} while (collision(*AC2, *C2) == true || collision(*B2, *C2) == true || collision(*S2, *C2) == true);
			C2->drawShip();

			D2->setPlayer(2);
			do
			{
				D2->generateShip();
			} while (collision(*AC2, *D2) == true || collision(*B2, *D2) == true || collision(*S2, *D2) == true || collision(*C2, *D2) == true);
			D2->drawShip();
			
			while (HITS1 < 5 && HITS2 < 5) //repeat while ship objects still exist, there are 5 objects
			{
				turn = 1; //make equal to 1 again in case of entering play after watching AI battle
				gotoXY(0, 26); //go to end of battleship boards and ask player to enter a position to guess
				for (int i = 0; i < 10; i++)
				{
					cout << "                                 " << endl; //to hide previous
				}
				if (turn == 1) //Player's turn
				{
					gotoXY(0, 26); //go to end of battleship boards and ask player to enter a position to guess
					for (int i = 0; i < 10; i++)
					{
						cout << "                                 " << endl; //to hide previous
					}
					gotoXY(0, 26);
					cout << "Enter a coordinate X: " << endl;//WILL BE CIN COORDINATES TO SINK SHIPS!! will compare to array list of coordinates
					cin >> guessX;
					cout << "Enter a coordinate Y: " << endl;
					cin >> guessY;
					gotoXY(0, 32);
					guess(guessX, guessY, 2, *AC1);
					guess(guessX, guessY, 2, *B1);
					guess(guessX, guessY, 2, *S1);
					guess(guessX, guessY, 2, *C1);
					guess(guessX, guessY, 2, *D1);

					cout << endl <<"Enter any integer to continue." << endl;
					cin >> ok;

					turn = 2;
				}
				if (turn == 2 && HITS2 != 5) //AI's turn
				{
					gotoXY(0, 26); //go to end of battleship boards and ask player to enter a position to guess
					for (int i = 0; i < 10; i++)
					{
						cout << "                                 " << endl; //to hide previous
					}
					gotoXY(0, 26);
					cout << "The computer guesses: " << endl;//randomly generated guess for AI
					guessX = rand() % 10;
					guessY = rand() % 10;
					cout << "(" << guessX << ", " << guessY << ")" << endl;
					guess(guessX, guessY, 1, *AC2);
					guess(guessX, guessY, 1, *B2);
					guess(guessX, guessY, 1, *S2);
					guess(guessX, guessY, 1, *C2);
					guess(guessX, guessY, 1, *D2);

					Sleep(1000);

					turn = 1;
				}
			}
			
			if (HITS2 == 5)
			{
				gotoXY(0, 26);
				for (int i = 0; i < 10; i++)
				{
					cout << "                                 " << endl; //to hide previous
				}
				gotoXY(0, 26);
				cout << "CONGRATULATIONS, YOU WIN!!!" << endl << endl;

				HITS1 = 0; //reset variables
				HITS2 = 0;
			}
			if (HITS1 == 5)
			{
				gotoXY(0, 26);
				for (int i = 0; i < 10; i++)
				{
					cout << "                                 " << endl; //to hide previous
				}
				gotoXY(0, 26);
				cout << "AS EXPECTED, YOU LOST TO THE AI!!!" << endl << endl;

				HITS1 = 0; //reset variables
				HITS2 = 0;
			}

			cout << "What would you like to do now?" << endl << "[1] - Return to Main Menu [2] - Play again [3] - Quit" << endl;
			cin >> select;
		}
		if (current == State::AI || select == 2) //would select random sets of numbers in range of the board
		{
			system("CLS");

			//AI 1
			gotoXY(4, 2);
			cout << "AI 1:" << endl;
			gotoXY(2, 3);
			cout << "For total";
			gotoXY(1, 4);
			cout << "Destruction";
			gotoXY(15, 1); //label axes of board
			cout << "0123456789";
			for (int i = 0; i < 10; i++)
			{
				gotoXY(14, (i + 2));
				cout << i;
			}

			drawBoard(1);

			//generating ships for AI 1
			AC1->setPlayer(1);
			AC1->generateShip();
			AC1->drawShip();

			B1->setPlayer(1);
			do
			{
				B1->generateShip();
			} while (collision(*AC1, *B1) == true);
			B1->drawShip();

			S1->setPlayer(1);
			do
			{
				S1->generateShip();
			} while (collision(*AC1, *S1) == true || collision(*B1, *S1) == true);
			S1->drawShip();

			C1->setPlayer(1);
			do
			{
				C1->generateShip();
			} while (collision(*AC1, *C1) == true || collision(*B1, *C1) == true || collision(*S1, *C1) == true);
			C1->drawShip();

			D1->setPlayer(1);
			do
			{
				D1->generateShip();
			} while (collision(*AC1, *D1) == true || collision(*B1, *D1) == true || collision(*S1, *D1) == true || collision(*C1, *D1) == true);
			D1->drawShip();

			//drawBoard(1); //to hide player 1 (opposing player) ships

			//line of separation
			gotoXY(0, 13);
			cout << "-----------------------------------------------------" << endl;

			//AI 2
			gotoXY(4, 15);
			cout << "AI 2:" << endl;
			gotoXY(3, 16);
			cout << "For the";
			gotoXY(3, 17);
			cout << "Freedom";
			gotoXY(3, 18);
			cout << "of the";
			gotoXY(2, 19);
			cout << "Human Race";
			gotoXY(15, 14); //label axes of board
			cout << "0123456789";
			for (int i = 0; i < 10; i++)
			{
				gotoXY(14, (i + 15));
				cout << i;
			}
			drawBoard(2);

			//generating AI 2 ships
			AC2->setPlayer(2);
			AC2->generateShip();
			AC2->drawShip();

			B2->setPlayer(2);
			do
			{
				B2->generateShip();
			} while (collision(*AC2, *B2) == true);
			B2->drawShip();

			S2->setPlayer(2);
			do
			{
				S2->generateShip();
			} while (collision(*AC2, *S2) == true || collision(*B2, *S2) == true);
			S2->drawShip();

			C2->setPlayer(2);
			do
			{
				C2->generateShip();
			} while (collision(*AC2, *C2) == true || collision(*B2, *C2) == true || collision(*S2, *C2) == true);
			C2->drawShip();

			D2->setPlayer(2);
			do
			{
				D2->generateShip();
			} while (collision(*AC2, *D2) == true || collision(*B2, *D2) == true || collision(*S2, *D2) == true || collision(*C2, *D2) == true);
			D2->drawShip();

			while (HITS1 < 5 && HITS2 < 5) //repeat while ship objects still exist
			{
				turn = 1;
				gotoXY(0, 26); //go to end of battleship boards and ask player to enter a position to guess
				for (int i = 0; i < 10; i++)
				{
					cout << "                                 " << endl; //to hide previous
				}
				if (turn == 1) //AI 2's turn
				{
					gotoXY(0, 26); //go to end of battleship boards and ask player to enter a position to guess
					for (int i = 0; i < 10; i++)
					{
						cout << "                                 " << endl; //to hide previous
					}
					gotoXY(0, 26);
					gotoXY(0, 26);
					cout << "AI 2 guesses: " << endl;//randomly generated guess for AI
					guessX = rand() % 10;
					guessY = rand() % 10;
					cout << "(" << guessX << ", " << guessY << ")" << endl;
					guess(guessX, guessY, 2, *AC1);
					guess(guessX, guessY, 2, *B1);
					guess(guessX, guessY, 2, *S1);
					guess(guessX, guessY, 2, *C1);
					guess(guessX, guessY, 2, *D1);

					Sleep(1);
					turn = 2;
				}
				if (turn == 2 && HITS2 != 5) //AI 1's turn
				{
					gotoXY(0, 26); //go to end of battleship boards and ask player to enter a position to guess
					for (int i = 0; i < 10; i++)
					{
						cout << "                                 " << endl; //to hide previous
					}
					gotoXY(0, 26);
					cout << "AI 1 guesses: " << endl;//randomly generated guess for AI
					guessX = rand() % 10;
					guessY = rand() % 10;
					cout << "(" << guessX << ", " << guessY << ")" << endl;
					guess(guessX, guessY, 1, *AC2);
					guess(guessX, guessY, 1, *B2);
					guess(guessX, guessY, 1, *S2);
					guess(guessX, guessY, 1, *C2);
					guess(guessX, guessY, 1, *D2);

					Sleep(1);
					turn = 1;
				}
			}

			if (HITS2 == 5)
			{
				gotoXY(0, 26);
				for (int i = 0; i < 10; i++)
				{
					cout << "                                 " << endl; //to hide previous
				}
				gotoXY(0, 26);
				cout << "CONGRATULATIONS, AI 2 IS THE NEW OVERLORD!!!" << endl << endl;
				HITS1 = 0; //reset variables
				HITS2 = 0;
			}
			if (HITS1 == 5)
			{
				gotoXY(0, 26);
				for (int i = 0; i < 10; i++)
				{
					cout << "                                 " << endl; //to hide previous
				}
				gotoXY(0, 26);
				cout << "SALUTE OUR NEW PRESDIENT AI 1!!" << endl << endl;
				HITS1 = 0; //reset variables
				HITS2 = 0;
			}

			cout << "What would you like to do now?" << endl << "[1] - Return to Main Menu [2] - Play again [3] - Quit" << endl;
			cin >> select;
		}
		if (current == State::Quit || select == 3)
		{
			system("CLS");
			cout << "Terminating." << endl;
			break;
		}
	}

	
}

void gotoXY(int x, int y)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(ConsoleHandle, position);
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.bVisible = false;
	CursorInfo.dwSize = 10;
	SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
}

void drawBoard(int player)
{
	int myArray[10][10];
	if (player == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				myArray[i][j] = 176;
				gotoXY((i + 15), (j+2));
				cout << (char)myArray[i][j] << endl;
			}
		}
	}
	if (player == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				myArray[i][j] = 176;
				gotoXY((i + 15), (j + 15));
				cout << (char)myArray[i][j] << endl;
			}
		}
	}
}

void guess(int x, int y, int player, Boat &ship)
{
	if (player == 1)
	{
		for (int i = 0; i < ship.getSize(); i++)
		{
			if (ship.getPosition(0, i) != 100 && ship.getPosition(1, i) != 100)
			{
				if (x == ship.getPosition(0, i) && y == ship.getPosition(1, i)) //needs to check for all X and Y values of ship
				{
					gotoXY(x + 15, y + 15);
					cout << "X";

					gotoXY(0, 31);
					ship.sound();
					ship.counter = 0;
					for (int i = 0; i < ship.getSize(); i++) //CHECK IF ALL POSITIONS HAVE BEEN HIT, loop through array
					{
						if (ship.getPosition(0, i) == 100)
						{
							ship.counter++;
						}
					}

					if (ship.counter == (ship.getSize() - 1))
					{
						delete &ship;
						HITS1++;
					}
					else
					{
						cout << "They hit your " << ship.getName() << endl;
					}

					ship.setPosition(0, i, 100); //set to other value to "remove" from array
					ship.setPosition(1, i, 100);
				}

			}

		}
	}
	if (player == 2)
	{
		for (int i = 0; i < ship.getSize(); i++)
		{
			if (ship.getPosition(0, i) != 100 && ship.getPosition(1, i) != 100)
			{
				if (x == ship.getPosition(0, i) && y == ship.getPosition(1, i))
				{
					gotoXY(x + 15, y + 2);
					cout << "X";

					gotoXY(0, 31);
					ship.sound();
					ship.counter = 0;
					for (int i = 0; i < ship.getSize(); i++) //CHECK IF ALL POSITIONS HAVE BEEN HIT, loop through array
					{
						if (ship.getPosition(0,i) == 100)
						{	
							ship.counter++;
						}
					}
					if (ship.counter == (ship.getSize()-1))
					{
						delete &ship;
						HITS2++;
					}
					else
					{
						cout << "You hit their " << ship.getName() << endl;
					}
					ship.setPosition(0, i, 100); //set to other value (out of range) to remove from array
					ship.setPosition(1, i, 100);
				}
			}
		}
	}
}

bool collision(Boat &ship1, Boat &ship)
{
	for (int i = 0; i < ship1.getSize(); i++)
	{
		for (int j = 0; j < ship.getSize(); j++)
		{
			if (ship1.getPosition(0, i) == ship.getPosition(0, j) && ship1.getPosition(1, i) == ship.getPosition(1, j))
			{
				return true;
			}
		}
	}
	return false;
}