//inclusion guard
#pragma once 
#include <iostream>
#include <memory>
#include <exception>

using namespace std; 

template<typename T>
struct Position 
{
	T x_pos; 
	T y_pos; 
	Position(T x_pos = T(), T y_pos = T()) {}; 
};

class Vehicle
{
protected: 
	Position<int> coord; 
public:
	Vehicle(int x = 0, int y = 0) : coord{ x,y } {}; 
	void SetCoord(int x, int y) noexcept
	{
		coord.x_pos = x; 
		coord.y_pos = y; 
	}
	virtual void Left() = 0; 
	virtual void Right() = 0; 
	virtual void Forward() = 0;
	virtual void Back() = 0;
	int XPosition() const noexcept
	{
		return coord.x_pos;
	}
	int YPosition() const noexcept
	{
		return coord.y_pos;
	}

	~Vehicle() {}; 
};

class Car : public Vehicle
{
	int _diameter; 
public: 
	Car(int diameter) : _diameter{ diameter } {};
    virtual void Left() override
	{
		coord.x_pos--; 
	}
	virtual void Right() override
	{
		coord.x_pos++;
	}
	virtual void Forward() override
	{
		coord.y_pos++;
	}
	virtual void Back() override
	{
		coord.y_pos++;
	}
	~Car() {}; 
};


template<typename V, typename... Args>
class Room
{
	int _width; 
	int _length; 
	unique_ptr<V> _ptr; 
	friend ostream& operator <<(ostream& os, const Room& obj) noexcept
	{
		os << "Room (width: " << obj._width << ", length: " << obj._length << ")" << endl; 
		os << "Car Position: (" << obj._ptr->XPosition() << ", " << obj._ptr->YPosition() << ")" << endl; 
		return os; 
	}
	using vehicle_type = V; 
	public: 
	Room(int width, int length, Args&&... args) : _width{ width }, _length{ length }
	{
		_ptr = make_unique<V>(args...); 
	}
	InitialPos(int x, int y)
	{

	}
	//Getters 
	int Width() const noexcept 
	{
		return _width; 
	}
	int Length() const noexcept
	{
		return _length; 
	}
	~Room() = default; 
};




