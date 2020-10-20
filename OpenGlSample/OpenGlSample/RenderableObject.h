#pragma once
#include "Object.h"

class RenderableObject : public Object {

public:
	void SetTranslate(float x, float y, float z);

	virtual void shutDown() override 
	{
		Object::shutDown();
	}
};