#include <string>
#include <iostream>

using namespace std;

class GPS {

public:
        double latitude;
        double longtitude;

        GPS* next;

        GPS();
};
