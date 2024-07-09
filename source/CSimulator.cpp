#include <iostream>
#include "CSimulator.h"

Position<int>& Vehicle::GetCoordinates() noexcept
{
	return coordinates;
}

void Vehicle::SetCoordinates(int x, int y) noexcept
{
	coordinates.x = x;
	coordinates.y = y;
}

void Car::Forward() 
{
	switch (traject)
	{
	case South:
		coordinates.y--;
		break;

	case West:
		coordinates.x--;
		break;
	case North:
		coordinates.y++;
		break;
	case East:
		coordinates.x++;
		break;
	default:
		break;
	}

}

void Car::Back()
{
	switch (traject)
	{
	case South:
		coordinates.y++;
		break;

	case West:
		coordinates.x++;
		break;
	case North:
		coordinates.y--;
		break;
	case East:
		coordinates.x--;
		break;
	default:
		break;
	}
}

template<typename V, typename... Args>
Room<V, Args...>::Room(int width, int length, unique_ptr<int>&& ptr) : _width{ width }, _length{ length }, _ptr{ move(ptr) } 
{

};

template<typename V, typename... Args>
Room<V, Args...>::Room(int width, int length, V* ptr) : _width{ width }, _length{ length }, _ptr{ ptr } 
{

};

template<typename V, typename... Args> 
Room<V, Args...>::Room(int width, int length, Args&&... args) : _width{ width }, _length{ length }, _ptr{ make_unique<V>(args...) }
{

}


int main()
{
	//Room<Car, int > r(1, 2, 3); 
	Room<Car, int> r2(1, 2, new Car(1));
	cout << r2 << endl; 
	return 0; 
}
