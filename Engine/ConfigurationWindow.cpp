#include "Application.h"
#include "Globals.h"
#include "ConfigurationWindow.h"

#include "mmgr\mmgr.h"
#include "Assimp/include/version.h"
#include "rapidjson/rapidjson.h"
#define RAPIDJSON_VERSION_STRING \
  RAPIDJSON_STRINGIFY(RAPIDJSON_MAJOR_VERSION.RAPIDJSON_MINOR_VERSION.RAPIDJSON_PATCH_VERSION)

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
	if (App->gui->show_config_window)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 0));
		ImGui::Begin("Configuration");
		ImGui::Text("Options");
		ImGui::Separator();

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::InputText("Engine", TITLE, 30);
			ImGui::InputText("Organization", ORGANIZATION, 50);

			//Framerate
			ImGui::PlotHistogram("##framerate", &App->fps[0], App->fps.size(), 0, "Framerate", 0.0f, 100.0f, ImVec2(310, 100));
			ImGui::Text("Framerate: %.1f", App->fps[App->fps.size() - 1]);

			//Memory Consumption
			sMStats stats = m_getMemoryStatistics();
			memory.push_back((float)stats.totalReportedMemory);
			if (memory.size() > MEMORY_LOG_SIZE)
			{
				memory.erase(memory.begin());
			}		

			ImGui::PlotHistogram("##memory", &memory[0], memory.size(), 0, "Memory Consumption", 0.0f, (float)stats.totalReportedMemory*1.2f, ImVec2(310, 100));
			ImGui::Text("Total Reported: %u", stats.totalReportedMemory);
			ImGui::Text("Total Actual: %u", stats.totalActualMemory);
			ImGui::Text("Peak Reported: %u", stats.peakReportedMemory);
			ImGui::Text("Peak Actual: %u", stats.peakActualMemory);
			ImGui::Text("Accumulated Reported: %u", stats.accumulatedReportedMemory);
			ImGui::Text("Accumulated Actual: %u", stats.accumulatedActualMemory);
			ImGui::Text("Accumulated Alloc Unit Count: %u", stats.accumulatedAllocUnitCount);
			ImGui::Text("Total Alloc Unit Count: %u", stats.totalAllocUnitCount);
			ImGui::Text("Peak Alloc Unit Count: %u", stats.peakAllocUnitCount);
		}

		if (ImGui::CollapsingHeader("Window"))
		{
			if (ImGui::SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f))
				App->window->SetBrightness(App->window->brightness);

			if (ImGui::SliderInt("Width", &App->window->width, 600, 1920));
			App->window->SetWindowSize(App->window->width, App->window->height);

			if (ImGui::SliderInt("Height", &App->window->height, 400, 1080));
			App->window->SetWindowSize(App->window->width, App->window->height);

			if (ImGui::Checkbox("Fullscreen", &App->window->fullscreen))
				App->window->SetFullscreen(App->window->fullscreen);

			ImGui::SameLine();

			if (ImGui::Checkbox("Resizable", &App->window->resizable))
				App->window->SetResizable(App->window->resizable);

			if (ImGui::Checkbox("Borderless", &App->window->borderless))
				App->window->SetBorderless(App->window->borderless);

			ImGui::SameLine();

			if (ImGui::Checkbox("Full Desktop", &App->window->fullscreendesktop))
				App->window->SetFullscreenDesktop(App->window->fullscreendesktop);
		}

		if (ImGui::CollapsingHeader("Camera"))
		{
			if (ImGui::SliderFloat("Sensitivity", &App->camera->Sensitivity, 0.0f, 10.0f));
		}
		if (ImGui::CollapsingHeader("Hardware and Software"))
		{
			
			ImGui::Text("CPUs:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", cpu_count);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "(Cache: %dkb)", cpu_cache);

			ImGui::Text("System RAM:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dGb", system_ram);

			ImGui::Text("Caps:");
			ImGui::SameLine();
			if (RDTSC) { ImGui::TextColored(ImVec4(1, 1, 0, 1), "RDTSC", RDTSC); }
			ImGui::SameLine();
			if (MMX) { ImGui::TextColored(ImVec4(1, 1, 0, 1), "MMX", MMX); }

			ImGui::Separator();

			ImGui::Text("3rd Party Libraries used:");
			ImGui::BulletText("ASSIMP Version: %i.%i.%i", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
			ImGui::BulletText("Dear ImGUI Version: %s", ImGui::GetVersion());
			ImGui::BulletText("DevIL Version: 1.8.0");
			ImGui::BulletText("Glew Version: %s ", glewGetString(GLEW_VERSION));
			ImGui::BulletText("MathGeoLib Version: v1.5");
			ImGui::BulletText("OpenGL Version: %s", glGetString(GL_VERSION));
			ImGui::BulletText("RapidJSON Version: %s", RAPIDJSON_VERSION_STRING); //it works don't know why it marks it as undefined
			SDL_version ver;
			SDL_GetVersion(&ver);
			ImGui::BulletText("SDL Version: %d.%d.%d.", ver.major, ver.minor, ver.patch);
			

		}
		if (ImGui::CollapsingHeader("OpenGL"))
		{
			ImGui::Checkbox("DEPTH TEST", &gl_depth_test);
			SetGLEnum(gl_depth_test, GL_DEPTH_TEST);

			ImGui::Checkbox("CULL FACE", &gl_cull_face);
			SetGLEnum(gl_cull_face, GL_CULL_FACE);

			ImGui::Checkbox("LIGHTING", &gl_lighting);
			SetGLEnum(gl_lighting, GL_LIGHTING);

			ImGui::Checkbox("COLOR MATERIAL", &gl_color_material);
			SetGLEnum(gl_color_material, GL_COLOR_MATERIAL);

			ImGui::Checkbox("TEXTURE 2D", &gl_texture_2D);
			SetGLEnum(gl_texture_2D, GL_TEXTURE_2D);
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
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