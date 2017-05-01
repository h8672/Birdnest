#include "includes.h"
#include "graphics.h"
#include "filereader.h"
#include "keycalls.h"
#include "player.h"
#include "menu.h"
#include "gameengine.h"
#include "box.h"


int main() {

	GraphicEngine graphics;
	graphics.init();

	GameEngine game;
	Player * player;

	ModelList models;
	MaterialList materials;

	//No longer used...
	graphics.addTexture(FileReader::read2Dtexture("test.png"));


	//Kerran neljässä tunnissa aika nollataan! ;D
	//Eli yksi päivä pelissä on 4 tuntia
	GLint day = 4 * 3600; //Day in game is 4 hours...

	//Init player
	player = new Player(graphics.getCamera());

	//Init window
	graphics.ShowWindow();

	//Bind ModelList to engines
	graphics.BindModelList(&models);
	//graphics.BindMaterialList(&materials);

	game.BindModelList(&models);
	game.BindMaterialList(&materials);

	Box box;
	box.SetPosition(glm::vec3(8));
	box.SetColor(glm::vec4(1));
	box.SetSize(16, 12);
	box.SetTexture(FileReader::read2Dtexture("textures/above.png"));
	graphics.BindBox(box);

	game.init();


	//FPS counter
	//GLdouble times[5] = { 0, 0, 0, 0, 0 };
	//GLint tilts = 0;
	//GLdouble timee = 0;
	
	//Bind strings temporarily
	//Needs reconfiguring!!!
	Strings string = { glm::vec3(2, 0, 0), glm::vec3(0), "String of text!?", 1.0f, glm::vec4(1.0f, 0.2f, 0.7f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.3f), false };
	graphics.bindString(string);
	Strings string2 = { glm::vec3(2), glm::vec3(10), "0123456789", 2.0f, glm::vec4(0.2f, 0.5f, 0.8f, 1), glm::vec4(0.5f, 0.2f, 0.2f, 0.5f), true };
	graphics.bindString(string2);
	Strings string3 = { glm::vec3(-1.0f), glm::vec3(0), "ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ", 2.0f, glm::vec4(0.8f, 0.5f, 0.2f, 1), glm::vec4(0.2f, 0.2f, 0.9f, 0.5f), true };
	graphics.bindString(string3);
	Strings string4 = { glm::vec3(-1.5f), glm::vec3(0), "abcdefghijklmnopqrstuvwxyzåäö", 2.0f, glm::vec4(0.8f, 0.5f, 0.2f, 1), glm::vec4(0.2f, 0.2f, 0.9f, 0.5f), false };
	graphics.bindString(string4);


	//Need text texture loader and use it to print text in opengl window!
	// Game loop
	GLdouble time = 0, deltatime = 0;
	while (!glfwWindowShouldClose(graphics.getWindow())) {
		
		if (true) {
			//Get times
			deltatime = time;
			time = glfwGetTime();//parhaimmillaan antaa 585 vuotta sekuntteina
			deltatime = time - deltatime;
			//Update graphics, test keys and move camera...
			graphics.update(deltatime);

			//FPS counter
			std::cout << "FPS: " << 1.0 / (deltatime) << std::endl;


			//Update new loop time
			player->SetDeltaTime(deltatime);

			player->Move(graphics.getWindow());

			//graphics.getCamera()->CameraTarget(glm::vec3(0), true);
			//temp = keys::getPos();
			//graphics.getCamera()->CameraPos(temp, false);
			//std::cout << "temp pos: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;
			//std::cout << "temp rot: " << temp.x << ", " << temp.y << ", " << temp.z << std::endl;
		}
		else {
			//menu->Draw();
		}
	}

	graphics.terminate();

	return 0;
}

