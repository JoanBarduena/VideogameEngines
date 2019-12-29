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

	w_Size = { 1000, 700 }; 

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
			App->camera->Position = { 0,20,20 };
		}

		ImGui::SameLine();
		ImGui::Button("STOP");

	//	LOG("canvas: %f", App->viewport->canvas->GetComponentCanvas()->pos.x);

		if (canvas_on_camera)
		{/* 
			App->viewport->image->GetComponentTransform()->position.x = -App->camera->Position.x;
			App->viewport->image->GetComponentTransform()->position.y = -App->camera->Position.y;
			App->viewport->image->GetComponentTransform()->position.z = -App->camera->Position.z;
																	    
			App->viewport->image->GetComponentTransform()->rotation.x = -App->camera->Reference.x;
			App->viewport->image->GetComponentTransform()->rotation.y = -App->camera->Reference.y;
			App->viewport->image->GetComponentTransform()->rotation.z = -App->camera->Reference.z;

			App->viewport->image->GetComponentTransform()->SetPosition(App->viewport->image->GetComponentTransform()->position);
			App->viewport->image->GetComponentTransform()->SetQuatRotation(App->viewport->image->GetComponentTransform()->rotation);*/
		}
		 
		LOG("%f", App->camera->Position.x); 

		ImGui::Image((ImTextureID)App->viewport->fbo_scene->fboTexture, ImVec2(w_Size.x, w_Size.y), ImVec2(0, 1), ImVec2(1, 0));
		
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
