#include "Application.h"
#include "Globals.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include <string>

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
			if (ImGui::MenuItem("Demo Window")) { show_demo_window = !show_demo_window; }
			if (ImGui::MenuItem("RNG Window")) { show_random_num_window = !show_random_num_window; }
			if (ImGui::MenuItem("Configuration")) { show_config_window = !show_config_window; }
			ImGui::EndMenu(); 
		}
		if (ImGui::BeginMenu("Help", true))
		{
			if (ImGui::MenuItem("About", "F1", false, true)) { show_about_modal = true; }
			ImGui::EndMenu();
		}		
	}

	ImGui::EndMainMenuBar();

	//DEMO WINDOW 
	if (show_demo_window)
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

	//RNG WINDOW
	if (show_random_num_window)
	{ 
		ImGui::Begin("RNG Window", &show_random_num_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Random Number Generator!");

		ImGui::InputInt("Minimum", &min);
		ImGui::InputInt("Maximum", &max);

		ImGui::Text("Random number between the set interval");

		if (ImGui::Button("Click"))
			interval = pcg32i_boundedrand_r(&bounded, ((max + min) + 1 ) -  min);
		ImGui::SameLine();
		ImGui::Text("%d", interval);

		if (ImGui::Button("Close Me"))
			show_random_num_window = false;
		ImGui::End();
	}

	//CONFIGURATION 
	if (show_config_window)
	{
		ImGui::Text("Options");
		ImGui::Separator(); 

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::InputText("Engine", TITLE, 30);
			ImGui::InputText("Organization", ORGANIZATION, 50); 
		}

		if (ImGui::CollapsingHeader("Window"))
		{
			
		}
	}

	//ABOUT
	if (show_about_modal)
		ImGui::OpenPopup("About");
	
	if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		ImGui::Text("The Engine engine");
		ImGui::Separator();
		ImGui::Text("This engine has been developed as part of the Game Engines subject at UPC-CITM.\n");
		ImGui::Text("by Joan Barduena and Clara Ratera.\n");
		if (ImGui::Button("Joan Barduena"));
		ImGui::SameLine();
		if (ImGui::Button("Clara Ratera"));

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			show_about_modal = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();		

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