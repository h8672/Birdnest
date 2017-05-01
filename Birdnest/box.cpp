#include "box.h"

Box::Box()
{
	this->Position = glm::vec3(0);
	this->Rotation = glm::vec3(0);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	GLfloat code = 1.0f;//Currently not using it at all in shaders...
	GLfloat vertices[4][8] = {
		// Position					// Colors			// Texture Coords
		code,	 code, 0.0f,		code, code, code,   1.0f, 0.0f, // Top Right
		code,	-code, 0.0f,		code, code, code,   1.0f, 1.0f, // Bottom Right
		-code,	-code, 0.0f,		code, code, code,   0.0f, 1.0f, // Bottom Left
		-code,	 code, 0.0f,		code, code, code,   0.0f, 0.0f  // Top Left 
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

void Box::SetSize(GLfloat width, GLfloat height) {
	GLfloat fix = 1.0f;
	this->height = height * fix;
	this->width = width * fix;
}
void Box::SetTexture(GLuint texture) { this->texture = texture; }
void Box::SetColor(glm::vec4 Color) { this->Color = Color; }
void Box::SetPosition(glm::vec3 Position) { this->Position = Position; }
void Box::SetRotation(glm::vec3 Rotation) { this->Rotation = Rotation; }
GLuint Box::GetTexture() { return this->texture; }

glm::vec3 Box::GetPosition() { return this->Position; }

void Box::Draw(Shader * shader)
{
	shader->Use();
	glActiveTexture(GL_TEXTURE0);

	// Bind Texture
	glBindTexture(GL_TEXTURE_2D, this->texture);

	//glActiveTexture(GL_TEXTURE0);

	glm::mat4 model;
	glm::vec3 CurrentPosition = Position - glm::vec3(width/2 * 0.05f, 0, 0);
	model = glm::translate(model, CurrentPosition); //Kääntää yksittäin samaan suuntaa

	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(0, 0, 1));	//Pitch
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));	//Yaw
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(1, 0, 0));	//Roll
	
	model = glm::scale(model, glm::vec3(width, height, 0));

	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
