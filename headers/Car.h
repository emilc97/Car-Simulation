#pragma once 
#include <iostream>
#include "Simulator.h"
using namespace std; 


/*@class CarTrajectory
* @brief Derived from Abstract Trajectory Class
* The trajectory wrapper class is designated for post-increment
* and pre-increment of the vehicle direction (S, W, N, E) and
* provides wrap-around behavior.
*/
class CarTrajectory: public Trajectory
{

public:
	CarTrajectory(Direction dir = North) : Trajectory{ dir } {};
	virtual CarTrajectory& operator++(int) noexcept override; 
	virtual CarTrajectory& operator--(int) noexcept override; 
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
	using Vehicle<int>::_traject; 

	friend ostream& operator << (ostream& os, Car& obj)
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl;
		return os;
	}
	Car(int x, int y, Direction dir, int diameter = 1) : Vehicle{ x,y, diameter, new CarTrajectory{dir} }{};
	virtual void Left() override
	{
		(*_traject)--;
	}
	virtual void Right() override
	{
		(* _traject)++;
	}
	virtual void Forward() override;
	virtual void Back() override;

};