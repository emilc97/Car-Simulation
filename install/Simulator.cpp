#include <iostream>
#include "Simulator.h"

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


