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

	if (go == App->gui->inspector_w->selected_go)
		node_flags |= ImGuiTreeNodeFlags_Selected;

	if (go != nullptr)
	{
		if (go->active == false)
		{
			ImGui::PushStyleColor(0, ImVec4(1, 1, 1, 0.5f)); //make the text grey and add [not active] 
			nodeOpen = ImGui::TreeNodeEx(go->unactive_name.c_str(), node_flags);
			ImGui::PopStyleColor(); 
		}		
		else
			nodeOpen = ImGui::TreeNodeEx(go->name.c_str(), node_flags);
	}
	else
		nodeOpen = ImGui::TreeNode("[NULL] Game Object"); 
		

	if (ImGui::IsItemClicked())
	{
		App->gui->inspector_w->selected_go = go; 
	}

	if (nodeOpen)
	{
		if (!go->childs.empty()) 
		{
			for (std::list<GameObject*>::iterator it = go->childs.begin(); it != go->childs.end(); ++it)
			{
				TreeNodeHierarchy(*it);
			}
		}
		ImGui::TreePop(); 
	}
}