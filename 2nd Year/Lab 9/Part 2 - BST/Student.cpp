#include <iostream>
#include <string>
#include "Student.h"

Student::Student()
	: lastName(""), firstName(""), ID(0), Mark(0), left(NULL), right(NULL){

}

Student::Student(string lname, string fname, int id, int m)
	: lastName(lname), firstName(fname), ID(id), Mark(m), left(NULL), right(NULL){

}

Student::~Student(){

	if (left != NULL)
		delete left;
	if (right != NULL)
		delete right;

}

int Student::compare(Student* data) {

    if(ID > data->ID)
            return 0;
    else return 1;

}