#include "keycalls.h"

//keycalls
bool keycalls[1024];
bool keyrepeat[1024];
bool mousecalls[24];
bool mouserepeat[24];

//Angles
GLdouble pitch = 0, yaw = 0;
//Delta angles
GLdouble dpitch = 0, dyaw = 0;

//Mouse position
GLdouble x = 0, y = 0;
GLdouble dx = 0, dy = 0;
//Scroll position
GLdouble sx = 0, sy = 0;
GLdouble dsx = 0, dsy = 0;

//Camera rotation sensitivity in screen. Debug values commented
GLdouble pitchsense = 5;//1;
GLdouble yawsense = 5;//1;
GLdouble rollsense = 5;//1;

GLint width, height;

//Repeatable button
bool presskey(GLuint key, Inputs input) {
	switch (input)
	{
	case KEYBOARD:
		if (keycalls[key] || keyrepeat[key]) return true;
		break;
	case MOUSE:
		if (mousecalls[key] || mouserepeat[key]) return true;
		
		break;
	case JOYSTICK:
		break;
	default:
		break;
	}
	return false;
}

//Non-repeatable button
bool togglekey(GLuint key, Inputs input) {
	switch (input)
	{
	case KEYBOARD:
		if (keycalls[key]) {
			keycalls[key] = false;
			return true;
		}
		break;
	case MOUSE:
		if (mousecalls[key]) {
			mousecalls[key] = false;
			return true;
		}
		break;
	case JOYSTICK:
		break;
	default:
		break;
	}
	return false;
}

namespace keys{
	//If keyboard keys are used...
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		if (action == GLFW_PRESS) {
			if (!keyrepeat[key]) keycalls[key] = true;
			std::cout << "Key pressed\n";
		}
		else if (action == GLFW_REPEAT) {
			if (keycalls[key]) {
				keyrepeat[key] = true;
				keycalls[key] = false;
			}
		}
		else if (action == GLFW_RELEASE) {
			//Both to false so nothing goes wrong. Without key might stay true
			keycalls[key] = false;
			keyrepeat[key] = false;
			std::cout << "Key released\n";
		}
	}
	//If mouse buttons are used...
	void mouse_button_callback(GLFWwindow* window, int key, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			if (!mouserepeat[key]) mousecalls[key] = true;
			std::cout << "Mouse pressed\n";
		}
		else if (action == GLFW_REPEAT) {
			if (mousecalls[key]) {
				mouserepeat[key] = true;
				mousecalls[key] = false;
			}
		}
		else if (action == GLFW_RELEASE) {
			//Both to false so nothing goes wrong. Without key might stay true
			mousecalls[key] = false;
			mouserepeat[key] = false;
			std::cout << "Mouse released\n";
		}
	}

	//If key used
	//Return delta time, or 0 as key not used
	bool ifkey(GLuint key, bool toggled) {
		if (toggled) {
			if(togglekey(key, KEYBOARD))
				return true;
		}
		if (!toggled) {
			if(presskey(key, KEYBOARD))
				return true;
		}
		return 0;
	}
	//If mouse used
	//Return delta time, or 0 as mouse not used
	bool ifmouse(GLuint mousekey, bool toggled) {
		if (toggled) {
			if (togglekey(mousekey, MOUSE))
				return true;
		}
		if (!toggled) {
			if (presskey(mousekey, MOUSE))
				return true;
		}
		return 0;
	}
	//If scroll used
	//Return delta time, or 0 as scroll not used
	GLdouble ifscroll(scroll scroll) {
		switch (scroll)
		{
		case up:
			if (dsy > 0) return dsy;
			break;
		case down:
			if (dsy < 0) {
				return dsy;
			}
			break;
		default:
			break;
		}
		return 0;
	}

	//Returns cursor position
	glm::vec2 getCursorPos() { return glm::vec2(x, y); }
	//Returns xy xz yz rotations
	//Returns xy xz yz delta rotations
	glm::vec2 getDeltaRotations() { return glm::vec2((GLfloat)dpitch, (GLfloat)dyaw); }

	void use_keys(GLFWwindow * window, GLdouble dtime) {

		//Get delta scroll values
		dsx = sx;
		dsy = sy;
		sx = 0;
		sy = 0;

		//Get Cursor data
		glfwGetCursorPos(window, &x, &y);
		glfwGetWindowSize(window, &width, &height);

		//clear cursor position for deltas
		glfwSetCursorPos(window, width/2, height/2);

		//set deltas
		//Set angle 0 to middle, then adjust angle to screen with maximum degree
		//Adding dtime and multiplying value by 1000 it works quite well,
		//not too slow or fast.
		yaw = (x - width / 2) / width * -360 * 1000 * dtime;
		pitch = (y - height / 2) / height * -180 * 1000 * dtime;

		if(yaw != dyaw)
			dyaw = yaw;
		if (pitch != dpitch)
			dpitch = pitch;

		x = 0;
		y = 0;


	}
	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		x = xpos;
		y = ypos;
	}
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		sx = xoffset;
		sy = yoffset;
	}
	glm::vec2 getRot(GLdouble dtime) {
		return glm::vec2((GLfloat)dtime * 3) * glm::vec2((GLfloat)dpitch * pitchsense, (GLfloat)dyaw * yawsense);
	}
}
//The end...