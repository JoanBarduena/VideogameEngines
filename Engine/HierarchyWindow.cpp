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
	static int selection_mask = (1 << 3);

	if (App->gui->show_hierarchy_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Hierarchy");

		for (std::vector<GameObject*>::iterator iterator = App->scene_intro->game_objects.begin(); iterator != App->scene_intro->game_objects.end(); iterator++)
		{
			ImGuiTreeNodeFlags node_flags;
			node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

			const bool is_selected = (selection_mask & (1 << (*iterator)->id)) != 0;

			if (is_selected)
				node_flags |= ImGuiTreeNodeFlags_Selected; 

			ImGui::TreeNodeEx((*iterator)->name.data(), node_flags);

			if (starts_clicked) //so the programms starts with an item clicked.
			{
				App->gui->inspector_w->GO_Inspector = (*iterator);
				starts_clicked = false; 
			}
				
			if (ImGui::IsItemClicked())
			{
				node_clicked = (*iterator)->id; 
				App->gui->inspector_w->GO_Inspector = (*iterator); 
			}		
		
		}

		if (node_clicked != -1)
		{
			if (ImGui::GetIO().KeyCtrl)
				selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
			else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
				selection_mask = (1 << node_clicked);           // Click to single-select
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
