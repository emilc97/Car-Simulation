//inclusion guard
#pragma once 
#include <iostream>
#include <memory>
#include <exception>

using namespace std; 

template<typename T> 
struct Position
{
	using value_type = T; //making the type publicly accessible (metapr.) 
	T x; 
	T y; 
	Position(T y = T(), T x = T()) : x{ x }, y{ y } {}
	~Position() = default; 
};

enum Direction
{
	South = 0,
	West,
	North,
	East
};

class Trajectory
{
	Direction _dir; 
	public:
	Trajectory(Direction dir = North) : _dir{ dir } {};
	Trajectory& operator++(int) noexcept
	{
		_dir = static_cast<Direction>(_dir + 1); 
		return *this; 
	}
	//Conversion operator 
	Trajectory& operator--(int) noexcept
	{
		_dir = static_cast<Direction>(_dir - 1); 
		return *this; 
	}
	//conversion operator to be treated as an enum 
	operator Direction()
	{
		return _dir; 
	}
};

class Vehicle
{
	protected: 
	Position<int> coordinates; 
	Trajectory traject; 
	public: 
	virtual void Left() = 0; 
	virtual void Right() = 0; 
	virtual void Forward() = 0; 
	virtual void Back() = 0; 
	Position<int>& GetCoordinates() noexcept; 
	void SetCoordinates(int x, int y) noexcept; 
	Vehicle(int x = 0, int y = 0) : coordinates{ x,y } {}; 
	~Vehicle() = default; 
};

class Car : public Vehicle
{
	int _diameter; 
	public: 
	Car(int diameter) : _diameter{ diameter } {}; 
	virtual void Left() override
	{
		traject++; 
	}
	virtual void Right() override
	{
		traject++; 
	}
	virtual void Forward() override; 
	virtual void Back() override; 
};

template<typename V, typename... Args> 
class Room
{
	int _width; 
	int _length; 
	unique_ptr<V> _ptr; 
	friend ostream& operator << (ostream& os, const Room& obj) 
	{
		os << "Room Size: " << obj._width << "x" << obj._length << "m" << endl; 
		os << "Vehicle position: (" << obj._ptr->GetCoordinates().x << ","; 
		os << obj._ptr->GetCoordinates().y << ")" << endl;
		return os; 
	}
	public: 
	Room(int width, int length, Args&&... args); 
	explicit Room(int width, int length, V* ptr); 
	void Left()
	{
		_ptr->Left(); 
	}
	void Right()
	{
		_ptr->Right(); 
	}
	void Forward()
	{
		_ptr->Forward(); 
	}
	void Back()
	{
		_ptr->Back(); 
	}
	void Initial_Position(int x, int y)
	{
		_ptr->SetCoordinates(x, y); 
	}
	Room(int width, int length, unique_ptr<int>&& ptr); 
	~Room() = default; 

};

