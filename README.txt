Author: Emil Carmegren 
Date: 2024-07-10
Project: Radio Car Simulation 
OS: Linux/Ubuntu
Build System: Make 

[DESCRIPTION]
This projects simulates a vehicle in a 2-dimensional space. 
Each vehicle (e.g., car) inherits from abstract base class which requires 
virtual override of a set of elementary methods. This includes Left(), Right() 
Forward() and Back(). The 2-dimensional space is represented by the class 'Room' 
which monitors and manages control of the vehicle. If the vehicle hits any of the 
walls an exception will be thrown, stack unwinding occurs, and the user will 
prompted that the program has terminated. 

The program is developed using templates and parameter packing to support 
simulation of a wide range of vehicles that inherits from the abstract base 
class. The vehicle is dynamically allocated to preserve stack space, and ensure 
compatibility with future extensions of the vehicle class. 


The Room class has a set of overloaded constructors that supports: 
- Construction of the vehicle object using parameter packing, e.g., 
  Room<Car> r(10, 2, 1, 2, South); 
  Where, the 3 last parameters are (x,y) coordinate for initial position 
  and initial heading (direction). 

- Construction of the vehicle using vehicle pointer. 
  Room<Car> r(10,2, new Car(1,2, South); 

- Construction of the vehicle using a unique_ptr to a pre-existing 
  vehicle objects. 
  Room<Car> r(10,2, make_unique<Car>(1,2,South); 

- Construction of the vehicle using placement new for in-place construction
  passing an rvalue reference to a vehicle. 

This allows for a diverse set of construction capabilities, which enhances readability 
and range of applications where the library can be used. 

The Room class holds the vehicle object using a unique_ptr, eliminating risk 
of memory leakage and reducing risk of stack overflow. 

A room can be constructed with any vehicle that inherits from the abstract 
base class Vehicle. As long as the pure virtual functions has been overloaded. 
This makes the class easy to extend for a wide range of vehicles, without the 
need to modify the Room or Vehicle class itself. 

[BUILD]
The program is built using make. The following commands are supported: 

make install   : Install the project under the same directory as the install folder is located. 
                 This creates the directories: bin/, source/, header/, libs/, build/
make uninstall : Removes the folders created during installation. 
make clean     : Clear the build/ and bin/ directory. 
make info      : Print information regarding the build. Including compiler, pre-processor flags, 
                 directories etc. 
make all       : Build all targets 
make bin/test  : Build the test application for the library.
make bin/main  : Build the target. 

The build system uses two makefiles: 
common.mk 
makefile 

The common.mk includes common set of variables useful for 
any new makefile that might be added. This includes, compiler, 
CXXFLAGS, CPPFLAGS, directories and more. 

**********************************************************************************************

[RACE CONDITIONS] 
None. Single-threaded application. 

[EXCEPTION HANDLING]
The class Room constructor and member methods may throw and shall be put within try black to avoid call to std::terminate. 
The following scenarios will throw an exception: 
- A vehicle is constructed at a coordinate that is negative or outside of room. 
- A vehicle is constructed having an invalid direction. Valid (North - 'N', East - 'E', South - 'S', West - 'W') 
- If the initial position coordinates of the vehicle uses characters (e.g., 1 N, S 2) 
- If the room width or length is set by using a character (e.g., 10 N, N 11)






