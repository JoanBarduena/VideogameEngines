#include "Application.h"
#include "HierarchyWindow.h"
HierarchyWindow::HierarchyWindow()
{
}

HierarchyWindow::~HierarchyWindow()
{
}

bool HierarchyWindow::Start()
{
	return true;
}

bool HierarchyWindow::Draw()
{
	static int selection_mask = 0x02;

	if (App->gui->show_hierarchy_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Hierarchy");

		for (std::vector<GameObject*>::iterator iterator = App->scene_intro->game_objects.begin(); iterator != App->scene_intro->game_objects.end(); iterator++)
		{
			ImGui::Text((*iterator)->name.c_str()); 
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	return true;
}

bool HierarchyWindow::CleanUp()
{
	return true;
}
