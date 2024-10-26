#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Source/Application/Application.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	Application::get().start();

	return 0;
}

// TODO:
// sky singleton, mosteneste entity, similar cu throwable
// logica pt throwable, dupa click devine statusul IN_AIR, se misca, opacitate 1.0f (nu mai e transparenta)
// pasari



// interactiune bila <-> pasari
// cade o pasare cand e lovita de bila
// ciclu zi-noapte folosind blending?


