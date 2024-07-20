#pragma once 
#include <iostream>
#include "Simulator.h"
using namespace std; 


/*@class CarHeading
* @brief Derived from Abstract Heading Class
* The Heading wrapper class is designated for post-increment
* and pre-increment of the vehicle direction (S, W, N, E) and
* provides wrap-around behavior.
*/
class CarHeading: public Heading
{

public:
	CarHeading(Direction dir = North) : Heading{ dir } {};
	virtual CarHeading& operator++(int) noexcept override; 
	virtual CarHeading& operator--(int) noexcept override; 
	virtual Direction& GetDirection() noexcept override 
	{
		return _dir; 
	}
	virtual string HeadingStr()  noexcept override; 
};


class Car : public Vehicle<int>
{
public:
	/*@brief Overload of stream extraction operator
	* @param ostream: Output stream object
	* @param obj: Car object
	* @retval os: lvalue reference to ensure modification persist in current stream object
	*/
	using Vehicle<int>::_heading; 

	friend ostream& operator << (ostream& os, Car& obj)
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Car(int x, int y, Direction dir, int diameter = 1) : Vehicle{ x,y, diameter, new CarHeading{dir} }{};
	virtual void Left() override
	{
		(*_heading)--;
	}
	virtual void Right() override
	{
		(* _heading)++;
	}
	virtual void Forward() override;
	virtual void Back() override;

};