#ifndef RASTERIZABLE_FRAME_HEADER
#define RASTERIZABLE_FRAME_HEADER

#include "VideoWindow.h"

class RenderableFrame{
	private:
		GLfloat * vertexArray;
		GLfloat * colorArray;
		GLuint * indexArray;
		int getNumberOfVertices(Proportions proportions);
		int getNumberOfIndices(Proportions proportions);
	public:
		RenderableFrame(GLfloat * vertexArray, GLfloat * colorArray, GLuint * indexArray);
		void draw(VideoWindow videoWindow);
};

#endif
