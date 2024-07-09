#include <iostream>
#include "CSimulator.h"

Position<int>& Vehicle::GetCoordinates() noexcept
{
	return coordinates;
}

void Vehicle::SetCoordinates(int x, int y) noexcept
{
	coordinates.x = x;
	coordinates.y = y;
}

void Car::Forward() 
{
	switch (traject)
	{
	case South:
		coordinates.y--;
		break;

	case West:
		coordinates.x--;
		break;
	case North:
		coordinates.y++;
		break;
	case East:
		coordinates.x++;
		break;
	default:
		break;
	}

}

void Car::Back()
{
	switch (traject)
	{
	case South:
		coordinates.y++;
		break;

	case West:
		coordinates.x++;
		break;
	case North:
		coordinates.y--;
		break;
	case East:
		coordinates.x--;
		break;
	default:
		break;
	}
}




int main()
{
	//Room<Car, int > r(1, 2, 3); 
	try
	{
		Room<Car, int,int> r2(20, 16, 1,2);
		r2.Initial_Position(2, 2);
		cout << r2 << endl;
		r2.Forward(); 
		r2.Forward(); 
		r2.Right(); 
		r2.Back(); 
		r2.Back(); 
		
	}
	catch (const exception& e)
	{
		cout << e.what() << endl; 
	}
	
	return 0; 
}
