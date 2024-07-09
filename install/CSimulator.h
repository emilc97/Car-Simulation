//inclusion guard 
#pragma once 
#include <iostream>

using namespace std; 

class Room
{
	int _width; 
	int _length; 
	public: 
	explicit Room(int width, int length) : _width{ width }, _lenght{ length }
	{
#ifdef VERBOSE 
		cout << "Room constructor called with width:" << width << " and length " << length << endl; 
#endif 
	}


};
