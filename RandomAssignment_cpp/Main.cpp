#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "List.h"
#include "GPSlist.h"

using namespace std;

int main () {

    List sList, glist;
    ifstream in;
	double threshold;


    in.open("GPS.txt");
    if (in.fail()) {
            cout << "unable to open GPS.txt" << endl;
	}

    while (!in.eof()) {
        GPS *gps = new GPS();						
        in >> gps->latitude >> gps->longtitude;

        glist.addGPS(gps);
    }
    in.close();
	
	in.open("Sensor.txt");
    if (in.fail()) {

            cout << "unable to open Sensor.txt" << endl;

            }

    while (!in.eof()) {

        Sensor *sensor = new Sensor();
        in >> sensor->X >> sensor->Y;
        in >> sensor->Z;
        sList.addSensor(sensor);
    }

    in.close();
	
	//Ask user if he/she wants to get location/acceleration??
	
	glist.getLocation(); 
	sList.readAcceleration();

	cout << "================================================" << endl;
	cout << "Z axis threshold?: ";
	cin >> threshold;
	
	glist.print(sList, threshold);

	return 0;
}
