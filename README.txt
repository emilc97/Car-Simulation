Author: Emil Carmegren 
Date: 2024-07-10
Project: Radio Car Simulation 
OS: Linux/Ubuntu
Build System: Make 

[BRIEF]
This projects simulates a vehicle in a 2-dimensional space. 
The 2-dimensional space is represented by the class 'Room' 
which monitors and manages control of the vehicle. If the vehicle hits any of the 
walls an exception will be thrown, stack unwinding occurs, and the user will 
prompted that the program has terminated. Otherwise, simulation will succeed 
and a message regarding end position and heading will be printed to the terminal. 

[Features]
- Templates are used to support a wide range of coordinate types and 
  parameter packing for object construction. 
- Specialization of vehicles through inheritance using a common 
  abstract base class and trajectory system. 
- Smart pointer for memory leakage protection and prevention 
  of stack overflow. 
- Exception handling for invalid input and simulation failure. 
- The templated classes are header-only to problem during 
  linking due to template instantiation. 
- Cross platform: The project uses make and is thus compatible 
  with several platforms and IDEs (e.g., Visual Studio). 

[DESCRIPTION] 
The application is implemented using one abstract base class Vehicle.
Each vehicle implements as set of basic methods, purely virtual, such as left, 
right, forward and back. Additionally, the cardinal points are managed via 
overloaded ++ and -- operators for wrap-around behaviour. This natively 
moves from South-> South West ->West .. and vice versa for ++ and -- 
respectively. The operators could be used each time left/right is 
called (e.g., Monster Truck) or be managed more intelligently depending 
on the vehicle and derived class specialization. 

Each vehicle holds a coordinate system instantiated using a template 
parameter. This enables support for movement in both floating point 
and integral grid. The vehicle allows for public access of its template 
parameter as 'value_type'. 

The Room requires a concrete type of class Vehicle. This means that 
all the purely virtual methods needs to be properly overridden. The 
Room uses the inherent left(), back(), forward(), right() methods 
to move the vehicle. The type for the underlying vehicle coordinate 
system is obtained from the Vehicle<T>::value_type. This ensures that methods 
that uses parameters from the vehicle can work for all types of vehicles. 
Independent of which template type they were instantiated with. 

[Overloaded Constructors]
The Room class provides a set of overloaded constructors to support 
parameter packing, c-style pointers, smart pointers and move semantics. 

- Construction of the vehicle object using parameter packing, e.g., 
  Room<Monster_Truck> r(10, 12, 1, 2, South); 
  Where, the 3 last parameters are (x,y) coordinate for initial position 
  and initial heading (direction). 

- Construction of the vehicle using vehicle pointer. 
  Room<Monster_Truck> r(10, 12, new Monster_Truck(1,2, South); 

- Construction of the vehicle using a unique_ptr to a pre-existing 
  vehicle objects. 
  Room<Monster_Truck> r(10,2, make_unique<Monster_Truck>(1,2,South); 

- Construction of the vehicle using placement new for in-place construction
  passing an rvalue reference to a vehicle. 
  Room<Monster_Truck>(10, 12, Monster_Truck(1,2, West)); 

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







