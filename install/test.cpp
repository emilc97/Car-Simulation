#include "CSimulator.h"
#include <iostream>

using namespace std; 


int main()
{
	//Room<Car, int > r(1, 2, 3); 
	try
	{
		Room<Car, int, int, Direction> r2(20, 16, 1, 2, West);
		Room<Car> r3(20, 16, new Car(1, 2, South));
		unique_ptr<Car> ptr = make_unique<Car>(1, 2, South);
		Room<Car> r4(20, 16, move(ptr));
		Room<Car> r5(20, 16, make_unique<Car>(1, 2, South));

		r2.Right();
		r2.Back();
		r2.Back();

	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
