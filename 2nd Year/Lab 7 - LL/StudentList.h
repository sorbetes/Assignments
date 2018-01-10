#include <string>
#include <iostream>
#include "Student.h"

using namespace std;

class StudentList {

public:
	StudentList();
	~StudentList();
	void add(Student* s);
	void output(string);

private:
	Student *head;
	Student *tail;
	int n;

};