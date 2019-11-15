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

		if (ImGui::CollapsingHeader("Transform"))
		{
			float position[3];
			position[0] = GO_Inspector->transform->GetPosition().x;
			position[1] = GO_Inspector->transform->GetPosition().y;
			position[2] = GO_Inspector->transform->GetPosition().z;
			
			float rotation[3];
			rotation[0] = GO_Inspector->transform->GetRotationEuler().x;
			rotation[1] = GO_Inspector->transform->GetRotationEuler().y;
			rotation[2] = GO_Inspector->transform->GetRotationEuler().z;

			float scale[3];
			scale[0] = GO_Inspector->transform->GetScale().x;
			scale[1] = GO_Inspector->transform->GetScale().y;
			scale[2] = GO_Inspector->transform->GetScale().z;
			
			ImGui::InputFloat3("Position", position);
			ImGui::InputFloat3("Rotation", rotation);
			ImGui::InputFloat3("Scale", scale);
		}

		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::Text("Vertices ID: %d", GO_Inspector->mesh->id_vertex); 
			ImGui::Text("Vertices Num: %d", GO_Inspector->mesh->num_vertex);
			ImGui::Text("Indices ID: %d", GO_Inspector->mesh->id_index); 
			ImGui::Text("Indices Num: %d", GO_Inspector->mesh->num_index);
		}

		if (ImGui::CollapsingHeader("Texture"))
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

