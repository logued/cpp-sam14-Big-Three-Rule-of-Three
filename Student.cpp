//
//  Rule of Three       --       April 2022
//

#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student(string name, double latitude, double longitude) {
    this->name = name;

    this->location = new double[2];    // dynamically allocate an array of 2 doubles from the Heap
                                        // (could also be a class object or any resource)
    this->location[0] = latitude;
    this->location[1] = longitude;
}

Student::Student()    // default constructor
{
    this->name = "John Doe";
    this->location = new double[2];    // dynamically allocate an array of 2 doubles from the Heap
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
Student::Student(const Student &source) {
    cout << "... Student Copy Constructor was called." << endl;
    this->name = source.name;

    this->location = new double[2];    // dynamically allocate a new block of memory
    // to hold a copy of the location data

    this->location[0] = source.location[0];    // copy the location data
    this->location[1] = source.location[1];
}

void Student::printStudent() {
    cout << this->name << ", " << location[0] << ", " << location[1] << endl;
}

void Student::setLocation(double latitude, double longitude) {
    this->location[0] = latitude;
    this->location[1] = longitude;
}

// Destructor.
// When each Student object goes out of scope, or is deleted,
// its destructor is called.
// This is your chance to delete any dynamically allocated memory that
// has been allocated by this object. Omitting this will cause memory leaks.
//
Student::~Student() {
    cout << "... Student Destructor ~Student() was called." << endl;

    // delete the array of doubles we allocated dynamically in the constructor
    delete[] this->location;

    // If deleting only a single object, then leave out the brackets []
}

// Overloaded assignment "operator="
// This is invoked (called) when one student object is assigned to another
// e.g. student1 = student2;
// Again, its purpose is to ensure that data stored in dynamically allocated memory (on Heap)
// belonging to the source object, is properly copied to dynamically allocated memory
// belonging to the destination object.
//
Student &Student::operator=(const Student &otherStudent) {
    cout << "... Student Overloaded assignment operator= was called." << endl;

    // self-assignment guard i.e. no need to do anything if someone uses s1 = s1;
    if (this == &otherStudent)
        return *this;            // reference to same object

    // copy data from the source (rhs) to this object - the destination (lhs)
    this->name = otherStudent.name;

    // must make a new location object to store a copy of other student location
    if (this->location == nullptr)        // allocate memory if it doesn't already exist
        this->location = new double[2];

    for (int i = 0; i < 2; i++) {
        this->location[i] = otherStudent.location[i];  // copy the 2 location values
    }

    // return this new object so that we can 'chain' this operator (e.g. "s1=s2=s3")
    return *this;   // returns this Student object
}

/* the stream insertion "operator<<" is invoked by the following pattern :
   "outputStream << Student"  e.g. cout << s1;
   Note that this is somewhat equivalent to the .toString() method in Java.
   It allows us to 'dump' and object's contents to the output stream.
*/

// Parameters:   << ("output stream", "reference to a constant Student object")
// Returns:      reference to the output stream (usually 'cout')
//
ostream& operator<< (ostream& out, const Student& student)
{
    // As this is defined as a 'friend' of Student in the header file,
    // code here has direct access to the private member data of the Student object.
    // (So, we don't need to call getters and setters)

    // code to implement the operator<< functionality
    out << "Name: " << student.name << endl;
    out << "Location - Latitude : "  << student.location[0] << endl;
    out << "Location - Longitude: "  << student.location[1] << endl;

    return out;
}

/* The extraction "operator>>"  is invoked by the following pattern
   "  inputStream >> Student     "

*/

istream& operator>> (istream& in, Student& student)
{
    cout << "extraction operator not implemented yet";

}