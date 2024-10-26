#include "Application.h"

#include "../WindowManager/WindowManager.h"
#include "../TextureManager/TextureManager.h"
#include "../Renderer/Renderer.h"

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

}

void Application::start()
{
	this->loadResources();
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
	Renderer::get().draw(500.0f, 500.0f, 100.0f, 100.0f, 0.0f, "throwablePrimitive", "test2", glm::vec3(1.0f, 1.0f, 1.0f), 0.9f, 1.0f);

	// glutSwapBuffers();

	glFlush();

	glutPostRedisplay();
}

void Application::releaseResources()
{
	Renderer::get().releaseResources();
}