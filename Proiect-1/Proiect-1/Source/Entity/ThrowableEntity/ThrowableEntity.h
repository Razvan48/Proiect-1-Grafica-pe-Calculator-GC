#pragma once

#include "../Entity.h"

#include <string>

class ThrowableEntity : virtual public Entity // Singleton
{
protected:
	enum class Status
	{
		IN_HAND,
		IN_AIR
	};

	ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float radius, GLfloat initialPosX, GLfloat initialPosY, ThrowableEntity::Status status, const std::string& primitiveName);
	virtual ~ThrowableEntity();
	ThrowableEntity(const ThrowableEntity& other) = delete;
	ThrowableEntity& operator= (const ThrowableEntity& other) = delete;
	ThrowableEntity(const ThrowableEntity&& other) = delete;
	ThrowableEntity& operator= (const ThrowableEntity&& other) = delete;

	float radius;
	GLfloat initialPosX;
	GLfloat initialPosY;

	ThrowableEntity::Status status;

	std::string primitiveName;

public:
	static ThrowableEntity& get();

	virtual void draw() override;
	virtual void update() override;
};