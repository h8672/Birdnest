#ifndef modellisth
#define modellisth

#include "includes.h"
#include "model.h"

//Contains maps and vectors of models, textures & strings that are used to draw objects to screen
class ModelList {
	//Contains all Model classes
	std::vector<Model> models;

	//Currently used models
	//Maps Model pointers with integers
	std::map<GLint, Model*> modelmap;
	
public:
	//Get model pointers by their id from map class
	Model* Get(GLint ID) { return modelmap.find(ID)->second; }

	//Returns count of elements in map class
	GLuint GetSize() { return this->modelmap.size(); }

	void Bind(GLint ID) { modelmap.insert(std::make_pair(ID, &models.at(ID))); }
	void Unbind(GLint ID) { modelmap.erase(modelmap.find(ID)->first); }
	void Load(Model mod) { this->models.push_back(mod); }
	void LoadModel(GLchar* source) {
		Model model(source);
		this->models.push_back(model);
		std::cout << "Model added to list: " << this->models.size();
	}

};

#endif // !modellisth
