
#include <string>
#include <iostream>
#include "MP3.h"
#include "MusicCollection.h"


using namespace std;

int main ()
{
	
	int max;

	cout << "-------------------------Enter max number of songs: ";
	cin >> max;

	MusicCollection collection(max);
	
	MP3 song1("song1", "artist1", 123, "blah1");
	MP3 song2("song2", "artist2", 123, "blah2");
	MP3 song3("song3", "artist3", 123, "blah3");

/*
	MP3 *start = collection.list;
	
	*collection.list++ = MP3("song1", "artist1", 123, "blah1");
	*collection.list++ = MP3("song2", "artist2", 123, "blah2");
	*collection.list++ = MP3("song3", "artist3", 123, "blah3");

	collection.list = start;

*/
	if (collection.add (song1))
		cout <<"-------------------------successfully added" <<endl;
	else 
		cout << "-------------------------array full"<<endl;
	if (collection.add (song2))
		cout <<"-------------------------successfully added" <<endl;
	else 
		cout << "-------------------------array full"<<endl;
	if (collection.add (song3))
		cout <<"-------------------------successfully added" <<endl;
	else 
		cout << "-------------------------array full"<<endl;
	if (collection.add (song3))
		cout <<"-------------------------successfully added" <<endl;
	else 
		cout << "-------------------------array full"<<endl;
	if (collection.add (song3))
		cout <<"-------------------------successfully added" <<endl;
	else 
		cout << "-------------------------array full"<<endl;

	if (collection.isInTheList("song1","artist1"))
		cout <<"-------------------------song found" <<endl;
	else
		cout <<"-------------------------no song found" <<endl;

	if (collection.isInTheList("song4","artist4"))
		cout <<"-------------------------song found" <<endl;
	else
		cout <<"-------------------------song not found" <<endl;

return 0;
}