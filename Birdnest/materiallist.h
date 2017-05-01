#ifndef materiallisth
#define materiallisth

#include "include\includes.h"
#include "material.h"

class MaterialList {
	std::vector<Material> materials;

	std::map<GLint, Material*> mapmaterial;

public:
	//Material* Get(GLint ID);
	//Get material pointers by their id from map class
	Material* Get(GLint ID) { return mapmaterial.find(ID)->second; }

	//Returns count of elements in map class
	GLuint GetSize() { return this->mapmaterial.size(); }

	void BindMaterial(GLint ID) { this->mapmaterial.insert(std::make_pair(ID, &this->materials.at(ID))); }
	void UnbindMaterial(GLint ID) { this->mapmaterial.erase(mapmaterial.find(ID)->first); }
	void Load(Material mat) { this->materials.push_back(mat); }
	void LoadMaterial(GLchar* source) {
		Material material(source);
		this->materials.push_back(material);
		std::cout << "Model added to list: " << this->materials.size();
	}

};

#endif // !materiallisth
