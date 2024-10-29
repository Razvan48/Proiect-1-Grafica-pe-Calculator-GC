#pragma once

#include "../Entity.h"

#include <map>
#include <string>

class BirdEntity : virtual public Entity
{
public:
	enum class Status
	{
		FLYING,
		FALLING,
	};
	BirdEntity::Status status;

protected:
	float width;
	float height;

	std::string primitiveName;

	float gravity;

	float collisionEpsilon;

	bool isInCollisionWithThrowable();

	float centerXEllipse;
	float centerYEllipse;
	float aEllipse;
	float bEllipse;

	float speedScalar;

	float timeOffset;

	float currentWidth;
	float currentHeight;

	int rotationDirectionFlying;
	int rotationDirectionFalling;

	float ellipseScale;
	float ellipseSpeedScale;

	int MAX_STORED_POSITIONS;
	std::map<int, glm::vec2> storedPositions;
	int totalNumPositions;
	float lastTimeAddedStoredPosition;
	float timeBetweenStoredPositions;

public:
	BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height, const std::string& primitiveName, float gravity, const BirdEntity::Status& status, float collisionEpsilon, float centerXEllipse, float centerYEllipse, float aEllipse, float bEllipse, float speedScalar, float timeOffset, float currentWidth, float currentHeight);
	virtual ~BirdEntity();

	virtual void draw() override;
	virtual void update() override;

	inline float getGravity() const { return this->gravity; }
	inline BirdEntity::Status getStatus() const { return this->status; }
};