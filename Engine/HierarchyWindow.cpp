#include "Application.h"
#include "HierarchyWindow.h"

#include "mmgr/mmgr.h"

HierarchyWindow::HierarchyWindow()
{
}

HierarchyWindow::~HierarchyWindow()
{
}

bool HierarchyWindow::Start()
{
	App->Console_Log("[CREATING]: Hierarchy Window");

	return true;
}

bool HierarchyWindow::Draw()
{
	if (App->gui->show_hierarchy_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Hierarchy");

		TreeNodeHierarchy(App->scene_intro->root); 

		ImGui::End();
		ImGui::PopStyleVar();
	}

	return true;
}

bool HierarchyWindow::CleanUp()
{
	return true;
}

void HierarchyWindow::TreeNodeHierarchy(GameObject* go)
{
	static ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
	ImGuiTreeNodeFlags node_flags = flag;

	bool nodeOpen = false; 

	if (go == App->gui->inspector_w->selected_go) // Draw selected TreeNode as selected
		node_flags |= ImGuiTreeNodeFlags_Selected;

	if (go != nullptr)
	{
		if (go->active) // Active GameObjects
		{
			nodeOpen = ImGui::TreeNodeEx(go->name.c_str(), node_flags);
		}		
		else // Unactive GameObjects
		{
			ImGui::PushStyleColor(0, ImVec4(1, 1, 1, 0.5f)); //make the text grey and add [not active] 
			nodeOpen = ImGui::TreeNodeEx(go->unactive_name.c_str(), node_flags);
			ImGui::PopStyleColor();
		}	
	}
	else
		nodeOpen = ImGui::TreeNode("[NULL] Game Object"); 
		

	if (ImGui::IsItemClicked())
	{
		App->gui->inspector_w->selected_go = go; 
	}

	if (nodeOpen)
	{
		if (go->childs.size() > 0) // Draw all childs of the GO (root)
		{
			for (std::vector<GameObject*>::iterator it = go->childs.begin(); it != go->childs.end(); ++it)
			{
				if (go->active == false)
				{
					(*it)->active = false;
					(*it)->was_unactive = true;

					if (it == go->childs.end() - 1)
					{
						go->was_unactive = true;
					}
				}

				if (go->was_unactive && go->active)
				{
					(*it)->active = true;
					(*it)->was_unactive = false;
					
					if (it == go->childs.end() - 1)
					{
						go->was_unactive = false;
					}					
				}
					
				TreeNodeHierarchy(*it);
			}
		}
		ImGui::TreePop(); 
	}
}