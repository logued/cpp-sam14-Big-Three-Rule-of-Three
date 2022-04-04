/* Student Class				March 2022

Rule of Three (the Big Three) - (now the Big Five with Modern C++)

RULE:  (The Rule of Three)
 "Classes that have one or more pointer fields MUST
 implement the following three items :"
    1. Copy Constructor
    2. Destructor (to delete/free memory)
    3. Overloaded Assignment operator=

 If we do not implement a Copy Constructor then the
 default Copy Constructor  will perform a 'bitwise copy'
 of the member data from source to destination.
 Meaning that, it simply copies the values from the source
 fields into the destination fields.

 The problem with this is, that, if one or more source fields
 are pointers, then it is the value(address) in the pointer field
 that is copied, and we end up with the source and
 destination pointers both containing the same address values,
 and thus, both will be pointing at the SAME dynamic memory
 object in Heap memory. The dynamic memory ends up being shared by
 both source and destination objects.
 
 Usually, we don't want this, and instead, we want each object to
 have its own copy of the object pointed to. Therefore, we must write
 a Copy Constructor in the class, that will dynamically
 allocate its own block of memory to store a copy of the dynamically
 allocated data in the source object.

 Destructor.
 In C++, when an object goes out of scope, its destructor is called.
 If there are no pointer fields in the class than we do not need to
 implement anything in the destructor. (as there is no memory to free up).
 If there are pointer fields, and if they have been assigned addresses of
 dynamically allocated memory, then we must call "delete" or "delete[]"
 from the Destructor to free up that dynamic memory.
 If we do not free up this memory, a memory leak will occur.

 Overloaded assignment "operator="
 If we assign one object to another, and there are no pointer fields,
 then field values are copied across directly (a 'bitwise copy').
 If the objects have pointer fields, then we need to copy the data
 from the source object to the destination object.
 (Sometimes,  it may be necessary to
 allocate memory in the destination, if it doesn't already exist)
  
 */
#include<iostream> 
using namespace std;

class Student       // Student class defined in same file here for ease of reading
{
private:
	string name;
	double* location;	// GPS location , using array of two double values, latitude and longitude

		// Note: Dynamically allocated memory used here for demonstration purposes.
		// A standard array could be used for the location as it doesn't change.
public:
	Student(string name, double latitude, double longitude) {
		this->name = name;

		this->location = new double[2];	// dynamically allocate an array of 2 doubles from the Heap
									// (could also be a class object or any resource)
		this->location[0] = latitude;
		this->location[1] = longitude;

	}
	Student()	// default constructor
	{
		this->name = "John Doe";
		this->location = new double[2];	// dynamically allocate an array of 2 doubles from the Heap
									// (could also be a class object or any resource)
		this->location[0] = 0.0;
		this->location[1] = 0.0;
	}

	// Copy constructor
    // Accepts one Student object as a parameter (the source) and
    // copies the data from the source into the Student object
    // being constructed (the destination).
    // If the source contains data in dynamically allocated memory (on Heap) then
    // new memory must be allocated in the destination object to store that data.
    //
	Student(const Student& source)
	{
		cout << "Student copy constructor called." << endl;
		this->name = source.name;  

		this->location = new double[2];	// dynamically allocate a new block of memory 
										// to hold a copy of the location data
		
		this->location[0] = source.location[0];	// copy the location data
		this->location[1] = source.location[1];
	}

	void printStudent() {
		cout << this->name << ", " << location[0] << ", " << location[1] << endl;
	}

	void setLocation(double latitude, double longitude) {
		this->location[0] = latitude;
		this->location[1] = longitude;
	}

	// Destructor.
	// When each Student object goes out of scope, or is deleted, 
	// its destructor is called.
	// This is your chance to delete any dynamically allocated memory that 
	// has been allocated by this object. Omitting this will cause memory leaks.
    //
	~Student() {
		cout << "Destructor ~Student() called." << endl;

        // delete the array of doubles we allocated dynamically in the constructor
		delete [] this->location;

        // If deleting only a single object, then leave out the brackets []
	}

	// Overloaded assignment "operator="
    // This is invoked (called) when one student object is assigned to another
    // e.g. student1 = student2;
    // Again, its purpose is to ensure that data stored in dynamically allocated memory (on Heap)
    // belonging to the source object, is properly copied to dynamically allocated memory
    // belonging to the destination object.
    //
	Student& operator= (const Student& otherStudent)
	{
		cout << "Overloaded assignment operator= called." << endl;

		// self-assignment guard i.e. no need to do anything if someone uses s1 = s1; 
		if (this == &otherStudent)
			return *this;			// reference to same object

		// copy data from the source (rhs) to this object - the destination (lhs)
		this->name = otherStudent.name;

		// must make a new location object to store a copy of other student location
		if (this->location == nullptr)		// allocate memory if it doesn't already exist
			this->location = new double[2];

		for (int i = 0; i < 2; i++) {
			this->location[i] = otherStudent.location[i];  // copy the 2 location values
		}

		// return this new object so that we can 'chain' this operator (e.g. "s1=s2=s3")
		return *this;   // returns this Student object
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

	Student s3 = s1; // also calls copy constructor (and NOT the assignment operator !!)
	cout << "s3 = ";
	s3.printStudent();

	Student s4;
	s4 = s1;			// overloaded assignment operator= is called in this case, (s4 has already been constructed)
	cout << "s4 = ";
	s4.printStudent();

	// chaining of assignments is allowed (this is why we return "*this" from overloaded "operator=" )
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