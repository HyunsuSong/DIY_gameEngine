#pragma once
#include "Renderer.h"

Renderer::Renderer()
{
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);

	ModelMatrix = glm::mat4(1.0);

	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
}

void Renderer::SetCamera_World(int x, int y, int z)
{
	cam_World = glm::vec3(x, y, z);
	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);
}

void Renderer::SetCamera_Lookat(int x, int y, int z)
{
	cam_Lookat = glm::vec3(x, y, z);
	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);
}

void Renderer::SetCamera_Headup(int x, int y, int z)
{
	cam_Headup = glm::vec3(x, y, z);
	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);
}

void Renderer::SetDraw(FileManager* src)
{
	glfwSwapBuffers(src->window);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(src->programID);
}

void Renderer::DrawObject(FileManager* src2, RenderableObject* src)
{
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix * src->Trans_Model;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, src->Texture);
	glUniform1i(src2->TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, src->vertexbuffer);
	glVertexAttribPointer(
		0,                 
		3,                 
		GL_FLOAT,          
		GL_FALSE,          
		0,                 
		(void*)0           
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, src->uvbuffer);
	glVertexAttribPointer(
		1,                                
		2,                                
		GL_FLOAT,                         
		GL_FALSE,                         
		0,                                
		(void*)0                          
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, src->normalbuffer);
	glVertexAttribPointer(
		2,                                
		3,                                
		GL_FLOAT,                         
		GL_FALSE,                         
		0,                                
		(void*)0                          
	);

	glUniformMatrix4fv(src2->MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, GLsizei(src->vertices.size()));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}