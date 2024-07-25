#include <iostream>
#include "Simulator.h"
#include <string>
#include <Monster_Truck.h>


using namespace std; 

int main()
{
	try
	{
		string str;
		int width;
		int length;
		int x_initial;
		int y_initial;

		Cardinal_Points dir = North; 
		RoomSize(width, length); 
		VehiclePosition(x_initial, y_initial, dir); 
		//construction from rvalue reference (placement new)
		Room<Monster_Truck> r(width, length, Monster_Truck(x_initial, y_initial, dir)) ;
		cout << "Enter a route (F-Forward, B-Back, R-Right, L-Left): ";
		cin >> str;
		r.ChangeHeading(str); 
		cout << "Simulation Successful" << endl; 
		cout << "Coordinates: " << "(" << r.GetXPosition() << "," << r.GetYPosition() << ")" << endl; 
		cout << "Heading: " << r.GetHeading() << endl; 
	}
	catch (const exception& e)
	{
		cout << "Exception caught: " << e.what() << endl; 
	}

	return 0; 
}