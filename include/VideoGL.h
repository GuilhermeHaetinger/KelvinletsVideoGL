#ifndef VIDEOGL_HEADER
#define VIDEOGL_HEADER

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"

#include "RenderableFrame.h"
#include "VideoWindow.h"
#include "Logger/Logger.h"

class VideoGL{
	private:
		RenderableFrame * renderableFrames;
		VideoWindow videoWindow;
		void initializeVertices();
		void initializeColors();
		void initializeIndices();
	public:
		VideoGL(const char * videoPath);
		void show();
};

#endif
