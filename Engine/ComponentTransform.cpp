#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* GObj):Component(GObj, Type::Transform)
{
	this->Position_.x = 0; 
	this->Position_.y = 0; 
	this->Position_.z = 0; 

	this->Rotation.x = 0; 
	this->Rotation.y = 0; 
	this->Rotation.z = 0; 
	
	this->Scale.x = 1; 
	this->Scale.y = 1;
	this->Scale.z = 1; 
}

ComponentTransform::~ComponentTransform()
{
}

//bool ComponentTransform::Enable()
//{
//	transform_local.SetIdentity();
//	transform_global.SetIdentity(); 
//
//	return true; 
//}
//
//const void ComponentTransform::SetPosition(float3 &pos)
//{
//	transform_local[3][0] = pos.x;
//	transform_local[3][1] = pos.y;
//	transform_local[3][2] = pos.z;
//}
//
float3 ComponentTransform::GetPosition() const 
{
	return Position_;
}

float3 ComponentTransform::GetRotationEuler() const
{
	return Rotation;
}

float3 ComponentTransform::GetScale() const
{
	/*float x = Sqrt(Pow(transform_local[0][0], 2) + Pow(transform_local[0][1], 2) + Pow(transform_local[0][2], 2));
	float y = Sqrt(Pow(transform_local[1][0], 2) + Pow(transform_local[1][1], 2) + Pow(transform_local[1][2], 2));
	float z = Sqrt(Pow(transform_local[2][0], 2) + Pow(transform_local[2][1], 2) + Pow(transform_local[2][2], 2));*/

	return Scale;
}
