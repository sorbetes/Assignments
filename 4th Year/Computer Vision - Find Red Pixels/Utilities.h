/*
 * This code is provided as part of "A Practical Introduction to Computer Vision with OpenCV"
 * by Kenneth Dawson-Howe © Wiley & Sons Inc. 2014.  All rights reserved.
 */
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include <iostream>

using namespace std;
using namespace cv;

void writeText( Mat image, char* text, int row, int column, Scalar colour=-1.0, double scale=0.4, int thickness=1 );
Mat JoinImagesHorizontally( Mat& image1, char* name1, Mat& image2, char* name2, int spacing=0, Scalar colour=-1.0 );
Mat JoinImagesVertically( Mat& image1, char* name1, Mat& image2, char* name2, int spacing=0, Scalar colour=-1.0 );

void findPixels(Mat& orig_image, Mat& samp_image, Mat& red_image);


Mat StretchImage( Mat& image );
void DrawHistogram( MatND histograms[], int number_of_histograms, Mat& display_image );