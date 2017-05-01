#include "light.h"

Light::Light(glm::vec3 Position, glm::vec3 Color)
{
	this->Position = Position;
	this->Color = Color;
}

Light::Light()
{
	this->Position = glm::vec3(0);
	this->Color = glm::vec3(0);
}

//Gets
glm::vec3 Light::GetPosition() { return this->Position; }
glm::vec3 Light::GetColor() { return this->Color; }

//Sets
void Light::SetPosition(glm::vec3 Position) { this->Position = Position; }
void Light::SetColor(glm::vec3 Color) { this->Color = Color; }
