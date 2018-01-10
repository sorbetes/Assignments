#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "StudentList.h"

StudentList::StudentList(){

	head = NULL;
	tail= NULL;
	n = 0;
	
	cout << "CONSTUCTOR." << endl;

}

StudentList::~StudentList() {

	while(head) {
		Student *p = head->next;
		delete head;
		head = p;
	}
	cout << "DESTRUCTOR." << endl;
}

void StudentList::add(Student* s){
	
	if((head == 0) || (s->compare(head) == 1)){
		s->next = head;
		head = s;
		n++;
		cout << "Adding/Sorting." << n << endl;
	}
	
	else {
		Student *p = head;
	
		while ((p->next) && (s->compare(p->next) == 0 )) 
			p = p->next;

		s->next = p->next;
		p->next = s;
		n++;
		
		cout << "Adding/Sorting. " << n << endl;
	
	}
	

}

void StudentList::output(string){
	
	cout << "Creating output." << endl;
	ofstream out; 
	out.open("studentSorted.txt"); 
	if (out.fail()) { 
		cout << "unable to open studentSorted.txt" << endl; 
		return;
	}
	
	Student *p = head;

	while (p) {
	
		out << left << setw(15) << p->lastName << setw(20) << p->firstName << "  0" << p->ID << " " << p->Mark; 
		out << endl;

		p = p->next;
	}
		out.close(); 

}
