#include <string>
#include <iostream>
#pragma once

using namespace std;

class MP3 {

private:
	string songName;		
	string artistName;		  
	int duration;

	char *review;
	int length;

public:
	MP3();
	~MP3();
	
	MP3(string name, string artist, int d, char *rev);	
	
	MP3 (const MP3 &source);
	void operator=(const MP3&source);

	void print ();

	string getSongName();
	string getArtistName();
	int getDuration();
	char *getReview();

	void setSongName(const string& s);
	void setArtistName(const string& a);
	void setDuration(const int& a);
	void setReview(char *rev);

};