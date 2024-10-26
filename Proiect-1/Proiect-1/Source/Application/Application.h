#pragma once

#include <vector>
#include <memory>

#include "../Entity/Entity.h"

class Application
{
private:
	Application();
	~Application();
	Application(const Application& other) = delete;
	Application& operator= (const Application& other) = delete;
	Application(const Application&& other) = delete;
	Application& operator= (const Application&& other) = delete;

	void loadResources();
	void run();
	void update();
	void draw();
	void releaseResources();

	static void drawWrapper();
	static void releaseResourcesWrapper();

	std::vector<std::shared_ptr<Entity>> entities;

public:
	static Application& get();
	void start();
};