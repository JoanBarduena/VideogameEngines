#include "ComponentImage.h"
#include "GameObject.h"
#include "Application.h"

ComponentImage::ComponentImage(GameObject* GO, uint h, uint w, const char* path) :ComponentUI(GO, TypeUI::UI_Image, h, w)
{
	ComponentTexture* text = go_ui->GetComponentTexture();
	//text->texture = App->Mtexture->LoadTexturePath(path);

	height = h;
	width = w;
}

ComponentImage::~ComponentImage()
{
}

bool ComponentImage::Update()
{
	SceneDraw();

	return false;
}

void ComponentImage::SceneDraw()
{
	ComponentTransform* transform = go_ui->GetComponentTransform();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	float3 pos = transform->GetPosition();

	glVertex3f(pos.x, pos.y, pos.z);					// Vertex 1
	glVertex3f(pos.x + width, pos.y, pos.z);			// Vertex 2
	glVertex3f(pos.x + width, pos.y + height, pos.z);	// Vertex 3 
	glVertex3f(pos.x, pos.y + height, pos.z);			// Vertex 4
														// Position Z is always the same as the canvas is on 2D, but it's necessary as it's placed on a scene 3D. 

	glEnd();
}
