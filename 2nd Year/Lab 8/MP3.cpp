
#include <iostream>
#include <string>
#include "MP3.h"



MP3::MP3(){

	songName = "";
	artistName = "";
	duration = 0;
	review = new char;
	*review = 0;
	length = 0;

	cout << "DEFAULT CONSTRUCTOR" << endl;
}		

MP3::~MP3(){

	delete [] review;

	cout << "DESTRUCTOR" << endl;
}

MP3::MP3(string name, string artist, int d, char *rev){

	songName = name;
	artistName = artist;
	duration = d;

	int i;

	for (i = 0; rev[i]!=0; i++);
	length = i;

	review = new char [length+1];

	for (i = 0; i < length+1; i++){
		review[i] = rev[i];
	}

	cout << "CONSTRUCTOR" << endl;
}

MP3::MP3(const MP3 &source)
	: songName(source.songName), artistName(source.artistName),duration(source.duration), length(source.length) {

		review = new char [length+1];
		for (int i = 0;i < length+1; i++){
			review[i] = source.review[i];
		}

	cout << "COPY CONSTRUCTOR" << endl;
}

void MP3::operator=(const MP3&source){

	songName = source.songName;
	artistName = source.artistName;
	duration = source.duration;
	length = source.length;

	delete [] review;

	review = new char[length+1];
	for(int i = 0; i < length+1; i++){
		review[i] = source.review[i];
	}

	cout << "ASSIGNMENT OPERATOR" << endl;

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
char *MP3::getReview(){
	
	char *rev= new char [length+1];

	for (int i=0; i <length+1; i++)
		rev[i] = review[i];

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
void MP3::setReview(char* rev){

	int i;
	
	for (i=0; rev[i]!=0; i++);

	length = i;

	review= new char [length+1];

	for (i=0; i < length+1; i++){
		review[i] = rev[i];
	}

}
	
void MP3::print (){
		cout << "--------------------Song name: "<< songName << endl;
		cout << "--------------------Artist name: "<< artistName << endl;
		cout << "--------------------Duration (seconds): "<< duration << endl;
		cout << "--------------------Review: "<< review << endl;
		cout << endl;
}