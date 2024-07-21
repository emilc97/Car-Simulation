#pragma once 
#include <iostream>
#include "Simulator.h"
using namespace std; 


class Car : public Vehicle<int>
{
public:
	/*@brief Overload of stream extraction operator
	* @param ostream: Output stream object
	* @param obj: Car object
	* @retval os: lvalue reference to ensure modification persist in current stream object
	*/
	using _base = Vehicle<int>; 

	friend ostream& operator << (ostream& os, Car& obj)
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Car(int x, int y, Cardinal_Points dir = North, int diameter = 1) : Vehicle{ x,y, diameter,dir } {}; 
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
	virtual Car& operator++(int) noexcept override; 
	virtual Car& operator--(int) noexcept override; 

};


