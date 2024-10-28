#include "ThrowableEntity.h"

#include "../../WindowManager/WindowManager.h"
#include "../../Renderer/Renderer.h"
#include "../../InputManager/InputManager.h"

#include <iostream>

ThrowableEntity::ThrowableEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float radius, GLfloat initialPosX, GLfloat initialPosY, ThrowableEntity::Status status)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, radius(radius), initialPosX(initialPosX), initialPosY(initialPosY), status(status)
{

}

ThrowableEntity& ThrowableEntity::get()
{
	static ThrowableEntity
		instance(WindowManager::get().getWindowWidth() / 2.0f,
			-WindowManager::get().getWindowHeight() / 16.0f,
			glm::vec2(0.0f, 0.0f), 0.0f, "rockTexture",
			glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.5f,
			WindowManager::get().getWindowWidth() / 4.0f,
			WindowManager::get().getWindowWidth() / 2.0f,
			-WindowManager::get().getWindowHeight() / 16.0f,
			ThrowableEntity::Status::IN_HAND);
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
		"throwablePrimitive",
		this->textureName,
		color,
		textureBlendFactor,
		backgroundBlendFactor
	);
}

void ThrowableEntity::update()
{
	if (this->status == ThrowableEntity::Status::IN_HAND)
	{
		this->posCenterX = InputManager::get().getCurrentMouseX();

		bool recentlyMouseUp = InputManager::get().recentlyMouseUp();
		if (recentlyMouseUp)
		{
			std::cout << "RELEASED" << std::endl;
			std::cout << InputManager::get().getCurrentMouseX() << " " << InputManager::get().getCurrentMouseY() << std::endl;
		}
	}
	else if (this->status == ThrowableEntity::Status::IN_AIR)
	{

	}
	else
	{
		std::cout << "Error: ThrowableEntity: update(): invalid status" << std::endl;
	}
}

