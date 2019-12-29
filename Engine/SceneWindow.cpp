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

	fbo = new FBO(); 
	fbo->Start(w_Size.x, w_Size.y);

	return true;
}

bool SceneWindow::Draw()
{
	if (App->gui->show_scene_window)
	{
		ImGui::Begin("Scene", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		pos_y = ImGui::GetCursorScreenPos().y;
		pos_x = ImGui::GetCursorScreenPos().x;
		width = ImGui::GetWindowWidth();
		height = ImGui::GetWindowHeight();

		w_NewSize = ImGui::GetContentRegionAvail();

		ImGui::Image((ImTextureID)fbo->fboTexture, ImVec2(w_Size.x, w_Size.y), ImVec2(0, 1), ImVec2(1, 0));
		w_Size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		worldposx = App->input->GetMouseX() - ImGui::GetCursorScreenPos().x;
		worldposy = App->input->GetMouseY() - ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y;

		ImGui::End();

	}	
	return true;
}

update_status SceneWindow::PreUpdate(float dt)
{
	if (this->active)
	{
		if (OnResize())
		{
			fbo->Start(w_Size.x, w_Size.y);
			App->renderer3D->OnResize(w_Size.x, w_Size.y);
		}
		fbo->Draw();
		LOG("PEE"); 
	}
	return UPDATE_CONTINUE;
}

update_status SceneWindow::PostUpdate(float dt)
{
	if (this->active)
		fbo->Undraw(); 
	return UPDATE_CONTINUE;
}

bool SceneWindow::CleanUp()
{
	fbo->CleanUp(); 
	delete fbo; 
	fbo = nullptr; 

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
