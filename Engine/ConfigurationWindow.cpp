#include "Application.h"
#include "ConfigurationWindow.h"

ConfigurationWindow::ConfigurationWindow() : Window()
{ 
}

ConfigurationWindow::~ConfigurationWindow() {}


bool ConfigurationWindow::Start()
{
	App->Console_Log("Creating Configuration Window"); 

	cpu_count = SDL_GetCPUCount();
	system_ram = SDL_GetSystemRAM();
	cpu_cache = SDL_GetCPUCacheLineSize();
	RDTSC = SDL_HasRDTSC();
	MMX = SDL_HasMMX();

	return true; 
}

bool ConfigurationWindow::Draw()
{
	//if (App->gui->show_config_window)
	//{
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 0));
	//	ImGui::Begin("Configuration");
	//	ImGui::Text("Options");
	//	ImGui::Separator();

	//	if (ImGui::CollapsingHeader("Application"))
	//	{
	//		ImGui::InputText("Engine", TITLE, 30);
	//		ImGui::InputText("Organization", ORGANIZATION, 50);
	//	}

	//	if (ImGui::CollapsingHeader("Window"))
	//	{
	//		if (ImGui::SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f))
	//			App->window->SetBrightness(App->window->brightness);

	//		if (ImGui::SliderInt("Width", &App->window->width, 600, 1920));
	//		App->window->SetWindowSize(App->window->width, App->window->height);

	//		if (ImGui::SliderInt("Height", &App->window->height, 400, 1080));
	//		App->window->SetWindowSize(App->window->width, App->window->height);

	//		if (ImGui::Checkbox("Fullscreen", &App->window->fullscreen))
	//			App->window->SetFullscreen(App->window->fullscreen);

	//		ImGui::SameLine();

	//		if (ImGui::Checkbox("Resizable", &App->window->resizable))
	//			App->window->SetResizable(App->window->resizable);

	//		if (ImGui::Checkbox("Borderless", &App->window->borderless))
	//			App->window->SetBorderless(App->window->borderless);

	//		ImGui::SameLine();

	//		if (ImGui::Checkbox("Full Desktop", &App->window->fullscreendesktop))
	//			App->window->SetFullscreenDesktop(App->window->fullscreendesktop);
	//	}
	//	if (ImGui::CollapsingHeader("Hardware"))
	//	{
	//		ImGui::Text("SDL Version:");
	//		ImGui::Separator();

	//		ImGui::Text("CPUs:");
	//		ImGui::SameLine();
	//		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", cpu_count);
	//		ImGui::SameLine();
	//		ImGui::TextColored(ImVec4(1, 1, 0, 1), "(Cache: %dkb)", cpu_cache);

	//		ImGui::Text("System RAM:");
	//		ImGui::SameLine();
	//		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dGb", system_ram);

	//		ImGui::Text("Caps:");
	//		ImGui::SameLine();
	//		if (RDTSC) { ImGui::TextColored(ImVec4(1, 1, 0, 1), "RDTSC", RDTSC); }
	//		ImGui::SameLine();
	//		if (MMX) { ImGui::TextColored(ImVec4(1, 1, 0, 1), "MMX", MMX); }

	//		ImGui::Separator();
	//	}
	//	if (ImGui::CollapsingHeader("OpenGL"))
	//	{
	//		ImGui::Checkbox("DEPTH TEST", &gl_depth_test);
	//		SetGLEnum(gl_depth_test, GL_DEPTH_TEST);

	//		ImGui::Checkbox("CULL FACE", &gl_cull_face);
	//		SetGLEnum(gl_cull_face, GL_CULL_FACE);

	//		ImGui::Checkbox("LIGHTING", &gl_lighting);
	//		SetGLEnum(gl_lighting, GL_LIGHTING);

	//		ImGui::Checkbox("COLOR MATERIAL", &gl_color_material);
	//		SetGLEnum(gl_color_material, GL_COLOR_MATERIAL);

	//		ImGui::Checkbox("TEXTURE 2D", &gl_texture_2D);
	//		SetGLEnum(gl_texture_2D, GL_TEXTURE_2D);
	//	}
	//	ImGui::End();
	//	ImGui::PopStyleVar();
	//}
	return true;
}

void ConfigurationWindow::SetGLEnum(bool is_enabled, GLenum cap)
{
	if (is_enabled)
		glEnable(cap);
	else
		glDisable(cap);
}

bool ConfigurationWindow::CleanUp()
{
	return true; 
}