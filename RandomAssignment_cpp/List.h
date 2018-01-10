#include <string>
#include <iostream>
#include "Sensor.h"
#include "GPS.h"

using namespace std;

class List {

public:
        List();
        //~List();
		void addSensor(Sensor* s);
		void readAcceleration();

        void addGPS(GPS* g);
		void getLocation();
		void print (List a, double b);

private:
		Sensor *shead;
		Sensor *stail;
		double totalZ;
		int sCount;
		
		GPS *ghead;
        GPS *gtail;
        int counterforZ;
};
