#pragma once

#ifndef __WINDOW__
#define __WINDOW__

#include "Tools\Dependency\ToolsDependency.h"
#include "Tools\Dependency\ToolsMacro.h"

#include "Container\List\Array.hpp"
#include "Math\Vector\Color.h"

namespace EasyTools
{
	 
	LRESULT CALLBACK WndProc(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

	class PLATFORM_API Window
	{

	public:

		friend LRESULT CALLBACK WndProc(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

	private:

		HWND m_Hwnd;
		HDC m_Hdc;
		HBITMAP m_Hb;
		HBITMAP m_Ob;

	public:
		
		bool m_KeyDown[256];
		bool m_ScreenExit;
		int64 m_PixelCounts;
		int64 m_ScreenWidth, m_ScreenHeight;
		uint8* m_ScreenBuffer;
		int64 m_ScreenPitch;
		LPTSTR m_Title;
		uint32** m_FrameBuffer;

	public:

		Window(int64 Width, int64 Height, LPTSTR Title);
		~Window();

	private:

		void Close();

	public:

		void SetTitle(LPTSTR Title);
		void Dispatch();
		void UpdateDC();

	public:

		bool m_Update = true;

	public:

		static Window* GWindow;

	private:

		LRESULT CALLBACK MessageHandler(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam);
	
	};
}

#endif