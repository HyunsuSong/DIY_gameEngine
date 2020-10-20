#pragma once
#include <vector>
#include "ICleanUp.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Object : public ICleanUp {

private:

public:
	bool res;
	GLuint Texture;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	glm::mat4 Trans_Model = glm::mat4(1.0);

	virtual void shutDown() override
	{
		vertices.clear();
		uvs.clear();
		normals.clear();

		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteBuffers(1, &normalbuffer);

		glDeleteTextures(1, &Texture);
	}
};