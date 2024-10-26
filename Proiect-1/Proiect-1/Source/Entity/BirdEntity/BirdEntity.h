#pragma once

#include "../Entity.h"

class BirdEntity : virtual public Entity
{
protected:

public:
	BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor);
	~BirdEntity();

	virtual void draw() override;
	virtual void update() override;
};