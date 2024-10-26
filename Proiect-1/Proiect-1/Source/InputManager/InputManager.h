#pragma once

class InputManager
{
private:
	InputManager();
	~InputManager();
	InputManager(const InputManager& other) = delete;
	InputManager& operator= (const InputManager& other) = delete;
	InputManager(const InputManager&& other) = delete;
	InputManager& operator= (const InputManager&& other) = delete;

	static void mouseFuncWrapper(int button, int state, int x, int y);
	void mouseFunc(int button, int state, int x, int y);
	static void motionFuncWrapper(int x, int y);
	void motionFunc(int x, int y);

	bool leftMouseButtonUp;
	bool leftMouseButtonUpLastTime;
	int currentMouseX;
	int currentMouseY;

public:
	static InputManager& get();
	void update();

	inline int getCurrentMouseX() const { return this->currentMouseX; }
	inline int getCurrentMouseY() const { return this->currentMouseY; }
	inline bool recentlyMouseUp() const { return (!this->leftMouseButtonUpLastTime) && this->leftMouseButtonUp; }
};