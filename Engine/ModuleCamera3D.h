#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void ResetCamera();

	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	float mouse_sensitivity = 0.25f;
	float velocity = 10.0f;

	bool game_active = false; 
	Color background = Color(0, 0, 0, 255); 

private:

	vec3 InitialPos = vec3(0.0f, 0.0f, 100.0f);
	vec3 InitialRef = vec3(0.0f, 0.0f, 0.0f);
	vec3 OffSet = vec3(0.0f, 5.0f, 15.0f);

	mat4x4 ViewMatrix, ViewMatrixInverse;

	float speed;
};