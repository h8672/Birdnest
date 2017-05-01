#ifndef camerah
#define camerah

#include "includes.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FALL,
	ZOOM,
	ROLL,
	YAW,
	PITCH
};
/* Not used
// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;
*/

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
	// Camera Attributes
	glm::vec3 Position;		//Cameras position, maybe locked forever
	glm::vec3 Target;		//Target position
	glm::vec3 Direction;	//of camera from target, not direction of target from camera
	glm::vec3 Front;		//umm...target?
	glm::vec3 Up;			//up axis
	glm::vec3 Right;		//right axis
	glm::vec3 WorldUp;		//set in constructor
	// Eular Angles
	GLfloat pitch;	//up-down in xy-axis
	GLfloat yaw;	//turn left-right in xz-axis
	GLfloat roll;	//roll left right in zy-axis
	// Camera options
	//GLfloat MovementSpeed;		//umm---
	GLfloat MouseSensitivity;	//umm---
	GLfloat WindowScale;		//Window size
	GLfloat Zoom;				//Zoom percentage
	GLfloat maxzoom;			//Sets max zoom percentage
	GLfloat fov;				//Field of vision
	GLfloat range;				//Vision range
	bool lockcamera;			//Is camera locked into something?
	bool locktarget;			//is cameras target locked into something?

	// Deltatime
	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame


	void CoutPosition();

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();

public:

	Camera();
	Camera(glm::vec3 Position);
	Camera(glm::vec3 Position, GLfloat pitch, GLfloat yaw);

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	//Gets
	glm::vec3 GetPosition();
	glm::vec3 GetRotations();
	glm::vec3 GetTarget();
	GLfloat GetFov();
	GLfloat GetZoom();
	GLfloat GetWindowScale();
	GLfloat GetRange();

	//Sets
	void SetZoom(GLfloat Zoom);
	void SetWindowScale(GLfloat width, GLfloat height);

	//Sets camera position and cameralock
	void CameraPos(glm::vec3 Position, bool Lock);
	//Sets camera target and targetlock
	void CameraTarget(glm::vec3 Target, bool Lock);
	//Sets camera turn xy xz rotations
	void CameraTurn(GLfloat pitch, GLfloat yaw);
	//Sets camera turn xy xz yz rotations
	void CameraTurn(GLfloat pitch, GLfloat yaw, GLfloat roll);
	//Adds movement to position
	void MoveCamera(Camera_Movement move, GLfloat Add);
	//Turns camera xy rotation
	void TurnCamera(GLfloat pitch);
	//Turns camera xy xz rotations
	void Camera::TurnCamera(glm::vec2 Turn);
	void TurnCamera(GLfloat pitch, GLfloat yaw);
	//Turns camera xy xz yz rotations
	void Camera::TurnCamera(glm::vec3 Turn);
	void TurnCamera(GLfloat pitch, GLfloat yaw, GLfloat roll);

};

#endif // !camerah