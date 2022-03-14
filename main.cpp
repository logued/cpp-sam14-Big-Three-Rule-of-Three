/* Student Class				March 2022

Rule of Three (the Big Three) - (now the Big Five with Modern C++)

Classes that use dynamically allocated memory data members (fields)
   (i.e. pointer fields) should always implement the following:

    1. Copy Constructor 
    2. Destructor (to delete/free memory)
    3. Overloaded Assignment operator=
 
 If we do not implement a Copy Constructor then the default Copy Constructor 
 will perform a 'bitwise copy' of the member data from source to destination.
 It simply copies the values from the source fields into the destination fields.

 The problem with this is, that, if one or more source fields are pointers, then
 it is the value(address) in the pointer that is copied, and we end up with the source and
 destination pointers both containing the same address values, and thus, both
 will be pointing at the SAME object in Heap memory.
 
 Usually, we don't want this, and instead, we want each object to have its own copy 
 of the object pointed to. Therefore, our Copy Constructor must dynamically allocate 
 a new object to store a copy.

 Destructor.  In C++, when an object goes out of scope, its destructor is called.
 If there are no pointer fields in the class than we do not need to implement
 anything in the destructor.
 If there are pointer fields (data members) adn if they have been assigned
 dynamically allocated memory blocks, then we must call "delete" or "delete[]"
 to free up the dynamic memory owned by the object.
 If we do not free up this memory, a memory leak will occur.

 Overloaded assignment "operator="
 If we assign one object to another, and there are no pointer fields, then field
 values are copied across directly (a 'bitwise copy' ). If the objects have
 pointer fields, then we need to dynamically allocate a new block of memory to store
 the destination object, and copy the data from the source memory block
 to the destination heap-based block of memory.
  
 */
#include<iostream> 
using namespace std;

class Student       // Student class defined in same file here for ease of reading
{
private:
	string name;
	double* location;	// GPS location , using array of two double values, latitude and longitude

		// Note: Dynamically allocated memory used here for demonstration purposes
		// A standard array could be used for the location as it doesn't change.
public:
	Student(string name, double latitude, double longitude) {
		this->name = name;

		location = new double[2];	// dynamically allocate an array of 2 doubles from the Heap
									// (could also be a class object or any resource)
		location[0] = latitude;
		location[1] = longitude;

	}
	Student()	// default constructor
	{
		name = "John Doe";
		location = new double[2];	// dynamically allocate an array of 2 doubles from the Heap
									// (could also be a class object or any resource)
		location[0] = 0.0;
		location[1] = 0.0;
	}

	// Copy constructor 
	// Copies the fields from the source object into this object 
	// i.e the object being created.
	Student(const Student& source)
	{
		cout << "Copy constructor called. " << endl;
		this->name = source.name;  

		this->location = new double[2];	// dynamically allocate a new block of memory 
										// to hold a copy of the location data
		
		location[0] = source.location[0];	// copy the location data
		location[1] = source.location[1];
	}

	void printStudent() {
		cout << name << ", " << location[0] << ", " << location[1] << endl;
	}

	void setLocation(double latitude, double longitude) {
		location[0] = latitude;
		location[1] = longitude;
	}

	// Destructor.
	// When each Student object goes out of scope, or is deleted, 
	// its destructor is called.
	// This is your chance to delete any dynamically allocated memory that 
	// has been allocated by this object. 

	~Student() {
		cout << "Destructor ~Student called." << endl;
		delete[] location;  // delete the array of doubles we allocated dynamically in the constructor
							// if deleting only a single object, then leave out the brackets []
	}

	// Overloaded assignment operator=
	Student& operator= (const Student& otherStudent)
	{
		cout << "Overloaded assignment operator= called." << endl;

		// self-assignment guard i.e. no need to do anything if someone uses s1 = s1; 
		if (this == &otherStudent)
			return *this;			// reference to same object

		// copy data from the source (rhs) to this object (the destination) lhs
		name = otherStudent.name;

		// must make a new location object to store a copy of other student location

		if (location == nullptr)		// allocate memory if it doesn't already exist
			location = new double[2];

		for (int i = 0; i < 2; i++) {
			location[i] = otherStudent.location[i];  // copy over the 2 location values
		}

		// return the existing object so we can 'chain' this operator
		return *this;
	}
};

int main()
{
	cout << "Creating s1" << endl;
	Student  s1("Tom", 54.10324, -6.41667);		// Normal constructor is called here 
	cout << "s1 = ";
	s1.printStudent();

	Student s2(s1); // calls copy constructor to initialize s2 fields from s1 fields
	cout << "s2 = ";
	s2.printStudent();

	cout << "Changing location in s1." << endl;
	s1.setLocation(77.77777, 88.88888);	// change the location fields of s1
	cout << "s1 = ";
	s1.printStudent();

	Student s3 = s1; // also calls copy constructor
	cout << "s3 = ";
	s3.printStudent();

	Student s4;
	s4 = s1;			// overloaded assignment operator= is called in this case, (s4 has already been constructed)
	cout << "s4 = ";
	s4.printStudent();

	// chaining of assignments is allowed (this is why we return "*this" from overloaded operator=)
	// s4 = s3 = s2 = s1;  // sets them all to value of s1

	Student* pStudent = new Student("Jane", 54.10324, -6.41667);  // dynamically allocate object

	pStudent->printStudent();
	delete pStudent;		// free up dynamically allocated student, destructor is called
	pStudent = nullptr;

    // On return , the Students objects that were automatically created on the stack
    // are now automatically removed from the stack. The destructor for each Student
    // object is called just before it is removed.

	return 0;

	//TODO - study the output, and note the calls to the destructor ~Student() as each
	// object goes out of scope. Can you account for each destructor call.
}