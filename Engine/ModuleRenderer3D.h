#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "ModuleGeometry.h"

#define MAX_LIGHTS 8

template <typename Container>
struct RenderBox
{
	RenderBox(const Container* container, const Color& color) : container(container), color(color)
	{}

	const Container* container;
	Color color;
};

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true); 
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void DrawMesh(GameObject* GO);

	void AddAABB(const AABB& container, const Color& color);
	void DrawAABB();

	std::vector<RenderBox<AABB>> aabbs;
	bool render_aabb = false; 

	template <typename Box>
	static void DrawContainer(const Box& box, Color color)
	{
		float3 corners[8];
		box.GetCornerPoints(corners);
		DrawContainerCube(corners, color);
	}

	static void DrawContainerCube(const float3* corners, Color color); 

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};