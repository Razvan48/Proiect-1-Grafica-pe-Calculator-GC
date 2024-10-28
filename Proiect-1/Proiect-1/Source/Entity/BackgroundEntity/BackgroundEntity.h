#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../Entity.h"

class BackgroundEntity : virtual public Entity
{
protected:
	BackgroundEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height);
	virtual ~BackgroundEntity();
	BackgroundEntity(const BackgroundEntity& other) = delete;
	BackgroundEntity& operator= (const BackgroundEntity& other) = delete;
	BackgroundEntity(const BackgroundEntity&& other) = delete;
	BackgroundEntity& operator= (const BackgroundEntity&& other) = delete;

	float width;
	float height;

public:
	static BackgroundEntity& get();

	virtual void draw() override;
	virtual void update() override;
};