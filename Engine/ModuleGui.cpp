#include "Application.h"
#include "Globals.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "glew\include\GL\glew.h"

ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGui::~ModuleGui()
{}

bool ModuleGui::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	return true; 
}

bool ModuleGui::Start()
{
	bool ret = true;

	cpu_count = SDL_GetCPUCount(); 
	system_ram = SDL_GetSystemRAM(); 
	cpu_cache = SDL_GetCPUCacheLineSize(); 
	RDTSC =  SDL_HasRDTSC();
	MMX = SDL_HasMMX(); 

	return ret;
}

update_status ModuleGui::PreUpdate(float dt)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("File", true)) 
		{
			if (ImGui::MenuItem("Exit", "Esc", false, true)) { return update_status::UPDATE_STOP; }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View", true))
		{
			
			if (ImGui::MenuItem("Random Numbers")) { RNGWindow(); show_random_num_window = !show_random_num_window; }
			if (ImGui::MenuItem("Configuration")) { ConfigWindow(); show_config_window = !show_config_window; }
			if (ImGui::MenuItem("OpenGL Config")) { OpenGLConfigWindow(); show_opengl = !show_opengl; }
			if (ImGui::MenuItem("Console")) { show_app_console = !show_app_console; }
			ImGui::EndMenu(); 
		}
		if (ImGui::BeginMenu("Help", true))
		{
			if (ImGui::MenuItem("Gui Demo")) { DemoWindow(); show_demo_window = !show_demo_window; }
			if (ImGui::MenuItem("Documentation")) { App->RequestBrowser("https://github.com/JoanBarduena/VideogameEngines/wiki"); }
			if (ImGui::MenuItem("Download latest")) { App->RequestBrowser("https://github.com/JoanBarduena/VideogameEngines/releases"); }
			if (ImGui::MenuItem("Report a bug")) { App->RequestBrowser("https://github.com/JoanBarduena/VideogameEngines/issues"); }
			if (ImGui::MenuItem("About", "F1", false, true)) { AboutWindow(); show_about_modal = !show_about_modal; }
			ImGui::EndMenu();
		}		
	}

	ImGui::EndMainMenuBar();

	//DEMO WINDOW 
	if (show_demo_window)
		DemoWindow();
	
	//RNG WINDOW
	if (show_random_num_window)
		RNGWindow();	

	//CONFIGURATION 
	if (show_config_window)
		ConfigWindow();
	
	//OPENGL CONFIG
	if (show_opengl)
		OpenGLConfigWindow();
	
	//ABOUT
	if (show_about_modal)
		AboutWindow();

	//CONSOLE
	if (show_app_console)
	{
		ImGui::Begin("Console", &show_app_console);
		ImGui::SetWindowSize(ImVec2(1000, 600));

		if (console_log)
		{
			for (int i = 0; i < App->vector_log.size(); ++i)
			{
				gui_console.AddLog(App->vector_log[i].data());
				if (i+1 == App->vector_log.size())
					console_log = false;
			}
		}

		gui_console.Draw(); 

		ImGui::End(); 
	}	

	return UPDATE_CONTINUE;
}

update_status ModuleGui::PostUpdate(float dt)
{
	//Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

void ModuleGui::SetGLEnum(bool is_enabled, GLenum cap)
{
	if (is_enabled)
		glEnable(cap);
	else
		glDisable(cap); 
}

void ModuleGui::DemoWindow()
{
	ImGui::ShowDemoWindow(&show_demo_window);
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
void ModuleGui::RNGWindow()
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

void ModuleGui::ConfigWindow()
{
	ImGui::Begin("Configuration", &show_config_window);
	ImGui::Text("Options");
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Application"))
	{
		ImGui::InputText("Engine", TITLE, 30);
		ImGui::InputText("Organization", ORGANIZATION, 50);
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
	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("SDL Version:");
		ImGui::Separator();

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
	}
	ImGui::End();
}

void ModuleGui::OpenGLConfigWindow()
{
	ImGui::Begin("OpenGL Configuration", &show_opengl);
	ImGui::SetWindowSize(ImVec2(400, 300));

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

	ImGui::End();
}
void ModuleGui::AboutWindow()
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