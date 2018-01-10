#include <string>
#include <iostream>

using namespace std;

class Student {

public:
	string lastName;
	string firstName;
	int ID;
	int Mark;

	Student* left;
	Student* right;

	Student();
	~Student();
	Student(string, string, int, int);
	
	int compare(Student* data);

};