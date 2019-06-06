#include "../include/VideoGL.h"

VideoGL::VideoGL(const char * videoPath) : videoWindow(Proportions(0, 0, 0)){
	cv::VideoCapture video(videoPath);
	int width = video.get(CV_CAP_PROP_XI_WIDTH);
	int height = video.get(CV_CAP_PROP_XI_HEIGHT);
	int length = video.get(CV_CAP_PROP_FRAME_COUNT);

}

void VideoGL::initializeVertices(){}
void VideoGL::initializeColors(){}
void VideoGL::initializeIndices(){}

void VideoGL::show(){}
