#pragma once

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
private:
	Renderer();
	~Renderer();
	Renderer(const Renderer& other) = delete;
	Renderer& operator= (const Renderer& other) = delete;
	Renderer(const Renderer&& other) = delete;
	Renderer& operator= (const Renderer&& other) = delete;

	const std::string VERTEX_SHADER_PATH;
	const std::string FRAGMENT_SHADER_PATH;

	std::string readShader(const std::string& shaderPath);
	const std::string vertexShaderSource;
	const std::string fragmentShaderSource;

	GLuint shaderProgram;

	std::map<std::string, std::tuple<GLuint, GLuint, GLuint, std::vector<GLfloat>, std::vector<GLuint>>> primitives;

	GLint transformationMatrixLocation;
	GLint textureSampler2DLocation;
	GLint colorLocation;
	GLint textureBlendFactorLocation;
	GLint backgroundBlendFactorLocation;

	void populateBirdPrimitive(std::vector<GLfloat>& coordinates, std::vector<GLuint>& indices);
	const int NUM_EDGES_THROWABLE_PRIMITIVE;
	void populateThrowablePrimitive(std::vector<GLfloat>& coordinates, std::vector<GLuint>& indices);
	void populateBackgroundPrimitive(std::vector<GLfloat>& coordinates, std::vector<GLuint>& indices);

	void generatePrimitiveBuffers(const std::string& primitiveName);

public:
	static Renderer& get();

	void draw(GLfloat posCenterX, GLfloat posCenterY, GLfloat width, GLfloat height, GLfloat rotateAngle, const std::string& primitiveName, const std::string& textureName2D, glm::vec3 color, float textureBlendFactor, float backgroundBlendFactor);

	inline const std::string& getVertexShaderPath() const { return this->VERTEX_SHADER_PATH; }
	inline const std::string& getFragmentShaderPath() const { return this->FRAGMENT_SHADER_PATH; }

	void releaseResources();
};