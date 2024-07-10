#include <iostream>
#include "CSimulator.h"

Position<int>& Vehicle::GetCoordinates() noexcept
{
	return coordinates;
}

/*@brief Vehicle constructor
* @param x: x coordinate
* @param y: y coordinate
* @throw  : x and y coordinates must be non-negative
*/
void Vehicle::SetCoordinates(int x, int y) noexcept
{
	coordinates.x = x;
	coordinates.y = y;
}

Vehicle::Vehicle(int x, int y) : coordinates{ x,y }
{
	if (x < 0 || y < 0)
		throw out_of_range("Coordinates must be non-negative");
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

Trajectory& Trajectory::operator++(int) noexcept
{
	if (_dir == South)
		_dir = West;
	else if (_dir == West)
		_dir = North;
	else if (_dir == North)
		_dir = East;
	else if (_dir == East)
		_dir = South;

	return *this;
}

Trajectory& Trajectory::operator--(int) noexcept
{
	if (_dir == South)
		_dir = East;
	else if (_dir == West)
		_dir = South;
	else if (_dir == North)
		_dir = West;
	else if (_dir == East)
		_dir = North;

	return *this;
}


