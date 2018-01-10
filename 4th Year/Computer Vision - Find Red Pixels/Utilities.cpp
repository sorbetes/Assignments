/*
 * This code is provided as part of "A Practical Introduction to Computer Vision with OpenCV"
 * by Kenneth Dawson-Howe © Wiley & Sons Inc. 2014.  All rights reserved.
 */
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include "Utilities.h"

using namespace std;
using namespace cv;

void writeText( Mat image, char* text, int row, int column, Scalar passed_colour, double scale, int thickness )
{
	Scalar colour( 0, 0, 255);
	Point location( column, row );
	putText( image, text, location, FONT_HERSHEY_SIMPLEX, scale, (passed_colour.val[0] == -1.0) ? colour : passed_colour, thickness );
}
Mat JoinImagesHorizontally( Mat& image1, char* name1, Mat& image2, char* name2, int spacing, Scalar passed_colour/*=-1.0*/ )
{
	Mat result( (image1.rows > image2.rows) ? image1.rows : image2.rows,
		        image1.cols + image2.cols + spacing,
				image1.type() );
	result.setTo(Scalar(255,255,255));
    Mat imageROI;
	imageROI = result(cv::Rect(0,0,image1.cols,image1.rows));
	image1.copyTo(imageROI);
	if (spacing > 0)
	{
		imageROI = result(cv::Rect(image1.cols,0,spacing,image1.rows));
		imageROI.setTo(Scalar(255,255,255));
	}
	imageROI = result(cv::Rect(image1.cols+spacing,0,image2.cols,image2.rows));
	image2.copyTo(imageROI);
	writeText( result, name1, 13, 6, passed_colour );
	writeText( imageROI, name2, 13, 6, passed_colour );
	return result;
}
Mat JoinImagesVertically( Mat& image1, char* name1, Mat& image2, char* name2, int spacing, Scalar passed_colour/*=-1.0*/ )
{
	Mat result( image1.rows + image2.rows + spacing,
		        (image1.cols > image2.cols) ? image1.cols : image2.cols,
				image1.type() );
	result.setTo(Scalar(255,255,255));
	Mat imageROI;
	imageROI = result(cv::Rect(0,0,image1.cols,image1.rows));
	image1.copyTo(imageROI);
	if (spacing > 0)
	{
		imageROI = result(cv::Rect(0,image1.rows,image1.cols,spacing));
		imageROI.setTo(Scalar(255,255,255));
	}
	imageROI = result(cv::Rect(0,image1.rows+spacing,image2.cols,image2.rows));
	image2.copyTo(imageROI);
	writeText( result, name1, 13, 6, passed_colour );
	writeText( imageROI, name2, 13, 6, passed_colour );
	return result;
}
Mat StretchImage( Mat& image )
{
	Mat& result = image.clone();
	// Find max value
	int image_rows = image.rows;
	int image_channels = image.channels();
	int values_on_each_row = image.cols * image_channels;
	uchar max = 0;
	for (int row=0; row < image_rows; row++) {
		uchar* value = image.ptr<uchar>(row);
		for (int column=0; column < values_on_each_row; column++)
		{
			if (*value > max)
				max= *value;
			value++;
		}
	}
	// Stretch values using a lookup-table
	int entries(256);
	Mat lut(1,entries,CV_8U);
	for (int i=0; (i<256); i++)
		lut.at<uchar>(i) = (255*i)/max;
	LUT(image,lut,result);

	return result;
}
void DrawHistogram( MatND histograms[], int number_of_histograms, Mat& display_image )
	{
		int number_of_bins = histograms[0].size[0];
		double max_value=0, min_value=0;
		double channel_max_value=0, channel_min_value=0;
		for (int channel=0; (channel < number_of_histograms); channel++)
		{
			minMaxLoc(histograms[channel], &channel_min_value, &channel_max_value, 0, 0);
			max_value = ((max_value > channel_max_value) && (channel > 0)) ? max_value : channel_max_value;
			min_value = ((min_value < channel_min_value) && (channel > 0)) ? min_value : channel_min_value;
		}
		float scaling_factor = ((float)256.0)/((float)number_of_bins);
		
		Mat histogram_image((int)(((float)number_of_bins)*scaling_factor),(int)(((float)number_of_bins)*scaling_factor),CV_8UC3,Scalar(255,255,255));
		display_image = histogram_image;
		int highest_point = static_cast<int>(0.9*((float)number_of_bins)*scaling_factor);
		for (int channel=0; (channel < number_of_histograms); channel++)
		{
			int last_height;
			for( int h = 0; h < number_of_bins; h++ )
			{
				float value = histograms[channel].at<float>(h);
				int height = static_cast<int>(value*highest_point/max_value);
				int where = (int)(((float)h)*scaling_factor);
				if (h > 0)
					line(histogram_image,Point((int)(((float)(h-1))*scaling_factor),(int)(((float)number_of_bins)*scaling_factor)-last_height),
								         Point((int)(((float)h)*scaling_factor),(int)(((float)number_of_bins)*scaling_factor)-height),
							             Scalar(channel==0?255:0,channel==1?255:0,channel==2?255:0));
				last_height = height;
			}
		}
	}

