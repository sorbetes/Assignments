#include <string>
#include <iostream>

using namespace std;

class Student {

public:
	string lastName;
	string firstName;
	int ID;
	int Mark;

	Student* next;

	Student();
	//Student(string, string, int, int);
	int compare(Student* data);

};