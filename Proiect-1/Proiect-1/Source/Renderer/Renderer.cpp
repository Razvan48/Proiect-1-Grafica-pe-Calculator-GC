#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../WindowManager/WindowManager.h"
#include "../TextureManager/TextureManager.h"

Renderer::Renderer()
	: VERTEX_SHADER_PATH("Shaders/vertexShader.txt"), FRAGMENT_SHADER_PATH("Shaders/fragmentShader.txt")
	, vertexShaderSource(this->readShader(VERTEX_SHADER_PATH)), fragmentShaderSource(this->readShader(FRAGMENT_SHADER_PATH))
	, NUM_EDGES_THROWABLE_PRIMITIVE(10)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexShaderSource = this->vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	const char* fragmentShaderSource = this->fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(this->shaderProgram);

	this->transformationMatrixLocation = glGetUniformLocation(this->shaderProgram, "transformationMatrix");
	this->textureSampler2DLocation = glGetUniformLocation(this->shaderProgram, "textureSampler2D");
	// glActiveTexture(GL_TEXTURE0); // este scrisa in metoda draw()
	glUniform1i(this->textureSampler2DLocation, 0);
	this->colorLocation = glGetUniformLocation(this->shaderProgram, "color");
	this->textureBlendFactorLocation = glGetUniformLocation(this->shaderProgram, "textureBlendFactor");
	this->backgroundBlendFactorLocation = glGetUniformLocation(this->shaderProgram, "backgroundBlendFactor");

	this->generatePrimitiveBuffers("birdPrimitive");
	this->generatePrimitiveBuffers("throwablePrimitive");
	this->generatePrimitiveBuffers("backgroundPrimitive");

	// Teoretic ar fi enabled pt fiecare apel in parte, apoi glDisable(GL_BLEND);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::populateBirdPrimitive(std::vector<GLfloat>& coordinates, std::vector<GLuint>& indices)
{
	coordinates.clear();
	indices.clear();

	coordinates.push_back(0.0f);
	coordinates.push_back(0.0f);
	coordinates.push_back(0.5f);
	coordinates.push_back(0.5f);

	coordinates.push_back(-0.5f);
	coordinates.push_back(-0.5f);
	coordinates.push_back(0.0f);
	coordinates.push_back(0.0f);

	coordinates.push_back(-0.5f);
	coordinates.push_back(0.5f);
	coordinates.push_back(0.0f);
	coordinates.push_back(1.0f);

	coordinates.push_back(0.5f);
	coordinates.push_back(-0.5f);
	coordinates.push_back(1.0f);
	coordinates.push_back(0.0f);

	coordinates.push_back(0.5f);
	coordinates.push_back(0.5f);
	coordinates.push_back(1.0f);
	coordinates.push_back(1.0f);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(3);
}

void Renderer::populateThrowablePrimitive(std::vector<GLfloat>& coordinates, std::vector<GLuint>& indices)
{
	coordinates.clear();
	indices.clear();

	coordinates.push_back(0.0f);
	coordinates.push_back(0.0f);
	coordinates.push_back(0.5f);
	coordinates.push_back(0.5f);

	coordinates.push_back(0.5f);
	coordinates.push_back(0.0f);
	coordinates.push_back(1.0f);
	coordinates.push_back(0.5f);

	for (int i = 1; i <= this->NUM_EDGES_THROWABLE_PRIMITIVE; i++)
	{
		GLfloat angle = 2.0f * glm::pi<float>() * i / this->NUM_EDGES_THROWABLE_PRIMITIVE;

		coordinates.push_back(0.5f * glm::cos(angle));
		coordinates.push_back(0.5f * glm::sin(angle));
		coordinates.push_back(0.5f + 0.5f * glm::cos(angle));
		coordinates.push_back(0.5f + 0.5f * glm::sin(angle));

		int indexCurent = coordinates.size() / 4 - 1;

		indices.push_back(0);
		indices.push_back(indexCurent - 1);
		indices.push_back(indexCurent);
	}
}

void Renderer::populateBackgroundPrimitive(std::vector<GLfloat>& coordinates, std::vector<GLuint>& indices)
{
	coordinates.clear();
	indices.clear();

	coordinates.push_back(-0.5f);
	coordinates.push_back(-0.5f);
	coordinates.push_back(0.0f);
	coordinates.push_back(0.0f);

	coordinates.push_back(0.5f);
	coordinates.push_back(-0.5f);
	coordinates.push_back(1.0f);
	coordinates.push_back(0.0f);

	coordinates.push_back(-0.5f);
	coordinates.push_back(0.5f);
	coordinates.push_back(0.0f);
	coordinates.push_back(1.0f);

	coordinates.push_back(0.5f);
	coordinates.push_back(0.5f);
	coordinates.push_back(1.0f);
	coordinates.push_back(1.0f);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);
}

void Renderer::generatePrimitiveBuffers(const std::string& primitiveName)
{
	if (this->primitives.find(primitiveName) != this->primitives.end())
	{
		std::cout << "Warning: Primitive with name " << primitiveName << " already exists" << std::endl;
	}

	this->primitives[primitiveName] = std::tuple<GLuint, GLuint, GLuint, std::vector<GLfloat>, std::vector<GLuint>>();
	GLuint* VAO = &std::get<0>(this->primitives[primitiveName]);
	GLuint* VBO = &std::get<1>(this->primitives[primitiveName]);
	GLuint* EBO = &std::get<2>(this->primitives[primitiveName]);
	std::vector<GLfloat>* coordinates = &std::get<3>(this->primitives[primitiveName]);
	std::vector<GLuint>* indices = &std::get<4>(this->primitives[primitiveName]);

	if (primitiveName == "birdPrimitive")
	{
		this->populateBirdPrimitive(*coordinates, *indices);
	}
	else if (primitiveName == "throwablePrimitive")
	{
		this->populateThrowablePrimitive(*coordinates, *indices);
	}
	else if (primitiveName == "backgroundPrimitive")
	{
		this->populateBackgroundPrimitive(*coordinates, *indices);
	}
	else
	{
		std::cout << "Error: Primitive with name " << primitiveName << " not found" << std::endl;
		return;
	}

	glGenVertexArrays(1, VAO);
	glBindVertexArray(*VAO);

	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, coordinates->size() * sizeof(GLfloat), coordinates->data(), GL_STATIC_DRAW);

	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), indices->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Renderer::~Renderer()
{

}

void Renderer::releaseResources()
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	for (auto& primitive : this->primitives)
	{
		glDeleteBuffers(1, &std::get<2>(primitive.second));
		glDeleteBuffers(1, &std::get<1>(primitive.second));
		glDeleteVertexArrays(1, &std::get<0>(primitive.second));
	}

	glUseProgram(0);
	glDeleteProgram(this->shaderProgram);
}

Renderer& Renderer::get()
{
	static Renderer instance;
	return instance;
}

void Renderer::draw(GLfloat posCenterX, GLfloat posCenterY, GLfloat width, GLfloat height, GLfloat rotateAngle, const std::string& primitiveName, const std::string& textureName2D, glm::vec3 color, float textureBlendFactor, float backgroundBlendFactor)
{
	if (this->primitives.find(primitiveName) == this->primitives.end())
	{
		std::cout << "Error: Primitive with name " << primitiveName << " not found" << std::endl;
		return;
	}

	auto& primitive = this->primitives[primitiveName];

	glActiveTexture(GL_TEXTURE0); // Din cauza ca shader-ul contine o singura textura, am putea sa mutam aceasta linie in constructor-ul clasei
	glBindTexture(GL_TEXTURE_2D, TextureManager::get().getTexture(textureName2D));

	// glUseProgram(this->shaderProgram); // Nu schimbam shader-ul, deoarece avem doar unul

	glm::mat4 transformationMatrix =
		glm::ortho(0.0f, (GLfloat)WindowManager::get().getWindowWidth(), 0.0f, (GLfloat)WindowManager::get().getWindowHeight())
		* glm::translate(glm::mat4(1.0f), glm::vec3(posCenterX, posCenterY, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f))
		* glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 1.0f));

	glUniformMatrix4fv(this->transformationMatrixLocation, 1, GL_FALSE, glm::value_ptr(transformationMatrix));

	glUniform4f(this->colorLocation, color.x, color.y, color.z, 1.0f);
	glUniform1f(this->textureBlendFactorLocation, textureBlendFactor);
	glUniform1f(this->backgroundBlendFactorLocation, backgroundBlendFactor);

	glBindVertexArray(std::get<0>(primitive));
	glDrawElements(GL_TRIANGLES, std::get<4>(primitive).size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Renderer::readShader(const std::string& shaderPath)
{
	std::ifstream inputFileStream(shaderPath);
	if (!inputFileStream.is_open())
	{
		std::cout << "Error: Could not open shader file from: " << shaderPath << std::endl;
	}

	std::stringstream stringStream;
	stringStream << inputFileStream.rdbuf();

	// std::cout << "Shader file from " << shaderPath << " content: " << stringStream.str() << std::endl;

	return stringStream.str();
}