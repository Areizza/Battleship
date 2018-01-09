#include "Boat.h"

Boat::Boat()
{
	m_x = 0;
	m_y = 0;
	m_ascii = 0;
	m_size = 0;
	m_position[2][5] = { };
	m_player = 0;
	m_name = " ";
	counter = 0;
}

Boat::~Boat()
{
	if (m_player == 1)
	{
		cout << "You sank their " << getName() << endl;
	}
	else
	{
		cout << "They sank your " << getName() << endl;
	}
}

//METHODS
void Boat::gotoXY(int x, int y)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(ConsoleHandle, position);
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.bVisible = false;
	CursorInfo.dwSize = 10;
	SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
}

void Boat::generateShip()
{
	int orient = rand() % 10;
	int boundary = 10- m_size;

	if (m_player == 1)
	{
		m_x = rand() % boundary + 15;
		m_y = rand() % boundary + 2;

		m_xprev = m_x - 15;
		m_yprev = m_y - 2;

		if (orient % 2 == 0) //HORIZONTAL
		{
			m_ascii = 205;
			for (int i = 0; i < m_size; i++)
			{
				m_position[0][i] = m_x - 15;
				m_position[1][i] = m_y - 2;
				m_x++;
			}
		}
		else //VERTICAL
		{
			m_ascii = 186;
			for (int i = 0; i < m_size; i++)
			{
				m_position[0][i] = m_x - 15;
				m_position[1][i] = m_y - 2;
				m_y++;
			}
		}
	}
	else
	{
		m_x = rand() % boundary + 15;
		m_y = rand() % boundary + 15;

		m_xprev = m_x - 15;
		m_yprev = m_y - 15;

		if (orient % 2 == 0) //HORIZONTAL
		{
			m_ascii = 205;
			for (int i = 0; i < m_size; i++)
			{
				m_position[0][i] = m_x - 15;
				m_position[1][i] = m_y - 15;
				m_x++;
			}
		}
		else //VERTICAL
		{
			m_ascii = 186;
			for (int i = 0; i < m_size; i++)
			{
				m_position[0][i] = m_x - 15;
				m_position[1][i] = m_y - 15;
				m_y++;
			}
		}
	}
}

void Boat::drawShip()
{
	if (m_player == 1)
	{
		for (int i = 0; i < m_size; i++)
		{
			gotoXY((m_position[0][i] + 15), (m_position[1][i] + 2));
			cout << (char)m_ascii;
		}
	}
	else
	{
		for (int i = 0; i < m_size; i++)
		{
			gotoXY((m_position[0][i] + 15), (m_position[1][i] + 15));
			cout << (char)m_ascii;
		}
	}
}

//VIRTUAL METHOD (outputs sound when hit)
void AircraftCarrier::sound()
{
	cout << "BOOOOOOOM!" << endl;
}
void Battleship::sound()
{
	cout << "BANG!" << endl;
}
void Submarine::sound()
{
	cout << "BLUBBADUBDUB!" << endl;
}
void Cruiser::sound()
{
	cout << "PLOP!" << endl;
}
void Destroyer::sound()
{
	cout << "KERPLUNK!" << endl;
}

#pragma region GETTERS
int Boat::getX()
{
	return m_x;
}
int Boat::getY()
{
	return m_y;
}
int Boat::getSize()
{
	return m_size;
}
string Boat::getName()
{
	return m_name;
}
int Boat::getPosition(int index, int index2)
{
	return m_position[index][index2];
}
#pragma endregion

#pragma region SETTERS
void Boat::setX(int x)
{
	m_x = x;
}
void Boat::setY(int y)
{
	m_y = y;
}
void Boat::setPlayer(int player)
{
	m_player = player;
}
void Boat::setPosition(int index, int index2, int value)
{
	m_position[index][index2] = value;
}
#pragma endregion

AircraftCarrier::AircraftCarrier()
{
	m_size = 5;
	m_name = "Aircraft Carrier";
}

Battleship::Battleship()
{
	m_size = 4;
	m_name = "Battleship";
}

Submarine::Submarine()
{
	m_size = 3;
	m_name = "Submarine";
}

Cruiser::Cruiser()
{
	m_size = 3;
	m_name = "Cruiser";
}

Destroyer::Destroyer()
{
	m_size = 2;
	m_name = "Destroyer";
}