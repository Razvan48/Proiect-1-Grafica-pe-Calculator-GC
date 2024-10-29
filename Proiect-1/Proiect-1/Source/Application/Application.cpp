#include "Application.h"

#include "../WindowManager/WindowManager.h"
#include "../TextureManager/TextureManager.h"
#include "../Renderer/Renderer.h"
#include "../InputManager/InputManager.h"

#include "../Entity/Entity.h"
#include "../Entity/ThrowableEntity/ThrowableEntity.h"
#include "../Entity/BackgroundEntity/BackgroundEntity.h"
#include "../Entity/BirdEntity/BirdEntity.h"
#include "../RandomGenerator/RandomGenerator.h"

#include "../GlobalClock/GlobalClock.h"

#include <iostream>

Application::Application()
	: NUM_BIRDS(20)
{
	for (int i = 0; i < this->NUM_BIRDS; ++i)
	{
		this->entities.push_back(std::make_shared<BirdEntity>(
			0.0f, 0.0f,
			glm::vec2(0.0f, 0.0f),
			0.0f,
			"birdTexture",
			glm::vec3(1.0f, 1.0f, 1.0f),
			0.0f,
			1.0f,
			WindowManager::get().getWindowWidth() / 20.0f,
			WindowManager::get().getWindowWidth() / 20.0f,
			"birdPrimitive",
			250.0f,
			BirdEntity::Status::FLYING,
			0.1f,
			WindowManager::get().getWindowWidth() / 2.0f + RandomGenerator::randomUniformDouble(-150.0, 150.0), // x elipsa
			WindowManager::get().getWindowHeight() / 2.0f + RandomGenerator::randomUniformDouble(-150.0, 150.0), // y elipsa
			WindowManager::get().getWindowWidth() / 3.0f + RandomGenerator::randomUniformDouble(-150.0, 150.0), // a elipsa
			WindowManager::get().getWindowHeight() / 3.0f + RandomGenerator::randomUniformDouble(-150.0, 150.0), // b elipsa
			100.0f + RandomGenerator::randomUniformDouble(-50.0, 50.0), // speed scalar
			RandomGenerator::randomUniformDouble(0.0, 360.0), // offset pentru start pe elipsa
			0.0f, 0.0f
		));
	}
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
	GlobalClock::get(); // Nu cred ca e necesar
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
	GlobalClock::get().update();

	BackgroundEntity::get().update();

	for (int i = 0; i < this->entities.size(); ++i)
		this->entities[i]->update();

	for (int i = 0; i < this->entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<BirdEntity>(this->entities[i])
			&& std::dynamic_pointer_cast<BirdEntity>(this->entities[i])->getStatus() == BirdEntity::Status::FALLING
			&& std::dynamic_pointer_cast<BirdEntity>(this->entities[i])->getPosCenterY() < -5.0f * WindowManager::get().getWindowHeight())
		{
			std::swap(this->entities[i], this->entities.back());
			this->entities.pop_back();
			--i;
		}
	}
	std::cout << "Number of entities: " << this->entities.size() << std::endl;

	ThrowableEntity::get().update();

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
	BackgroundEntity::get().draw();

	for (int i = 0; i < this->entities.size(); ++i)
		this->entities[i]->draw();

	ThrowableEntity::get().draw();

	// TEST: TODO: delete after testing
	// Renderer::get().draw(500.0f, 500.0f, 100.0f, 100.0f, 0.0f, "throwablePrimitive", "test1Texture", glm::vec3(1.0f, 1.0f, 1.0f), 0.9f, 1.0f);

	// glutSwapBuffers();

	glFlush();

	glutPostRedisplay();
}

void Application::releaseResources()
{
	Renderer::get().releaseResources();
}