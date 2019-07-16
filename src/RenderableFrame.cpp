#include "../include/RenderableFrame.h"

RenderableFrame::RenderableFrame() : frame(){}

RenderableFrame::RenderableFrame(Frame frame) : frame(frame){}

void RenderableFrame::checkArrays(){
	Logger::log_debug("Checking Arrays!");

	if(!this->frame.vertexArray){
		Logger::log_fatal("Vertex Array not initialized!");
		exit(1);
	}else if(!this->frame.colorArray){
		Logger::log_fatal("Color Array not initialized!");
		exit(1);
	}

	Logger::log_correct("Arrays are set!");
}

void RenderableFrame::setVertexArray(GLfloat * vertexArray, int size){
	if(this->frame.vertexArray != NULL){
		Logger::log_debug("Freeing previous Vertex Array");
		free(this->frame.vertexArray);
	}else
		this->frame.vertexArray = (GLfloat *) malloc(size);
	memcpy(this->frame.vertexArray, vertexArray, size);	
}

void RenderableFrame::setColorArray(GLfloat * colorArray, int size){
	if(this->frame.colorArray != NULL){
		Logger::log_debug("Freeing previous Color Array");
		free(this->frame.colorArray);
	}else
		this->frame.colorArray = (GLfloat *) malloc(size);
	memcpy(this->frame.colorArray, colorArray, size);	
}

Frame RenderableFrame::getFrame(){return this->frame;}

void RenderableFrame::draw(VideoWindow videoWindow){
	Logger::log_debug("Drawing frame!");
	this->checkArrays();

	glClear(GL_COLOR_BUFFER_BIT);

	int vertexArrayDataSize = videoWindow.getNumberOfVertices() * 2 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, videoWindow.getVertexBuffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexArrayDataSize, this->frame.vertexArray);
	glEnableVertexAttribArray(0);

	int colorArrayDataSize = videoWindow.getNumberOfVertices() * 3 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, videoWindow.getColorBuffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, colorArrayDataSize, this->frame.colorArray);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLE_STRIP, videoWindow.getNumberOfIndices(), GL_UNSIGNED_INT, nullptr);
	glfwSwapBuffers(videoWindow.getGLFWWindow());
	glfwPollEvents();
}
