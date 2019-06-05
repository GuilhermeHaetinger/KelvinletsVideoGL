#ifndef VIDEOGL_HEADER
#define VIDEOGL_HEADER

#include "RenderableFrame.h"
#include "GLFW/glfw3.h"

class VideoGL{
	private:
		RenderableFrame * renderableFrames;
		void InitializeVertices();
		void InitializeColors();
		void InitializeIndices();
	public:
		VideoGL(const char * videoPath);
		void show();
};

#endif
