#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "imGui/imgui.h"

#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>

typedef unsigned int uint;

class Console 
{
public: 

	static char                  InputBuf[256];
	static ImVector<char*>       Items;
	static ImVector<const char*> Commands;
	static ImVector<char*>       History;
	static int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	static ImGuiTextFilter       Filter;
	static bool                  AutoScroll;
	static bool                  ScrollToBottom;
	//static bool					 ShowVerboseLog;
	//static bool					 ShowGeometryLog;
	//static bool					 ShowDebugLog;

	Console();
	~Console();

	// Portable helpers
	static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
	static char* Strdup(const char* str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
	static void  Strtrim(char* str) { char* str_end = str + strlen(str); while (str_end > str&& str_end[-1] == ' ') str_end--; *str_end = 0; }

	static void ClearLog()
	{
		for (int i = 0; i < Items.Size; i++)
			free(Items[i]);
		Items.clear();
	}

	static void AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		// FIXME-OPT
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
		buf[IM_ARRAYSIZE(buf) - 1] = 0;
		va_end(args);
		Items.push_back(Strdup(buf));
	}

	void Draw();

	static void ExecCommand(const char* command_line);
	static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
	static int TextEditCallback(ImGuiInputTextCallbackData* data);

};

#endif __CONSOLE_H__
