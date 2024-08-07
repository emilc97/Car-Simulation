#include "Simulator.h"
#include <iostream>
#include "Monster_Truck.h"
using namespace std;

/*@brief Testing the Simulator library overloaded constructors*/
void Constructors()
{
	cout << "********************Constructors - START******************************" << endl;
	Room<Monster_Truck, int, int, Cardinal_Points> r(20, 16, 4,5, West);
	cout << "Executing some driving with parameter pack constructor" << endl;
	r.Forward();
	r.Forward(); 
	r.Forward(); 
	r.Right();
	r.Forward();
	r.Back();
	r.Back(); 
	r.Back(); 
	cout << "Expected coordinate (1,3)" << endl;
	cout << r << endl;
	Room<Monster_Truck> r2(20, 16, new Monster_Truck(1, 2, South));
	cout << "Executing some driving with Vehicle allocated using keyword new" << endl;
	r2.Back();
	r2.Back();
	r2.Left();
	r2.Left();
	r2.Forward();
	cout << "Expected coordinate (1,5)" << endl; 
	cout << r2 << endl;
	unique_ptr<Monster_Truck> ptr = make_unique<Monster_Truck>(1, 2, South);
	Room<Monster_Truck> r3(20, 16, move(ptr));
	cout << "Executing some driving with already allocated vehicle using unique_ptr (move ownership)" << endl;
	r3.Back();
	r3.Back();
	r3.Left();
	r3.Left();
	r3.Left();
	r3.Left();
	r3.Forward();
	r3.Forward(); 
	r3.Right(); 
	r3.Back(); 
	r3.Back(); 
	r3.Right(); 
	r3.Right(); 
	r3.Forward(); 
	cout << "Expected coordinate (4,2)" << endl;
	cout << r3 << endl;
	cout << "Executing some driving with already allocated vehicle using make unique in constructor (move ownership)" << endl;
	Room<Monster_Truck> r4(20, 16, make_unique<Monster_Truck>(8, 10, West));
	r4.Back();
	r4.Back();
	r4.Back(); 
	r4.Back(); 
	r4.Right();
	r4.Right();
	r4.Forward();
	r4.Left(); 
	r4.Left(); 
	r4.Left(); 
	r4.Left(); 
	r4.Right(); 
	r4.Forward(); 
	r4.Forward(); 
	r4.Forward(); 
	cout << "Expected coordinate (13,7)" << endl;
	cout << r4 << endl;
	cout << "Executing some driving with placement new constructor" << endl;
	Room<Monster_Truck> r5(20, 16, Monster_Truck(6, 8, West));
	r5.Back();
	r5.Back();
	r5.Back();
	r5.Back();
	r5.Right();
	r5.Right();
	r5.Forward();
	r5.Left();
	r5.Left();
	r5.Left();
	r5.Left();
	r5.Right();
	r5.Forward();
	r5.Forward();
	r5.Forward();
	cout << "Expected coordinate (11,5)" << endl;
	cout << r5 << endl;
	cout << "********************Constructors - END******************************" << "\n\n"; 
}

/*@brief Test Member Functions of the Simulator Library*/ 
void Member_Func()
{
	cout << "********************Member Functions - START*************************" << endl; 
	Room<Monster_Truck> r(20, 16, Monster_Truck(1, 2, South)); 
	r.Initial_Position(12, 11); 
	cout << "Position shall now be (12, 11)" << endl; 
	cout << "Using overloaded extraction << operator..." << endl; 
	cout << r << endl; 
	cout << "Using member methods..." << endl; 
	cout << "(" << r.GetXPosition() << "," << r.GetYPosition() << ")" << endl; 
	cout << "********************Member Functions - END*************************" << "\n\n"; 
}

/*@brief Testing Monster_Truck movement in the Simulator Library*/
void Routes()
{
	cout << "*****************Routes Testing - START************************" << endl; 
	Room<Monster_Truck> r(25, 12, Monster_Truck(4, 4, West)); 
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
	try
	{
		string str; 
		Constructors();
		Member_Func(); 
		//Routes(); 
		cout << "Enter a route (F- Forward, B-Back, L-Left, R-Right) and end with a newline. Start position will be (1,2):" << endl; 
		cin >> str; 
		Room<Monster_Truck> r(20, 10, Monster_Truck(1, 2, North)); 
		r.ChangeHeading(str); 
	}
	catch (const exception& e)
	{
		cout << "Exception caught:" << e.what() << endl;
	}

	return 0;
}
