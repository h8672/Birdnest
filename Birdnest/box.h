#ifndef boxh
#define boxh

#include "includes.h"
#include "include\graphic\shader.h"

//2D box with texture
class Box {
	GLfloat height, width;
	GLuint texture;
	glm::vec3 Position, Rotation;
	glm::vec4 Color;

	GLuint VAO, VBO, EBO;
	GLuint indices[6] = { 1, 2, 3, 0, 1, 3 };
public:
	Box();

	void SetSize(GLfloat height, GLfloat width);
	void SetTexture(GLuint texture);
	void SetColor(glm::vec4 Color);
	void SetPosition(glm::vec3 Position);
	void SetRotation(glm::vec3 Rotation);

	GLuint GetTexture();
	glm::vec3 GetPosition();

	void Draw(Shader * shader);
};

#endif // ! boxh