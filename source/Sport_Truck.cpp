#include "Sport_Truck.h"

void Monster_Truck::Forward()
{
	switch (_cpts)
	{
	case South:
		_coordinates.y -= 1.5;
		break;
	case SouthWest:
		_coordinates.y -= 1.06;
		_coordinates.x -= 1.06;
		break;
	case West:
		_coordinates.x -= 1.5;
		break;
	case NorthWest:
		_coordinates.y += 1.06;
		_coordinates.x -= 1.06;
		break;
	case North:
		_coordinates.y += 1.5;
		break;
	case NorthEast:
		_coordinates.y += 1.06;
		_coordinates.x += 1.06;
		break;
	case East:
		_coordinates.x += 1.5;
		break;
	case SouthEast:
		_coordinates.x += 1.06;
		_coordinates.y -= 1.06;
		break;
	default:
		break;
	}
}

void Monster_Truck::Back()
{
	switch (_cpts)
	{
	case South:
		_coordinates.y += 1.5;
		break;
	case SouthWest:
		_coordinates.y += 1.06;
		_coordinates.x += 1.06;
		break;
	case West:
		_coordinates.x += 1.5;
		break;
	case NorthWest:
		_coordinates.y -= 1.06;
		_coordinates.x += 1.06;
		break;
	case North:
		_coordinates.y -= 1.5;
		break;
	case NorthEast:
		_coordinates.y -= 1.06;
		_coordinates.x -= 1.06;
		break;
	case East:
		_coordinates.x -= 1.5;
		break;
	case SouthEast:
		_coordinates.x -= 1.06;
		_coordinates.y += 1.06;
		break;
	default:
		break;
	}
}
