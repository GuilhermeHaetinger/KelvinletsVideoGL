#include "../include/VideoGL.h"

VideoGL::VideoGL(const char * videoPath) :
	videoWindow(Proportions(0, 0, 0))
{
	Logger::log_debug("Initializing VideoGL from VideoPath constructor!");

	cv::VideoCapture video(videoPath);

	if(!video.isOpened()){
		Logger::log_fatal("Video could not be opened!");
		exit(1);
	}

	int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
	int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
	int length = video.get(cv::CAP_PROP_FRAME_COUNT);

	Proportions proportions = Proportions(width, height, length);
  this->videoWindow = VideoWindow(proportions);
	this->renderableFrames = (RenderableFrame *) malloc(this->getLength() * sizeof(RenderableFrame));

	this->initializeFrames();
	this->initializeVertices();
	this->initializeColors(video);

	Logger::log_correct("Initialized VideoGL from VideoPath!");
}

void VideoGL::resetFrames(Frame * frames){
	Logger::log_debug("Resetting VideoGL from Frame array constructor!");
	for(int index = 0; index < this->getLength(); index++)
		this->renderableFrames[index] = RenderableFrame(frames[index]);
	Logger::log_correct("Resetting VideoGL from Frame array!");
}

int VideoGL::getWidth(){ return this->videoWindow.getProportions().width;}
int VideoGL::getHeight(){ return this->videoWindow.getProportions().height;}
int VideoGL::getLength(){ return this->videoWindow.getProportions().length;}

GLfloat VideoGL::normalizeWidth(int index){
	return 2 * ((GLfloat) index / (this->getWidth() - 1)) - 1;
}

GLfloat VideoGL::normalizeHeight(int index){
	return 2 * ((GLfloat)(this->getHeight() - 1 - index)/(this->getHeight() - 1)) - 1;
}

void VideoGL::initializeFrames(){
	Logger::log_debug("Initializing Frames");
	for(int frame = 0; frame < this->getLength(); frame++){
		this->renderableFrames[frame] = RenderableFrame();
	}
	Logger::log_correct("Finished Initializing Frames");
}

void VideoGL::initializeVertices(){
	int size = this->videoWindow.getNumberOfVertices() * 2;
	GLfloat * templateArray = (GLfloat *) malloc(size * sizeof(GLfloat));
	int index = 0;
	for(int y = 0; y < this->getHeight(); y++)
		for(int x = 0; x < this->getWidth(); x++){
			templateArray[index] = (GLfloat) normalizeWidth(x);
			templateArray[index + 1] = (GLfloat) normalizeHeight(y);
			index += 2;
		}

	for(int frame = 0; frame < this->getLength(); frame++)
		renderableFrames[frame].setVertexArray(templateArray, size * sizeof(GLfloat));

	Logger::log_correct("Finished Initializing Vertices!");
}

void VideoGL::initializeColors(cv::VideoCapture video){
	Logger::log_debug("Initializing Color Array!");
	int size = this->videoWindow.getNumberOfVertices() * 3;
	
	for(int frame = 0; frame < this->getLength(); frame++){
		cv::Mat mat;
	  uint8_t * frameColors = (uint8_t *) malloc(size * sizeof(uint8_t));
	  GLfloat * frameColorArray = (GLfloat *) malloc(size * sizeof(GLfloat));
		video >> mat;
		memcpy(frameColors, mat.ptr(0), mat.cols*mat.rows * sizeof(uint8_t) * 3);
	
		for(int index = 0; index < size; index += 3){
			frameColorArray[index] = ((GLfloat) frameColors[index + 2])/256;
			frameColorArray[index + 1] = ((GLfloat) frameColors[index + 1])/256;
			frameColorArray[index + 2] = ((GLfloat) frameColors[index])/256;
		}
		this->renderableFrames[frame].setColorArray(frameColorArray, size * sizeof(GLfloat));
	}
	Logger::log_correct("Finished Initializing Colors!");
}

Proportions VideoGL::getProportions(){return this->videoWindow.getProportions();}
void VideoGL::getFrames(Frame * dest){
	for(int frame = 0; frame < this->getLength(); frame++){
		dest[frame] = this->renderableFrames[frame].getFrame();
	}
}

void VideoGL::show(){
	for(int frame = 0; frame < this->getLength(); frame++){
		renderableFrames[frame].draw(this->videoWindow);
		std::cout << frame << "/" << this->getLength()-1 << std::endl;
		getchar();
	}
}
