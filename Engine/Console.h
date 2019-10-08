#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>

class Console 
{
public: 

	char                  InputBuf[256];
	ImVector<char*>       Items;
	ImVector<const char*> Commands;
	ImVector<char*>       History;
	int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImGuiTextFilter       Filter;
	bool                  AutoScroll;
	bool                  ScrollToBottom;

	Console();
	~Console();

	void ClearLog();
	void AddLog(const char* fmt, ...);
	void Draw(const char* title, bool* p_open);
	void ExecCommand(const char* command_line);
	int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
	int TextEditCallback(ImGuiInputTextCallbackData* data);

};

#endif __CONSOLE_H__
