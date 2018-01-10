#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include "opencv2/core/core_c.h"
#include <dlib/opencv/cv_image.h>
#include <dlib/image_processing/generic_image.h>

#include "A.h"


//using namespace cv;
using namespace dlib;

bool mouthOpen(point mouthU, point mouthL) {

	//int distance_n;
	int distance;

	//distance_n = sqrt(pow(n_mouthU.x() - n_mouthL.x(), 2) + pow(n_mouthU.y() - n_mouthL.y(), 2));
	distance = sqrt(pow(mouthU.x() - mouthL.x(), 2) + pow(mouthU.y() - mouthL.y(), 2));

	if (distance > 5) {
		return true;
	}

	else return false;

}

int mouthCornersClose(point left, point right, point up) {

	//Emotion
	point ab2(up.x() - left.x(), up.y() - left.y());
	point cb2(up.x() - right.x(), up.y() - right.y());
	float dot2 = (ab2.x() * cb2.x() + ab2.y() * cb2.y()); // dot product
	float cross2 = (ab2.x() * cb2.y() - ab2.y() * cb2.x()); // cross product
	float alpha2 = atan2(cross2, dot2);
	float Angle2 = (int)floor(alpha2 * 180. / pi + 0.5);
	cout << "Angle: " << Angle2 << endl;

	//if there's a difference in angle
//	if (abs(abs(AngleN) - abs(Angle2)) > 5) {	//neutral still if only slight angle change
		if (Angle2 > -175 && Angle2 < -10) {
			cout << "Downwards. \n";
			return 1;
		}

		else if (Angle2 < 175 && Angle2 > 10) {
			cout << "Upwards. \n";
			return 2; //Downwards
		}
//	}

	cout << "Neutral. \n";

	return 0;

}

int mouthCornersOpen(point left, point right, point up) {

	point ab2 = up - left;
	point cb2 = up - right;
	float dot2 = (ab2.x() * cb2.x() + ab2.y() * cb2.y());		//dot product
	float cross2 = (ab2.x() * cb2.y() - ab2.y() * cb2.x());		//cross product
	float alpha2 = atan2(cross2, dot2);
	float Angle2 = (int)floor(alpha2 * 180. / pi + 0.5);
	cout << "Angle: " << Angle2 << endl;

	//if (abs(abs(AngleN) - abs(Angle2)) > 5) {
		if (Angle2 > -175 && Angle2 < -10) {
			cout << "Downwards. \n";
			return 3;
		}

		else if (Angle2 < 175 && Angle2 > 10)  {
			cout << "Upwards. \n";
			return 4;
		}
	//}

	cout << "Smiling. \n";

	return 4;


}
