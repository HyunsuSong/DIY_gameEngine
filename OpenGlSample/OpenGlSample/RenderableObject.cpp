#pragma once
#include "RenderableObject.h"

void RenderableObject::SetTranslate(float x, float y, float z)
{
	Trans_Model = glm::translate(Trans_Model, glm::vec3(x, y, z));
}