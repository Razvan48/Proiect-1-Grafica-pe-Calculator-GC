#pragma once

#include "../Entity.h"

class ThrowableEntity : virtual public Entity // Singleton
{
protected:
	enum class Status
	{
		IN_HAND,
		IN_AIR
	};

	ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float radius, GLfloat initialPosX, GLfloat initialPosY, ThrowableEntity::Status status);
	virtual ~ThrowableEntity();
	ThrowableEntity(const ThrowableEntity& other) = delete;
	ThrowableEntity& operator= (const ThrowableEntity& other) = delete;
	ThrowableEntity(const ThrowableEntity&& other) = delete;
	ThrowableEntity& operator= (const ThrowableEntity&& other) = delete;

	float radius;
	GLfloat initialPosX;
	GLfloat initialPosY;

	ThrowableEntity::Status status;

public:
	static ThrowableEntity& get();

	virtual void draw() override;
	virtual void update() override;
};