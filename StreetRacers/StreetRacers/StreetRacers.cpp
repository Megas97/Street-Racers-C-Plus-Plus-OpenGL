#include "pch.h"

#include <GL\glew.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <gl\GLU.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

bool init();
bool initGL();
void render();
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

Shader gShader, gShader2, gShader3, gShader4, gShader5;
Model gModel, gModel2, gModel3, gModel4, gModel5;
bool frontSideButtonPressed, leftSideButtonPressed, rightSideButtonPressed, rearSideButtonPressed, fullScreenButtonPressed;
bool loadTire, loadDodgeChallenger, loadDodgeCharger, loadDodgeChallengerAndDodgeCharger, loadNanosuit, loadCJ, loadNanosuitAndCJ, loadDodgeChallengerAndNanosuit, loadDodgeChargerAndCJ, loadEverything;
bool tireLoaded, dodgeChallengerLoaded, dodgeChargerLoaded, dodgeChallengerAndDodgeChargerLoaded, nanosuitLoaded, CJLoaded, nanosuitAndCJLoaded, dodgeChallengerAndNanosuitLoaded, dodgeChargerAndCJLoaded, everythingLoaded;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));
float lastX = -1;
float lastY = -1;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//event handlers
void HandleKeyDown(const SDL_KeyboardEvent& key);
void HandleMouseMotion(const SDL_MouseMotionEvent& motion);
void HandleMouseWheel(const SDL_MouseWheelEvent& wheel);

// https://wiki.libsdl.org/SDL_Keycode
void HandleKeyDown(const SDL_KeyboardEvent& key)
{
	switch (key.keysym.sym)
	{
	case SDLK_f:
		if (fullScreenButtonPressed != true) {
			fullScreenButtonPressed = true;
		}
		else {
			fullScreenButtonPressed = false;
		}
		close();
		init();
		break;
	case SDLK_q:
		close();
		break;
	case SDLK_w:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case SDLK_s:
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		break;
	case SDLK_a:
		camera.ProcessKeyboard(LEFT, deltaTime);
		break;
	case SDLK_d:
		camera.ProcessKeyboard(RIGHT, deltaTime);
		break;
	case SDLK_KP_PLUS:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case SDLK_KP_MINUS:
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		break;
	case SDLK_KP_DIVIDE:
		camera.ProcessKeyboard(LEFT, deltaTime);
		break;
	case SDLK_KP_MULTIPLY:
		camera.ProcessKeyboard(RIGHT, deltaTime);
		break;
	case SDLK_UP:
		frontSideButtonPressed = true;
		leftSideButtonPressed = false;
		rightSideButtonPressed = false;
		rearSideButtonPressed = false;
		camera.setPosition(glm::vec3(0.0f, 2.0f, 3.0f));
		break;
	case SDLK_LEFT:
		frontSideButtonPressed = false;
		leftSideButtonPressed = true;
		rightSideButtonPressed = false;
		rearSideButtonPressed = false;
		camera.setPosition(glm::vec3(0.0f, 2.0f, 3.0f));
		break;
	case SDLK_RIGHT:
		frontSideButtonPressed = false;
		leftSideButtonPressed = false;
		rightSideButtonPressed = true;
		rearSideButtonPressed = false;
		camera.setPosition(glm::vec3(0.0f, 2.0f, 3.0f));
		break;
	case SDLK_DOWN:
		frontSideButtonPressed = false;
		leftSideButtonPressed = false;
		rightSideButtonPressed = false;
		rearSideButtonPressed = true;
		camera.setPosition(glm::vec3(0.0f, 2.0f, 3.0f));
		break;
	case SDLK_0:
		loadTire = true;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_1:
		loadTire = false;
		loadDodgeChallenger = true;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_2:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = true;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_3:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = true;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_4:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = true;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_5:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = true;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_6:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = true;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_7:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = true;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_8:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = true;
		loadEverything = false;
		initGL();
		break;
	case SDLK_9:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = true;
		initGL();
		break;
	case SDLK_KP_0:
		loadTire = true;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_1:
		loadTire = false;
		loadDodgeChallenger = true;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_2:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = true;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_3:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = true;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_4:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = true;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_5:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = true;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_6:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = true;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_7:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = true;
		loadDodgeChargerAndCJ = false;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_8:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = true;
		loadEverything = false;
		initGL();
		break;
	case SDLK_KP_9:
		loadTire = false;
		loadDodgeChallenger = false;
		loadDodgeCharger = false;
		loadDodgeChallengerAndDodgeCharger = false;
		loadNanosuit = false;
		loadCJ = false;
		loadNanosuitAndCJ = false;
		loadDodgeChallengerAndNanosuit = false;
		loadDodgeChargerAndCJ = false;
		loadEverything = true;
		initGL();
		break;
	}
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glewInit();

	// Original Code
	/*error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
	}*/

	// https://community.khronos.org/t/glgeterror-issue/74986/3
	// AMD Radeon RX 580 8GB Code
	while (true) {
		error = glGetError();
		if (error == GL_NO_ERROR)
		{
			success = true;
			break;
		}
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gShader.Load("./shaders/vertex.vert", "./shaders/fragment.frag");
	gShader2.Load("./shaders/vertex.vert", "./shaders/fragment.frag");
	gShader3.Load("./shaders/vertex.vert", "./shaders/fragment.frag");
	gShader4.Load("./shaders/vertex.vert", "./shaders/fragment.frag");
	gShader5.Load("./shaders/vertex.vert", "./shaders/fragment.frag");

	gModel = NULL;
	gModel2 = NULL;
	gModel3 = NULL;
	gModel4 = NULL;
	gModel5 = NULL;
	if (loadDodgeChallenger == true) {
		gModel = NULL;
		gModel.LoadModel("./models/Dodge Challenger 1971/CHALLENGER71.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = true;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadDodgeCharger == true) {
		gModel = NULL;
		gModel.LoadModel("./models/Dodge Charger RT 1969/CHARGER69.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = true;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadDodgeChallengerAndDodgeCharger == true) {
		gModel = NULL;
		gModel2 = NULL;
		gModel.LoadModel("./models/Dodge Challenger 1971/CHALLENGER71.obj");
		gModel2.LoadModel("./models/Dodge Charger RT 1969/CHARGER69.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = true;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadNanosuit == true) {
		gModel = NULL;
		gModel.LoadModel("./models/Nanosuit/nanosuit.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = true;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadCJ == true) {
		gModel = NULL;
		gModel.LoadModel("./models/CJ/cj.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = true;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadNanosuitAndCJ == true) {
		gModel = NULL;
		gModel2 = NULL;
		gModel.LoadModel("./models/Nanosuit/nanosuit.obj");
		gModel2.LoadModel("./models/CJ/cj.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = true;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadDodgeChallengerAndNanosuit == true) {
		gModel = NULL;
		gModel2 = NULL;
		gModel.LoadModel("./models/Dodge Challenger 1971/CHALLENGER71.obj");
		gModel2.LoadModel("./models/Nanosuit/nanosuit.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = true;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}
	else if (loadDodgeChargerAndCJ == true) {
		gModel = NULL;
		gModel2 = NULL;
		gModel.LoadModel("./models/Dodge Charger RT 1969/CHARGER69.obj");
		gModel2.LoadModel("./models/CJ/cj.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = true;
		everythingLoaded = false;
	}
	else if (loadEverything == true) {
		gModel = NULL;
		gModel2 = NULL;
		gModel3 = NULL;
		gModel4 = NULL;
		gModel5 = NULL;
		gModel.LoadModel("./models/Tire/Tire.obj");
		gModel2.LoadModel("./models/Dodge Challenger 1971/CHALLENGER71.obj");
		gModel3.LoadModel("./models/Nanosuit/nanosuit.obj");
		gModel4.LoadModel("./models/Dodge Charger RT 1969/CHARGER69.obj");
		gModel5.LoadModel("./models/CJ/cj.obj");
		tireLoaded = false;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = true;
	}
	else if (((loadDodgeChallenger != true) && (loadDodgeCharger != true) && (loadDodgeChallengerAndDodgeCharger != true) && (loadNanosuit != true) && (loadCJ != true) && (loadNanosuitAndCJ != true) && (loadDodgeChallengerAndNanosuit != true) && (loadDodgeChargerAndCJ != true) && (loadEverything != true)) || (loadTire == true)) {
		gModel = NULL;
		gModel.LoadModel("./models/Tire/Tire.obj");
		tireLoaded = true;
		dodgeChallengerLoaded = false;
		dodgeChargerLoaded = false;
		dodgeChallengerAndDodgeChargerLoaded = false;
		nanosuitLoaded = false;
		CJLoaded = false;
		nanosuitAndCJLoaded = false;
		dodgeChallengerAndNanosuitLoaded = false;
		dodgeChargerAndCJLoaded = false;
		everythingLoaded = false;
	}

	// Center camera view
	camera.setPosition(glm::vec3(0.0f, 2.0f, 3.0f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Other modes: GL_FILL, GL_POINT

	return success;
}

void render()
{
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model2 = glm::mat4(1.0f);
	glm::mat4 model3 = glm::mat4(1.0f);
	glm::mat4 model4 = glm::mat4(1.0f);
	glm::mat4 model5 = glm::mat4(1.0f);
	if (tireLoaded == true) {
		// Default look
		model = glm::translate(model, glm::vec3(0.0f, 1.18f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		// Front side look
		if (frontSideButtonPressed == true) {
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
	else if (dodgeChallengerLoaded == true) {
		// Default look
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Front side look
		else if (frontSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
	}
	else if (dodgeChargerLoaded == true) {
		// Default look
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Front side look
		else if (frontSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(-0.2f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.2f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
	}
	else if (dodgeChallengerAndDodgeChargerLoaded == true) {
		// Default look
		// Dodge Challenger
		model = glm::translate(model, glm::vec3(-0.9f, 2.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		// Dodge Charger
		model2 = glm::translate(model2, glm::vec3(0.9f, 1.92f, -1.0f));
		model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Dodge Charger
			model2 = glm::translate(model2, glm::vec3(0.0f, -1.3f, 0.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Front side look
		else if (frontSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Dodge Charger
			model2 = glm::translate(model2, glm::vec3(0.0f, -1.3f, 0.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(1.7f, -1.5f, -4.0f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Dodge Charger
			model2 = glm::translate(model2, glm::vec3(-1.9f, -1.3f, 0.0f));
			model2 = glm::rotate(model2, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model2 = glm::rotate(model2, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(1.9f, -1.5f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Dodge Charger
			model2 = glm::translate(model2, glm::vec3(-1.7f, -1.3f, -4.0f));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(3.6f, -1.5f, -0.6f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Dodge Charger
			model2 = glm::translate(model2, glm::vec3(-3.6f, -1.3f, -0.6f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
		}
	}
	else if (nanosuitLoaded == true) {
		// Default look
		model = glm::translate(model, glm::vec3(0.0f, 1.32f, 1.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		// Front side look
		if (frontSideButtonPressed == true) {
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
	else if (CJLoaded == true) {
		// Default look
		model = glm::translate(model, glm::vec3(0.0f, 1.32f, 1.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		// Front side look
		if (frontSideButtonPressed == true) {
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
	else if (nanosuitAndCJLoaded == true) {
		// Default look
		// Nanosuit
		model = glm::translate(model, glm::vec3(-0.5f, 1.29f, 1.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		// CJ
		model2 = glm::translate(model2, glm::vec3(0.5f, 1.32f, 1.0f));
		model2 = glm::scale(model2, glm::vec3(0.02f, 0.02f, 0.02f));
		// Front side look
		if (frontSideButtonPressed == true) {
			// Nanosuit
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// CJ
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			// Nanosuit
			model = glm::translate(model, glm::vec3(5.3f, 0.33f, -10.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// CJ
			model2 = glm::translate(model2, glm::vec3(-25.0f, 1.32f, 1.0f));
			model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			// Nanosuit
			model = glm::translate(model, glm::vec3(5.3f, 0.33f, -1.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// CJ
			model2 = glm::translate(model2, glm::vec3(-25.0f, 1.32f, -52.0f));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			// Nanosuit
			model = glm::translate(model, glm::vec3(11.0f, 0.4f, 1.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.945f, 0.945f, 0.945f));
			// CJ
			model2 = glm::translate(model2, glm::vec3(-48.0f, 0.7f, 7.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(0.945f, 0.945f, 0.945f));
		}
	}
	else if (dodgeChallengerAndNanosuitLoaded == true) {
		// Default look
		// Dodge Challenger
		model = glm::translate(model, glm::vec3(-0.2f, 2.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		// Nanosuit
		model2 = glm::translate(model2, glm::vec3(0.7f, 1.32f, -1.0f));
		model2 = glm::scale(model2, glm::vec3(0.09f, 0.09f, 0.09f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.0f, -1.3f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Front side look
		else if (frontSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.0f, -1.3f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.35f, -1.3f, -1.8f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model2 = glm::translate(model2, glm::vec3(-5.5f, -0.7f, -1.0f));
			model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.35f, -1.3f, -1.3f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model2 = glm::translate(model2, glm::vec3(-10.5f, -0.7f, -17.0f));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			// Dodge Challenger
			model = glm::translate(model, glm::vec3(0.7f, -1.3f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model2 = glm::translate(model2, glm::vec3(-16.0f, -0.3f, -1.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
	else if (dodgeChargerAndCJLoaded == true) {
		// Default look
		// Dodge Charger
		model = glm::translate(model, glm::vec3(-0.2f, 2.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		// CJ
		model2 = glm::translate(model2, glm::vec3(0.7f, 1.32f, -1.0f));
		model2 = glm::scale(model2, glm::vec3(0.02f, 0.02f, 0.02f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			// Dodge Charger
			model = glm::translate(model, glm::vec3(0.0f, -1.3f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Front side look
		if (frontSideButtonPressed == true) {
			// Dodge Charger
			model = glm::translate(model, glm::vec3(0.0f, -1.3f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			// Dodge Charger
			model = glm::translate(model, glm::vec3(0.10f, -1.3f, -1.8f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model2 = glm::translate(model2, glm::vec3(-31.5f, -0.7f, -1.0f));
			model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			// Dodge Charger
			model = glm::translate(model, glm::vec3(0.7f, -1.3f, -1.3f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model2 = glm::translate(model2, glm::vec3(-40.5f, -0.7f, -77.0f));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			// Dodge Charger
			model = glm::translate(model, glm::vec3(0.7f, -1.3f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model2 = glm::translate(model2, glm::vec3(-72.0f, -0.3f, -1.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
	else if (everythingLoaded == true) {
		// Default look
		// Tire
		model = glm::translate(model, glm::vec3(0.0f, 1.32f, -2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		// Dodge Challenger
		model2 = glm::translate(model2, glm::vec3(-1.45f, 2.0f, -2.0f));
		model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			model2 = glm::translate(model2, glm::vec3(0.0f, -1.5f, 0.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// Nanosuit
		model3 = glm::translate(model3, glm::vec3(-0.6f, 1.32f, -2.0f));
		model3 = glm::scale(model3, glm::vec3(0.09f, 0.09f, 0.09f));
		// Dodge Charger
		model4 = glm::translate(model4, glm::vec3(1.45f, 2.0f, -2.0f));
		model4 = glm::scale(model4, glm::vec3(0.5f, 0.5f, 0.5f));
		if ((frontSideButtonPressed != true) && (leftSideButtonPressed != true) && (rightSideButtonPressed != true) && (rearSideButtonPressed != true)) {
			model4 = glm::translate(model4, glm::vec3(0.0f, -1.5f, 0.0f));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model4 = glm::scale(model4, glm::vec3(1.2f, 1.2f, 1.2f));
		}
		// CJ
		model5 = glm::translate(model5, glm::vec3(0.6f, 1.32f, -2.0f));
		model5 = glm::scale(model5, glm::vec3(0.02f, 0.02f, 0.02f));
		// Front side look
		if (frontSideButtonPressed == true) {
			// Tire
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Challenger
			model2 = glm::translate(model2, glm::vec3(0.0f, -1.5f, 0.0f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Charger
			model4 = glm::translate(model4, glm::vec3(0.0f, -1.5f, 0.0f));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model4 = glm::scale(model4, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model5 = glm::scale(model5, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Left side look
		else if (leftSideButtonPressed == true) {
			// Tire
			model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Challenger
			model2 = glm::translate(model2, glm::vec3(2.5f, -1.3f, -6.0f));
			model2 = glm::rotate(model2, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model2 = glm::rotate(model2, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model3 = glm::translate(model3, glm::vec3(6.0f, -0.7f, -23.5f));
			model3 = glm::rotate(model3, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Charger
			model4 = glm::translate(model4, glm::vec3(-3.2f, -1.3f, 0.0f));
			model4 = glm::rotate(model4, glm::radians(270.0f), glm::vec3(0, 0, 1));
			model4 = glm::rotate(model4, glm::radians(270.0f), glm::vec3(0, 1, 0));
			model4 = glm::rotate(model4, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model4 = glm::scale(model4, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model5 = glm::translate(model5, glm::vec3(-31.5f, -0.7f, -45.0f));
			model5 = glm::rotate(model5, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			model5 = glm::scale(model5, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Right side look
		else if (rightSideButtonPressed == true) {
			// Tire
			model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Challenger
			model2 = glm::translate(model2, glm::vec3(2.95f, -1.3f, 0.0f));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model3 = glm::translate(model3, glm::vec3(7.0f, -0.7f, -10.5f));
			model3 = glm::rotate(model3, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Charger
			model4 = glm::translate(model4, glm::vec3(-2.7f, -1.3f, -6.0f));
			model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(0, 0, 1));
			model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model4 = glm::rotate(model4, glm::radians(0.0f), glm::vec3(0, 1, 1));
			model4 = glm::scale(model4, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model5 = glm::translate(model5, glm::vec3(-30.0f, -0.7f, -105.0f));
			model5 = glm::rotate(model5, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model5 = glm::scale(model5, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		// Rear side look
		else if (rearSideButtonPressed == true) {
			// Tire
			model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Challenger
			model2 = glm::translate(model2, glm::vec3(5.85f, -1.5f, -0.5f));
			model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model2 = glm::scale(model2, glm::vec3(1.2f, 1.2f, 1.2f));
			// Nanosuit
			model3 = glm::translate(model3, glm::vec3(13.5f, -0.3f, -1.5f));
			model3 = glm::rotate(model3, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
			// Dodge Charger
			model4 = glm::translate(model4, glm::vec3(-5.75f, -1.5f, -0.5f));
			model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(0, 1, 1));
			model4 = glm::scale(model4, glm::vec3(1.2f, 1.2f, 1.2f));
			// CJ
			model5 = glm::translate(model5, glm::vec3(-59.0f, -0.3f, -1.5f));
			model5 = glm::rotate(model5, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model5 = glm::scale(model5, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat3 normalMat = glm::transpose(glm::inverse(model));

	glUseProgram(gShader.ID);
	gShader.setMat4("model", model);
	gShader.setMat4("view", view);
	gShader.setMat4("proj", proj);
	gShader.setMat3("normalMat", normalMat);

	// Lighting
	gShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader.setVec3("light.position", lightPos);
	gShader.setVec3("viewPos", camera.Position);

	gModel.Draw(gShader);
	//////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 view2 = camera.GetViewMatrix();
	glm::mat4 proj2 = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat3 normalMat2 = glm::transpose(glm::inverse(model2));

	glUseProgram(gShader2.ID);
	gShader2.setMat4("model", model2);
	gShader2.setMat4("view", view2);
	gShader2.setMat4("proj", proj2);
	gShader2.setMat3("normalMat", normalMat2);

	// Lighting
	gShader2.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader2.setVec3("light.position", lightPos);
	gShader2.setVec3("viewPos", camera.Position);

	gModel2.Draw(gShader2);
	//////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 view3 = camera.GetViewMatrix();
	glm::mat4 proj3 = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat3 normalMat3 = glm::transpose(glm::inverse(model3));

	glUseProgram(gShader3.ID);
	gShader3.setMat4("model", model3);
	gShader3.setMat4("view", view3);
	gShader3.setMat4("proj", proj3);
	gShader3.setMat3("normalMat", normalMat3);

	// Lighting
	gShader3.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader3.setVec3("light.position", lightPos);
	gShader3.setVec3("viewPos", camera.Position);

	gModel3.Draw(gShader3);
	//////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 view4 = camera.GetViewMatrix();
	glm::mat4 proj4 = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat3 normalMat4 = glm::transpose(glm::inverse(model4));

	glUseProgram(gShader4.ID);
	gShader4.setMat4("model", model4);
	gShader4.setMat4("view", view4);
	gShader4.setMat4("proj", proj4);
	gShader4.setMat3("normalMat", normalMat4);

	// Lighting
	gShader4.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader4.setVec3("light.position", lightPos);
	gShader4.setVec3("viewPos", camera.Position);

	gModel4.Draw(gShader4);
	//////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 view5 = camera.GetViewMatrix();
	glm::mat4 proj5 = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat3 normalMat5 = glm::transpose(glm::inverse(model5));

	glUseProgram(gShader5.ID);
	gShader5.setMat4("model", model5);
	gShader5.setMat4("view", view5);
	gShader5.setMat4("proj", proj5);
	gShader5.setMat3("normalMat", normalMat5);

	// Lighting
	gShader5.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader5.setVec3("light.position", lightPos);
	gShader5.setVec3("viewPos", camera.Position);

	gModel5.Draw(gShader5);
}

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Original Code
		// Use OpenGL 3.3
		/*SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);*/

		// AMD Radeon RX 580 8GB Code
		// Use OpenGL 3.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		
		// Create window
		if (fullScreenButtonPressed == true) {
			// Full screen window
			gWindow = SDL_CreateWindow("Street Racers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		}
		else {
			// Small window
			gWindow = SDL_CreateWindow("Street Racers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		}
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				// Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	if (success == true) {
		printf("Usage:\n");
		printf("\n");
		printf("Button(s) - Action(s)\n");
		printf("\n");
		printf("num0 | 0 - Load Tire\n");
		printf("num1 | 1 - Load Dodge Challenger 1971\n");
		printf("num2 | 2 - Load Dodge Charger R/T 1969\n");
		printf("num3 | 3 - Load Dodge Challenger 1971 & Dodge Charger R/T 1969\n");
		printf("num4 | 4 - Load Carl Johnson (CJ)\n");
		printf("num5 | 5 - Load Nanosuit\n");
		printf("num6 | 6 - Load Carl Johnson (CJ) & Nanosuit\n");
		printf("num7 | 7 - Load Dodge Challenger 1971 & Carl Johnson (CJ)\n");
		printf("num8 | 8 - Load Dodge Charger R/T 1969 & Nanosuit\n");
		printf("num9 | 9 - Load Dodge Challenger 1971 & Nanosuit & Dodge Charger R/T 1969 & Carl Johnson (CJ)\n");
		printf("\n");
		printf("num_div (/) | a - Move camera to the left\n");
		printf("num_mul (*) | d - Move camera to the right\n");
		printf("num_add (+) | w - Move camera forward\n");
		printf("num_sub (-) | s - Move camera backward\n");
		printf("mouse_wheel_up - Zoom camera in\n");
		printf("mouse_wheel_down - Zoom camera out\n");
		printf("\n");
		printf("arrow_left - Change view to left side\n");
		printf("arrow_up - Change view to front side\n");
		printf("arrow_right - Change view to right side\n");
		printf("arrow_down - Change view to rear side\n");
		printf("\n");
		printf("F - Toggle fullscreen\n");
		printf("Q - Quit\n");
	}

	return success;
}

void HandleMouseMotion(const SDL_MouseMotionEvent& motion)
{
	if (firstMouse)
	{
		lastX = motion.x;
		lastY = motion.y;
		firstMouse = false;
	}
	else
	{
		camera.ProcessMouseMovement(motion.x - lastX, lastY - motion.y);
		lastX = motion.x;
		lastY = motion.y;
	}
}

void HandleMouseWheel(const SDL_MouseWheelEvent& wheel)
{
	camera.ProcessMouseScroll(wheel.y);
}

void close()
{
	// Delete GL programs, buffers and objects
	glDeleteProgram(gShader.ID);
	glDeleteProgram(gShader2.ID);
	glDeleteProgram(gShader3.ID);
	glDeleteProgram(gShader4.ID);
	glDeleteProgram(gShader5.ID);

	// Delete OGL context
	SDL_GL_DeleteContext(gContext);
	// Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	init();

	SDL_Event e;
	// While application is running
	bool quit = false;
	while (!quit)
	{
		// per-frame time logic
		// --------------------
		float currentFrame = SDL_GetTicks() / 1000.0f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				else
				{
					HandleKeyDown(e.key);
				}
				break;
			case SDL_MOUSEMOTION:
				HandleMouseMotion(e.motion);
				break;
			case SDL_MOUSEWHEEL:
				HandleMouseWheel(e.wheel);
				break;
			}
		}

		// Render
		render();

		// Update screen
		SDL_GL_SwapWindow(gWindow);
	}

	close();

	return 0;
}