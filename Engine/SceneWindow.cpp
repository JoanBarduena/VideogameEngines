#include "SceneWindow.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

#include "mmgr/mmgr.h"

SceneWindow::SceneWindow() : Window()
{
}

SceneWindow::~SceneWindow()
{
}

bool SceneWindow::Start()
{
	App->Console_Log("[CREATING]: Scene Window");

	return true;
}

bool SceneWindow::Draw()
{
	if (App->gui->show_scene_window)
	{
		ImGui::Begin("Scene", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		/*ComponentCanvas* canvas = App->viewport->canvas->GetComponentCanvas(); 

		lookAtCanvas.x = canvas->pos.x + (canvas->width / 2);
		lookAtCanvas.y = canvas->pos.y + (canvas->height / 2); 
		lookAtCanvas.z = canvas->pos.z - 30; */

		pos_y = ImGui::GetCursorScreenPos().y;
		pos_x = ImGui::GetCursorScreenPos().x;
		width = ImGui::GetWindowWidth();
		height = ImGui::GetWindowHeight();

		w_NewSize = ImGui::GetContentRegionAvail();
		 
		if (ImGui::Button("PLAY"))
		{
			canvas_on_camera = true; 
		}
		ImGui::SameLine();
		ImGui::Button("STOP");

		LOG("camera: %f", App->camera->Position.x);
		LOG("canvas: %f", App->viewport->canvas->GetComponentCanvas()->pos.x);

		if (canvas_on_camera)
		{ 
			App->viewport->canvas->GetComponentCanvas()->pos.x = -App->camera->Position.x;
			App->viewport->canvas->GetComponentCanvas()->pos.y = -App->camera->Position.y;
			App->viewport->canvas->GetComponentCanvas()->pos.z = -App->camera->Position.z;
			App->viewport->canvas->GetComponentTransform()->SetPosition(App->viewport->canvas->GetComponentCanvas()->pos);
		}
		 
		LOG("%f", App->camera->Position.x); 

		ImGui::Image((ImTextureID)App->viewport->fbo_scene->fboTexture, ImVec2(w_Size.x, w_Size.y), ImVec2(0, 1), ImVec2(1, 0));
		w_Size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		worldposx = App->input->GetMouseX() - ImGui::GetCursorScreenPos().x;
		worldposy = App->input->GetMouseY() - ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y;

		ImGui::End();
	}	
	return true;
}

bool SceneWindow::OnResize()
{
	if (w_Size.x != w_NewSize.x || w_Size.y != w_NewSize.y)
	{
		w_NewSize = w_Size;
		return true;
	}
	else
		return false;
}
