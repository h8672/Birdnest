#include "camera.h"

void Camera::CoutPosition() {
	std::cout << "Camera in: "
		<< this->Position.x << ", "
		<< this->Position.y << ", "
		<< this->Position.z << ", " << std::endl;
}


Camera::Camera() {
	this->Position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->Target = glm::vec3(1.0f, 0.0f, 0.0f);
	this->Direction = glm::vec3(1.0f, 0.0f, 0.0f);
	this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;
	this->Zoom = 1.00f;
	this->fov = 45.0f;
	this->range = 100.0f;
	this->lockcamera = false;
	this->locktarget = false;
	//cout position
	this->CoutPosition();
}

Camera::Camera(glm::vec3 Position) {
	this->Position = Position;
	this->Target = glm::vec3(1.0f, 0.0f, 0.0f);
	this->Direction = glm::vec3(1.0f, 0.0f, 0.0f);
	this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;
	this->Zoom = 1.00f;
	this->fov = 45.0f;
	this->range = 100.0f;
	this->lockcamera = false;
	this->locktarget = false;
	//cout position
	this->CoutPosition();
}

Camera::Camera(glm::vec3 Position, GLfloat pitch, GLfloat yaw) {
	this->Position = Position;
	this->Target = glm::vec3(1.0f, 0.0f, 0.0f);
	this->Direction = glm::vec3(1.0f, 0.0f, 0.0f);
	this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = 0.0f;
	this->Zoom = 1.00f;
	this->fov = 45.0f;
	this->range = 100.0f;
	this->lockcamera = false;
	this->locktarget = false;
	//cout position
	this->CoutPosition();
}

void Camera::updateCameraVectors() {

	if (this->pitch > 89)	this->pitch = 89;
	if (this->pitch < -89)	this->pitch = -89;

	if (this->yaw > 180) this->yaw -= 360;
	if (this->yaw <= -180) this->yaw += 360;

	if (this->roll > 180) this->roll -= 360;
	if (this->roll <= -180) this->roll += 360;

	glm::vec3 temp;

	//Target vector
	if (this->locktarget) {//Got target
		;//No need to transform it
	}
	else {//no target
			this->Target = glm::vec3((1 / this->Zoom) * range) * glm::vec3(															//Rotation	start	end
				sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),// * sin(glm::radians(this->roll)),			//pitch		x		y
				sin(glm::radians(this->pitch)),// * cos(glm::radians(this->roll)),											//yaw		z		x
				cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))// * sin(glm::radians(this->roll))			//roll		z		y
				);
		//this->Target += this->Position;
	}
	temp = this->Target;
	//std::cout << "temp target: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;

	//Direction of negative target vector and so vector points from target to camera
	this->Direction = glm::normalize(glm::normalize(this->Position) - this->Target);
	temp = this->Direction;
	//std::cout << "temp direction: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;

	//Right, so yaw is yaw + 90 degrees
	//Needs roll here, so angle will be right in up aswell
	this->Right = glm::normalize(glm::cross(this->WorldUp, this->Direction));
	temp = this->Right;
	//std::cout << "temp right: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;

	//Up, so pitch is pitch + 90 degrees
	this->Up = glm::cross(this->Direction, this->Right);
	temp = this->Up;
	//std::cout << "temp up: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;

	if (this->locktarget) {//Got target
		this->Front = glm::normalize(this->Target);//Fit target to front vector
	}
	else {//no target
		this->Front = this->Target;
	}
	//Practically same as target...
	temp = this->Front;
	//std::cout << "temp front: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;

}

glm::mat4 Camera::GetViewMatrix() {
	this->updateCameraVectors();
	//glm::mat4 projection = glm::perspective(glm::radians(this->fov / this->Zoom), this->WindowScale, 0.1f, this->range * this->Zoom);
	glm::mat4 Look = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
	//Rotates world around camera, not camera\
	Look = glm::rotate(Look, glm::radians(this->roll), glm::vec3(1, 0, 0));
	return Look;
	
	//Failed roll attempt, world starts to spin in origo instead of camera spinning in the world
	//return glm::rotate(glm::lookAt(this->Position, this->Position + this->Front, this->Up), this->roll, this->Right);
}

glm::vec3 Camera::GetPosition() { return glm::normalize(this->Position); }
glm::vec3 Camera::GetRotations() { return glm::vec3(this->pitch, this->yaw, this->roll); }
glm::vec3 Camera::GetTarget() { return this->Target; }
GLfloat Camera::GetFov() { return this->fov; }
GLfloat Camera::GetZoom() { return this->Zoom; }
GLfloat Camera::GetWindowScale() { return this->WindowScale; }
GLfloat Camera::GetRange() { return this->range; }

void Camera::SetZoom(GLfloat Zoom) { this->Zoom = Zoom; }
void Camera::SetWindowScale(GLfloat width, GLfloat height) { this->WindowScale = width / height; }

void Camera::CameraPos(glm::vec3 Position, bool Lock = false) {
	this->lockcamera = Lock;
	this->Position = Position;
}

void Camera::CameraTarget(glm::vec3 Target, bool Lock = false) {
	this->Target = Target;
	this->locktarget = Lock;
}

void Camera::CameraTurn(GLfloat pitch, GLfloat yaw) {
	this->pitch = pitch;
	this->yaw = yaw;
}

void Camera::CameraTurn(GLfloat pitch, GLfloat yaw, GLfloat roll) {
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

//Move camera
//Adds length to position after checking angles
void Camera::MoveCamera(Camera_Movement move, GLfloat Add) {
	glm::vec3 Speed;

	switch (move) {
	case FORWARD:
		Speed += glm::vec3(
			sin(glm::radians(this->yaw)),
			0,
			cos(glm::radians(this->yaw)));
		this->Position += glm::vec3(Add) * Speed;
		break;
	case BACKWARD:
		Speed -= glm::vec3(
			sin(glm::radians(this->yaw)),
			0,
			cos(glm::radians(this->yaw)));
		this->Position += glm::vec3(Add) * Speed;
		break;
	case RIGHT:
		Speed -= glm::vec3(
			sin(glm::radians(this->yaw + 90)),
			0,
			cos(glm::radians(this->yaw + 90)));
		this->Position += glm::vec3(Add) * Speed;
		break;
	case LEFT:
		Speed += glm::vec3(
			sin(glm::radians(this->yaw + 90)),
			0,
			cos(glm::radians(this->yaw + 90)));
		this->Position += glm::vec3(Add) * Speed;
		break;
	case UP:
		Speed += glm::vec3(
			0,
			sin(2*3.14 / 360 * 90),
			0);
		this->Position += glm::vec3(Add) * Speed;
		break;
	case DOWN:
		Speed -= glm::vec3(
			0,
			sin(2 * 3.14 / 360 * 90),
			0);
		this->Position += glm::vec3(Add) * Speed;
		break;
	case ROLL:
		this->roll += Add;
		std::cout << "Roll: " << this->roll << std::endl;
		break;
	case YAW:
		this->yaw += Add;
		std::cout << "Yaw: " << this->yaw << std::endl;
		break;
	case PITCH:
		this->pitch += Add;
		std::cout << "Pitch: " << this->pitch << std::endl;
		break;
	case FALL:
		break;
	case ZOOM:
		this->Zoom += Add;
		if (this->Zoom > 8) this->Zoom = 8;
		if (this->Zoom < 1) this->Zoom = 1;
		std::cout << this->Zoom << std::endl;
		break;
	default:
		std::cout << "Not Moving!\n";
		break;
	}
	//Ei lisättäviä arvoja tänne! omg! ;D
}

//Turns are divided with zoom so it will be in good sensitivity at all zoom values

//Turn up-down
void Camera::TurnCamera(GLfloat pitch) {
	//Turn
	this->pitch += pitch / this->Zoom;
}
//Turn up-down, left-right
void Camera::TurnCamera(glm::vec2 Turn) {
	//Turn
	this->pitch += Turn.x / this->Zoom;
	this->yaw += Turn.y / this->Zoom;
}
void Camera::TurnCamera(GLfloat pitch, GLfloat yaw) {
	//Turn
	this->pitch += pitch / this->Zoom;
	this->yaw += yaw / this->Zoom;
}
//Turn up-down, left-right, roll left-right
void Camera::TurnCamera(glm::vec3 Turn) {
	//Turn
	this->pitch += Turn.x / this->Zoom;
	this->yaw += Turn.y / this->Zoom;
	this->roll += Turn.z;
}
void Camera::TurnCamera(GLfloat pitch, GLfloat yaw, GLfloat roll) {
	//Turn
	this->pitch += pitch / this->Zoom;
	this->yaw += yaw / this->Zoom;
	this->roll += roll;
}

