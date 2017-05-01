#ifndef lighth
#define lighth

#include "includes.h"

class Light {
	glm::vec3 Position;
	glm::vec3 Color;

public:
	Light(glm::vec3 Position, glm::vec3 Color);
	Light();

	//Gets
	glm::vec3 GetPosition();
	glm::vec3 GetColor();

	//Sets
	void SetPosition(glm::vec3 Position);
	void SetColor(glm::vec3 Color);

};

#endif // !lighth
