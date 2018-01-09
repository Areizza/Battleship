#include <iostream>
#include <time.h>
#include <string>
#include <Windows.h>

using namespace std;

class Boat
{
	protected:
		int m_x;
		int m_y;
		int m_xprev;
		int m_yprev;
		int m_ascii;
		int m_size;
		int m_position[2][5]; //because this is the largest array needed
		int m_player;
		string m_name;

	public:
		Boat();
		~Boat();

		void gotoXY(int x, int y);
		void generateShip();
		void drawShip();
		virtual void sound() = 0;

		int getX();
		int getY();
		int getSize();
		string getName();
		int getPosition(int index, int index2);

		void setX(int x);
		void setY(int y);
		void setPlayer(int player);
		void setPosition(int index, int index2, int value);

		int counter;
};

class AircraftCarrier : public Boat
{
public:
	AircraftCarrier();
	void sound();
};

class Battleship : public Boat
{
public:
	Battleship();
	void sound();
};

class Submarine : public Boat
{
public:
	Submarine();
	void sound();
};

class Cruiser : public Boat
{
public:
	Cruiser();
	void sound();
};

class Destroyer : public Boat
{
public:
	Destroyer();
	void sound();
};