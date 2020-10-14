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

	Mgr->SetShader("송현수_20161642_vs.shader", "송현수_20161642_fs.shader");

	Mgr->GetData(Mecury, "금성.DDS", "sphere.obj");
	Mgr->GetData(Cube, "태양.DDS", "cube.obj");

	Mgr->SetObject(Mecury, 2.0f, 0.0f, 0.0f);
	Mgr->SetObject(Sphere, -1.0f, 0.0f, 0.0f);

	do {
		Render->SetDraw(Mgr);

		Render->DrawObject(Mgr, Mecury);
		Render->DrawObject(Mgr, Sphere);
	}
	while (Mgr->isEND());

	Render->shutDown();

	Mecury->shutDown();
	Sphere->shutDown();
	Cube->shutDown();

	delete Cube;
	delete Sphere;
	delete Mecury;

	return 0;
}