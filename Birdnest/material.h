#ifndef materialh
#define materialh

#include "include\includes.h"

class Material {

	//Visual values
	glm::vec3 Ambient;		//Ambient color							Hohto
	glm::vec3 Diffuse;		//Diffuse color							sekoitus
	glm::vec3 Specular;		//Specular color						tarkkuus
	GLfloat Shininess;		//Shininess								Kirkkaus
	//GLfloat Opaque;			//Opaqueness							Läpinäkyvyys

	//Physical values
	GLfloat Toughness;	//How tough, pressure / square meter?		Kestävyys
	GLfloat Density;	//How dense, kg / cubic meter.				Tiheys
	//GLfloat Elongation;	//How much it can stretch					Venyminen	Elasticity?
	
	GLfloat Smelt;		//Smelting temperature
	GLfloat Boil;		//Boiling temperature

public:
	//Init
	Material();
	Material(GLchar* source);

	//Visual functions

	//Gets
	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	GLfloat GetShininess();

	//Sets
	void SetAmbient(glm::vec3 Ambient);
	void SetDiffuse(glm::vec3 Diffuse);
	void SetSpecular(glm::vec3 Specular);
	void SetShininess(GLfloat Shininess);

	//Physical functions

	//Gets
	GLfloat GetToughness();
	GLfloat GetDensity();
	//GLfloat GetElongation();
	GLfloat GetSmelt();
	GLfloat GetBoil();

	//Sets
	void SetToughness(GLfloat data);
	void SetDensity(GLfloat data);
	//void SetElongation(GLfloat data);
	void SetSmelt(GLfloat data);
	void SetBoil(GLfloat data);

};


#endif // !materialh
