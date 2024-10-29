#include "ThrowableEntity.h"

#include "../../WindowManager/WindowManager.h"
#include "../../Renderer/Renderer.h"
#include "../../InputManager/InputManager.h"
#include "../../GlobalClock/GlobalClock.h"
#include "../../RandomGenerator/RandomGenerator.h"

#include <iostream>

ThrowableEntity::ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float radius, float initialRadius, GLfloat initialPosX, GLfloat initialPosY, ThrowableEntity::Status status, const std::string& primitiveName, float launchTime, float launchDuration, float currentInitialLaunchSpeed)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, radius(radius), initialRadius(initialRadius), initialPosX(initialPosX), initialPosY(initialPosY)
	, status(status), primitiveName(primitiveName), launchTime(launchTime)
	, launchDuration(launchDuration), currentInitialLaunchSpeed(currentInitialLaunchSpeed), rotationDirection(1)
	, targetPosX(0.0f), targetPosY(0.0f)
{

}

ThrowableEntity& ThrowableEntity::get()
{
	static ThrowableEntity
		instance(WindowManager::get().getWindowWidth() / 2.0f,
			-WindowManager::get().getWindowHeight() / 32.0f,
			glm::vec2(0.0f, 0.0f), 0.0f, "rockTexture",
			glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.5f,
			WindowManager::get().getWindowWidth() / 16.0f, // radius
			WindowManager::get().getWindowWidth() / 16.0f, // initial radius
			WindowManager::get().getWindowWidth() / 2.0f,
			-WindowManager::get().getWindowHeight() / 32.0f,
			ThrowableEntity::Status::IN_HAND, "throwablePrimitive", 0.0f, 1.0f, 0.0f);
	return instance;
}

ThrowableEntity::~ThrowableEntity()
{

}

void ThrowableEntity::draw()
{
	Renderer::get().draw(
		this->posCenterX, this->posCenterY,
		2.0f * this->radius, 2.0f * this->radius,
		this->rotateAngle,
		this->primitiveName,
		this->textureName,
		this->color,
		this->textureBlendFactor,
		this->backgroundBlendFactor
	);
}

void ThrowableEntity::update()
{
	if (this->status == ThrowableEntity::Status::IN_HAND)
	{
		this->posCenterX = InputManager::get().getCurrentMouseX();

		bool leftMouseButtonUp = InputManager::get().getLeftMouseButtonUp();
		if (leftMouseButtonUp)
		{
			this->targetPosX = InputManager::get().getCurrentMouseX();
			this->targetPosY = InputManager::get().getCurrentMouseY();

			this->status = ThrowableEntity::Status::IN_AIR;
			this->rotationDirection = 2 * RandomGenerator::randomUniformInt(0, 1) - 1;
			this->backgroundBlendFactor = 1.0f;
			this->launchTime = GlobalClock::get().getCurrentTime();

			this->currentInitialLaunchSpeed = 4.0f * (InputManager::get().getCurrentMouseY() - this->initialPosY) / this->launchDuration;
			this->speed.y = this->currentInitialLaunchSpeed;
		}
	}
	else if (this->status == ThrowableEntity::Status::IN_AIR)
	{
		if (GlobalClock::get().getCurrentTime() - this->launchTime > this->launchDuration)
		{
			this->status = ThrowableEntity::Status::IN_HAND;
			this->backgroundBlendFactor = 0.5f;
			this->posCenterX = this->initialPosX;
			this->posCenterY = this->initialPosY;
			this->radius = this->initialRadius;

			this->currentInitialLaunchSpeed = 0.0f;

			this->speed.y = 0.0f;
		}
		else
		{
			float timeSinceLaunch = GlobalClock::get().getCurrentTime() - this->launchTime;

			this->radius = this->initialRadius *
				std::max((1.0f - (timeSinceLaunch / this->launchDuration) * (timeSinceLaunch / this->launchDuration)), 0.0f); // INFO: 2.0f e hardcodat

			this->speed.y -= 2.0f * (this->currentInitialLaunchSpeed / this->launchDuration) * GlobalClock::get().getDeltaTime();

			this->posCenterY += this->speed.y * GlobalClock::get().getDeltaTime();

			this->rotateAngle = 500.0f * this->rotationDirection * GlobalClock::get().getCurrentTime();
		}
	}
	else
	{
		std::cout << "Error: ThrowableEntity: update(): invalid status" << std::endl;
	}

	// TODO:
	this->initialRadius = WindowManager::get().getWindowWidth() / 16.0f;
}

