/* Student Class				Apr 2024

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
 a Copy Constructor in the class that will dynamically
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
#include "Student.h"
#include<iostream>

using namespace std;

int main()
{
	cout << "Creating Student object s1 (will be created on Stack)" << endl;
	Student s1("Tom", 54.10324, -6.41667);		// Normal constructor is called here
    cout << s1 << endl;     // uses overloaded operator<< to output student

    cout << "Student s2(s1); --calls the Copy constructor,  s2 = " << endl;
    Student s2(s1); // calls Copy Constructor to initialize fields in s2 from s1 fields
    cout << s2 << endl;

	cout << "Changing location in s1." << endl;
	s1.setLocation(77.77777, 88.88888);	// change the location fields of s1
	cout << "s1 = ";
	s1.printStudent();

	Student s3 = s1; // also calls copy constructor (and NOT the assignment operator !!)
                    // as s3 is being constructed and did not previously exist.

	cout << "Student s3 = s1;  - calls Copy Constructor, so s3 = ";
	s3.printStudent();

    cout << "Creating s4 (on Stack)" << endl;
	Student s4;
    cout << "s4 = s1; calls overloaded assignment operator= , so s4 = " << endl;
    s4 = s1;			// overloaded assignment operator= is called in this case, (s4 has already been constructed)
	cout << s4 << endl;

	// chaining of assignments is allowed (this is why we return "*this" from the overloaded "operator=" )
	// s4 = s3 = s2 = s1;  // sets them all to value of s1; evaluated Right to Left

    cout << "Using stream insertion operator>> for Student:";
    Student s5;
    cin >> s5;
    cout << "Print s5:\n " << s5 << endl;

    // Dynamically allocate a Student object on the HEAP
	Student* pStudent = new Student("Dynamic Dave", 54.10324, -6.41667);  // dynamically allocate object

    cout << "Print the dynamically allocate student using *pStudent: " << endl;
	cout << *pStudent << endl;  // dereference pointer to print object

    cout << " Deleting pStudent - (student object on Heap) - so expect to see its destructor called." << endl;
	delete pStudent;	// free up dynamically allocated student,
                        // ~Student() destructor is called when we delete the student memory
	pStudent = nullptr;


    // On return ,the Students objects that were automatically created on the stack
    // are now automatically removed from the stack. The destructor for each Student
    // object is called just before it is removed.

    cout << "Exiting the main function(), expect to see destructors called as stack objects are destroyed." << endl;
	return 0;

	//TODO - study the output, and note the calls to the destructor ~Student() as each
	// object goes out of scope. Can you account for each destructor call.
}