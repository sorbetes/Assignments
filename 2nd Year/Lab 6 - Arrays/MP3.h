#include <string>
#include <iostream>
#pragma once

using namespace std;

class MP3 {

private:
	string songName;		
	string artistName;		  
	int duration;
	string review;

public:
	MP3();		
	MP3(string, string, int, string);	

	void print ();

	string getSongName();
	string getArtistName();
	int getDuration();
	string getReview();

	void setSongName(const string& s);
	void setArtistName(const string& a);
	void setDuration(const int& a);
	void setReview(const string& a);

};