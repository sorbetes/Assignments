#include <string>
#include <iostream>
#include "Student.h"

using namespace std;

class StudentList {

public:
	int x;
	StudentList();
	~StudentList();

	void add(Student* s);
	//void output(string);
	Student *findStudent (int id);

private:
	Student *root;
	int numberOfComparisons;
};