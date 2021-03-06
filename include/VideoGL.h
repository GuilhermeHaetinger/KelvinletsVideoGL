#ifndef VIDEOGL_HEADER
#define VIDEOGL_HEADER

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <unistd.h>

#include "RenderableFrame.h"
#include "VideoWindow.h"
#include "Logger/Logger.h"

#include <FreeImage.h>

class VideoGL{
	private:
		RenderableFrame * renderableFrames;
		VideoWindow videoWindow;
		int getWidth();
		int getHeight();
		int getLength();
		GLfloat normalizeWidth(int index);
		GLfloat normalizeHeight(int index);
		void initializeFrames();
		void initializeVertices();
		void initializeColors(cv::VideoCapture video);
	public:
		VideoGL(const char * videoPath);
		void resetFrames(Frame * frames);	
		void getFrames(Frame * dest);
		Proportions getProportions();
		void show(unsigned int fm);
};

#endif
