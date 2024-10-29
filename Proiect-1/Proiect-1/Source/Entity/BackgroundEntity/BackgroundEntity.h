#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../Entity.h"

#include <string>

class BackgroundEntity : virtual public Entity
{
protected:
	BackgroundEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height, const std::string& primitiveName);
	virtual ~BackgroundEntity();
	BackgroundEntity(const BackgroundEntity& other) = delete;
	BackgroundEntity& operator= (const BackgroundEntity& other) = delete;
	BackgroundEntity(const BackgroundEntity&& other) = delete;
	BackgroundEntity& operator= (const BackgroundEntity&& other) = delete;

	enum class Status
	{
		DAY,
		SUNSET,
		NIGHT,
		SUNRISE,
	};

	float width;
	float height;

	std::string primitiveName;

	BackgroundEntity::Status status;

	float dayDuration;
	float timeSinceLastStatusChange;

public:
	static BackgroundEntity& get();

	virtual void draw() override;
	virtual void update() override;
};