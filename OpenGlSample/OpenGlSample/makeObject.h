#pragma once
#include "RenderableObject.h"

class makeObject : public RenderableObject {

public :
	void SetTranslate(float x, float y, float z);

	virtual void shutDown() override
	{
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteBuffers(1, &normalbuffer);

		glDeleteTextures(1, &Texture);
	}
};