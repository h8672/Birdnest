#include "material.h"

//Visual functions

Material::Material()
{
	//Create basic material which attributes
	//are written inside program
	std::cout << "Customable material made!" << std::endl;
}

Material::Material(GLchar * source)
{
	//Read material from source binary file
	std::cout << "Material(source) not yet implemented!" << std::endl;
}

//Gets
glm::vec3 Material::GetAmbient() { return this->Ambient; }
glm::vec3 Material::GetDiffuse() { return this->Diffuse; }
glm::vec3 Material::GetSpecular(){	return this->Specular;}
GLfloat Material::GetShininess() { return this->Shininess; }

//Sets
void Material::SetAmbient(glm::vec3 Ambient) { this->Ambient = Ambient; }
void Material::SetDiffuse(glm::vec3 Diffuse) { this->Diffuse = Diffuse; }
void Material::SetSpecular(glm::vec3 Specular) { this->Specular = Specular; }
void Material::SetShininess(GLfloat Shininess) { this->Shininess = Shininess; }

//Physical functions

//Gets
GLfloat Material::GetToughness() { return this->Toughness; }
GLfloat Material::GetDensity() { return this->Density; }
//GLfloat Material::GetElongation() { return this->Elongation; }

//Sets
void Material::SetToughness(GLfloat data) { this->Toughness = data; }
void Material::SetDensity(GLfloat data) { this->Density = data; }
void Material::SetSmelt(GLfloat data) { this->Smelt = data; }
void Material::SetBoil(GLfloat data) { this->Boil = data; }
//void Material::SetElongation(GLfloat data) { this->Elongation = data; }

