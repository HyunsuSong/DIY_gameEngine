#pragma once
#include "FileManager.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

int main(void)
{
	FileManager* Mgr = new FileManager();

	Renderer* Render = new Renderer();
	Render->SetCamera_World(0, 7, 7);

	makeObject* Mecury = new makeObject();
	NonRenderObject* Cube = new NonRenderObject();
	SphereObject* Sphere = new SphereObject();

	Render->SetShader("������_20161642_vs.shader", "������_20161642_fs.shader");


	Mgr->GetData(Mecury, "�ݼ�.DDS", "sphere.obj");
	Mgr->GetData(Cube, "�¾�.DDS", "cube.obj");

	Mgr->SetObject(Mecury, 2.0f, 0.0f, 0.0f);
	Mgr->SetObject(Sphere, -1.0f, 0.0f, 0.0f);

	Render->addObject(Mecury);
	Render->addObject(Sphere);

	do 
	{
		Render->Update(Cube);

		Render->render();
	}
	while (Render->isEND());

	Render->shutDown();

	delete Cube;
	delete Sphere;
	delete Mecury;

	return 0;
}