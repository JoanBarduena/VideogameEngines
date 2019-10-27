#include "GameWindow.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

GameWindow::GameWindow() : Window()
{
}

GameWindow::~GameWindow()
{
}

bool GameWindow::Start()
{
	App->Console_Log("Creating Game Window");

	size_.x = 1024;
	size_.y = 768; 

	fbo = new FrameBuffer(); 
	fbo->Start(size_);

	return true;
}

bool GameWindow::Draw()
{
	if (App->gui->show_game_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Game");

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			App->camera->game_active = ImGui::IsWindowHovered();
		}

		new_size = ImGui::GetContentRegionAvail();


		ImGui::Image((ImTextureID)fbo->texture, ImVec2(size_.x, size_.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();
	}

	if (size_.x != new_size.x || size_.y != new_size.y)
	{
		size_ = new_size;
		fbo->Start(size_);
		App->renderer3D->OnResize(size_.x, size_.y);
	}


	fbo->Draw();

	return true;
}

bool GameWindow::CleanUp()
{
	fbo->CleanUp(); 
	delete fbo; 

	return true;
}
