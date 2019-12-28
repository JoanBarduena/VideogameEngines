#include "GameWindow.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

#include "mmgr/mmgr.h"

GameWindow::GameWindow() : Window()
{
}

GameWindow::~GameWindow()
{
}

bool GameWindow::Start()
{
	App->Console_Log("[CREATING] Game Window");

	//Wsize.x = 1024;
	//Wsize.y = 768; 

	fbo = new FBO(); 
	fbo->Start(Wsize.x, Wsize.y);

	return true;
}

bool GameWindow::Draw()
{
	/*if (App->gui->show_game_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Game");

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			App->camera->game_active = ImGui::IsWindowHovered();
		}

		Wnew_size = ImGui::GetContentRegionAvail();


		ImGui::Image((ImTextureID)fbo_b->fboTexture, ImVec2(Wsize.x, Wsize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();
	}

	if (Wsize.x != Wnew_size.x || Wsize.y != Wnew_size.y)
	{
		Wsize = Wnew_size;
		fbo_b->Start(Wsize);
		App->renderer3D->OnResize(Wsize.x, Wsize.y);
	}


	fbo_b->Draw();*/
	//fbo->Draw(); 

	ImGui::Begin("SceneWindow", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	pos_y = ImGui::GetCursorScreenPos().y;
	pos_x = ImGui::GetCursorScreenPos().x;
	width = ImGui::GetWindowWidth();
	height = ImGui::GetWindowHeight();

	Wnew_size = ImGui::GetContentRegionAvail(); 

	ImGui::Image((ImTextureID)fbo->fboTexture, ImVec2(Wsize.x, Wsize.y), ImVec2(0, 1), ImVec2(1, 0));
	Wsize = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

	worldposx = App->input->GetMouseX() - ImGui::GetCursorScreenPos().x;
	worldposy = App->input->GetMouseY() - ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y;

	ImGui::End();

	return true;
}

update_status GameWindow::PreUpdate(float dt)
{
	if (OnResize())
	{
		fbo->Start(Wsize.x, Wsize.y); 
		App->renderer3D->OnResize(Wsize.x, Wsize.y); 
	}
	fbo->Draw();
	return UPDATE_CONTINUE;
}

update_status GameWindow::PostUpdate(float dt)
{
	fbo->Undraw(); 
	return UPDATE_CONTINUE;
}

bool GameWindow::CleanUp()
{
	//fbo->CleanUp(); 
	//delete fbo; 

	return true;
}

bool GameWindow::OnResize()
{
	if (Wsize.x != Wnew_size.x || Wsize.y != Wnew_size.y)
	{
		Wnew_size = Wsize;
		return true;
	}
	else
		return false;
}
