#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Entity
{
protected:
	GLfloat posCenterX;
	GLfloat posCenterY;
	glm::vec2 speed;
	GLfloat rotateAngle;
	std::string textureName;
	glm::vec3 color;
	float textureBlendFactor;
	float backgroundBlendFactor;

public:
	Entity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor);
	virtual ~Entity();

	virtual void draw() = 0;
	virtual void update() = 0;

	inline GLfloat getPosCenterX() const { return this->posCenterX; }
	inline GLfloat getPosCenterY() const { return this->posCenterY; }
};