#ifndef gameengineh
#define gameengineh

#include "includes.h"
#include "materiallist.h"
#include "include\graphic\modellist.h"


class GameEngine {
	
	//Model list
	ModelList * models;
	MaterialList * materials;


	//Physical attributes
	GLfloat gravity = 9.81f;


	//Vectors of objects
	//std::vector<GameObject> objects;
	//std::vector<Menu> menus;

	//Maps of objects
	//std::map<GLint, GameObject*> mapobjects;
	//std::map<GLint, Menu> mapmenus;

	void loadModels();
	void bindModels();

	void loadMaterials();
	void bindMaterials();

public:
	void init();


	void BindModelList(ModelList * list);
	void BindMaterialList(MaterialList * list);

};

#endif // !gameengineh