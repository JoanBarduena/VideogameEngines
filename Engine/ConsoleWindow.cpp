#include "Application.h"
#include "ConsoleWindow.h"

#include "mmgr/mmgr.h"

ConsoleWindow::ConsoleWindow() : Window()
{ 
}

ConsoleWindow::~ConsoleWindow() {}

bool ConsoleWindow::Start()
{
	App->Console_Log("[CREATING]: Console Window");

	return true;
}

bool ConsoleWindow::Draw()
{
	if (App->gui->show_app_console)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		ImGui::Begin("Console");

		for (int i = 0; i < App->vector_log.size(); ++i)
		{
			ImGui::Text(App->vector_log[i].c_str());
		}
		//gui_console.Draw(); not using console.h as it never stops rendering

		if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;

		ImGui::End();
		ImGui::PopStyleVar();
	}
	
	return true;
}

bool ConsoleWindow::CleanUp()
{
	return true;
}

