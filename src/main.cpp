#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <iostream>
#include "../include/Logger/Logger.h"
#include "../include/VideoGL.h"

using namespace std;
using namespace cv;


int main(){

	VideoCapture cap("videoSamples/bunny.mp4");
	if(!cap.isOpened()){
		Logger::log_error("Video wont open!");
	}

	Logger::log_debug("Entering Main function!");
	VideoGL video("videoSamples/bowler.avi");
	video.show();

	return 0;
}

