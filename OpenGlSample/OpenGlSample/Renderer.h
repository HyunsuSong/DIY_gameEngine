#pragma once
#include "FileManager.h"
#include "Object.h"

class Renderer : public RenderableObject {

private:
	glm::vec3 cam_World = glm::vec3(0, 5, 7);
	glm::vec3 cam_Lookat = glm::vec3(0, 0, 0);
	glm::vec3 cam_Headup = glm::vec3(0, 1, 0);

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

public:

	Renderer();


	void SetCamera_World(int x, int y, int z);
	void SetCamera_Lookat(int x, int y, int z);
	void SetCamera_Headup(int x, int y, int z);
	void SetDraw(FileManager* src);
	void DrawObject(FileManager* src2, RenderableObject* src);

	virtual void shutDown() override
	{
		glfwTerminate();
	}
};