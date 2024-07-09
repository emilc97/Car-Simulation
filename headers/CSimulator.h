//inclusion guard
#pragma once 

template<typename T> 
struct Position 
{
	x_pos; 
	y_pos, 
};

template<typename T>
class Vehicle
{
	T diameter;
	Position<T> pos; 
	using value_type = T; //publicly accessible template parameter 
public:
	//pure virtual functions 
	virtual void Left() = 0; 
	virtual void Right() = 0; 
	virtual void Forward() = 0; 
	virtual void Back() = 0; 
};

template<typename T> 


template<typename T> 
class Room
{
	T _width; 
	T _length; 
	using value_type = T; 
	public: 
	Room(T width, T length); 
	//Getters 
	T Width() const noexcept 
	{
		return _width; 
	}
	T Length() const noexcept
	{
		return _length; 
	}
	~Room() = default; 
};

template<typename T>
Room<T>::Room(T width, T length) : _width{ width }, _length{ length }
{
	if (length == 0 || width == 0)
		throw length_error("Room width or length cannot be 0");
	else if (length < 0 || width < 0)
		throw length_error("Room width or length cannot be negative");

}