/*
* This code is provided as part of "A Practical Introduction to Computer Vision with OpenCV"
* by Kenneth Dawson-Howe © Wiley & Sons Inc. 2014.  All rights reserved.
*/
#include "Utilities.h"

//Adapted from CVExample

class Histogram
{
protected:
	Mat mImage;
	int mNumberChannels;
	int* mChannelNumbers;
	int* mNumberBins;
	float mChannelRange[2];
public:
	Histogram(Mat image, int number_of_bins)
	{
		mImage = image;
		mNumberChannels = mImage.channels();
		mChannelNumbers = new int[mNumberChannels];
		mNumberBins = new int[mNumberChannels];
		mChannelRange[0] = 0.0;
		mChannelRange[1] = 255.0;
		for (int count = 0; count<mNumberChannels; count++)
		{
			mChannelNumbers[count] = count;
			mNumberBins[count] = number_of_bins;
		}
	}
	virtual void ComputeHistogram() = 0;
	virtual void NormaliseHistogram() = 0;
	
};
class ColourHistogram : public Histogram
{
private:
	MatND mHistogram;
public:
	ColourHistogram(Mat image, int number_of_bins) :
		Histogram(image, number_of_bins)
	{
		ComputeHistogram();
	}
	void ComputeHistogram()
	{
		const float* channel_ranges[] = { mChannelRange, mChannelRange, mChannelRange };
		calcHist(&mImage, 1, mChannelNumbers, Mat(), mHistogram, mNumberChannels, mNumberBins, channel_ranges);
	}
	void NormaliseHistogram()
	{
		normalize(mHistogram, mHistogram, 1.0);
	}
	Mat BackProject(Mat& image)
	{
		Mat& result = image.clone();
		const float* channel_ranges[] = { mChannelRange, mChannelRange, mChannelRange };
		calcBackProject(&image, 1, mChannelNumbers, mHistogram, result, channel_ranges, 255.0);
		return result;
	}
	MatND getHistogram()
	{
		return mHistogram;
	}
};

void findPixels(Mat& orig_image, Mat& samp_image, Mat& red_image)
{
	//FIND RED PIXELS============================================================
	//find the road signs using sample image - back projection (road sign sample)
	Mat hls_image;
	
	cvtColor(samp_image, hls_image, CV_BGR2HLS);
	ColourHistogram histogram3D(hls_image, 8);
	histogram3D.NormaliseHistogram();
	cvtColor(orig_image, hls_image, CV_BGR2HLS);
	Mat back_projection_probabilities = histogram3D.BackProject(hls_image);
	back_projection_probabilities = StretchImage(back_projection_probabilities);
	Mat back_projection_probabilities_display;
	cvtColor(back_projection_probabilities, back_projection_probabilities_display, CV_GRAY2BGR);
	char c = cvWaitKey();

	Mat stop_signs;
	orig_image.copyTo(stop_signs, back_projection_probabilities_display);
	imshow("Stop Signs", stop_signs);
	//imwrite("Stop Signs.jpg", stop_signs);
	c = cvWaitKey();
	cvDestroyAllWindows;

	//find the red pixels of the stop signs image using inRange
	Mat hsv;
	cvtColor(stop_signs, hsv, COLOR_BGR2HSV);

	Mat mask1, mask2;
	inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
	inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);
	Mat mask = mask1 | mask2;

	Mat red_pix1;
	stop_signs.copyTo(red_pix1, mask);
	imshow("Red Pixels 1", red_pix1);
	//imwrite("Red Pixels 1.jpg", red_pix1);
	c = cvWaitKey();


	//find red using back projection (red sample)
	cvtColor(red_image, hls_image, CV_BGR2HLS);
	ColourHistogram histogram3d(hls_image, 8);
	histogram3d.NormaliseHistogram();
	cvtColor(stop_signs, hls_image, CV_BGR2HLS);
	back_projection_probabilities = histogram3d.BackProject(hls_image);
	back_projection_probabilities = StretchImage(back_projection_probabilities);
	cvtColor(back_projection_probabilities, back_projection_probabilities_display, CV_GRAY2BGR);

	Mat red_pix2;
	stop_signs.copyTo(red_pix2, back_projection_probabilities_display);
	imshow("Red Pixels 2", red_pix2);
	//imwrite("Red Pixels 2.jpg", red_pix2);
	c = cvWaitKey();
	cvDestroyAllWindows();

	//combine both mask
	Mat red_both;
	bitwise_or(mask, back_projection_probabilities, red_both);
	imshow("Both", red_both);
	//imwrite("Both.jpg", red_both);
	c = cvWaitKey();
	cvDestroyAllWindows();

	//Red Pixels of Road sign after applying mask
	Mat show_red;
	stop_signs.copyTo(show_red, red_both);
	imshow("Red Pixels in Road Signs", show_red);
	//imwrite("Red Pixels in Road Signs.jpg", show_red);
	c = cvWaitKey();
	cvDestroyAllWindows();

	//Process to close the gaps
	Mat eroded_image, dilated_image;
	Mat five_by_five_element(11, 11, CV_8U, Scalar(1));
	dilate(red_both, dilated_image, five_by_five_element);
	erode(dilated_image, eroded_image, five_by_five_element);

	//Final Red Pixels of Road Signs
	Mat final_red;
	orig_image.copyTo(final_red, eroded_image);
	imshow("Red Pixels After Processing", final_red);
	//imwrite("Red Pixels After Processing.jpg", final_red);
	c = cvWaitKey();
	cvDestroyAllWindows;
	//imwrite("Red Pixels.jpg", final_red);

	//FIND WHITE PIXELS=================================================================
	//FIND COUNTOURS TO GET IMAGE INSIDE RED BORDER
	//http://bytefish.de/blog/extracting_contours_with_opencv/
	Mat gray_rs;
	cvtColor(final_red, gray_rs, CV_RGB2GRAY);
	imshow("Red Pixels - Gray Scale", gray_rs);
	//imwrite("Red Pixels - Gray Scale.jpg", gray_rs);
	c = cvWaitKey();

	vector< vector<Point> > contours;
	findContours(gray_rs, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	Mat mask_4 = Mat::zeros(gray_rs.rows, gray_rs.cols, CV_8UC1);
	drawContours(mask_4, contours, -1, Scalar(255), CV_FILLED);
	imshow("Filled Contours", mask_4);
	//imwrite("Filled Contours.jpg", mask_4);
	c = cvWaitKey();

	//The Road Signs in full
	Mat roadSigns_full;
	orig_image.copyTo(roadSigns_full, mask_4);
	imshow("Road Signs - Full", roadSigns_full);
	//imwrite("Road Signs Full.jpg", roadSigns_full);
	c = cvWaitKey();
	cvDestroyAllWindows;

	//GET BLACK AND WHITE PIXELS
	Mat gray_s;
	cvtColor(roadSigns_full, gray_s, COLOR_BGR2GRAY);
	imshow("Gray", gray_s);
	//imwrite("Gray.jpg", gray_s);
	c = cvWaitKey();
	threshold(gray_s, gray_s, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("Threshold", gray_s);
	//imwrite("Threshold.jpg", gray_s);
	c = cvWaitKey();

	//Remove red pixels aka 'both' so that only white and black is left
	Mat only_bw;
	subtract(gray_s, eroded_image, only_bw);
	imshow("Threshold Black And White", only_bw);
	//imwrite("ThresholdBW.jpg", only_bw);
	c = cvWaitKey();
	//imwrite("white.jpg", only_bw);
	cvDestroyAllWindows;

	//Show only white pixels
	Mat white;
	roadSigns_full.copyTo(white, only_bw);
	imshow("White", white);
	//imwrite("White Pixels.jpg", white);
	c = cvWaitKey();

	//Show only black pixels
	Mat black = roadSigns_full - white - final_red;
	imshow("Black", black);
	//imwrite("Black Pixels.jpg", black);
	c = cvWaitKey();

	//Show both black and white pixels
	Mat bandw = black + white;
	imshow("Black & White", bandw);
	//imwrite("Black & White Pixels.jpg", bandw);
	c = cvWaitKey();
	cvDestroyAllWindows;

}
