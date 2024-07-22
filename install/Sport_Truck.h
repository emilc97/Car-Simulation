#pragma once 
#include "Simulator.h"

/*@class Sport_Truck 
* @brief Sport Truck implement a Vehicle that is faster than a traditional car and 
* is driven in a floating point 2D-grid. 
*/
class Sport_Truck : public Vehicle<float>
{
public: 
	/*@brief Overload of stream extraction operator
	* @param ostream: Output stream object
	* @param obj: Car object
	* @retval os: lvalue reference to ensure modification persist in current stream object
	*/
	using _base = Vehicle<float>;

	friend ostream& operator << (ostream& os, Sport_Truck& obj)
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Sport_Truck(float x, float y, Cardinal_Points dir = North, float diameter = 1) : Vehicle{ x,y, diameter,dir } {};
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


