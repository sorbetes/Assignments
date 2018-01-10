#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "StudentList.h"

using namespace std;

int main () {

    StudentList sList;

    ifstream in;
    in.open("student10000.txt");
    if (in.fail()) {
            cout << "unable to open student10000.txt" << endl;
            }

    while (!in.eof()) {
        Student *student = new Student();
        in >> student->lastName >> student->firstName;
        in >> student->ID >> student->Mark;

        sList.add(student);
    }

    in.close();

    //sList.output("studentSorted.txt");
	int id1, id2, id3,id4;
	id1 = 8004100;
	id2 = 8008363;
	id3 = 8000000;
	id4 = 8888888;

	Student* p;

	p = sList.findStudent(id1);

	if (p == NULL){
		cout << "Student not found. " << endl;
	}
	else {
		cout << left << setw(13) << p->lastName << setw(10) << p->firstName << "  0" << p->ID << " " << p->Mark;
        cout << endl;
	}

	p = sList.findStudent(id2);

	if (p == NULL){
		cout << "Student not found. " << endl;
	}
	else {
		cout << left << setw(13) << p->lastName << setw(10) << p->firstName << "  0" << p->ID << " " << p->Mark;
        cout << endl;
	}

	p = sList.findStudent(id3);

	if (p == NULL){
		cout << "Student not found. " << endl;
	}
	else {
		cout << left << setw(13) << p->lastName << setw(10) << p->firstName << "  0" << p->ID << " " << p->Mark;
        cout << endl;
	}

	p = sList.findStudent(id4);

	if (p == NULL){
		cout << "Student not found. " << endl;
	}
	else {
		cout << left << setw(13) << p->lastName << setw(10) << p->firstName << "  0" << p->ID << " " << p->Mark;
        cout << endl;
	}

	return 0;
}