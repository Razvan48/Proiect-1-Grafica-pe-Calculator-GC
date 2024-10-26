#include "BirdEntity.h"

BirdEntity::BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
{

}

BirdEntity::~BirdEntity()
{

}

void BirdEntity::draw()
{

}

void BirdEntity::update()
{

}