#include "Car.h"

/*@brief Moves the car forward in the 2D-grid. */
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

/*@brief Moves the car backward in the 2D-grid. */
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

/*@brief Override of virtual post increment operator for Car. Calling the 
* native implementation of the base class twice ensures no cardinal points 
* other than South, West, North, East are available. 
* @retval Reference to car object (*this) 
*/
Car& Car::operator++(int) noexcept
{
	_base::operator++(0); 
	_base::operator++(0); 
	return *this;
}

/*@brief Override of virtual post decrement operator for Car. Calling the
* native implementation of the base class twice ensures no cardinal points
* other than South, West, North, East are available.
* @retval Reference to car object (*this) 
*/
Car& Car::operator--(int) noexcept
{
	_base::operator--(0); 
	_base::operator--(0); 

	return *this;
}



