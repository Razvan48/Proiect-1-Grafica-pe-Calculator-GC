#include "Application.h"

#include "../WindowManager/WindowManager.h"
#include "../TextureManager/TextureManager.h"
#include "../Renderer/Renderer.h"
#include "../InputManager/InputManager.h"

#include "../Entity/Entity.h"
#include "../Entity/ThrowableEntity/ThrowableEntity.h"

Application::Application()
{

}

Application::~Application()
{

}

Application& Application::get()
{
	static Application instance;
	return instance;
}

void Application::loadResources()
{
	WindowManager::get(); // Asigura setup-ul la OpenGL
	TextureManager::get().loadResources();
}

void Application::run()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutDisplayFunc(Application::drawWrapper);
	glutCloseFunc(Application::releaseResourcesWrapper);

	glutMainLoop();
}

void Application::update()
{
	ThrowableEntity::get().update();
	for (int i = 0; i < this->entities.size(); ++i)
		this->entities[i]->update();

	InputManager::get().update(); // Trebuie sa fie ultima in metoda de update() ca sa nu anuleze efectele de input.
}

void Application::start()
{
	this->loadResources();

	// TODO: Incarcare entitati




	this->run();
}

void Application::drawWrapper()
{
	Application::get().draw();
}

void Application::releaseResourcesWrapper()
{
	Application::get().releaseResources();
}

void Application::draw(void)
{
	this->update();

	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: draw
	Renderer::get().draw(WindowManager::get().getWindowWidth() / 2.0f,
		WindowManager::get().getWindowHeight() / 2.0f,
		WindowManager::get().getWindowWidth(),
		WindowManager::get().getWindowHeight(),
		0.0f, "backgroundPrimitive", "background", glm::vec3(1.0f, 1.0f, 1.0f),
		0.0f, 1.0f);

	ThrowableEntity::get().draw();
	for (int i = 0; i < this->entities.size(); ++i)
		this->entities[i]->draw();

	Renderer::get().draw(500.0f, 500.0f, 100.0f, 100.0f, 0.0f, "throwablePrimitive", "test2", glm::vec3(1.0f, 1.0f, 1.0f), 0.9f, 1.0f);

	// glutSwapBuffers();

	glFlush();

	glutPostRedisplay();
}

void Application::releaseResources()
{
	Renderer::get().releaseResources();
}