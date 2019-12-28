#include "ComponentImage.h"
#include "GameObject.h"
#include "Application.h"

ComponentImage::ComponentImage(GameObject* GO, uint h, uint w, const char* path) :Component(GO, Type::IMAGE)
{
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
	/*ComponentTransform* transform = go_ui->GetComponentTransform();

	//glBegin(GL_POLYGON);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//float3 pos = transform->GetPosition();

	//glVertex3f(pos.x, pos.y, pos.z);					// Vertex 1
	//glVertex3f(pos.x + width, pos.y, pos.z);			// Vertex 2
	//glVertex3f(pos.x + width, pos.y + height, pos.z);	// Vertex 3 
	//glVertex3f(pos.x, pos.y + height, pos.z);			// Vertex 4
	//													// Position Z is always the same as the canvas is on 2D, but it's necessary as it's placed on a scene 3D. 
	//glEnd();

	//if (parent == App->gui->inspector_w->selected_go)
	//{
	//	// Centered on the canvas
	//	ComponentTransform* transform_ = parent->GetComponentTransform();

	//	float3 pos_;
	//	pos_.x = transform_->GetPosition().x + (parent->GetComponentCanvas()->width / 2) - (width / 2);
	//	pos_.y = transform_->GetPosition().y + (parent->GetComponentCanvas()->height / 2) - (height / 2);
	//	pos_.z = transform_->GetPosition().z;

	//	//Initial position on the canvas square
	//	transform->SetPosition(pos_);
	//}*/
}
