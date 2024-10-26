#include "BirdEntity.h"

#include "../../Renderer/Renderer.h"

BirdEntity::BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, width(width), height(height)
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