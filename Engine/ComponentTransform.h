#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "Component.h"
#include "Globals.h"

#include "MathGeoLib/include/MathGeoLib.h"

class ComponentTransform : public Component
{
public: 

	ComponentTransform(GameObject* GObj);
	~ComponentTransform(); 

	//bool Enable();
	const void SetPosition(float3 &new_pos);

	float3 GetPosition() const; 
	Quat GetRotationEuler() const;
	float3 GetScale() const;
	float4x4 GetGlobalTransform() const;

	void UpdateLocalTransform();
	void UpdateTRS();
	void UpdateEulerAngles();
	void UpdateTransformInGame(const float4x4 parent_global);

private:

	float3 position = float3::zero;
	Quat rotation = Quat::identity; 
	float3 scale = float3::zero; 

	float4x4 transform_local = float4x4::identity;
	float4x4 transform_global = float4x4::identity;
	float4x4 transform_global_transposed = float4x4::identity; 

	float3 euler_rotation = float3::zero; 

public:

	bool is_transformed = true;
};

#endif //__COMPONENT_TRANSFORM_H__
