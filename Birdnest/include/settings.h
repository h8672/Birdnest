#ifndef settingsh
#define settingsh

#include "includes.h"

namespace Settings {

	//Loads default graphic settings
	void defaults();
	//Reads old settings
	void getData();
	//Saves current settings
	void saveData();

	//Graphic Functions

	GLuint getWindowWidth();
	GLuint getWindowHeight();
	std::string getWindowTitle();

	void setWindowWidth(GLuint width);
	void setWindowHeight(GLuint height);
	void setWindowTitle(std::string title);

};

#endif // !settingsh