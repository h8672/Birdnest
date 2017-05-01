#ifndef playerh
#define playerh

#include "includes.h"
#include "graphic\camera.h"

enum Cheats {
	fly = 1,
	undead,
	immortal
};

class Player {
	Camera * camera;

	GLfloat dtime;
	GLfloat speed;
	GLfloat gravity = 9.81f;
	GLfloat mousesensitivity = 1;

	//Cheats
	bool cheats[20];
	bool cheat(Cheats chew) { return this->cheats[chew]; }
	void cheat(Cheats chew, bool enable) { this->cheats[chew] = enable; }

public:

	void SetDeltaTime(GLdouble time) { this->dtime = (GLfloat)time; }

	Player(Camera * camera) {
		this->camera = camera;
		this->cheats[0] = false;
	}

	void Move(GLFWwindow * window) {
		//1st is key, 2nd is it toggle key
		if(keys::ifkey(GLFW_KEY_ESCAPE, true)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		//Special keys

		//Open menu
		if (keys::ifkey(GLFW_KEY_ENTER, true)) {
			;
		}


		//Cheat keys

		//Fly
		if (keys::ifkey(GLFW_KEY_F1, true)) {
			if (this->cheat(fly)) {
				this->cheat(fly, false);
				std::cout << "Fly disabled\n";
			}
			else {
				this->cheat(fly, true);
				if (fly) std::cout << "Fly enabled\n";
			}
		}

		//Movement keys
		this->speed = 5 * this->dtime;

		//Default movement forward\
		this->speed += glm::vec3(\
			cos(glm::radians(camera->GetRotations().y)) * cos(glm::radians(camera->GetRotations().x)),		//forward\
			-sin(glm::radians(camera->GetRotations().x)),\
			sin(glm::radians(camera->GetRotations().y)) * cos(glm::radians(camera->GetRotations().x)));


		//Forward
		if (keys::ifkey(GLFW_KEY_W, false))
			this->camera->MoveCamera(FORWARD, speed);

		//Backward
		if (keys::ifkey(GLFW_KEY_S, false))
			this->camera->MoveCamera(BACKWARD, speed);

		//Left
		if (keys::ifkey(GLFW_KEY_A, false))
			this->camera->MoveCamera(LEFT, speed);

		//Right
		if (keys::ifkey(GLFW_KEY_D, false))
			this->camera->MoveCamera(RIGHT, speed);

		//Jump
		if (keys::ifkey(GLFW_KEY_SPACE, false)) {
			this->camera->MoveCamera(UP, speed);
		}
		//To knees!
		if (keys::ifkey(GLFW_KEY_LEFT_CONTROL, false)) {
			this->camera->MoveCamera(DOWN, speed);
		}
		//Strafe / Roll left
		if (keys::ifkey(GLFW_KEY_Q, false))
			//this->camera->MoveCamera(YAW, -90.0f * this->dtime);
			this->camera->MoveCamera(ROLL, -90.0f * this->dtime);

		//Strafe / Roll right
		if (keys::ifkey(GLFW_KEY_E, false))
			//this->camera->MoveCamera(YAW, 90.0f * this->dtime);
			this->camera->MoveCamera(ROLL, 90.0f * this->dtime);


		//Mouse buttons
		//Shoot aka zoom in or curve in
		if (keys::ifmouse(GLFW_MOUSE_BUTTON_1, false)) {
			;
		}
		//Aim aka zoom out or curve out
		if (keys::ifmouse(GLFW_MOUSE_BUTTON_2, false)) {
			;
		}
		//Throw grenade! wot?
		if (keys::ifmouse(GLFW_MOUSE_BUTTON_3, false)) {
			;
		}
		//Zoom out
		if (keys::ifmouse(GLFW_MOUSE_BUTTON_4, false)) {
			;
		}
		//Zoom in
		if (keys::ifmouse(GLFW_MOUSE_BUTTON_5, false)) {
			;
		}




		if (keys::ifscroll(up)) {
			this->camera->MoveCamera(ZOOM, 120.0f * this->dtime);
		}
		if (keys::ifscroll(down)) {
			this->camera->MoveCamera(ZOOM, -120.0f * this->dtime);
		}


		//Who wouldn't fall? ME!\
		if (!this->cheat(fly)) {\
			this->camera->MoveCamera(FALL, gravity);\
		}
	}
};

#endif // !playerh