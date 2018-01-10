#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Utilities.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

//Adapted from CVExample

#define ORIGINAL_IMAGE 0
#define SAMPLE_IMAGE 1
#define RED_SAMPLE_IMAGE 2
#define WELCOME 3



int main(int argc, const char** argv)
{
	//Reading more than one image
	char* file_location = "../Media/";
	char* image_files[] = {

		"original_image.jpg",		//0
		"sample_roadsigns.jpg",		//1
		"sample_red.jpg",			//2
		"welcome.jpg",				//3
	};

	

	int number_of_images = sizeof(image_files) / sizeof(image_files[0]);

	Mat* image = new Mat[number_of_images];

	for (int file_no = 0; (file_no < number_of_images); file_no++)
	{
		string filename(file_location);
		filename.append(image_files[file_no]);
		image[file_no] = imread(filename, -1);
		if (image[file_no].empty())
		{
			cout << "Could not open " << image[file_no] << endl;
			return -1;
		}
	}

	blur(image[0], image[0], Size(5, 5));

	int choice;
	do
	{
		imshow("Welcome", image[WELCOME]);
		choice = cvWaitKey();
		cvDestroyAllWindows();
		switch (choice)
		{
		case 'a':
			findPixels(image[ORIGINAL_IMAGE], image[SAMPLE_IMAGE], image[RED_SAMPLE_IMAGE]);
			break;
		break;
		default:
			break;
		}
	} while ((choice != 'x') && (choice != 'X'));

	//===============================================================for reading
	//http://docs.opencv.org/3.1.0/dc/df6/tutorial_py_histogram_backprojection.html
	//http://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/back_projection/back_projection.html
	//http://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html
	//http://answers.opencv.org/question/4330/road-signs-detection-filling-conturs/
	//http://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html
	//http://docs.opencv.org/3.1.0/d3/dc0/group__imgproc__shape.html
	//http://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html
	//http://docs.opencv.org/2.4/modules/core/doc/clustering.html
	//http://docs.opencv.org/3.1.0/d3/dc0/group__imgproc__shape.html#ga17ed9f5d79ae97bd4c7cf18403e1689a
	//http://stackoverflow.com/questions/12204522/efficiently-threshold-red-using-hsv-in-opencv
	//http://opencv-srf.blogspot.ie/2010/09/object-detection-using-color-seperation.html
	//====================================================================

	destroyAllWindows();
}