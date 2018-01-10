#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "StudentList.h"

StudentList::StudentList(){

    root = NULL;
	numberOfComparisons = 0;
    cout << "CONSTRUCTOR." << endl;

}

StudentList::~StudentList() {

   if(root != NULL)
	   delete root;
    cout << "DESTRUCTOR." << endl;
}

void StudentList::add(Student* s){
	
	Student *p, *pp;
	int r;

	if (root == NULL)
		root = s;
	
	else {
		p = root;
		pp = NULL;
		while (p) {
			pp = p;
			r = s->compare(p);
			p = (r > 0) ? p->right : p->left;
		}
		if (r > 0)
			pp->right = s; 
		else 
			pp->left = s;
	}
    cout << "Adding/Sorting." << endl;
}
/*
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

    cout << "Output created. Check folder." << endl;
    out.close();

}
*/
Student* StudentList::findStudent(int id){
	
	Student *p, *pp;
	numberOfComparisons = 0;
	p = root;
	pp = NULL;
	while (p) {
		numberOfComparisons++;
		if (p->ID == id){
			cout << "----------NUMBER OF COMPARISONS: " << numberOfComparisons << endl;
			return p;
		}

		pp = p;
		p = (p->ID > id) ? p->right : p->left;
	}
	cout << "----------NUMBER OF COMPARISONS: " << numberOfComparisons << endl;
	return NULL;
}