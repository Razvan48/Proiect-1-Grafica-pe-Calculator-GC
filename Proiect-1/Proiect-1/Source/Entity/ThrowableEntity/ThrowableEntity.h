#pragma once

#include "../Entity.h"

class ThrowableEntity : virtual public Entity
{
protected:

public:
	ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor);
	~ThrowableEntity();

	virtual void draw() override;
	virtual void update() override;
};