#include "../include/VideoWindow.h"

VideoWindow::VideoWindow(Proportions proportions) :
	proportions(0, 0, 0)
{
	if(proportions.width == 0 || proportions.height == 0 || proportions.length == 0){
		Logger::log_warning("Null proportion created for VideoWindow: Buffers won't be initialized!");
	}else{
		Logger::log_debug("Creating VideoWindow!");
		this->proportions = proportions;
        this->initializeGLFW();
		this->initializeGLFWWindow();
		this->initializeGLEW();
		this->initializeBuffers();
		this->initializeBufferData();
		this->initializeShaderProgram();
		Logger::log_correct("Initialized VideoWindow!");
	}
}

void VideoWindow::initializeBuffers(){
	Logger::log_debug("Initializing Buffer data!");	
	glGenBuffers(1, &(this->vertexBuffer));
	glGenBuffers(1, &(this->colorBuffer));
	glGenBuffers(1, &(this->indexBuffer));
}

void VideoWindow::initializeBufferData(){
	Logger::log_debug("Initializing Buffer data!");
	this->initializeVertexData();
	this->initializeColorData();
	this->initializeIndexData();	
}

void VideoWindow::initializeVertexData(){
	Logger::log_debug("Initializing Vertex Buffer data!");
	int vertexDataSize = this->getNumberOfVertices() * 2 * sizeof(GLfloat);
	GLfloat * vertexArray = (GLfloat *)malloc(vertexDataSize);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), 0);
	free(vertexArray);
}

void VideoWindow::initializeColorData(){
	Logger::log_debug("Initializing Color Buffer data!");
	int colorDataSize = this->getNumberOfVertices() * 3 * sizeof(GLfloat);
	GLfloat * colorArray = (GLfloat *) malloc(colorDataSize);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorDataSize, colorArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	free(colorArray);
}

void VideoWindow::initializeIndexData(){
	Logger::log_debug("Initializing Index Buffer data!");
	int indexDataSize = this->getNumberOfIndices() * sizeof(GLuint);
	GLuint * indexArray = this->initializeIndexArray();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexArray, GL_STATIC_DRAW);
	free(indexArray);
}

GLuint * VideoWindow::initializeIndexArray(){
  Logger::log_debug("Initializing Indices!");
  int size = this->getNumberOfIndices();
  GLuint * templateArray = (GLuint *) malloc(size * sizeof(GLuint));
  int counter = 0;

  for(int y = 0; y < this->proportions.height - 1; y++){
    templateArray[counter] = y * this->proportions.width;
    counter++;
    for(int x = 0; x < this->proportions.width; x++){
      int columnOutset = y * this->proportions.width;
			int position = columnOutset + x;
      templateArray[counter] = y * this->proportions.width + x;
      templateArray[counter+1] = (y+1) * this->proportions.width + x;
      counter += 2;
    }
    templateArray[counter] = (y+1) * this->proportions.width + this->proportions.width -     1;
    counter++;
  }

  Logger::log_correct("Finished Initializing Indices");
  return templateArray;
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
	}else{
		glfwMakeContextCurrent(this->glWindow);
		Logger::log_correct("Initialized Window!");
	}
}

void VideoWindow::initializeShaderProgram(){
	Logger::log_debug("Initializing Shaders!");
	const char * vertexShaderPath = "shaders/vertexShader.glsl";
	const char * fragmentShaderPath = "shaders/fragmentShader.glsl";

	string vertexShader = ParseShader(vertexShaderPath);
	string fragmentShader = ParseShader(fragmentShaderPath);

	int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
}


GLuint VideoWindow::getVertexBuffer(){return this->vertexBuffer;}
GLuint VideoWindow::getColorBuffer(){return this->colorBuffer;}
GLuint VideoWindow::getIndexBuffer(){return this->indexBuffer;}

int VideoWindow::getNumberOfVertices(){
	return this->proportions.width * this->proportions.height;
}

int VideoWindow::getNumberOfIndices(){
	return (this->proportions.height - 1) * ((2 * this->proportions.width) + 2);
}

Proportions VideoWindow::getProportions(){return this->proportions;}
GLFWwindow * VideoWindow::getGLFWWindow(){return this->glWindow;}

