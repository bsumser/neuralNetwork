#include "Student.hpp"
#include <string>

//Default Constructor
Student::Student(void) {
	std::cout << "student class created" << std::endl;
}

//Copy Constructor
Student::Student(void) {
	std::cout << "student class created" << std::endl;
}


//Move Constructor
Student::Student(void) {
	std::cout << "student class created" << std::endl;
}


//Overloaded constructor?
Student::Student(std::string f, std::string l, int a) {
	std::cout << "student class created" << std::endl;
	std::cout << "first name set" << std::endl;
	std::cout << "last name set" << std::endl;
	std::cout << "age set" << std::endl;

	setfirstName(f);
	setlastName(l);
	setAge(a);
}
