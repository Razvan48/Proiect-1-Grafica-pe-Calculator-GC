#pragma once

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

public:
	static Application& get();
	void start();
};