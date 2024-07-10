#include "Car.h"

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
