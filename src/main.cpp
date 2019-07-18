#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <iostream>
#include "../include/Logger/Logger.h"
#include "../include/VideoGL.h"
#include "../include/VideoDeformer.h"

using namespace std;
using namespace cv;


int main(){

	VideoCapture cap("videoSamples/bunny.mp4");
	if(!cap.isOpened()){
		Logger::log_error("Video wont open!");
	}

	Logger::log_debug("Entering Main function!");
	VideoGL video("videoSamples/bunny.mp4");
	
//	video.show();
		
	Proportions prop = video.getProportions();
	Frame * frames = (Frame *) malloc(prop.length * sizeof(Frame));

	video.getFrames(frames);

	Deformation deformation(vec3(100, 100, 50), vec3(10,50,70), 50.);
	VideoDeformer * def = new VideoDeformer(deformation, frames, prop);

	Frame * newFrames = def->deform(deformation);

	video.resetFrames(newFrames);
	video.show();

	return 0;
}

