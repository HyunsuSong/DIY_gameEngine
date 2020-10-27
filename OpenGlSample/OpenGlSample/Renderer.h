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
	GLuint LightID;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	// Initial position : on +Z
	glm::vec3 position = glm::vec3(2, 2, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	bool isStart = false;

public:

	Renderer();
	bool isEND();
	void GameStart();
	void computeMatricesFromInputs();
	void SetCamera_World(int x, int y, int z);
	void SetCamera_Lookat(int x, int y, int z);
	void SetCamera_Headup(int x, int y, int z);
	void DrawObject(RenderableObject* src);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetShader(const char* vs, const char* fs);

	void hideObject(RenderableObject* src)
	{
		a.clear();
	}

	void Update(IUpdater* src)
	{
		src->Update();
	}

	virtual void shutDown() override
	{
		Object::shutDown();

		glfwTerminate();
	}

	virtual void addObject(RenderableObject* src) override
	{
		a.push_back(src);
	}

	//ȭ�� ������ �κа� ��ü ��� �κ��� ������ >> ������ ���۰� ���� ���� �� ���� �� ����
	virtual void render() override
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		for (int i = 0; i < a.size(); i++)
		{
			if (!a.at(i)->vertices.empty())
			{
				DrawObject(a.at(i));
			}
			else
			{
				a.at(i)->collision_check = false;
			}

			GameStart();

			if (isStart)
			{
				for (int j = 1; j < a.size(); j++)
				{
					if (a.at(i)->IsCharacter == true && a.at(j)->IsCharacter == false)
					{
						if (a.at(i)->object_pos.x - a.at(j)->object_pos.x <= 2.0f
							&& a.at(i)->object_pos.x - a.at(j)->object_pos.x >= -2.0f
							&& a.at(i)->object_pos.y - a.at(j)->object_pos.y <= 2.0f
							&& a.at(i)->object_pos.y - a.at(j)->object_pos.y >= -2.0f)
						{
							a.at(j)->collision_check = true;
						}
						else
						{
							a.at(j)->collision_check = false;
						}
					}
				}

				if (a.at(i)->IsCharacter)
				{
					if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
					{
						a.at(i)->SetTranslate(0, a.at(i)->y_speed, 0);
					}

					if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
					{
						a.at(i)->SetTranslate(0, -a.at(i)->y_speed, 0);
					}

					if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
					{
						a.at(i)->SetTranslate(a.at(i)->x_speed, 0, 0);
					}

					if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
					{
						a.at(i)->SetTranslate(-a.at(i)->x_speed, 0, 0);
					}
				}

				if (a.at(i)->isMove)
				{
					a.at(i)->IsPatrol(a.at(i)->x_speed, a.at(i)->y_speed, 0);
				}
			}
		}
	}

};