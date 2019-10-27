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

		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::Text("Vertices ID: %d", GO_Inspector->Comp_Mesh->id_vertex); 
			ImGui::Text("Vertices Num: %d", GO_Inspector->Comp_Mesh->num_vertex);
			ImGui::Text("Indices ID: %d", GO_Inspector->Comp_Mesh->id_index); 
			ImGui::Text("Indices Num: %d", GO_Inspector->Comp_Mesh->num_index);
		}

		if (ImGui::CollapsingHeader("Texture"))
		{
			ImGui::Text("Texture ID: %d", GO_Inspector->Comp_Texture->texture->textureID); 
			ImGui::Text("Preview:");
			ImGui::Image((ImTextureID*)GO_Inspector->Comp_Texture->texture->textureID, ImVec2(200, 200));
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

