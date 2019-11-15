#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* GObj) : Component(GObj, Component::Type::Transform)
{
}

ComponentTransform::~ComponentTransform()
{
}

// ----------- Get() Functions -----------

float3 ComponentTransform::GetPosition() const 
{
	return position;
}

Quat ComponentTransform::GetRotationEuler() const
{
	return rotation;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}

// ----------- Set() Functions -----------

const void ComponentTransform::SetPosition(float3& new_pos)
{
	position = new_pos;
	UpdateLocalTransform();
}

void ComponentTransform::UpdateLocalTransform()
{
	transform_local = float4x4::FromTRS(position, rotation, scale);
	is_transformed = true; 
}
