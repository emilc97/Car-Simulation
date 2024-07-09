//inclusion guard
#pragma once 
#include <iostream>
#include <memory>
#include <exception>

using namespace std; 

enum Direction
{
	South = 0,
	West,
	North,
	East
};

template<typename T> 
struct Position
{
	using value_type = T; //making the type publicly accessible (metapr.) 
	T x; 
	T y; 
	Position(T y = T(), T x = T()) : x{ x }, y{ y } {}
	~Position() = default; 
};


class Vehicle
{
	protected: 
	Position<int> coordinates; 
	public: 
	virtual void Left() = 0; 
	virtual void Right() = 0; 
	virtual void Forward() = 0; 
	virtual void Back() = 0; 
	Position<int>& GetCoordinates() noexcept; 
	void SetCoordinates(int x, int y) noexcept; 
	void PrintCoordinates()
	{
		cout << "(" << coordinates.x << "," << coordinates.y << ")" << endl; 
	}
	Vehicle(int x = 0, int y = 0) : coordinates{ x,y } {}; 
	~Vehicle() = default; 
};



class Trajectory
{
	Direction _dir;
public:
	Trajectory(Direction dir = North) : _dir{ dir } {};
	Trajectory& operator++(int) noexcept
	{
		_dir = static_cast<Direction>((_dir + 1) % 4);
		return *this;
	}
	//Conversion operator 
	Trajectory& operator--(int) noexcept
	{
		_dir = static_cast<Direction>((_dir - 1) % 4);
		return *this;
	}
	//conversion operator to be treated as an enum 
	operator Direction()
	{
		return _dir;
	}
};

class Car : public Vehicle
{
	Trajectory traject;
	public: 
	friend ostream& operator << (ostream& os, Car& obj) 
	{
		os << "Car Position (" << obj.GetCoordinates().x << "," << obj.GetCoordinates().y << endl; 
		return os; 
	}
	Car(int x, int y) : Vehicle{ x,y } {};
	virtual void Left() override
	{
		traject--; 
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
		os << "Room Size: " << obj._width << "x" << obj._length << " m" << endl; 
		os << "Vehicle position: (" << obj._ptr->GetCoordinates().x; 
		os << ","; 
		os << obj._ptr->GetCoordinates().y << ")" << endl;
		return os; 
	}
	public: 
	Room(int width, int length, Args&&... args) : _width{ width }, _length{ length }, _ptr{ make_unique<V>(args...) }
	{
		if (width <= 0 || length <= 0)
			throw invalid_argument("Width and length shall only be positive");
	};
	explicit Room(int width, int length, V* ptr) : _width{ width }, _length{ length }, _ptr{ ptr }
	{
		if (width <= 0 || length <= 0)
			throw invalid_argument("Width and length shall only be positive");

	};
	Room(int width, int length, unique_ptr<int>&& ptr) : _width{ width }, _length{ length }, _ptr{ move(ptr) }
	{
		if (width <= 0 || length <= 0)
			throw invalid_argument("Width and length shall only be positive");
	};
	void Left()
	{
		_ptr->Left(); 
	}
	void Right()
	{
		_ptr->Right(); 
	}
	void Forward(); 
	void Back(); 
	void Initial_Position(int x, int y)
	{
		_ptr->SetCoordinates(x, y); 
	}
	int GetXPosition() const
	{
		return _ptr->GetCoordinates().x; 
	}
	int GetYPosition() const
	{
		return _ptr->GetCoordinates().y;
	}
	
	~Room() = default; 

};

template<typename V, typename... Args> 
void Room<V,Args...>::Back()
{
	_ptr->Back();
	_ptr->PrintCoordinates();
	if (_ptr->GetCoordinates().x > _width)
		throw out_of_range("The Vehicle hit the rightside wall");

	else if (_ptr->GetCoordinates().x < 0)
		throw out_of_range("The vehicle hit the leftmost wall");

	else if (_ptr->GetCoordinates().y > _length)
		throw out_of_range("The vehicle hit the upper wall");

	else if (_ptr->GetCoordinates().y < 0)
		throw out_of_range("The vehicle hit the bottom wall");
}

template<typename V, typename... Args>
void Room<V, Args...>::Forward()
{
	_ptr->Forward();
	_ptr->PrintCoordinates();
	if (_ptr->GetCoordinates().x > _width)
		throw out_of_range("The Vehicle hit the rightside wall");

	else if (_ptr->GetCoordinates().x < 0)
		throw out_of_range("The vehicle hit the leftmost wall");

	else if (_ptr->GetCoordinates().y > _length)
		throw out_of_range("The vehicle hit the upper wall");

	else if (_ptr->GetCoordinates().y < 0)
		throw out_of_range("The vehicle hit the bottom wall");
}