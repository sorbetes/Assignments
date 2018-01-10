#include <iostream>
#include <string>
#include <fstream>
#include "StudentList.h"

using namespace std;

int main () {
	
	StudentList sList;

	ifstream in; 
	in.open("student176.txt"); 
	if (in.fail()) { 
		cout << "unable to open student176.txt" << endl; 
		}	 
	int x = 0;

	while (!in.eof()) { 
		Student *student = new Student(); 
		in >> student->lastName >> student->firstName; 
		in >> student->ID >> student->Mark; 

		sList.add(student);
		x++;
		cout << student->lastName;
		cout << "==========added" << x << endl;
	}

	in.close();

	sList.output("studentSorted.txt");
	
	return 0;
}