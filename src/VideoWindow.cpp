#include "../include/VideoWindow.h"

VideoWindow::VideoWindow(Proportions proportions){
	this->proportions = proportions;
	this->initializeBuffers();
}

void VideoWindow::initializeBuffers(){
	glGenBuffers(1, &(this->vertexBuffer));
	glGenBuffers(1, &(this->colorBuffer));
	glGenBuffers(1, &(this->indexBuffer));
}

void VideoWindow::initializeGLFW(){
	Logger::log_debug("Initializing GLFW!");
	if(!glfwInit()){
		Logger::log_fatal("Couldn't initialize GLFW!");
		exit(1);
	}else
		Logger::log_correct("Initialized GLFW");
}


void VideoWindow::initializeGLEW(){
	Logger::log_debug("Initializing GLEW!");
	if(glewInit() != GLEW_OK){
		Logger::log_fatal("Couldn't initialize GLEW!");
		exit(1);
	}else
		Logger::log_correct("Initialized GLEW");
}

void VideoWindow::initializeGLFWWindow(){
	Logger::log_debug("Initializing Window!");
	this->glWindow = glfwCreateWindow(this->proportions.width, this->proportions.height,
																		"KELVINLETS VIDEO", NULL, NULL);
	glfwSetWindowSizeLimits(this->glWindow, this->proportions.width, this->proportions.height, 
													this->proportions.width, this->proportions.height);
	if(!this->glWindow){
		Logger::log_fatal("Couldn't initialize Window!");
		exit(1);
	}else
		Logger::log_correct("Initialized Window!");
}
