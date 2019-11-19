#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "Globals.h"
#include "Component.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"


class ComponentTransform : public Component
{
public: 
	ALIGN_CLASS_TO_16

	ComponentTransform(GameObject* GObj);
	~ComponentTransform(); 
	void CleanUp(); 

	//bool Enable();

	float3 GetPosition() const; 
	Quat GetQuatRotation() const;
	float3 GetScale() const;
	float3 GetEulerRotation() const;
	float4x4 GetGlobalTransform() const;

	void SetPosition(float3& new_pos);
	void SetScale(float3& sca);
	void SetEulerRotation(float3 rot);
	void SetQuatRotation(Quat rot);

	void UpdateLocalTransform();
	void UpdateTRS();
	void UpdateEulerAngles();
	void UpdateTransformInGame(const float4x4 &parent_global);

	void ResetPosition(); 
	void ResetEulerRotation(); 
	void ResetScale(); 
	void ResetALL(); 

private:

	float3 position = float3::zero;
	Quat rotation = Quat::identity; 
	float3 scale = float3::one; 
	float3 euler_rotation = float3::zero;

	float4x4 transform_local = float4x4::identity;
	float4x4 transform_global = float4x4::identity;
	float4x4 transform_global_transposed = float4x4::identity; 

public:

	bool is_transformed = false;
};

#endif //__COMPONENT_TRANSFORM_H__
