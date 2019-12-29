#include "ComponentImage.h"
#include "Application.h"

ComponentImage::ComponentImage(GameObject* GO) :Component(GO, Type::IMAGE)
{

}

ComponentImage::~ComponentImage()
{
}

bool ComponentImage::Update()
{
	return false;
}

