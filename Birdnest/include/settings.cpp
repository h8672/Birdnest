#include "settings.h"


//Graphic settings
std::string windowtitle;

GLint windowwidth;
GLint windowheight;


namespace Settings {

	void defaults() {
		windowtitle = "Birdnest";
		windowwidth = 800;
		windowheight = 600;
	}
	//Gets old settings
	void getData() {
		defaults();
	}
	//Saves current settings
	void saveData() {
		;
	}

	GLuint getWindowWidth() { return windowwidth; }
	GLuint getWindowHeight() { return windowheight; }
	std::string getWindowTitle() { return windowtitle; }

	void setWindowWidth(GLuint width) { windowwidth = width; }
	void setWindowHeight(GLuint height) { windowheight = height; }
	void setWindowTitle(std::string title) { windowtitle = title; }

}
