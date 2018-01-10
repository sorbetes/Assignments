#include <iostream>
#include <string>
#include "Student.h"

Student::Student(): lastName(""), firstName(""), ID(0), Mark(0), next(NULL){

}
/*
Student::Student(string lname, string fname, int id, int m): lastName(lname), firstName(fname), ID(id), Mark(m), next(NULL){

}
*/
int Student::compare(Student* data) {

    if(ID > data->ID)
            return 0;
    else return 1;

}