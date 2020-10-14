#pragma once
#include "Object.h"

class RenderableObject : public Object {

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

	void SetTranslate(float x, float y, float z);
};