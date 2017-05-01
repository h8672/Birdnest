#include "gameengine.h"

void GameEngine::loadModels() {
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
	models->LoadModel("models/nanosuit/nanosuit.obj");
}

void GameEngine::bindModels() {
	for (GLint i = 0; i < 1; i++)
		models->Bind(i);
}

void GameEngine::loadMaterials()
{
	Material mat;
	//Lightning values http://devernay.free.fr/cours/opengl/materials.html
	
	//Copper data from finnish wiki

	//Visible
	mat.SetAmbient(glm::vec3(0.19125f, 0.0735f, 0.0225f));
	mat.SetDiffuse(glm::vec3(0.7038f, 0.27048f, 0.0828f));
	mat.SetSpecular(glm::vec3(0.256777f, 0.137622f, 0.086014f));
	mat.SetShininess(0.1f);

	//Physical
	mat.SetDensity(8.96f * 1000);	//8960 kg / cubic meter
	mat.SetToughness(3.0f);			//Mohs asteikko
	mat.SetSmelt(1084.62f);			//Celcius asteina
	mat.SetBoil(2562.0f);
	
	materials->Load(mat);
}

void GameEngine::bindMaterials() {

}

void GameEngine::init() {
	loadModels();
	bindModels();
	loadMaterials();
	bindMaterials();
}

void GameEngine::BindModelList(ModelList * list) { this->models = list; }

void GameEngine::BindMaterialList(MaterialList * list) { this->materials = list; }
