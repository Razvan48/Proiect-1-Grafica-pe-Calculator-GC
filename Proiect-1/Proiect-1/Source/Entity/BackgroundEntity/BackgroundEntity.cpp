#include "BackgroundEntity.h"

#include "../../WindowManager/WindowManager.h"

#include "../../Renderer/Renderer.h"

BackgroundEntity::BackgroundEntity(GLfloat posCenterX, GLfloat posCenterY, const glm::vec2& speed, GLfloat rotateAngle, const std::string& textureName, const glm::vec3& color, float textureBlendFactor, float backgroundBlendFactor, float width, float height)
	: Entity(posCenterX, posCenterY, speed, rotateAngle, textureName
		, color, textureBlendFactor, backgroundBlendFactor)
	, width(width), height(height)
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
		glm::vec3(1.0f, 1.0f, 1.0f),
		0.5f,
		0.5f,
		1.0f * WindowManager::get().getWindowWidth(),
		1.0f * WindowManager::get().getWindowHeight()
	);
	return instance;
}

void BackgroundEntity::draw()
{
	Renderer::get().draw(
		this->posCenterX, this->posCenterY,
		this->width, this->height,
		this->rotateAngle,
		"backgroundPrimitive",
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
}