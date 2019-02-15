#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

class Student
{
	private:
		std::string firstName;
		std::string lastName;
		int age;

	public:
		setfirstName(string x){firstName = x;}
		setlastName(string y){lastName = y;}
		setAge(int z){age = z;}
		getfirstName(){return firstName;}
		getlastName(){return lastName;}
		getAge(){return age;}

		//constructor
		Student(void);
		
		//constructor
		Student();
		
		//constructor
		Student();
		
		//constructor
		Student();
		

};
#endif
