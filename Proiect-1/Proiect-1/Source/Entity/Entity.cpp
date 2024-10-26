#include "Entity.h"

Entity::Entity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor)
	: posCenterX(posCenterX), posCenterY(posCenterY), speed(speed)
	, rotateAngle(rotateAngle), textureName(textureName), color(color)
	, textureBlendFactor(textureBlendFactor), backgroundBlendFactor(backgroundBlendFactor)
{

}

Entity::~Entity()
{

}