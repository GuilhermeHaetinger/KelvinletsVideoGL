#include "../include/RenderableFrame.h"

RenderableFrame::RenderableFrame(GLfloat * vertexArray, GLfloat * colorArray, GLuint * indexArray){
	this->vertexArray = vertexArray;
	this->colorArray = colorArray;
	this->indexArray = indexArray;
}

void RenderableFrame::draw(VideoWindow videoWindow){
}
