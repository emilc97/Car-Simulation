//inclusion guard
#pragma once 
#include <iostream>
#include <memory>
#include <exception>
#include <string>
#include <cstring>

using namespace std; 


/*@brief Enum for directions */
enum Direction
{
	South = 0,
	West,
	North,
	East
};

/*@brief Position coordinates with template parameter T*/
template<typename T> 
struct Position
{
	using value_type = T; //making the type publicly accessible (metapr.) 
	T x; 
	T y; 
	//Call default constructor if no input parameter 
	Position(T x = T(), T y = T()) : x{ x }, y{ y } {}
	~Position() = default; 
};


/*@class Vehicle 
* @Abstract The abstract class for common to all vehicles
* 
* Contains basic member methods and coordinates that is required by all vehicles. 
* PrintCoordinates and SetCoordinates can be overloaded in the inherited class 
* for specialization. 
*/
template<typename T>
class Vehicle
{
	protected: 
	T diameter; 
	Position<T> coordinates; 
	public: 
	virtual void Left() = 0; 
	virtual void Right() = 0; 
	virtual void Forward() = 0; 
	virtual void Back() = 0; 
	Position<T>& GetCoordinates() noexcept; 
	void SetCoordinates(T x, T y) noexcept; 
	/*@brief  Print vehicle coordinates 
	* @retval None 
	*/
	void PrintCoordinates()
	{
		cout << "(" << coordinates.x << "," << coordinates.y << ")" << endl; 
	}
	
	T GetDiameter() const noexcept
	{
		return diameter; 
	}
	Vehicle(T x = T(), T y = T(), T diameter = T());
	~Vehicle() = default; 
};

/*@brief Vehicle constructor
* @param x: x coordinate
* @param y: y coordinate
* @throw  : x and y coordinates must be non-negative
*/
template<typename T>
void Vehicle<T>::SetCoordinates(T x, T y) noexcept
{
	coordinates.x = x;
	coordinates.y = y;
}

template<typename T>
Vehicle<T>::Vehicle(T x, T y, T diameter) : diameter{ diameter }, coordinates { x, y }
{
	if (x < 0 || y < 0)
		throw out_of_range("Coordinates must be non-negative");
}

template<typename T>
Position<T>& Vehicle<T>::GetCoordinates() noexcept
{
	return coordinates;
}


template<typename V, typename... Args> 
class Room
{
	int _width; 
	int _length; 
	unique_ptr<V> _ptr; 

	/*@brief Overload of stream extraction operator 
	* @param ostream: Output stream object 
	* @param obj: Room object 
	* @retval os: lvalue reference to ensure modification persist in current stream object 
	*/
	friend ostream& operator << (ostream& os, const Room& obj) 
	{
		os << "Room Size: " << obj._width << "x" << obj._length << " m" << endl; 
		os << "Vehicle position: (" << obj._ptr->GetCoordinates().x; 
		os << ","; 
		os << obj._ptr->GetCoordinates().y << ")" << endl;
		return os; 
	}
	public: 
	
	Room(int width, int length, Args&&... args); 
	explicit Room(int width, int length, V* ptr);
	Room(int width, int length, unique_ptr<V>&& ptr); 
	Room(int width, int length, V&& obj); 

	/*@brief Invoke native vehicle Left() method*/
	void Left()
	{
		_ptr->Left(); 
	}
	/*@brief Invoke native vehicle Right() method*/
	void Right()
	{
		_ptr->Right(); 
	}
	void Forward(); 
	void Back(); 
	void ChangeHeading(string& str); 

	/*@brief Set initial vehicle position 
	* @param x: x coordinate 
	* @param y: y coordinate 
	* @retval : None
	*/
	void Initial_Position(int x, int y)
	{
		_ptr->SetCoordinates(x, y); 
	}

	/*@brief Get x coordinate 
	* @retval : None 
	*/
	int GetXPosition() const
	{
		return _ptr->GetCoordinates().x; 
	}
	/*@brief Get y coordinate
	* @retval : None
	*/
	int GetYPosition() const
	{
		return _ptr->GetCoordinates().y;
	}
	~Room() = default; 

};

/*@brief  Change current direction (heading) using ASCII character (S, W, N, E)
* @param  str: String holding the ASCII character 
* @retval None 
*/
template<typename V, typename... Args> 
void Room<V, Args...>::ChangeHeading(string& str)
{
	string dir{ "FBLR" }; 
	for (auto& elem : str)
	{
		if (elem == dir[0])
			Forward();
		else if (elem == dir[1])
			Back();
		else if (elem == dir[2])
			Left();
		else if (elem == dir[3])
			Right(); 
	}
}

/*@brief  Room method for calling vehicle native Back implementation
* @retval None
*/
template<typename V, typename... Args> 
void Room<V,Args...>::Back()
{
	_ptr->Back();
	_ptr->PrintCoordinates();
	if (_ptr->GetCoordinates().x > _width - _ptr->GetDiameter())
		throw out_of_range("The Vehicle hit the rightside wall");

	else if (_ptr->GetCoordinates().x < 0)
		throw out_of_range("The vehicle hit the leftmost wall");

	else if (_ptr->GetCoordinates().y > _length - _ptr->GetDiameter())
		throw out_of_range("The vehicle hit the upper wall");

	else if (_ptr->GetCoordinates().y < 0)
		throw out_of_range("The vehicle hit the bottom wall");
}

/*@brief  Room method for calling vehicle native Forward implementation 
* @retval None
*/
template<typename V, typename... Args>
void Room<V, Args...>::Forward()
{
	_ptr->Forward();
	_ptr->PrintCoordinates();
	if (_ptr->GetCoordinates().x > _width - _ptr->GetDiameter())
		throw out_of_range("The Vehicle hit the rightside wall");

	else if (_ptr->GetCoordinates().x < 0)
		throw out_of_range("The vehicle hit the leftmost wall");

	else if (_ptr->GetCoordinates().y > _length - _ptr->GetDiameter())
		throw out_of_range("The vehicle hit the upper wall");

	else if (_ptr->GetCoordinates().y < 0)
		throw out_of_range("The vehicle hit the bottom wall");
}

/*@brief Constructor using parameter packing for vehicle construction
*        The vehicle uses perfect forwarding (constructed via make unique).
* @param width : Room width
* @param length: Room length
* @args        : Parameter pack for vehicle constructor
*/
template<typename V, typename... Args> 
Room<V,Args...>::Room(int width, int length, Args&&... args) : _width{ width }, _length{ length }, _ptr{ make_unique<V>(args...) }
{
	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");
}

/*@brief Constructor using vehicle pointer (V*).
* @param width : Room width
* @param length: Room length
* @param ptr   : Vehicle pointer
*/
template<typename V, typename... Args>
Room<V, Args...>::Room(int width, int length, V* ptr) : _width{ width }, _length{ length }, _ptr{ ptr }
{
	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");

}

/*@brief Constructor moving unique_ptr rvalue (holding pre-existing) into
*        object pointer.
* @param width : Room width
* @param length: Room length
* @param ptr   : Unique Ptr (rvalue)
*/
template<typename V, typename... Args>
Room<V, Args...>::Room(int width, int length, unique_ptr<V>&& ptr) : _width{ width }, _length{ length }, _ptr{ move(ptr) }
{
	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");
}

/*@brief Constructor that constructs rvalue vehicle object in place 
* @param width : Room width
* @param length: Room length
* @param obj   : Vehicle object (rvalue)
*/
template<typename V, typename... Args>
Room<V, Args...>::Room(int width, int length, V&& obj) : _width{ width }, _length{ length }
{
	auto ptr = operator new(sizeof(V));
	new (ptr) V(move(obj));
	_ptr = move(unique_ptr<V>(static_cast<V*>(ptr)));

}
