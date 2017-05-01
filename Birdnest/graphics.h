#ifndef graphicsh
#define graphicsh

#include "includes.h"
#include "include\graphic\shader.h"
#include "include\graphic\camera.h"
#include "include\graphic\model.h"
#include "include\graphic\text.h"
#include "include\graphic\modellist.h"
#include "materiallist.h"
#include "light.h"
#include "box.h"


class GraphicEngine {
	// Window attributes
	GLFWwindow * window;
	GLint windowwidth = 800, windowheight = 600;

	// Shader attributes
	Shader * shader3D;
	//Shader * shader2D;
	//Shader * shaderLight;

	GLint success;
	GLchar infoLog[512];

	//Model attributes
	ModelList * models;
	MaterialList * materials;
	//StringList * strings;

	std::vector<Strings> strings;
	std::vector<GLuint> textures;
	std::vector<Box> boxes;

	Text * textfont;

	//Camera
	Camera * camera;

	Light * moon;


	GLuint texture;

	// Private prototypes
	//void createWindow(GLchar * name);

public:
	GLFWwindow * getWindow();
	void ShowWindow();

	void init();
	void terminate();

	//Camera functions
	void setCamera(Camera * camera);
	Camera * getCamera();
	void freeCamera();

	//Graphic class can only bind modellist
	void BindModelList(ModelList * list);
	void BindMaterialList(MaterialList * list);

	GLuint bindString(Strings string);
	void addTexture(GLuint texture);

	void BindBox(Box box);

	void update(GLdouble dtime);

	//void updateView();
};

#endif // !graphicsh