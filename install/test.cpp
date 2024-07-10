#include "Simulator.h"
#include <iostream>
#include "Car.h"
using namespace std;


void Constructors()
{
	cout << "********************Constructors - START******************************" << endl;
	Room<Car, int, int, Direction> r(20, 16, 1, 2, West);
	cout << "Executing some driving with parameter pack constructor" << endl;
	r.Forward();
	r.Right();
	r.Forward();
	r.Back();
	cout << r << endl;
	Room<Car> r2(20, 16, new Car(1, 2, South));
	cout << "Executing some driving with Vehicle allocated using keyword new" << endl;
	r2.Back();
	r2.Back();
	r2.Left();
	r2.Left();
	r2.Forward();
	cout << r2 << endl;
	unique_ptr<Car> ptr = make_unique<Car>(1, 2, South);
	Room<Car> r3(20, 16, move(ptr));
	cout << "Executing some driving with already allocated vehicle using unique_ptr (move ownership)" << endl;
	r3.Back();
	r3.Back();
	r3.Left();
	r3.Left();
	r3.Forward();
	cout << r3 << endl;
	cout << "Executing some driving with already allocated vehicle using make unique in constructor (move ownership)" << endl;
	Room<Car> r4(20, 16, make_unique<Car>(1, 2, South));
	r4.Back();
	r4.Back();
	r4.Right();
	r4.Right();
	r4.Forward();
	cout << r4 << endl;
	cout << "Executing some driving with placement new constructor" << endl;
	Room<Car> r5(20, 16, Car(1, 2, South));
	r5.Back();
	r5.Back();
	r5.Right();
	r5.Right();
	r5.Forward();
	cout << r5 << endl;
	cout << "********************Constructors - END******************************" << "\n\n"; 
}

void Member_Func()
{
	cout << "********************Member Functions - START*************************" << endl; 
	Room<Car> r(20, 16, Car(1, 2, South)); 
	r.Initial_Position(12, 11); 
	cout << "Position shall now be (12, 11)" << endl; 
	cout << "Using overloaded extraction << operator..." << endl; 
	cout << r << endl; 
	cout << "Using member methods..." << endl; 
	cout << "(" << r.GetXPosition() << "," << r.GetYPosition() << ")" << endl; 
	cout << "********************Member Functions - END*************************" << "\n\n"; 
}

void Routes()
{
	cout << "*****************Routes Testing - START************************" << endl; 
	Room<Car> r(25, 12, Car(4, 4, West)); 
	r.Right(); 
	r.Forward(); 
	r.Forward(); 
	r.Forward(); 
	r.Left(); 
	r.Left(); 
	r.Back(); 
	cout << "Now the coordinates shall be (4, 8)" << endl; 
	r.Left(); 
	r.Left(); 
	r.Left(); 
	r.Left(); 
	r.Left(); 
	r.Right(); 
	r.Back(); 
	r.Back(); 
	r.Right(); 
	r.Forward(); 
	r.Forward(); 
	cout << "Now the coordinates shall be (2, 10)" << endl;
	cout << r << endl; 
	cout << "Lets hit the uppermost wall" << endl; 
	r.Right(); 
	r.Forward(); 
	r.Forward(); 
	r.Forward(); 
	cout << "********************Routes Testing - END*****************************" << "\n\n"; 
}

int main()
{
	//Room<Car, int > r(1, 2, 3); 
	try
	{
		string str; 
		Constructors();
		Member_Func(); 
		//Routes(); 
		cout << "Enter a route (F- Forward, B-Back, L-Left, R-Right) and end with a newline" << endl; 
		cin >> str; 
		Room<Car> r(20, 10, Car(1, 2, North)); 
		r.ChangeHeading(str); 
	}
	catch (const exception& e)
	{
		cout << "Exception caught:" << e.what() << endl;
	}

	return 0;
}
