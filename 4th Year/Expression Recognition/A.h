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


using namespace std;
//using namespace cv;
using namespace dlib;

bool mouthOpen(point mouthU, point mouthL);

int mouthCornersClose(point left, point right, point up);

int mouthCornersOpen(point left, point right, point up);

point processImage(cv::Mat& orig_image, shape_predictor SP, frontal_face_detector FFD);

void editImage(cv::Mat& image_emot, cv::Mat& image, point aboveHead);