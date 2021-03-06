#include "Application.h"
#include "ComponentCanvas.h"
#include "GameObject.h"
#include "glew/include/GL/glew.h"

ComponentCanvas::ComponentCanvas(GameObject* GO, uint h, uint w) :Component(GO, Type::CANVAS)
{
	height = h; 
	width = w; 
}

ComponentCanvas::~ComponentCanvas()
{
}

bool ComponentCanvas::Update()
{
	ComponentTransform* transform = my_go->GetComponentTransform();

	glBegin(GL_LINE_LOOP);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	float3 pos = transform->position;

	glVertex3f(pos.x, pos.y, pos.z);					// Vertex 1
	glVertex3f(pos.x + width, pos.y, pos.z);			// Vertex 2
	glVertex3f(pos.x + width, pos.y + height, pos.z);	// Vertex 3 
	glVertex3f(pos.x, pos.y + height, pos.z);			// Vertex 4
														// Position Z is always the same as the canvas is on 2D, but it's necessary as it's placed on a scene 3D. 
	glEnd();

	LOG("PEPE");

	return true;
}
