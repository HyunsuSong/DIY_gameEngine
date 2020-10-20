#pragma once
#include "FileManager.h"
#include "Object.h"
#include "IRender.h"
#include "IUpdater.h"

class Renderer : public RenderableObject, public IRender {

private:
	std::vector<RenderableObject*> a;

	glm::vec3 cam_World = glm::vec3(0, 5, 7);
	glm::vec3 cam_Lookat = glm::vec3(0, 0, 0);
	glm::vec3 cam_Headup = glm::vec3(0, 1, 0);

	GLFWwindow* window;
	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint TextureID;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

public:

	Renderer();
	bool isEND();

	void SetCamera_World(int x, int y, int z);
	void SetCamera_Lookat(int x, int y, int z);
	void SetCamera_Headup(int x, int y, int z);
	void DrawObject(RenderableObject* src);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetShader(const char* vs, const char* fs);

	virtual void shutDown() override
	{
		Object::shutDown();

		glfwTerminate();
	}

	virtual void addObject(RenderableObject* src) override
	{
		a.push_back(src);
	}

	virtual void render() override
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		for (int i = 0; i < a.size(); i++)
		{
			DrawObject(a.at(i));
		}
	}

	void Update(IUpdater* src)
	{
		src->Update();
	}
};