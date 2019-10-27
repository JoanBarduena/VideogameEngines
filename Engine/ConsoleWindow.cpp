#include "Application.h"
#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow() : Window()
{ 
}

ConsoleWindow::~ConsoleWindow() {}

bool ConsoleWindow::Start()
{
	App->Console_Log("Creating Console Window");

	return true;
}

bool ConsoleWindow::Draw()
{
	if (App->gui->show_app_console)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 2));
		ImGui::Begin("Console");

		for (int i = 0; i < App->vector_log.size(); ++i)
		{
			ImGui::Text(App->vector_log[i].data());
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

