#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Source/Application/Application.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	Application::get().start();

	return 0;
}


