
#include <iostream>
#include <string>
#include "MP3.h"



	MP3::MP3(): songName (""), artistName (""), duration (0), review ("") 
	{
	};		

	MP3::MP3(string name, string artist, int d, string rev): 
	songName (name), artistName (artist), duration (d), review (rev) 
	{
	}
	
	string MP3::getSongName(){
		return songName;
	}
	string MP3::getArtistName(){
		return artistName;
	}
	int MP3::getDuration(){
		return duration;
	}
	string MP3::getReview(){
		return review;
	}

	void MP3::setSongName(const string& s){
		songName=s;
	}
	void MP3::setArtistName(const string& a){
		artistName=a;
	}
	void MP3::setDuration(const int& d){
		duration=d;
	}
	void MP3::setReview(const string& r){
		review=r;
	}
	
	void MP3::print ()
	{
		cout << endl<<"Song name: "<< songName<<endl;
		cout << "Artist name: "<< artistName<<endl;
		cout << "Duration (seconds): "<< duration<<endl;
		cout << "Review: "<< review<<endl;
	
	}

