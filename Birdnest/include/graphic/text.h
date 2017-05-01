#ifndef texth
#define texth

#include "includes.h"
#include "shader.h"
#include "camera.h"

struct Character {
	//Visual basic object that is drawn!
	GLuint VBO;

	//Glyph attributes
	GLuint TextureID;		// ID handle of the glyph texture
	glm::vec2 Size;			// Size of glyph
	//glm::ivec2 Bearing;		// Offset from baseline to left/top of glyph
	GLfloat Advance;		// Offset to advance to next glyph
};

class Text {
	GLuint VAO, EBO;
	//Character map
	std::map<GLchar, Character> characters;
	Character chars[82];
	//Contain position vec3, color vec3, texture coords vec2

	//Text attributes
	glm::vec3 Position, Rotation, *Target;
	//Is it facing camera?
	bool FaceCamera;
	//Colors
	glm::vec4 textcolor, BGcolor;
	//Text size
	GLfloat scale;

	//Contain elements
	GLuint indices[6] = {1, 2, 3, 0, 1, 3};
public:
	Text(GLchar* font);	//Reads font and adds characters to list

	//Sets position, rotation and facing to camera settings...
	void SetVectors(glm::vec3 Position, glm::vec3 Rotation, bool FaceCamera);
	void SetVectors(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 *Target, bool FaceCamera);
	
	//Sets visual settings
	void SetVisuals(glm::vec4 textcolor, glm::vec4 BGcolor, GLfloat scale);

	//Draw line and rows, default column 24 letters
	void Draw(Shader * shader, std::string text);
	void Draw(Shader * shader, std::string text, GLuint rows);
	void Draw(Shader * shader, std::string text, GLuint rows, GLuint columns);

};


#endif // !texth