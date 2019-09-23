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

bool ModuleGui::Start()
{
	bool ret = true;

	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	////ImGui::StyleColorsClassic();

	//// Setup Platform/Renderer bindings
	//ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	//ImGui_ImplOpenGL3_Init();

	return ret;
}

update_status ModuleGui::PreUpdate(float dt)
{
	//SDL_Event event;
	//while (SDL_PollEvent(&event))
	//{
	//	ImGui_ImplSDL2_ProcessEvent(&event);
	//	/*if (event.type == SDL_QUIT)
	//		done = true;
	//	if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
	//		done = true;*/
	//}

	//// Start the Dear ImGui frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplSDL2_NewFrame(App->window->window);
	//ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{
	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	//{
	//	static float f = 0.0f;
	//	static int counter = 0;

	//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	////	ImGui::Checkbox("Another Window", &show_another_window);

	//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		counter++;
	//	ImGui::SameLine();
	//	ImGui::Text("counter = %d", counter);

	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//}

	//// 3. Show another simple window.
	//if (show_another_window)
	//{
	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window = false;
	//	ImGui::End();
	//}

	return UPDATE_CONTINUE;
}

update_status ModuleGui::PostUpdate(float dt)
{
	// Rendering
	//ImGui::Render();
	////glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	////glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	////glClear(GL_COLOR_BUFFER_BIT);
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

bool ModuleGui::CleanUp()
{
	bool ret = true; 

	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplSDL2_Shutdown();
	//ImGui::DestroyContext();

	//SDL_GL_DeleteContext(App->renderer3D->context);
	//SDL_DestroyWindow(App->window->window);
	//SDL_Quit();

	return ret;
}