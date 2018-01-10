#include <iostream>
#include <string>
#include "MusicCollection.h"

MusicCollection::MusicCollection(){

	list = new MP3[10];
	maxNumber = 0;
	currentlyInTheList = 0;
	cout << "Default CONSTRUCTOR" << endl;
}

MusicCollection::MusicCollection(int x){
	
	currentlyInTheList = 0;
	list = new MP3[x];
	maxNumber = x;
	cout << "x CONSTRUCTOR" << endl;

}

MusicCollection::~MusicCollection(){

	delete [] list;
	list = NULL;
	cout << "DESTRUCTOR" << endl;
}

bool MusicCollection::add (MP3 m){

	MP3 *p = list;
	cout << "Number of songs in list: " <<currentlyInTheList << endl;
	if (currentlyInTheList<maxNumber) {
		p[currentlyInTheList++]= m;
		cout << "ADD" << endl;
		return true;
	}
	else {
		cout << "ADD X" << endl;
		return false;
	}
}

bool MusicCollection::isInTheList(string song, string name){

	MP3* p = list;
	for (int i=0; i < maxNumber; i++){

		if ((p->getSongName()==song) && p->getArtistName()==name){
			cout << "isInTheList" << endl;
			return true;
		}
		p++;
	}
	cout << "isInTheList X" << endl;
	return false;
}