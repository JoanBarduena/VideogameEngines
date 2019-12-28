#include "ComponentImage.h"
#include "GameObject.h"
#include "Application.h"

ComponentImage::ComponentImage(GameObject* GO) :Component(GO, Type::IMAGE)
{

}

ComponentImage::~ComponentImage()
{
}

bool ComponentImage::Update()
{
	//SceneDraw();

	return false;
}

void ComponentImage::SceneDraw()
{

}
