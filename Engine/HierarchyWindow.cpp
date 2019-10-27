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

	if (App->gui->show_hierarchy_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Hierarchy");

		for (std::vector<GameObject*>::iterator iterator = App->scene_intro->game_objects.begin(); iterator != App->scene_intro->game_objects.end(); iterator++)
		{

			ImGuiTreeNodeFlags flags;
			flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

			ImGui::TreeNodeEx((*iterator)->name.data(), flags);

			if (ImGui::IsItemClicked())
				App->Console_Log("pepe");
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
