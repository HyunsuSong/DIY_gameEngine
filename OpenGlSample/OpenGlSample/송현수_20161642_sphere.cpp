#pragma once
#include <stdlib.h>
#include <time.h>

#include "FileManager.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

int main(void)
{
	const int size = 20;

	srand((unsigned int)time(NULL));

	FileManager* Mgr = new FileManager();

	Renderer* Render = new Renderer();
	Render->SetCamera_World(0, 0, 20);

	makeObject* Mecury = new makeObject();
	NonRenderObject* Cube = new NonRenderObject();

	SphereObject* fast[size];
	SphereObject* slow[size];

	for (int i = 0; i < size; i++)
	{
		fast[i] = new SphereObject();
		slow[i] = new SphereObject();
		Mgr->GetData(slow[i], "달.DDS", "sphere.obj");
	}

	Render->SetShader("송현수_20161642_vs.shader", "송현수_20161642_fs.shader");


	Mgr->GetData(Mecury, "태양.DDS", "sphere.obj");
	Mgr->GetData(Cube, "태양.DDS", "cube.obj");

	Mgr->SetObjectRange(Mecury, -35, 35, -26, 26);

	Mgr->SetObject(Mecury, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < size; i++)
	{
		Mgr->RandomSetObject(fast[i], -35, 35, -26, 26);

		Mgr->RandomSetObject(slow[i], -35, 35, -26, 26);

		Mgr->SetObjectRange(slow[i], -35, 35, -26, 26);

		slow[i]->isMove = true;
	}

	Mgr->IsGliter(Mecury, true, 0.001);

	Mgr->SetCharacter(Mecury);

	Render->addObject(Mecury);

	for (int i = 0; i < size; i++)
	{
		Render->addObject(fast[i]);

	}

	for (int i = 0; i < size; i++)
	{
		Render->addObject(slow[i]);

		slow[i]->isMove = true;
	}

	do
	{
		Render->Update(Cube);

		Render->render();

		//충돌체크 반짝이 속도 증가용 지구 및 속도 감소용 달과 태양의 충돌 체크
		for (int i = 0; i < size; i++)
		{
			if (fast[i]->collision_check)
			{
				fast[i]->shutDown();

				Mecury->gliter_speed += 0.01;
			}

			if (slow[i]->collision_check)
			{
				slow[i]->shutDown();

				Mecury->gliter_speed -= 0.01;
			}
		}	
	}
	while (Render->isEND());

	Render->shutDown();

	for (int i = 0; i < size; i++)
	{
		delete fast[i];
		delete slow[i];
	}
	delete Cube;
	delete Mecury;

	return 0;
}