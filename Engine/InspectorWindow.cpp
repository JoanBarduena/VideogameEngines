#include "InspectorWindow.h"
#include "Application.h"
#include "mmgr/mmgr.h"

InspectorWindow::InspectorWindow() : Window() {}

InspectorWindow::~InspectorWindow() {}

bool InspectorWindow::Start()
{
	App->Console_Log("[CREATING]: Inspector Window"); 
	return true; 
}

bool InspectorWindow::Draw()
{
	if (App->gui->show_inspector_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 2));
		ImGui::Begin("Inspector"); 

		if (selected_go != nullptr && selected_go->id != 0)
		{
			ImGui::Checkbox("Active", &selected_go->active);

			if (selected_go->active)
			{
				if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen) && selected_go->transform != nullptr)
				{
					ImGui::Text("RESET:");
					ImGui::SameLine();
					if (ImGui::Button("Position", ImVec2(0, 0)))
					{
						selected_go->transform->ResetPosition();
					}
					ImGui::SameLine();
					if (ImGui::Button("Rotation", ImVec2(0, 0)))
					{
						selected_go->transform->ResetEulerRotation();
					}
					ImGui::SameLine();
					if (ImGui::Button("Scale", ImVec2(0, 0)))
					{
						selected_go->transform->ResetScale();
					}
					ImGui::SameLine(); 
					if (ImGui::Button("ALL", ImVec2(0, 0)))
					{
						selected_go->transform->ResetALL(); 
					}

					float3 position = selected_go->transform->GetPosition();

					if (ImGui::DragFloat3("Position", (float*)&position, 0.05f))
					{
						selected_go->transform->SetPosition(position);
					}

					float3 rotation = selected_go->transform->GetEulerRotation();

					if (ImGui::DragFloat3("Rotation", (float*)&rotation, 0.20f))
					{
						selected_go->transform->SetEulerRotation(rotation); 
					}

					float3 scale = selected_go->transform->GetScale(); 

					if (ImGui::DragFloat3("Scale", (float*)&scale, 0.10f))
					{
						selected_go->transform->SetScale(scale);
					}
				}

				if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Text("Vertices ID: %d", selected_go->mesh->id_vertex);
					ImGui::Text("Vertices Num: %d", selected_go->mesh->num_vertex);
					ImGui::Text("Indices ID: %d", selected_go->mesh->id_index);
					ImGui::Text("Indices Num: %d", selected_go->mesh->num_index);
				}

				if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Text("Texture ID: %d", selected_go->texture->texture->textureID);
					ImGui::Text("Texture Width: %d", selected_go->texture->texture->width);
					ImGui::Text("Texture Height: %d", selected_go->texture->texture->height);
					ImGui::Text("Texture Path: %s", selected_go->texture->texture->path.c_str());
					ImGui::Text("Preview:");
					ImGui::Image((ImTextureID*)selected_go->texture->texture->textureID, ImVec2(200, 200));
				}
			}
		}
		ImGui::End(); 
		ImGui::PopStyleVar();
	}

	return true;
}

bool InspectorWindow::CleanUp()
{
	return true;
}

