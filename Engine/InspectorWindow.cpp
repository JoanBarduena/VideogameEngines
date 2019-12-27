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
			ImGui::TextColored(ImVec4(1, 0.9, 0, 1), selected_go->name.c_str());

			ImGui::Checkbox("Active", &selected_go->active);
			if (ImGui::Checkbox("Static", &selected_go->go_static))
				App->scene_intro->SetGameObjectStatic(selected_go); 

			if (selected_go->active)
			{
				if (ImGui::CollapsingHeader("Transformation", ImGuiTreeNodeFlags_DefaultOpen) && selected_go->GetComponentTransform() != nullptr)
				{
					ComponentTransform* transform = selected_go->GetComponentTransform(); 

					ImGui::Text("Reset:");
					
					if (ImGui::Button("Position", ImVec2(0, 0)) && !selected_go->go_static) // Reset initial position
					{
						transform->SetPosition(selected_go->reset_pos); 
					}
					
					if (ImGui::Button("Rotation", ImVec2(0, 0)) && !selected_go->go_static) // Reset initial rotation
					{
						transform->SetQuatRotation(selected_go->reset_rotation); 
					}
					
					if (ImGui::Button("Scale", ImVec2(0, 0)) && !selected_go->go_static) // Reset initial scale
					{
						transform->SetScale(selected_go->reset_scale); 
					}
					
					if (ImGui::Button("All Transformations", ImVec2(0, 0)) && !selected_go->go_static) // Reset ALL initial transformations
					{
						transform->SetPosition(selected_go->reset_pos);
						transform->SetQuatRotation(selected_go->reset_rotation);
						transform->SetScale(selected_go->reset_scale);
					}

					ImGui::Text("");
					float3 position = transform->GetPosition();

					if (ImGui::DragFloat3("Position", (float*)&position, 0.05f) && !selected_go->go_static)
					{
						transform->SetPosition(position);
					}

					float3 rotation = transform->GetEulerRotation();

					if (ImGui::DragFloat3("Rotation", (float*)&rotation, 0.20f) && !selected_go->go_static)
					{
						transform->SetEulerRotation(rotation); 
					}

					float3 scale = transform->GetScale(); 

					if (ImGui::DragFloat3("Scale", (float*)&scale, 0.10f) && !selected_go->go_static)
					{
						transform->SetScale(scale);
					}
				}

				if (selected_go->GetComponentMesh() != nullptr)
				{
					if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ComponentMesh* mesh = selected_go->GetComponentMesh();

						ImGui::Text("Vertices ID: %d", mesh->id_vertex);
						ImGui::Text("Vertices Num: %d", mesh->num_vertex);
						ImGui::Text("Indices ID: %d", mesh->id_index);
						ImGui::Text("Indices Num: %d", mesh->num_index);
					}
				}
				if (selected_go->GetComponentTexture() != nullptr)
				{
					if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ComponentTexture* c_texture = selected_go->GetComponentTexture();

						ImGui::Text("Texture ID: %d", c_texture->texture.textureID);
						ImGui::Text("Texture Width: %d", c_texture->texture.width);
						ImGui::Text("Texture Height: %d", c_texture->texture.height);
						ImGui::Text("Texture Path: %s", c_texture->texture.path.c_str());
						ImGui::Text("Preview:");
						ImGui::Image((ImTextureID*)c_texture->texture.textureID, ImVec2(200, 200));
					}
				}	
			}
			if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN && selected_go != nullptr)
			{
				App->Console_Log("[DELETED GAME OBJECT]: %s", selected_go->name.data());
				selected_go->DeleteGO(selected_go, true);
				selected_go = nullptr;
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

