#include "ComponentTransform.h"

#include "mmgr/mmgr.h"

ComponentTransform::ComponentTransform(GameObject* GObj) : Component(GObj, Component::Type::Transform)
{
	transform_local = float4x4::FromTRS(position, rotation, scale);
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

Quat ComponentTransform::GetQuatRotation() const
{
	return rotation;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}

float3 ComponentTransform::GetEulerRotation() const
{
	return euler_rotation; 
}

float4x4 ComponentTransform::GetGlobalTransform() const
{
	return transform_global;
}

// ----------- Set() Functions -----------

void ComponentTransform::SetPosition(float3& new_pos)
{
	this->position = new_pos;
	UpdateLocalTransform();
}

void ComponentTransform::SetScale(float3& sca)
{
	if (sca.x > 0.0f && sca.y > 0.0f && sca.z > 0.0f)
		this->scale = sca;

	UpdateLocalTransform();
}

void ComponentTransform::SetEulerRotation(float3 rot)
{
	float3 tmp = (rot - euler_rotation) * DEGTORAD;
	Quat quaternion_rotation = Quat::FromEulerXYZ(tmp.x, tmp.y, tmp.z);
	rotation = rotation * quaternion_rotation;
	euler_rotation = rot;
	UpdateLocalTransform();
}

void ComponentTransform::SetQuatRotation(Quat rot)
{
	this->rotation = rot;
	UpdateEulerAngles();
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
	euler_rotation = rotation.ToEulerXYZ() * RADTODEG;
}

void ComponentTransform::UpdateTransformInGame(const float4x4 &parent_global)
{
	transform_global = parent_global * transform_local; 
	//transform_global_transposed = transform_global.Transposed(); 

	UpdateTRS(); 

	is_transformed = false; 
}
