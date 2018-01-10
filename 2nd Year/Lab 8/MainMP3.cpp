#include "MP3.h"		
#include <iostream>	
#include <string>

using namespace std;

int main(){
	
	char rev1 [] = "1 - Meh.";
	MP3 song1("song1", "artist1", 111, rev1);
	cout << "--------------------SONG 1---- " << endl;
	song1.print();

	char rev2 [] = "2 - Blah Blah.";
	MP3 song2("song2", "artist2", 222, rev2);
	cout << "--------------------SONG 2---- " << endl;
	song2.print();
	
	MP3 song3(song2);
	cout << "--------------------SONG 3---- " << endl;
	cout << "--------------------(song2Copy)---- " << endl;
	song3.print();
	
	char *rev3 = song1.getReview();
	song3.setReview(rev3);
	cout << "--------------------SONG 3---- " << endl;
	cout << "--------------------(ReviewChanged)---- " << endl;
	song3.print();

	MP3 song4 = song1;
	cout << "--------------------SONG 4---- " << endl;
	cout << "--------------------(song1Copy)---- " << endl;
	song4.print();

	MP3 song5; 
	song5 = song1;
	cout << "--------------------SONG 5---- " << endl;
	cout << "--------------------(song1Assign)---- " << endl;
	song5.print();

	char rev5 [] = "Bleeeeugh.";
	song5.setReview(rev5);
	cout << "--------------------SONG 5---- " << endl;
	cout << "--------------------(ReviewChanged)---- " << endl;
	song5.print();

	return 0;
}
