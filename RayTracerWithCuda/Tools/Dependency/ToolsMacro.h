#pragma once

#ifndef __TOOLS_MACRO__
#define __TOOLS_MACRO__

#define WINDOW_CREATE(Width, Height, Title, OutputConsoleTitle) __WINDOW_CREATE(Width, Height, Title, OutputConsoleTitle)

#define WINDOW_SET_TITLE(Title) __WINDOW_SET_TITLE(Title)

#define WINDOW_UPDATE_PIXELS(Pixels) __WINDOW_UPDATE_PIXELS(Pixels)

#define WINDOW_UPDATE_FLAG(NeedUpdate) __WINDOW_UPDATE_FLAG(NeedUpdate)

#define WINDOW_MAINLOOP_BEGIN(CommandCallback) __WINDOW_MAINLOOP_BEGIN(CommandCallback)

#define WINDOW_MAINLOOP_END() __WINDOW_MAINLOOP_END()

/** =============These macros are on windows platform============= */

#define __WINDOW_CREATE(Width, Height, Title, OutputConsoleTitle)\
EasyTools::Window __Window((Width), (Height), _T(Title));\
SetConsoleTitle(_T(OutputConsoleTitle));\
std::mutex __Mutex;\
std::promise<String> __Promise;\
std::future<String> __Future;\
bool __IsInput = false;\
bool __Waiting = true

#define __WINDOW_SET_TITLE(Title) EasyTools::Window::GWindow->SetTitle(_T(Title))

#define __WINDOW_UPDATE_PIXELS(Pixels)\
if (EasyTools::Window::GWindow->m_Update)\
{\
	if (Pixels.Length() != EasyTools::Window::GWindow->m_PixelCounts)\
	{\
		DEBUG_ERROR("The Length of Array Pixels Is Not Equalt To The Number Of Pixels");\
	}\
	for (auto __i = 0, __j = 0; __j < Pixels.Length(); __i += 4, __j++)\
	{\
		EasyMath::Color __Color = Pixels[__j];\
		EasyTools::Window::GWindow->m_ScreenBuffer[__i] = static_cast<uint8>(__Color.B() * 255.0f);\
		EasyTools::Window::GWindow->m_ScreenBuffer[__i + 1] = static_cast<uint8>(__Color.G() * 255.0f);\
		EasyTools::Window::GWindow->m_ScreenBuffer[__i + 2] = static_cast<uint8>(__Color.R() * 255.0f);\
		EasyTools::Window::GWindow->m_ScreenBuffer[__i + 3] = 0;\
	}\
}

#define __WINDOW_UPDATE_FLAG(NeedUpdate) EasyTools::Window::GWindow->m_Update = (NeedUpdate)

#define __WINDOW_MAINLOOP_BEGIN(CommandCallback)\
while (!EasyTools::Window::GWindow->m_ScreenExit && !EasyTools::Window::GWindow->m_KeyDown[VK_ESCAPE])\
{\
	EasyTools::Window::GWindow->Dispatch();\
	if (__Waiting)\
	{\
		__Promise = std::promise<String>();\
		__Future = __Promise.get_future();\
		std::thread Thread([](std::promise<String>& __Promise, bool& __Waiting, bool& __IsInput, std::mutex& __Mutex)\
		{\
			String __Command;\
			__Waiting = false;\
			std::cin >> __Command;\
			__Promise.set_value(__Command);\
			__IsInput = true;\
		}, std::ref(__Promise), std::ref(__Waiting), std::ref(__IsInput), std::ref(__Mutex));\
		Thread.detach();\
	}\
	if (__IsInput)\
	{\
		String __Command = __Future.get();\
		__Waiting = true;\
		__IsInput = false;\
		CommandCallback(__Command);\
	}

#define __WINDOW_MAINLOOP_END() EasyTools::Window::GWindow->UpdateDC();}

/** ============================================================== */

#endif
