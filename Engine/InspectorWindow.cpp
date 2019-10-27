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

		ImGui::End(); 
		ImGui::PopStyleVar();
	}

	return true;
}

bool InspectorWindow::CleanUp()
{
	return true;
}

