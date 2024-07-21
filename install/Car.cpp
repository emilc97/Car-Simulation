#include "Car.h"

void Car::Forward()
{
	switch (_cpts)
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
	switch (_cpts)
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

Car& Car::operator++(int) noexcept
{
	_base::operator++(0); 
	_base::operator++(0); 
	return *this;
}

Car& Car::operator--(int) noexcept
{
	_base::operator--(0); 
	_base::operator--(0); 

	return *this;
}



