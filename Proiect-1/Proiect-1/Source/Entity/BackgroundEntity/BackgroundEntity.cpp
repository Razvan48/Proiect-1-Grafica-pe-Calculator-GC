#include "BackgroundEntity.h"

#include <iostream>

#include "../../WindowManager/WindowManager.h"
#include "../../Renderer/Renderer.h"
#include "../../GlobalClock/GlobalClock.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BackgroundEntity::BackgroundEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height, const std::string& primitiveName)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, width(width), height(height), primitiveName(primitiveName), status(BackgroundEntity::Status::DAY)
	, dayDuration(5.0f), timeSinceLastStatusChange(0.0f)
{

}

BackgroundEntity::~BackgroundEntity()
{

}

BackgroundEntity& BackgroundEntity::get()
{
	static BackgroundEntity instance(
		WindowManager::get().getWindowWidth() / 2.0f,
		WindowManager::get().getWindowHeight() / 2.0f,
		glm::vec2(0.0f, 0.0f),
		0.0f,
		"backgroundTexture",
		glm::vec3(1.0f, 75.0f / 255.0f, 0.0f),
		0.0f,
		1.0f,
		1.0f * WindowManager::get().getWindowWidth(),
		1.0f * WindowManager::get().getWindowHeight(),
		"backgroundPrimitive"
	);
	return instance;
}

void BackgroundEntity::draw()
{
	Renderer::get().draw(
		this->posCenterX, this->posCenterY,
		this->width, this->height,
		this->rotateAngle,
		this->primitiveName,
		this->textureName,
		this->color,
		this->textureBlendFactor,
		this->backgroundBlendFactor
	);
}

void BackgroundEntity::update()
{
	this->posCenterX = WindowManager::get().getWindowWidth() / 2.0f;
	this->posCenterY = WindowManager::get().getWindowHeight() / 2.0f;
	this->width = 1.0f * WindowManager::get().getWindowWidth();
	this->height = 1.0f * WindowManager::get().getWindowHeight();

	// this->textureBlendFactor = std::min((1.0f + glm::sin(50.0f * glm::radians(GlobalClock::get().getCurrentTime()))) / 2.0f, 0.35f);
	if (this->status == BackgroundEntity::Status::DAY)
	{
		if (GlobalClock::get().getCurrentTime() - this->timeSinceLastStatusChange > this->dayDuration)
		{
			this->color = glm::vec3(1.0f, 75.0f / 255.0f, 0.0f);
			this->textureBlendFactor = std::min(this->textureBlendFactor + 0.1f * GlobalClock::get().getDeltaTime(), 0.35f);

			if (this->textureBlendFactor == 0.35f)
			{
				this->status = BackgroundEntity::Status::SUNSET;
				this->timeSinceLastStatusChange = GlobalClock::get().getCurrentTime();
			}
		}
	}
	else if (this->status == BackgroundEntity::Status::SUNSET)
	{
		this->color = glm::vec3(
			std::max(0.0f, this->color.r - 0.3f * GlobalClock::get().getDeltaTime()),
			std::max(0.0f, this->color.g - 0.3f * GlobalClock::get().getDeltaTime()),
			std::max(0.0f, this->color.b - 0.3f * GlobalClock::get().getDeltaTime())
		);
		this->textureBlendFactor = std::min(0.85f, this->textureBlendFactor + 0.1f * GlobalClock::get().getDeltaTime());

		if (this->color == glm::vec3(0.0f, 0.0f, 0.0f) && this->textureBlendFactor == 0.85f)
		{
			this->status = BackgroundEntity::Status::NIGHT;
			this->timeSinceLastStatusChange = GlobalClock::get().getCurrentTime();
		}
	}
	else if (this->status == BackgroundEntity::Status::NIGHT)
	{
		if (GlobalClock::get().getCurrentTime() - this->timeSinceLastStatusChange > this->dayDuration)
		{
			this->status = BackgroundEntity::Status::SUNRISE;
			this->timeSinceLastStatusChange = GlobalClock::get().getCurrentTime();
		}
	}
	else if (this->status == BackgroundEntity::Status::SUNRISE)
	{
		this->color = glm::vec3(
			std::min(1.0f, this->color.r + 0.1f * GlobalClock::get().getDeltaTime()),
			std::min(75.0f / 255.0f, this->color.g + 0.1f * GlobalClock::get().getDeltaTime()),
			std::min(0.0f, this->color.b + 0.1f * GlobalClock::get().getDeltaTime())
		);
		this->textureBlendFactor = std::max(0.0f, this->textureBlendFactor - 0.1f * GlobalClock::get().getDeltaTime());

		if (this->color == glm::vec3(1.0f, 75.0f / 255.0f, 0.0f) && this->textureBlendFactor == 0.0f)
		{
			this->status = BackgroundEntity::Status::DAY;
			this->timeSinceLastStatusChange = GlobalClock::get().getCurrentTime();
		}
	}
}