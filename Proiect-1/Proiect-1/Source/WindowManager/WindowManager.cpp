#include "WindowManager.h"

WindowManager::WindowManager()
	: WINDOW_WIDTH(1024), WINDOW_HEIGHT(1024), WINDOW_TITLE("Proiect-1"), WINDOW_POS_X(100), WINDOW_POS_Y(100)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow(this->WINDOW_TITLE.c_str());

    glewInit();
}

WindowManager::~WindowManager()
{

}

WindowManager& WindowManager::get()
{
    static WindowManager instance;
    return instance;
}

