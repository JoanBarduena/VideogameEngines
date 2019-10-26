#include "Application.h"
#include "Globals.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "glew\include\GL\glew.h"

ModuleGui::ModuleGui(bool start_enabled) : Module(start_enabled)
{}

ModuleGui::~ModuleGui()
{}

bool ModuleGui::Init()
{
	IMGUI_CHECKVERSION();
	SDL_GL_MakeCurrent(App->window->window, App->renderer3D->context);
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

	//Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplOpenGL3_Init(); 

	ConfigurationWindow* config_w = new ConfigurationWindow(); 
	ConsoleWindow* console_w = new ConsoleWindow();

	windows.push_back(config_w); 
	windows.push_back(console_w);

	return true; 
}

bool ModuleGui::Start()
{
	bool ret = true;

	for (std::list<Window*>::const_iterator iterator = windows.begin(); iterator != windows.end(); iterator++)
	{
		ret = (*iterator)->Start();
	}

	return ret;
}

bool ModuleGui::Draw()
{
	bool ret = true; 

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	CreateMainWorkingSpace();

	for (std::list<Window*>::const_iterator iterator = windows.begin(); iterator != windows.end(); iterator++)
	{
		ret = (*iterator)->Draw();
	}

	//Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	return ret;
}

update_status ModuleGui::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{
	return exit_application;
}

update_status ModuleGui::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleGui::CleanUp()
{
	bool ret = true; 

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(App->renderer3D->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return ret;
}

void ModuleGui::CreateMainWorkingSpace()
{
	bool opt_fullscreen = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace_Demo", &p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("My_Dock_Space");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();

	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", "Esc", false, true)) { exit_application = UPDATE_STOP; }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Configuration")) { show_config_window = !show_config_window; }
			if (ImGui::MenuItem("Console")) { show_app_console = !show_app_console; }
			if (ImGui::MenuItem("RNG")) { show_random_num_window = !show_random_num_window; }
			if (ImGui::MenuItem("DemoGUI")) { show_demo_window = !show_demo_window; }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Documentation")) { App->RequestBrowser("https://github.com/JoanBarduena/VideogameEngines/wiki"); }
			if (ImGui::MenuItem("Download latest")) { App->RequestBrowser("https://github.com/JoanBarduena/VideogameEngines/releases"); }
			if (ImGui::MenuItem("Report a bug")) { App->RequestBrowser("https://github.com/JoanBarduena/VideogameEngines/issues"); }
			if (ImGui::MenuItem("About", "F1", false, true)) { show_about_modal = !show_about_modal; }
			ImGui::EndMenu();
		}
		if (show_about_modal)
		{
			ImGui::OpenPopup("About");

			if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
				ImGui::Text("The Engine engine");
				ImGui::Separator();
				ImGui::Text("This engine has been developed as part of the Game Engines subject at UPC-CITM.\n");
				ImGui::Text("by");
				ImGui::SameLine();
				if (ImGui::Button("Joan Barduena"))
					App->RequestBrowser("https://github.com/JoanBarduena");
				ImGui::SameLine();
				ImGui::Text("&");
				ImGui::SameLine();
				if (ImGui::Button("Clara Ratera"))
					App->RequestBrowser("https://github.com/RustikTie");

				ImGui::Text("3rd Party Libraries used:");
				SDL_version ver;
				SDL_GetVersion(&ver);
				ImGui::BulletText("SDL Version: %d.%d.%d.", ver.major, ver.minor, ver.patch);
				ImGui::BulletText("Dear ImGUI Version: %s", ImGui::GetVersion());
				ImGui::BulletText("MathGeoLib Version: v1.5");
				ImGui::BulletText("Glew Version: %s ", glewGetString(GLEW_VERSION));
				ImGui::BulletText("OpenGL Version: %s", glGetString(GL_VERSION));

				ImGui::Separator();

				ImGui::TextWrapped("License:\n\nMIT License\n\nCopyright (c) 2019 Lidux\n\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");


				if (ImGui::Button("OK", ImVec2(120, 0)))
				{
					show_about_modal = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		if (show_random_num_window)
		{
			ImGui::Begin("RNG Window", &show_random_num_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Random Number Generator!");

			ImGui::InputInt("Minimum", &min);
			ImGui::InputInt("Maximum", &max);

			ImGui::Text("Random number between the set interval");

			if (ImGui::Button("Click"))
				interval = pcg32i_boundedrand_r(&bounded, ((max + min) + 1) - min);
			ImGui::SameLine();
			ImGui::Text("%d", interval);

			if (ImGui::Button("Close Me"))
				show_random_num_window = false;
			ImGui::End();
		}
	}

	ImGui::EndMainMenuBar();
}