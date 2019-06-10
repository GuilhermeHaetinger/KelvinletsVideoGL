#ifndef RASTERIZABLE_FRAME_HEADER
#define RASTERIZABLE_FRAME_HEADER

#include "VideoWindow.h"
#include "Frame.h"
#include "Logger/Logger.h"

class RenderableFrame{
	private:
		Frame frame;
		void checkArrays();
	public:
		RenderableFrame();
		RenderableFrame(Frame frame);
		void setVertexArray(GLfloat * vertexArray, int size);
		void setColorArray(GLfloat * colorArray, int size);
		Frame getFrame();
		void draw(VideoWindow videoWindow);
};

#endif
