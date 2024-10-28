#pragma once

#include "../Entity.h"

#include <string>

class BirdEntity : virtual public Entity
{
protected:
	float width;
	float height;

	std::string primitiveName;

public:
	BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height, const std::string& primitiveName);
	virtual ~BirdEntity();

	virtual void draw() override;
	virtual void update() override;
};