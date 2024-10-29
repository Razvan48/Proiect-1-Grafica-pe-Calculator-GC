#include "BirdEntity.h"

#include "../../Renderer/Renderer.h"
#include "../../GlobalClock/GlobalClock.h"
#include "../ThrowableEntity/ThrowableEntity.h"
#include "../../RandomGenerator/RandomGenerator.h"

BirdEntity::BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height, const std::string& primitiveName, float gravity, const BirdEntity::Status& status, float collisionEpsilon, float centerXEllipse, float centerYEllipse, float aEllipse, float bEllipse, float speedScalar, float timeOffset, float currentWidth, float currentHeight)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, width(width), height(height), primitiveName(primitiveName)
	, gravity(gravity), status(status)
	, collisionEpsilon(collisionEpsilon)
	, centerXEllipse(centerXEllipse), centerYEllipse(centerYEllipse)
	, aEllipse(aEllipse), bEllipse(bEllipse), speedScalar(speedScalar)
	, timeOffset(timeOffset), currentWidth(currentWidth), currentHeight(currentHeight)
	, rotationDirectionFlying(2 * RandomGenerator::randomUniformInt(0, 1) - 1), rotationDirectionFalling(2 * RandomGenerator::randomUniformInt(0, 1) - 1)
	, ellipseScale(1.0f), ellipseSpeedScale(0.01f)
	, MAX_STORED_POSITIONS(10), totalNumPositions(0)
	, lastTimeAddedStoredPosition(0.0f), timeBetweenStoredPositions(0.065f)
{

}

BirdEntity::~BirdEntity()
{

}

void BirdEntity::draw()
{
	int count = 0;
	int currentStoredPositionsSize = this->storedPositions.size();
	for (auto& it : this->storedPositions)
	{
		// draw
		Renderer::get().draw(
			it.second.x, it.second.y,
			5.0f, 5.0f, // size
			0.0f, // rotate angle
			"throwablePrimitive",
			"rockTexture", // nu prea conteaza
			glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f,
			1.0f * (count + 1) / currentStoredPositionsSize
		);

		++count;
	}

	Renderer::get().draw(
		this->posCenterX, this->posCenterY,
		this->currentWidth, this->currentHeight,
		this->rotateAngle,
		this->primitiveName,
		this->textureName,
		this->color,
		this->textureBlendFactor,
		this->backgroundBlendFactor
	);
}

bool BirdEntity::isInCollisionWithThrowable()
{
	float distanceBetweenCentersSquared =
		(this->posCenterX - ThrowableEntity::get().getPosCenterX()) * (this->posCenterX - ThrowableEntity::get().getPosCenterX()) +
		(this->posCenterY - ThrowableEntity::get().getPosCenterY()) * (this->posCenterY - ThrowableEntity::get().getPosCenterY());

	return distanceBetweenCentersSquared < ThrowableEntity::get().getRadius() * ThrowableEntity::get().getRadius();
}

void BirdEntity::update()
{
	this->currentWidth = this->width;
	this->currentHeight = this->height;

	if (this->status == BirdEntity::Status::FALLING)
	{
		this->speed.y -= this->gravity * GlobalClock::get().getDeltaTime();

		this->posCenterX += this->speed.x * GlobalClock::get().getDeltaTime();
		this->posCenterY += this->speed.y * GlobalClock::get().getDeltaTime();

		this->rotateAngle = 100.0f * this->rotationDirectionFalling * GlobalClock::get().getCurrentTime();
	}

	if (this->status == BirdEntity::Status::FLYING)
	{
		if (ThrowableEntity::get().getStatus() == ThrowableEntity::Status::IN_AIR)
		{
			float timeSinceLaunch = GlobalClock::get().getCurrentTime() - ThrowableEntity::get().getLaunchTime();

			if (std::abs((ThrowableEntity::get().getLaunchDuration() / 2.0f) - timeSinceLaunch) < ThrowableEntity::get().getLaunchDuration() * this->collisionEpsilon
				&& this->isInCollisionWithThrowable())
			{
				this->status = BirdEntity::Status::FALLING;
				// this->speed.y = 0.0f;
				// this->speed.x = 0.0f;
			}
			else // bila e in aer, nu stim unde, dar pasarea nu a fost lovita
			{
				GLfloat targetPosX = ThrowableEntity::get().getTargetPosX();
				GLfloat targetPosY = ThrowableEntity::get().getTargetPosY();

				float distanceTargetX = targetPosX - this->posCenterX;
				float distanceTargetY = targetPosY - this->posCenterY;

				float crossProductSign = glm::sign(distanceTargetX * this->speed.y - this->speed.x * distanceTargetY);
				float scaleSign = -1.0f * crossProductSign * this->rotationDirectionFlying;

				// scaleSign = -1 = micsorare elipsa, scaleSign = 1 = marire elipsa
				// -1 = micsoram ellipseScale
				// 1 = marim ellipseScale
				this->ellipseScale += scaleSign * this->ellipseSpeedScale * this->speedScalar * GlobalClock::get().getDeltaTime();
			}
		}
		else // bila nu e in aer
		{
			if (this->ellipseScale > 1.0f)
				this->ellipseScale = std::max(1.0f, this->ellipseScale - this->ellipseSpeedScale * this->speedScalar * GlobalClock::get().getDeltaTime());
			else
				this->ellipseScale = std::min(1.0f, this->ellipseScale + this->ellipseSpeedScale * this->speedScalar * GlobalClock::get().getDeltaTime());
		}
	}

	if (this->status == BirdEntity::Status::FLYING)
	{
		this->posCenterX = this->centerXEllipse + this->ellipseScale * this->aEllipse * glm::cos(glm::radians(this->rotationDirectionFlying * (this->timeOffset + this->speedScalar * GlobalClock::get().getCurrentTime())));
		this->posCenterY = this->centerYEllipse + this->ellipseScale * this->bEllipse * glm::sin(glm::radians(this->rotationDirectionFlying * (this->timeOffset + this->speedScalar * GlobalClock::get().getCurrentTime())));

		float dX = this->posCenterX - this->centerXEllipse;
		float dY = this->posCenterY - this->centerYEllipse;

		float dXPerpendicular = -dY * this->rotationDirectionFlying + dX * (this->ellipseScale - 1.0f);
		float dYPerpendicular = dX * this->rotationDirectionFlying + dY * (this->ellipseScale - 1.0f);

		float normPerpendicular = glm::sqrt(dXPerpendicular * dXPerpendicular + dYPerpendicular * dYPerpendicular);
		float dXNormalizedPerpendicular = dXPerpendicular / normPerpendicular;
		float dYNormalizedPerpendicular = dYPerpendicular / normPerpendicular;

		this->rotateAngle = (glm::degrees((glm::acos(1.0f * dXNormalizedPerpendicular + 0.0f * dYNormalizedPerpendicular)))) * glm::sign(dYNormalizedPerpendicular) + 90.0f;

		this->speed.x = this->speedScalar * dXNormalizedPerpendicular;
		this->speed.y = this->speedScalar * dYNormalizedPerpendicular;

		this->currentWidth = this->width + 20.0f * glm::sin(glm::radians(10.0f * this->timeOffset + 10.0f * this->speedScalar * GlobalClock::get().getCurrentTime())); // INFO: valori hardcodate aici
	}

	if (GlobalClock::get().getCurrentTime() - this->lastTimeAddedStoredPosition > this->timeBetweenStoredPositions)
	{
		this->storedPositions[totalNumPositions++] = glm::vec2(this->posCenterX, this->posCenterY);
		if (this->storedPositions.size() > this->MAX_STORED_POSITIONS)
			this->storedPositions.erase(this->storedPositions.begin());

		this->lastTimeAddedStoredPosition = GlobalClock::get().getCurrentTime();
	}
}