#include "BirdEntity.h"

#include "../../Renderer/Renderer.h"

#include "../../GlobalClock/GlobalClock.h"

#include "../ThrowableEntity/ThrowableEntity.h"

BirdEntity::BirdEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height, const std::string& primitiveName, float gravity, const BirdEntity::Status& status, float collisionEpsilon, float centerXEllipse, float centerYEllipse, float aEllipse, float bEllipse, float speedScalar, float timeOffset, float currentWidth, float currentHeight)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, width(width), height(height), primitiveName(primitiveName)
	, gravity(gravity), status(status)
	, collisionEpsilon(collisionEpsilon)
	, centerXEllipse(centerXEllipse), centerYEllipse(centerYEllipse)
	, aEllipse(aEllipse), bEllipse(bEllipse), speedScalar(speedScalar)
	, timeOffset(timeOffset), currentWidth(currentWidth), currentHeight(currentHeight)
{

}

BirdEntity::~BirdEntity()
{

}

void BirdEntity::draw()
{
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

		this->rotateAngle = 100.0f * GlobalClock::get().getCurrentTime();
	}

	if (this->status == BirdEntity::Status::FLYING)
	{
		if (ThrowableEntity::get().getStatus() == ThrowableEntity::Status::IN_AIR)
		{
			float timeSinceLaunch = GlobalClock::get().getCurrentTime() - ThrowableEntity::get().getLaunchTime();

			if (std::abs((ThrowableEntity::get().getLaunchDuration() / 2.0f) - timeSinceLaunch) < ThrowableEntity::get().getLaunchDuration() * this->collisionEpsilon)
			{
				if (this->isInCollisionWithThrowable())
				{
					this->status = BirdEntity::Status::FALLING;
					// this->speed.y = 0.0f;
					// this->speed.x = 0.0f;
				}
			}
		}
	}

	if (this->status == BirdEntity::Status::FLYING)
	{
		this->posCenterX = this->centerXEllipse + this->aEllipse * glm::cos(glm::radians(this->timeOffset + this->speedScalar * GlobalClock::get().getCurrentTime()));
		this->posCenterY = this->centerYEllipse + this->bEllipse * glm::sin(glm::radians(this->timeOffset + this->speedScalar * GlobalClock::get().getCurrentTime()));

		float dX = this->posCenterX - this->centerXEllipse;
		float dY = this->posCenterY - this->centerYEllipse;

		float dXPerpendicular = -dY;
		float dYPerpendicular = dX;

		float normPerpendicular = glm::sqrt(dXPerpendicular * dXPerpendicular + dYPerpendicular * dYPerpendicular);
		float dXNormalizedPerpendicular = dXPerpendicular / normPerpendicular;
		float dYNormalizedPerpendicular = dYPerpendicular / normPerpendicular;

		this->rotateAngle = (glm::degrees((glm::acos(1.0f * dXNormalizedPerpendicular + 0.0f * dYNormalizedPerpendicular)))) * glm::sign(dYNormalizedPerpendicular) + 90.0f;

		this->speed.x = this->speedScalar * dXNormalizedPerpendicular;
		this->speed.y = this->speedScalar * dYNormalizedPerpendicular;

		this->currentWidth = this->width + 20.0f * glm::sin(glm::radians(10.0f * this->timeOffset + 10.0f * this->speedScalar * GlobalClock::get().getCurrentTime())); // INFO: valori hardcodate aici
	}
}