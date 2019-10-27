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
	App->Console_Log("Creating Hierarchy Window"); 

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

			if (starts_clicked) //so the programms starts with an item clicked.
			{
				App->gui->inspector_w->GO_Inspector = (*iterator);
				starts_clicked = false; 
			}
				

			if (ImGui::IsItemClicked())
			{
				App->gui->inspector_w->GO_Inspector = (*iterator); 
			}
				
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
