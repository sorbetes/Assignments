
#include <string>
#include "MP3.h"

class MusicCollection {

  public: 

	MP3 *list;
	int maxNumber;
	int currentlyInTheList;

	MusicCollection();
	~MusicCollection();
	MusicCollection(int x);

	bool add (MP3);
	bool isInTheList(string, string);

};