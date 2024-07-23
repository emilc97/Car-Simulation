#include "Monster_Truck.h"

/*@brief Moves the Monster_Truck forward in the 2D-grid. */
void Monster_Truck::Forward()
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

/*@brief Moves the Monster_Truck backward in the 2D-grid. */
void Monster_Truck::Back()
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

/*@brief Override of virtual post increment operator for Monster_Truck. Calling the 
* native implementation of the base class twice ensures no Monster_Truckdinal points 
* other than South, West, North, East are available. 
* @retval Reference to Monster_Truck object (*this) 
*/
Monster_Truck& Monster_Truck::operator++(int) noexcept
{
	_base::operator++(0); 
	_base::operator++(0); 
	return *this;
}

/*@brief Override of virtual post decrement operator for Monster_Truck. Calling the
* native implementation of the base class twice ensures no Monster_Truckdinal points
* other than South, West, North, East are available.
* @retval Reference to Monster_Truck object (*this) 
*/
Monster_Truck& Monster_Truck::operator--(int) noexcept
{
	_base::operator--(0); 
	_base::operator--(0); 

	return *this;
}



