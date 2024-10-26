#include "InputManager.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

InputManager::InputManager()
	: leftMouseButtonUp(true), leftMouseButtonUpLastTime(true), currentMouseX(0), currentMouseY(0)
{
	glutMouseFunc(mouseFuncWrapper);
	glutPassiveMotionFunc(motionFuncWrapper);
	glutMotionFunc(motionFuncWrapper);
}

InputManager& InputManager::get()
{
	static InputManager instance;
	return instance;
}

InputManager::~InputManager()
{

}

void InputManager::mouseFuncWrapper(int button, int state, int x, int y)
{
	InputManager::get().mouseFunc(button, state, x, y);
}

void InputManager::motionFuncWrapper(int x, int y)
{
	InputManager::get().motionFunc(x, y);
}

void InputManager::mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			this->leftMouseButtonUpLastTime = this->leftMouseButtonUp;
			this->leftMouseButtonUp = true;
		}
		else if (state == GLUT_DOWN)
		{
			this->leftMouseButtonUpLastTime = this->leftMouseButtonUp;
			this->leftMouseButtonUp = false;
		}
	}
}

void InputManager::motionFunc(int x, int y)
{
	this->currentMouseX = x;
	this->currentMouseY = y;
}

void InputManager::update()
{
	this->leftMouseButtonUpLastTime = this->leftMouseButtonUp;
	this->leftMouseButtonUp = false;
}