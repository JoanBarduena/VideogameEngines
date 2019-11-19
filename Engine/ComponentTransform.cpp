#include "ComponentTransform.h"

#include "mmgr/mmgr.h"

ComponentTransform::ComponentTransform(GameObject* GObj) : Component(GObj, Component::Type::Transform)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::CleanUp()
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

float4x4 ComponentTransform::GetGlobalTransform() const
{
	return transform_global;
}

// ----------- Set() Functions -----------

void ComponentTransform::SetPosition(float3& new_pos)
{
	position = new_pos;
	UpdateLocalTransform();
}

void ComponentTransform::UpdateLocalTransform()
{
	transform_local = float4x4::FromTRS(position, rotation, scale);
	is_transformed = true; 
}

void ComponentTransform::UpdateTRS()
{
	transform_local.Decompose(position, rotation, scale);
	UpdateEulerAngles();
}

void ComponentTransform::UpdateEulerAngles()
{
	euler_rotation = rotation.ToEulerXYZ();
	euler_rotation *= RADTODEG;
}

void ComponentTransform::UpdateTransformInGame(const float4x4 &parent_global)
{
	transform_global = parent_global * transform_local; 
	transform_global_transposed = transform_global.Transposed(); 

	UpdateTRS(); 

	is_transformed = false; 
}
