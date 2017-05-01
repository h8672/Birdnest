#ifndef includesh
#define includesh

//OpenGL core includes
#include <GL/glew.h>
#include <GLFW\glfw3.h>
//Basic...
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
//SOIL for png loading
#include <SOIL.h>
//GLM for OpenGL vector calculating
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//ASSIMP for model loading
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Own includes
#include "lasku.h" //Nothing anymore...
#include "settings.h"
#include "keycalls.h"

//Lists

#define ruotsino 'å'
#define aakkonen 'ä'
#define ookkonen 'ö'
#define isoruotsino 'Å'
#define isoaakkonen 'Ä'
#define isoookkonen 'Ö'

//Vertex points
struct Vertex {
	glm::vec3 Position;		//3D position vector
	glm::vec3 Normal;		//facing
	glm::vec2 TexCoords;	//texture position
};

//Texture pointer
struct Texture {
	GLuint id;				//texture id
	std::string type;		//type name
	aiString path;
};

struct Strings {
	glm::vec3 Position;		//Position vector
	glm::vec3 Rotation;		//Sets rotation
	std::string String;		//String of text
	GLfloat Scale;			//Size of text
	glm::vec4 Color;		//Color of text
	glm::vec4 BGColor;		//Color of background
	//bool ShowBG;			//Show background?
	bool ToCamera;			//Does it turn to camera?
};


#endif // !includesh
