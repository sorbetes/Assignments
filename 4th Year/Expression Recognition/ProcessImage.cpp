#include "A.h"

int expression_num;

point processImage(cv::Mat& image, shape_predictor SP, frontal_face_detector FFD){
	//int expression_num;
	image_window win;

	cout << "Processing image \n";
	array2d<bgr_pixel> img;
	assign_image(img, cv_image<bgr_pixel>(image));
	//image larger
	//pyramid_up(img);


	//currently only works for only one face
	std::vector<dlib::rectangle> dets = FFD(img);
	//https://ibug.doc.ic.ac.uk/resources/facial-point-annotations/
	std::vector<full_object_detection> shapes;
	full_object_detection shape = SP(img, dets[0]);

	// Draw circles
	draw_solid_circle(img, shape.part(48), 5, 2);
	draw_solid_circle(img, shape.part(54), 5, 2);
	draw_solid_circle(img, shape.part(62), 5, 2);
	draw_solid_circle(img, shape.part(66), 5, 2);

	win.set_image(img);

	if ((mouthOpen(shape.part(62), shape.part(66)) == true)) { //If mouth is open

		expression_num = mouthCornersOpen(shape.part(48), shape.part(54), shape.part(62));

		cout<< expression_num << "Open \n";
	}

	else {											//If mouth is closed
		expression_num = mouthCornersClose(shape.part(48), shape.part(54), shape.part(62));
		cout << expression_num << "Close \n";
	}

	//8 - chin
	//27 - top of nose
	//Get point above head 
	float lenAB = sqrt(pow(shape.part(8).x() - shape.part(27).x(), 2.0) + pow(shape.part(8).y() - shape.part(27).y(), 2.0));
	point C(shape.part(27).x() + (shape.part(27).x() - shape.part(8).x()) /
		lenAB * (lenAB * .5), shape.part(27).y() + (shape.part(27).y() - shape.part(8).y()) / lenAB * (lenAB * .5));

	cin.get();
	return C;
}


void editImage(cv::Mat& image_emot, cv::Mat& image, point aboveHead) {
	cout << "Editing Image. \n";

	image_window win_n;
	array2d<bgr_pixel> img, img_new;

	cv::resize(image_emot, image_emot, cv::Size(100, 100));

	cvtColor(image, image, cv::COLOR_BGR2RGBA);
	

	(image_emot).copyTo(image(cv::Rect(aboveHead.x() - (image_emot.cols / 2), 
		aboveHead.y() - (image_emot.rows / 2), image_emot.cols, image_emot.rows)));


	assign_image(img, cv_image<rgb_alpha_pixel>(image));
	dlib::assign_image(img_new, img);

	win_n.set_image(img_new);
	cin.get();
	
}