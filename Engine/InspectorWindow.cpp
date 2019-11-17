#include "InspectorWindow.h"
#include "Application.h"

InspectorWindow::InspectorWindow() : Window() {}

InspectorWindow::~InspectorWindow() {}

bool InspectorWindow::Start()
{
	App->Console_Log("Creating Inspector Window"); 
	return true; 
}

bool InspectorWindow::Draw()
{
	if (App->gui->show_inspector_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 2));
		ImGui::Begin("Inspector"); 

		//ImGui::InputText("Game Object", (char*)GO_Inspector->name.c_str(), 20, ImGuiInputTextFlags_EnterReturnsTrue);

		ImGui::Checkbox("Active", &GO_Inspector->active);

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			float3 position = GO_Inspector->transform->GetPosition(); 
			
			if (ImGui::DragFloat3("Position", (float*)&position, 0.15f))
			{
				GO_Inspector->transform->SetPosition(position);
			}

		}

		if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Vertices ID: %d", GO_Inspector->mesh->id_vertex); 
			ImGui::Text("Vertices Num: %d", GO_Inspector->mesh->num_vertex);
			ImGui::Text("Indices ID: %d", GO_Inspector->mesh->id_index); 
			ImGui::Text("Indices Num: %d", GO_Inspector->mesh->num_index);
		}

		if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Texture ID: %d", GO_Inspector->texture->texture->textureID); 
			ImGui::Text("Texture Width: %d", GO_Inspector->texture->texture->width);
			ImGui::Text("Texture Height: %d", GO_Inspector->texture->texture->height);
			ImGui::Text("Texture Path: %s", GO_Inspector->texture->texture->path.c_str());
			ImGui::Text("Preview:");
			ImGui::Image((ImTextureID*)GO_Inspector->texture->texture->textureID, ImVec2(200, 200));
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

