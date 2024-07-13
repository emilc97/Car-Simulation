#include <iostream>
#include "Simulator.h"
#include <sstream>
#include <string>
#include <Car.h>
using namespace std; 

/* @brief Set rooms size (width x length) 
*  @param width : room width
*  @param length: room length 
*  @return      : None
*/
void RoomSize(int& width, int& length)
{
	string str; 
	cout << "Enter the size of the room (width x length) separated by whitespace: ";
	getline(cin, str); //read entire line, do not stop at whitespace 
	istringstream isstream(str); //string stream for string to numeric conversion
	if (!(isstream >> width))
		throw invalid_argument("Room width must be numeric"); 
	if (!(isstream >> length))
		throw invalid_argument("Room length must be numeric");
	if (width == 0 || length == 0)
		throw invalid_argument("Room width and length must be positive"); 
}

/* @brief Set vehicle position (x,y) and initial heading (S, W, N, E) 
*  @param x  : x coordinate 
*  @param y  : y coordinate 
*  @param dir: Initial Heading (direction) 
*  @return   : None 
*/
void VehiclePosition(int& x, int& y, Direction& dir)
{
	string str, tmp; 
	cout << "Enter the initial coordinates (position) of the car and heading (S, W, N, E):";
	getline(cin, str);
	istringstream isstream{ str }; 
	if (!(isstream >> x))
		throw invalid_argument("X coordinate must be numeric");
	if (!(isstream >> y))
		throw invalid_argument("Y coordinate must be numeric");
	isstream >> tmp; //string stream for string to numeric conversion

	//set vehicle direction
	if (tmp == string{ 'S' })
		dir = South;
	else if (tmp == string{ 'W' })
		dir = West;
	else if (tmp == string{ 'N' })
		dir = North;
	else if (tmp == string{ 'E' })
		dir = East;
	else
		throw invalid_argument("Invalid direction requested for the vehicle. Valid are (S, W, N, E)"); 
}


int main()
{
	try
	{
		string str;
		int width;
		int length;
		int x_initial;
		int y_initial;

		Direction dir = North; 
		RoomSize(width, length); 
		VehiclePosition(x_initial, y_initial, dir); 
		//construction from rvalue reference (placement new) 
		Room<Car> r(width, length, Car(x_initial, y_initial, dir));
		cout << "Enter a route (F-Forward, B-Back, R-Right, L-Left): ";
		cin >> str;
		r.ChangeHeading(str); 
		cout << "Simulation Successful" << endl; 
	}
	catch (const exception& e)
	{
		cout << "Exception caught: " << e.what() << endl; 
	}

	return 0; 
}