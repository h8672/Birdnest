#ifndef keycallsh
#define keycallsh

#include "includes.h"

enum Inputs {
	KEYBOARD,
	MOUSE,
	JOYSTICK
};
enum scroll {
	up, down //, left, right
};

//Namespace Keys
//Contains fuctions of keycalls
namespace keys {
	//Get keys
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	bool ifkey(GLuint key, bool toggled);
	//Use keys
	void use_keys(GLFWwindow * window, GLdouble dtime);
	bool ifkey(GLuint key, bool toggled);
	bool ifmouse(GLuint mousekey, bool toggled);
	GLdouble ifscroll(scroll scroll);


	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	glm::vec2 getRot(GLdouble dtime);
}

#endif // !keycallsh