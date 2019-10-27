#pragma once
#include "Component.h"
#include "Globals.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"


class ComponentTransform : public Component
{
public: 

	ComponentTransform(GameObject* GObj);
	~ComponentTransform(); 

	//bool Enable();
	//const void SetPosition(float3 &pos);

	float3 GetPosition() const; 
	float3 GetRotationEuler() const;
	float3 GetScale() const;

	float3 Position_;
	float3 Rotation; 
	float3 Scale; 

	//float4x4 transform_local = float4x4::zero;
	//float4x4 transform_global = float4x4::zero;
};
