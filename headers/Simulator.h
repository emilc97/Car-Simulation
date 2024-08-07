//inclusion guard
#pragma once 
#include <iostream>
#include <memory>
#include <exception>
#include <string>
#include <sstream>
#include <cstring>
#include <sstream>

using namespace std; 


/*@brief Enum for Cardinal_Pointss */
enum Cardinal_Points
{
	South = 0,
	SouthWest, 
	West,
	NorthWest, 
	North,
	NorthEast, 
	East, 
	SouthEast 

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
	T _diameter; 
	Position<T> _coordinates; 
	Cardinal_Points _cpts; 
	public: 
	using value_type = T; //make the template parameter publicly accessible 

	virtual void Left() = 0; 
	virtual void Right() = 0; 
	virtual void Forward() = 0; 
	virtual void Back() = 0; 

	Vehicle(const Vehicle& obj);
	Vehicle(Vehicle&& obj) noexcept;

	virtual Vehicle& operator++(int) noexcept;
	virtual Vehicle& operator--(int) noexcept;
 
	Vehicle& operator=(const Vehicle& obj) noexcept; 

	Vehicle(T x = T(), T y = T(), T diameter = T(), Cardinal_Points dir = North);
	~Vehicle() = default;

	/*@brief  Print vehicle coordinates 
	* @retval None 
	*/
	void PrintCoordinates()
	{
		cout << "(" << _coordinates.x << "," << _coordinates.y << ")" << endl; 
	}

	//setters
	void SetCoordinates(T x, T y) noexcept;

	//getters 
	Position<T>& GetCoordinates() noexcept;
	virtual string HeadingStr() noexcept;

	/*@brief Get Vehicle Diameter
	* @retval Diameter
	*/
	T GetDiameter() const noexcept
	{
		return _diameter; 
	}

	/*brief Get Cardinal Points (North, West ...) 
	@retval Enum Cardinal Points 
	*/
	Cardinal_Points& Get_Cardinal_Points() noexcept
	{
		return _cpts; 
	}
};

/*@brief Vehicle Copy Constructor */
template<typename T> 
Vehicle<T>::Vehicle(const Vehicle& obj)
{
	_diameter = obj._diameter;
	_coordinates = obj._coordinates;
	_cpts = obj._cpts;
}

/*@brief Vehicle Copy Assignment Operator */
template<typename T>
Vehicle<T>& Vehicle<T>::operator=(const Vehicle& obj) noexcept
{
	_diameter = obj._diameter;
	_coordinates = obj._coordinates;
	_cpts = obj._cpts;
	return *this; 
}

/*@brief Set Coordinates of Vehicle*/
template<typename T>
void Vehicle<T>::SetCoordinates(T x, T y) noexcept
{
	_coordinates.x = x;
	_coordinates.y = y;
}


/*@brief Vehicle constructor
* @param x: x coordinate
* @param y: y coordinate
* @param diameter: Vehicle Diameter
* @param dir: Enum Cardinal Points (North, West etc..) 
* @throw  : x and y coordinates must be non-negative
*/
template<typename T>
Vehicle<T>::Vehicle(T x, T y, T diameter, Cardinal_Points dir) : _diameter{ diameter }, _coordinates { x, y }, _cpts{dir}
{
	if (x < 0 || y < 0)
		throw out_of_range("Coordinates must be non-negative");
}

/*@brief Get Coordinates of the Vehicle 
* @retval Coordinates
*/
template<typename T>
Position<T>& Vehicle<T>::GetCoordinates() noexcept
{
	return _coordinates;
}

/* @brief Transform user input to coordinates and cardinal points
*  @param x  : x coordinate
*  @param y  : y coordinate
*  @param dir: Initial Heading (Monster_Truckdinal_Points)
*  @return   : None
*/
template<typename T>
void VehiclePosition(T& x, T& y, Cardinal_Points& dir)
{
	string str, tmp;
	cout << "Enter the initial coordinates (position) of the Monster_Truck and heading (S, W, N, E):";
	getline(cin, str);
	istringstream isstream{ str };
	if (!(isstream >> x))
		throw invalid_argument("X coordinate must be numeric");
	if (!(isstream >> y))
		throw invalid_argument("Y coordinate must be numeric");
	isstream >> tmp; //string stream for string to numeric conversion

	//set vehicle Monster_Truckdinal_Points
	if (tmp == string{ 'S' })
		dir = South;
	else if (tmp == string{ 'W' })
		dir = West;
	else if (tmp == string{ 'N' })
		dir = North;
	else if (tmp == string{ 'E' })
		dir = East;
	else
		throw invalid_argument("Invalid Cardinal_Points requested for the vehicle. Valid are (S, W, N, E)");
}


/*@class Room 
* @brief A class representing a Vehicle and 2D-grid 
* @param V: Template parameter derived from the abstract class Vehicle 
* @param Args: Used for parameter packing to call the Vehicle Constructor
*/
template<typename V, typename... Args> 
class Room
{
	public:
	using value_type = typename V::value_type;

	private: 
	value_type _width; 
	value_type _length; 
	unique_ptr<V> _ptr; 

	public: 

	/*@brief Overload of stream extraction operator 
	* @param ostream: Output stream object 
	* @param obj: Room object 
	* @retval os: lvalue reference to ensure modification persist in current stream object 
	*/
	friend ostream& operator << (ostream& os, const Room& obj) 
	{
		int x = obj._ptr->GetCoordinates().x; 
		int y = obj._ptr->GetCoordinates().y; 
		os << "Room Size: " << obj._width << "x" << obj._length << " m" << endl; 
		os << "Vehicle position: (" << x << "," << y << ")" << endl;
		return os; 
	}
	

	Room(value_type width, value_type length, Args&&... args);
	explicit Room(value_type width, value_type length, V* ptr);
	Room(value_type width, value_type length, unique_ptr<V>&& ptr);
	Room(value_type width, value_type length, V&& obj);

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
	void Initial_Position(value_type x, value_type y)
	{
		_ptr->SetCoordinates(x, y); 
	}

	/*@brief Get x coordinate 
	* @retval : x position. 
	*/
	value_type GetXPosition() const
	{
		return _ptr->GetCoordinates().x; 
	}
	/*@brief Get y coordinate
	* @retval : y position 
	*/
	value_type GetYPosition() const
	{
		return _ptr->GetCoordinates().y;
	}

	/*@breif Get Current Heading of Vehicle 
	* @retval: "South", "West", "North" or "East" depending on heading. 
	*/
	string GetHeading() const noexcept
	{
		return 	_ptr->HeadingStr(); 
	}
	/*Default destructor*/
	~Room() = default; 

};

/*@brief  Move vehicle or change heading (F-Forward, B - Backward, R - Right, L - Left) 
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
		else
			throw invalid_argument("Invalid vehicle movement"); 
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
Room<V,Args...>::Room(value_type width, value_type length, Args&&... args) : _width{ width }, _length{ length }, _ptr{ make_unique<V>(forward<Args>(args)...) }
{
	value_type x = _ptr->GetCoordinates().x; 
	value_type y = _ptr->GetCoordinates().y; 
	value_type diameter = _ptr->GetDiameter();

	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");
	else if (( x > width - diameter)  || (y > length - diameter))
		throw out_of_range("Vehicle initial position outside of room"); 

}

/*@brief Constructor using vehicle pointer (V*).
* @param width : Room width
* @param length: Room length
* @param ptr   : Vehicle pointer
*/
template<typename V, typename... Args>
Room<V, Args...>::Room(value_type width, value_type length, V* ptr) : _width{ width }, _length{ length }, _ptr{ ptr }
{
	value_type x = _ptr->GetCoordinates().x;
	value_type y = _ptr->GetCoordinates().y;
	value_type diameter = _ptr->GetDiameter();

	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");
	else if ((x > width - diameter) || (y > length - diameter))
		throw out_of_range("Vehicle initial position outside of room");
}

/*@brief Constructor moving unique_ptr rvalue (holding pre-existing) into
*        object pointer.
* @param width : Room width
* @param length: Room length
* @param ptr   : Unique Ptr (rvalue)
*/
template<typename V, typename... Args>
Room<V, Args...>::Room(value_type width, value_type length, unique_ptr<V>&& ptr) : _width{ width }, _length{ length }, _ptr{ move(ptr) }
{
	value_type x = _ptr->GetCoordinates().x;
	value_type y = _ptr->GetCoordinates().y;
	value_type diameter = _ptr->GetDiameter();

	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");
	else if ((x > width - diameter) || (y > length - diameter))
		throw out_of_range("Vehicle initial position outside of room");
}

/*@brief Constructor that constructs rvalue vehicle object in place 
* @param width : Room width
* @param length: Room length
* @param obj   : Vehicle object (rvalue)
*/
template<typename V, typename... Args>
Room<V, Args...>::Room(value_type width, value_type length, V&& obj) : _width{ width }, _length{ length }
{
	value_type x = obj.GetCoordinates().x;
	value_type y = obj.GetCoordinates().y;
	value_type diameter = obj.GetDiameter();

	auto ptr = operator new(sizeof(V));
	new (ptr) V(x, y, obj.Get_Cardinal_Points(), diameter); //in place construction 
	_ptr = move(unique_ptr<V>(static_cast<V*>(ptr)));

	
	if (width <= 0 || length <= 0)
		throw invalid_argument("Width and length shall only be positive");
	else if ((x > width - diameter) || (y > length - diameter))
		throw out_of_range("Vehicle initial position outside of room");
}

/*@brief Get Vehicle Heading
 *@retval Vehicle heading in string format e.g., "North"
 */
template<typename T>
string Vehicle<T>::HeadingStr() noexcept
{
	string tmp;

	switch (_cpts)
	{
	case South:
		tmp = "South";
		break;
	case SouthEast:
		tmp = "SouthEast";
		break;
	case East:
		tmp = "East";
		break;
	case NorthEast:
		tmp = "NorthEast";
		break;
	case North:
		tmp = "North";
		break;
	case NorthWest:
		tmp = "NorthWest";
		break;
	case West:
		tmp = "West";
		break;
	case SouthWest:
		tmp = "SouthWest";
		break;

	default:
		break;

	}
	return tmp;
}

/*@brief Vehicle overloded post decrement opreator
* @retval Reference to the vehicle object calling the method (*this)
*/
template<typename T> 
Vehicle<T>& Vehicle<T>::operator--(int) noexcept
{
	switch (_cpts)
	{
	case South:
		_cpts = SouthEast;
		break;
	case SouthEast:
		_cpts = East;
		break;
	case East:
		_cpts = NorthEast;
		break;
	case NorthEast:
		_cpts = North;
		break;
	case North:
		_cpts = NorthWest;
		break;
	case NorthWest:
		_cpts = West;
		break;
	case West:
		_cpts = SouthWest;
		break;
	case SouthWest:
		_cpts = South;
		break;
	default:
		break;
	}

	return *this;
}

/*@brief Vehicle overloded post increment opreator
* @retval Reference to the vehicle object calling the method (*this)
*/
template<typename T>
Vehicle<T>& Vehicle<T>::operator++(int) noexcept
{

	switch (_cpts)
	{
	case South:
		_cpts = SouthWest;
		break;
	case SouthWest:
		_cpts = West;
		break;
	case West:
		_cpts = NorthWest;
		break;
	case NorthWest:
		_cpts = North;
		break;
	case North:
		_cpts = NorthEast;
		break;
	case NorthEast:
		_cpts = East;
		break;
	case East:
		_cpts = SouthEast;
		break;
	case SouthEast:
		_cpts = South;
		break;
	default:
		break;
	}

	return *this;
}

/* @brief Transform user input to room width and size
*  @param width : room width
*  @param length: room length
*  @return      : None
*/
template<typename T>
void RoomSize(T& width, T& length)
{
	string str;
	cout << "Enter the size of the room (width x length) separated by whitespace: ";
	getline(cin, str); //read entire line, do not stop at whitespace 
	istringstream isstream(str); //string stream for string to numeric conversion
	if (!(isstream >> width))
		throw invalid_argument("Room size must match the type of the coordinate system");
	if (!(isstream >> length))
		throw invalid_argument("Room size must match the type of the coordinate system");
	if (width == 0 || length == 0)
		throw invalid_argument("Room width and length must be positive");
}

