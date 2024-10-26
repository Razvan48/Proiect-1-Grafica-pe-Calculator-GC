#include "ThrowableEntity.h"

ThrowableEntity::ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
{

}

ThrowableEntity::~ThrowableEntity()
{

}

void ThrowableEntity::draw()
{

}

void ThrowableEntity::update()
{

}

