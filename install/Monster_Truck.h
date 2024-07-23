#pragma once 
#include <iostream>
#include "Simulator.h"
using namespace std; 

/*@class Monster_Truck 
* @brief A Monster_Truck is an concrete class of the Vehicle abstract class that supports
* movement in North, East, South and West direction. Using a inegral 2D-grid 
* as coordinate system. 
*/
class Monster_Truck : public Vehicle<int>
{
public:
	/*@brief Overload of stream extraction operator
	* @param ostream: Output stream object
	* @param obj: Monster_Truck object
	* @retval os: lvalue reference to ensure modification persist in current stream object
	*/
	using _base = Vehicle<int>; 

	friend ostream& operator << (ostream& os, Monster_Truck& obj)
	{
		os << "Monster_Truck Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Monster_Truck(int x, int y, Cardinal_Points dir = North, int diameter = 1) : Vehicle{ x,y, diameter,dir } {}; 
	virtual void Left() override
	{
		(*this)--;
	}
	virtual void Right() override
	{
		(*this)++; 
	}
	virtual void Forward() override;
	virtual void Back() override;
	virtual Monster_Truck& operator++(int) noexcept override; 
	virtual Monster_Truck& operator--(int) noexcept override; 

};


