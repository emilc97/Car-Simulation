#include "Car.h"

void Car::Forward()
{
	switch (*_heading)
	{
	case South:
		_coordinates.y--;
		break;

	case West:
		_coordinates.x--;
		break;
	case North:
		_coordinates.y++;
		break;
	case East:
		_coordinates.x++;
		break;
	default:
		break;
	}

}

void Car::Back()
{
	switch (*_heading)
	{
	case South:
		_coordinates.y++;
		break;

	case West:
		_coordinates.x++;
		break;
	case North:
		_coordinates.y--;
		break;
	case East:
		_coordinates.x--;
		break;
	default:
		break;
	}
}

CarHeading& CarHeading::operator++(int) noexcept
{
	Direction& dir = GetDirection(); 
	if (dir == South)
		dir = West;
	else if (dir == West)
		dir = North;
	else if (dir == North)
		dir = East;
	else if (dir == East)
		dir = South;

	return *this;
}

CarHeading& CarHeading::operator--(int) noexcept
{
	Direction& dir = GetDirection();
	if (dir == South)
		dir = East;
	else if (dir == West)
		dir = South;
	else if (dir == North)
		dir = West;
	else if (dir == East)
		dir = North;

	return *this;
}

string CarHeading::HeadingStr() noexcept 
{
	string tmp; 
	Direction dir = GetDirection(); 
	switch (dir)
	{
	case South: 
		tmp = "South"; 
		break; 
	case West:
		tmp = "West";
		break;
	case North:
		tmp = "South";
		break;
	case East:
		tmp = "West";
		break;
	default: 
			break; 

	}
	return tmp; 
}
