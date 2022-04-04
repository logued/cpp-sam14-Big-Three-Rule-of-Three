//
// April 2022
//

#ifndef SAM14_BIG_THREE_STUDENT_H
#define SAM14_BIG_THREE_STUDENT_H

#include <string>
#include <iostream>

class Student       // Student class defined in same file here for ease of reading
{
private:
    std::string name;
    double* location;	// GPS location , using array of two double values, latitude and longitude

    // Note: Dynamically allocated memory used here for demonstration purposes.
    // A standard array could be used for the location as it doesn't change in size.

public:

    Student(std::string name, double latitude, double longitude) ;

    Student();	// default constructor

    // Copy constructor
    // Accepts one Student object as a parameter (the source) and
    // copies the data from the source into the Student object
    // being constructed (the destination).
    // If the source contains data in dynamically allocated memory (on Heap) then
    // new memory must be allocated in the destination object to store that data.
    //
    Student(const Student& source);

    void printStudent() ;

    void setLocation(double latitude, double longitude) ;

    // Destructor.
    // When each Student object goes out of scope, or is deleted,
    // its destructor is called.
    // This is your chance to delete any dynamically allocated memory that
    // has been allocated by this object. Omitting this will cause memory leaks.
    //
    ~Student() ;

    // Overloaded assignment "operator="
    // This is invoked (called) when one student object is assigned to another
    // e.g. student1 = student2;
    // Again, its purpose is to ensure that data stored in dynamically allocated memory (on Heap)
    // belonging to the source object, is properly copied to dynamically allocated memory
    // belonging to the destination object.
    //
    Student& operator= (const Student& otherStudent);

    // Declaring overloaded global extraction >> and insertion << operators
    // These are NOT member functions (as they don't have the "Student::" scope resolution
    // operator in front of their definition in the Student.cpp file).
    // However, they are declared as FRIEND functions in the header file, which gives the functions
    // direct access to the fields (member data).

    friend std::ostream& operator << (std::ostream& out, const Student& c); // insertion operator

    friend std::istream& operator >> (std::istream& in, Student& c);        // extraction operator

};


#endif //SAM14_BIG_THREE_STUDENT_H
