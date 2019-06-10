#include "../include/Frame.h"

Frame::Frame(){
	this->vertexArray = NULL;
	this->colorArray = NULL;
	this->frameDeformed = false;
}

glm::vec2 Frame::getPosition(int x, int y, int width){
	int index = (y * width + x) * 2;
	return glm::vec2(this->vertexArray[index], this->vertexArray[index+1]);
}

glm::vec3 Frame::getColor(int x, int y, int width){
	int index = (y * width + x) * 3;
	return glm::vec3(this->colorArray[index], this->colorArray[index+1], this->colorArray[index+2]);
}

int Frame::isFrameDeformed(){return this->frameDeformed;}
