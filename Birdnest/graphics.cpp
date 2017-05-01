#include "graphics.h"
#include "filereader.h"

GLFWwindow* GraphicEngine::getWindow() { return window; }
Camera * GraphicEngine::getCamera() { return this->camera; }
void GraphicEngine::setCamera(Camera * camera) { this->camera = camera; }

void GraphicEngine::ShowWindow() {
	glfwShowWindow(window);
	glfwSetCursorPos(window, this->windowwidth/2, this->windowheight/2);
	this->camera->TurnCamera(glm::vec3(0,0,0));
	this->camera->CameraPos(glm::vec3(0, 11, -4), false);
}

void GraphicEngine::init() {
	// Init GLFW
	GLint er = glfwInit();
	if (er == GL_FALSE) std::cout << "GLFW init error!\n";
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	
	//Doesn't open created window just yet
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	//Use monitor\
	GLFWmonitor * monitor = glfwGetPrimaryMonitor();\
	glfwGetMonitorPhysicalSize(monitor, &this->windowwidth, &this->windowheight);\
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);\
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);\
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);\
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);\
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);\
	window = glfwCreateWindow(mode->width, mode->height, "Birdnest", monitor, NULL);

	//Create window
	window = glfwCreateWindow(windowwidth, windowheight, "Birdnest", nullptr, nullptr);

	if (!window) std::cout << "Creating window failed!\n";
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Set the required callback functions
	glfwSetKeyCallback(window, keys::key_callback);
	glfwSetMouseButtonCallback(window, keys::mouse_button_callback);
	//glfwSetCursorPosCallback(window, keys::mouse_callback);
	glfwSetScrollCallback(window, keys::scroll_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;//DO NOT TOUCH!!!
	if (!glewExperimental) std::cout << "Kuka koski experimantaliin!!!???\n";
	// Initialize GLEW to setup the OpenGL Function pointers
	GLenum err = glewInit();

	if (err != GLEW_OK)
		std::cout << "Glew error\n" << glewGetErrorString(err) << std::endl; // or handle the error in a nicer way
	if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
		std::cout << "Glew version error\n"; // or handle the error in a nicer way



	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	std::cout << major << " " << minor << " " << rev << std::endl;
	//Load screen, but not needed if have shaders!
	//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	//glViewport(0, 0, windowwidth, windowheight);

	this->camera = new Camera();
	this->camera->SetWindowScale((GLfloat)windowwidth, (GLfloat)windowheight);

	//Moonlight in position and with color
	moon = new Light(glm::vec3(10, 20, 50), glm::vec3(0.5f));

	//all shaders in shader class now
	shader3D = new Shader("3Dvertex.txt", "3Dfragment.txt");
	//shader2D = new Shader("textvertex.txt", "textfragment.txt");
	//shaderLight = new Shader("Lightvertex.txt", "Lightgragment.txt");

	//bindObjects();//continue into bindings

	this->textfont = new Text("arial");
	//createShaders();//Continue to shaders
}

//2D and 3D things
//Add object data
//Add texture data

GLuint GraphicEngine::bindString(Strings string) {
	this->strings.push_back(string);
	return this->strings.capacity();
}
void GraphicEngine::addTexture(GLuint texture) { this->texture = texture; }

void GraphicEngine::BindBox(Box box){
	this->boxes.push_back(box);
}

GLfloat x = 0, y = 0, z = 0;
GLfloat pitch = 0, yaw = 0, roll = 0;

void GraphicEngine::update(GLdouble dtime) {

	keys::use_keys(this->window, dtime);
	glm::vec2 temp;
	temp = keys::getRot(dtime);
	this->camera->TurnCamera(temp);
	temp = glm::vec2(0);

	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();

	// Clear the colorbuffer & depth bit
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(glm::radians(this->camera->GetFov() / this->camera->GetZoom()), this->camera->GetWindowScale(), 0.1f, this->camera->GetRange() * this->camera->GetZoom());
	//Rolls view!!! but not inputs, yet!\
	projection = glm::rotate(projection, glm::radians(this->camera->GetRotations().z), glm::vec3(0, 0, 1));
	
	glm::mat4 view = this->camera->GetViewMatrix();
	glm::mat4 model;
	//Rolls models!!! useless...
	//model = glm::rotate(model, glm::radians(this->camera->GetRotations().z), glm::vec3(0, 0, 1));

	glEnable(GL_BLEND);
	//GLuint projLoc = glGetUniformLocation(this->shader2D->Program, "projection");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//GLuint viewLoc = glGetUniformLocation(this->shader2D->Program, "view");
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Goes through all drawable strings
	for (Strings top : this->strings) {
		//Draw font if in vision of camera, or closer later.
		if ((this->camera->GetPosition() - top.Position).length() < this->camera->GetRange()) {
			textfont->SetVectors(top.Position, top.Rotation, &(this->camera->GetRotations()), top.ToCamera);
			textfont->SetVisuals(top.Color, top.BGColor, top.Scale);
			textfont->Draw(this->shader3D, top.String);
			//std::cout << "Should be drawn\n";
		}
	}
	//this->strings.empty();
	//glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	//glPopMatrix();
	//glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	
	//projektio matriisit... ei toimi jostai syystä
	//shadereissä mahdollisia muutoksia
	// Create transformations
	//glm::mat4 projection = glm::perspective(\
		glm::radians(this->camera->GetFov() / this->camera->GetZoom()),\
		this->camera->GetWindowScale(), 0.1f,\
		this->camera->GetRange() * this->camera->GetZoom()\
		);

	//Switch to 3D shader
	this->shader3D->Use();
	GLuint projLoc = glGetUniformLocation(this->shader3D->Program, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	GLuint viewLoc = glGetUniformLocation(this->shader3D->Program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glUniform3fv(
		glGetUniformLocation(this->shader3D->Program, "viewPos"),
		1, glm::value_ptr(this->camera->GetPosition()));

	
	if (yaw > 360) yaw -= 360;
	if (yaw <= 0) yaw += 360;

	//GLuint projLoc = glGetUniformLocation(this->shader3D->Program, "projection");
	//viewLoc = glGetUniformLocation(this->shader3D->Program, "view");
	// Pass them to the shaders
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	
	for (GLuint i = 0; i < this->models->GetSize(); i++) {
		//glm::mat4 model; already has 1...
		model = glm::translate(model, glm::vec3(x, y, z));
		model = glm::rotate(model, glm::radians(pitch), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(yaw), glm::vec3(0, 1, 0));
		//model = glm::rotate(model, glm::radians(roll), glm::vec3(1, 0, 0));
		glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(
			glGetUniformLocation(shader3D->Program, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		//Model material variables
		//glUniform3fv(
		//	glGetUniformLocation(this->shader3D->Program, "Material.ambient"),
		//	1, glm::value_ptr(this->materials->Get(0)->GetAmbient()));
		//glUniform3fv(
		//	glGetUniformLocation(this->shader3D->Program, "Material.diffuse"),
		//	1, glm::value_ptr(this->materials->Get(0)->GetDiffuse()));
		//glUniform3fv(
		//	glGetUniformLocation(this->shader3D->Program, "Material.specular"),
		//	1, glm::value_ptr(this->materials->Get(0)->GetSpecular()));
		//glUniform1f(
		//	glGetUniformLocation(this->shader3D->Program, "material.shininess"),
		//	this->materials->Get(0)->GetShininess());

		this->models->Get(i)->Draw(shader3D);
	}

	for (Box box : boxes) {
		if ((this->camera->GetPosition() - box.GetPosition()).length() < this->camera->GetRange()) {
			box.Draw(this->shader3D);
		}
	}



	//Move the model!!!
	if (keys::ifkey(GLFW_KEY_UP, false)) {
		//debug and release numbers
		//x += 0.1f * sin(glm::radians(yaw));
		//z += 0.1f * cos(glm::radians(yaw));
		x += 0.01f * sin(glm::radians(yaw));
		z += 0.01f * cos(glm::radians(yaw));
	}
	if (keys::ifkey(GLFW_KEY_DOWN, false)) {
		//debug and release numbers
		//x -= 0.1f * sin(glm::radians(yaw));
		//z -= 0.1f * cos(glm::radians(yaw));
		x -= 0.01f * sin(glm::radians(yaw));
		z -= 0.01f * cos(glm::radians(yaw));
	}
	if (keys::ifkey(GLFW_KEY_LEFT, false)) {
		//debug and release numbers
		//yaw += 1.0f;
		yaw += 0.5f;
	}
	if (keys::ifkey(GLFW_KEY_RIGHT, false)) {
		//debug and release numbers
		//yaw -= 1.0f;
		yaw -= 0.5f;
	}
	
	//std::cout << x << " " << y << " " << z << "\n";

	//glDisable(GL_CULL_FACE);
	//glDisable(GL_BLEND);
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	
	//glUniform1f(textureLocation, 0.0f);//bindataan GL_TEXTURE0:aan

	// Swap the screen buffers
	glfwSwapBuffers(window);

	//std::cout << "Time: " << glfwGetTime() << std::endl;
}


void GraphicEngine::terminate() {
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

//Creates new camera to same spot, resets rotations...
void GraphicEngine::freeCamera() {
	glm::vec3 Position = this->camera->GetPosition();
	this->camera = new Camera(Position);
}

void GraphicEngine::BindModelList(ModelList * list) {
	this->models = list;
}

void GraphicEngine::BindMaterialList(MaterialList * list) { this->materials = list; }



