#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>

class WindowManager
{
private:
	WindowManager();
	~WindowManager();
	WindowManager(const WindowManager& other) = delete;
	WindowManager& operator= (const WindowManager& other) = delete;
	WindowManager(const WindowManager&& other) = delete;
	WindowManager& operator= (const WindowManager&& other) = delete;

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const std::string WINDOW_TITLE;
	const int WINDOW_POS_X;
	const int WINDOW_POS_Y;

public:
	static WindowManager& get();
	inline int getWindowWidth() const { return this->WINDOW_WIDTH; }
	inline int getWindowHeight() const { return this->WINDOW_HEIGHT; }
	inline std::string getWindowTitle() const { return this->WINDOW_TITLE; }
	inline int getWindowPosX() const { return this->WINDOW_POS_X; }
	inline int getWindowPosY() const { return this->WINDOW_POS_Y; }
};

