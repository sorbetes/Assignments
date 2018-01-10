#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "List.h"
#include <algorithm>
#include <Windows.h>

List::List(){

	shead = stail = NULL;
	totalZ = 0;
	sCount = 0;

	ghead = gtail = NULL;
    counterforZ = 0;

}
/*
List::~List() {

	while(shead) {
            Sensor *s = shead->next;
            delete shead;
            shead = s;
    }

	while(ghead) {
            GPS *g = ghead->next;
            delete ghead;
            ghead = g;
    }

}
*/
void List::addSensor(Sensor* s){

        if(shead == 0){
            s->next = shead;
            shead = s;
		}

		else {
            Sensor *e = shead;

            while (e->next)
				e = e->next;
			
            s->next = e->next;
          e->next = s;
	    }
}

void List::readAcceleration(){

	Sensor *s = shead;
        while (s){
			cout << "(" << s->X << ", " << s->Y <<  ", " << s->Z <<")" << endl;
			s = s->next;
        }

}



void List::addGPS(GPS* g){

    if(ghead == 0){
            g->next = ghead;
            ghead = g;
    }

    else {
            GPS *p = ghead;

            while (p->next)
                    p = p->next;

            g->next = p->next;
            p->next = g;

    }
}

void List::getLocation(){

	GPS *g = ghead;
        while (g){
			cout << "(" << g->latitude << ", " << g->longtitude << ")" << endl;
			g = g->next;
        }

}


void List::print(List a, double b){

	cout << endl;

	GPS *g = ghead;
	Sensor *s = a.shead;

    while (g){
		cout << "(" << g->latitude << ", " << g->longtitude << "): " <<(s->Z)<< endl;
		sCount++;
		totalZ = totalZ + (s->Z);
		g = g->next;
		s = s->next;
		Sleep(1000);	
	}

	cout << endl;
	cout << "Average Z-axis acceleration is:" << totalZ/sCount << endl;
	cout << endl;
	cout << "Only the value where the absolute value of Z-axis component of the acceleration is greater than " << b <<", in descending order:" << endl;
	
	Sensor *y = a.shead;
	double threshold = b;
	double* zThresh = new double [sCount];
	int i = 0;
	
	while (y){                                                     //this loop stores Z-values that is greather than threshold
		if(((y->Z) > threshold)||(y->Z) < (threshold*-1)){         //in an array
			zThresh[i] = y->Z;
			i++;
		}
		y = y->next;
	}
	
	bool swapped = true;											//puts Z values in descending order
	int j= 0;
	while (swapped) {
		swapped = false;
		j++;
		for (int k = 0; k < i - j; k++){
			if (zThresh[k] < zThresh[k+1]){
				swap(zThresh[k], zThresh[k+1]);
				swapped = true;
			}
		}
	}	

	for (int k = 0; k < i; k++){                                   //prints out coordinates with Zvalue greater than threshold
		GPS *x = ghead;
		Sensor *n = a.shead;

		while (n){
		if(zThresh[k] == n->Z){
			cout << "(" << x->latitude << ", " << x->longtitude << "): " << (n->Z) << endl;
		}
		x = x->next;
		n = n->next;
		}
	}

	delete[] zThresh;
}