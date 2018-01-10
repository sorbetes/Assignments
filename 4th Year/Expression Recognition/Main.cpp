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


using namespace std;
//using namespace cv;
using namespace dlib;

extern int expression_num;

int main(int argc, const char** argv)
{

	array2d<bgr_pixel> img_new;
	array2d<unsigned char> img_gray;
	point head_pt;

	char* file_location = "../Data/";

	//Read Images for various emotions
	//cv::Mat I = cv::imread("../Data/Sun01.jpg", -1);
	//cv::resize(I, I, cv::Size(50, 50));
	
	char* image_emot[] = {

		"E00.jpg",		//0
		"E01.jpg",		//1
		"E02.jpg",		//2
		"E03.jpg",		//3
		"E04.jpg",		//4

	};

	int number_of_emot = sizeof(image_emot) / sizeof(image_emot[0]);

	cv::Mat* emot = new cv::Mat[number_of_emot];

	for (int file_no = 0; (file_no < number_of_emot); file_no++)
	{
		string filename(file_location);
		filename.append(image_emot[file_no]);
		emot[file_no] = cv::imread(filename, -1);

		if (emot[file_no].empty())
		{
			cout << "Could not open " << emot[file_no] << endl;
			return -1;
		}


	}

	cv::Mat background, bgr[3];

	for (int i = 0; i < number_of_emot; i++)
	{
		inRange(emot[i], cv::Scalar(0, 130, 0), cv::Scalar(0, 255, 0), background);
		cv::bitwise_not(background, background);


		split(emot[i], bgr);

		cv::Mat tmp[4] = {bgr[0], bgr[1], bgr[2], background};
		merge(tmp, 4, emot[i]);

		cvtColor(emot[i], emot[i], cv::COLOR_BGRA2RGBA);

		imshow("a", emot[i]);

		cout << "?? \n";

	}
	

	//Read Face Images
	char* image_files[] = {

		"01.jpg",		//0
		"02.jpg",		//1
		"03.jpg",		//2
		"04.jpg",		//3
		"05.jpg",		//4
		"06.jpg",		//5
		"07.jpg",

	};

	int number_of_images = sizeof(image_files) / sizeof(image_files[0]);

	cv::Mat* image = new cv::Mat[number_of_images];

	//OpenCV

	for (int file_no = 0; (file_no < number_of_images); file_no++)
	{
		string filename(file_location);
		filename.append(image_files[file_no]);
		image[file_no] = cv::imread(filename, -1);
		if (image[file_no].empty())
		{
			cout << "Could not open " << image[file_no] << endl;
			return -1;
		}

	}

	// Face detector - get bounding boxes for each face in an image.
	frontal_face_detector detector = get_frontal_face_detector();
	// Shape_predictor - predict face landmark positions given an image and face bounding box.
	shape_predictor sp;
	deserialize("../Data/shape_predictor_68_face_landmarks.dat") >> sp;

	// Loop over all the images
	for (int i = 0; i < number_of_images; i++)
	{

		head_pt = processImage(image[i], sp, detector);
		editImage(emot[expression_num], image[i], head_pt);

	}

	//cin.get();
	cv::destroyAllWindows();
}

//http://docs.opencv.org/2.4/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
//https://gist.github.com/nikotan/1148913
//http://www.learnopencv.com/facial-landmark-detection/
//http://dlib.net/
//http://blog.dlib.net/2014/08/real-time-face-pose-estimation.html