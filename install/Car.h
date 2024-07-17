#pragma once 
#include <iostream>
#include "Simulator.h"
using namespace std; 

/*@class Trajectory
* @brief Wrapper class for the direction enum for wrap-around
*
* The trajectory wrapper class is designated for post-increment
* and pre-increment of the vehicle direction (S, W, N, E) and
* provides wrap-around behavior.
*/
class Trajectory
{
	Direction _dir;
public:
	Trajectory(Direction dir = North) : _dir{ dir } {};
	Trajectory& operator++(int) noexcept;
	Trajectory& operator--(int) noexcept;
	//conversion operator to be treated as an enum 
	operator Direction()
	{
		return _dir;
	}

};

class Car : public Vehicle<int>
{
	Trajectory _traject;
public:
	/*@brief Overload of stream extraction operator
	* @param ostream: Output stream object
	* @param obj: Car object
	* @retval os: lvalue reference to ensure modification persist in current stream object
	*/
	friend ostream& operator << (ostream& os, Car& obj)
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Car(int x, int y, Direction dir, int diameter = 1) : Vehicle{ x,y, diameter }, _traject{ dir } {};
	virtual void Left() override
	{
		_traject--;
	}
	virtual void Right() override
	{
		_traject++;
	}
	virtual void Forward() override;
	virtual void Back() override;

};