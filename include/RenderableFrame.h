#ifndef RASTERIZABLE_FRAME_HEADER
#define RASTERIZABLE_FRAME_HEADER

#include "VideoWindow.h"

class RenderableFrame{
	private:
		GLfloat * vertexArray;
		GLfloat * colorArray;
		void checkArrays();
	public:
		RenderableFrame();
		void setVertexArray(GLfloat * vertexArray, int size);
		void setColorArray(GLfloat * colorArray, int size);
		void draw(VideoWindow videoWindow);
};

#endif
