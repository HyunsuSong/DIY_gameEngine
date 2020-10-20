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

	Render->SetShader("송현수_20161642_vs.shader", "송현수_20161642_fs.shader");


	Mgr->GetData(Mecury, "금성.DDS", "sphere.obj");
	Mgr->GetData(Cube, "태양.DDS", "cube.obj");

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