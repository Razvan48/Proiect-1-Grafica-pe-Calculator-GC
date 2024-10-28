#pragma once

#include "../Entity.h"

#include <string>

class ThrowableEntity : virtual public Entity // Singleton
{
public:
	enum class Status
	{
		IN_HAND,
		IN_AIR
	};

protected:
	ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float radius, float initialRadius, GLfloat initialPosX, GLfloat initialPosY, ThrowableEntity::Status status, const std::string& primitiveName, float launchTime, float launchDuration, float currentInitialLaunchSpeed);
	virtual ~ThrowableEntity();
	ThrowableEntity(const ThrowableEntity& other) = delete;
	ThrowableEntity& operator= (const ThrowableEntity& other) = delete;
	ThrowableEntity(const ThrowableEntity&& other) = delete;
	ThrowableEntity& operator= (const ThrowableEntity&& other) = delete;

	float radius;
	float initialRadius;
	GLfloat initialPosX;
	GLfloat initialPosY;

	ThrowableEntity::Status status;

	std::string primitiveName;

	float launchTime;
	float launchDuration;

	float currentInitialLaunchSpeed;

public:
	static ThrowableEntity& get();

	virtual void draw() override;
	virtual void update() override;

	inline float getRadius() const { return this->radius; }

	inline float getLaunchTime() const { return this->launchTime; }
	inline float getLaunchDuration() const { return this->launchDuration; }

	inline ThrowableEntity::Status getStatus() const { return this->status; }
};