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
	App->Console_Log("[CREATING]: Game Window");

	return true;
}

bool GameWindow::Draw()
{
	if (App->gui->show_game_window)
	{
		ImGui::Begin("Game", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		pos_y = ImGui::GetCursorScreenPos().y;
		pos_x = ImGui::GetCursorScreenPos().x;
		width = ImGui::GetWindowWidth();
		height = ImGui::GetWindowHeight();

		w_NewSize = ImGui::GetContentRegionAvail();

		ImGui::Image((ImTextureID)App->viewport->fbo_game->fboTexture, ImVec2(w_Size.x, w_Size.y), ImVec2(0, 1), ImVec2(1, 0));
		w_Size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		worldposx = App->input->GetMouseX() - ImGui::GetCursorScreenPos().x;
		worldposy = App->input->GetMouseY() - ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y;

		ImGui::End();
	}
	
	return true;
}

bool GameWindow::OnResize()
{
	if (w_Size.x != w_NewSize.x || w_Size.y != w_NewSize.y)
	{
		w_NewSize = w_Size;
		return true;
	}
	else
		return false;
}