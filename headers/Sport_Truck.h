#pragma once 
#include "Simulator.h"

class Monster_Truck : public Vehicle<float>
{
	int degrees = 0; 
public: 
	/*@brief Overload of stream extraction operator
	* @param ostream: Output stream object
	* @param obj: Car object
	* @retval os: lvalue reference to ensure modification persist in current stream object
	*/
	using _base = Vehicle<float>;

	friend ostream& operator << (ostream& os, Monster_Truck& obj)
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Monster_Truck(float x, float y, Cardinal_Points dir = North, float diameter = 1) : Vehicle{ x,y, diameter,dir } {};
	virtual void Left() override
	{
		_base::operator--(0);
	}
	virtual void Right() override
	{
		_base::operator++(0); 
	}
	virtual void Forward() override;
	virtual void Back() override;
};


