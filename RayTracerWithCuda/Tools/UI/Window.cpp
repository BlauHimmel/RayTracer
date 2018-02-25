#include "stdafx.h"

#include "Window.h"

namespace EasyTools
{

	Window::Window(int32 Width, int32 Height, LPTSTR Title)
	{
		if (GWindow != nullptr)
		{
			DEBUG_ERROR("A Window Has Already Been Created");
		}

		WNDCLASS WndClass;
		WndClass.style = CS_BYTEALIGNCLIENT;
		WndClass.lpfnWndProc = WndProc;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hInstance = NULL;
		WndClass.hIcon = NULL;
		WndClass.hCursor = NULL;
		WndClass.hbrBackground = NULL;
		WndClass.lpszMenuName = NULL;
		WndClass.lpszClassName = _T("SCREEN");

		BITMAPINFO BitmapInfo;
		BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		BitmapInfo.bmiHeader.biWidth = Width;
		BitmapInfo.bmiHeader.biHeight = Height;
		BitmapInfo.bmiHeader.biPlanes = 1;
		BitmapInfo.bmiHeader.biBitCount = 32;
		BitmapInfo.bmiHeader.biCompression = BI_RGB;
		BitmapInfo.bmiHeader.biSizeImage = Width * Height * 4;
		BitmapInfo.bmiHeader.biXPelsPerMeter = 0;
		BitmapInfo.bmiHeader.biYPelsPerMeter = 0;
		BitmapInfo.bmiHeader.biClrUsed = 0;
		BitmapInfo.bmiHeader.biClrImportant = 0;

		RECT Rect;
		Rect.left = 0;
		Rect.top = 0;
		Rect.right = Width;
		Rect.bottom = Height;

		Close();

		WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		WndClass.hInstance = GetModuleHandle(NULL);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		if (!RegisterClass(&WndClass))
		{
			DEBUG_ERROR("Error Occurred When Initialize Window");
		}

		m_Hwnd = CreateWindow(_T("SCREEN"), Title,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			0, 0, 0, 0, NULL, NULL, WndClass.hInstance, NULL);
		if (m_Hwnd == NULL)
		{
			DEBUG_ERROR("Error Occurred When Initialize Window");
		}

		m_ScreenExit = false;

		HDC HDC = GetDC(m_Hwnd);
		m_Hdc = CreateCompatibleDC(HDC);
		ReleaseDC(m_Hwnd, HDC);

		void* Ptr;
		m_Hb = CreateDIBSection(m_Hdc, &BitmapInfo, DIB_RGB_COLORS, &Ptr, 0, 0);
		if (m_Hb == NULL)
		{
			DEBUG_ERROR("Error Occurred When Initialize Window");
		}

		m_Title = new TCHAR[512];
		if (m_Title == NULL)
		{
			DEBUG_ERROR("Error Occurred When Initialize Window");
		}

		memset(m_KeyDown, false, sizeof(bool) * 256);
		m_Ob = (HBITMAP)SelectObject(m_Hdc, m_Hb);
		m_ScreenBuffer = (uint8*)Ptr;
		m_ScreenWidth = Width;
		m_ScreenHeight = Height;
		m_PixelCounts = Width * Height;
		m_ScreenPitch = Width * 4;
		lstrcpyW(m_Title, Title);

		AdjustWindowRect(&Rect, GetWindowLong(m_Hwnd, GWL_STYLE), 0);
		int32 WindowWidth = Rect.right - Rect.left;
		int32 WindowHeight = Rect.bottom - Rect.top;
		int32 ScreenX = (GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2;
		int32 ScreenY = (GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2;

		ScreenX = (ScreenX < 0) ? 0 : ScreenX;
		ScreenY = (ScreenY < 0) ? 0 : ScreenY;

		SetWindowPos(m_Hwnd, NULL, ScreenX, ScreenY, WindowWidth, WindowHeight, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
		SetForegroundWindow(m_Hwnd);
		ShowWindow(m_Hwnd, SW_NORMAL);

		Dispatch();
		
		memset(m_ScreenBuffer, 0, Width * Height * 4);
		
		m_FrameBuffer = new uint32*[m_ScreenHeight * 4];
		if (m_Title == NULL)
		{
			DEBUG_ERROR("Error Occurred When Initialize Window");
		}

		for (auto i = 0; i < m_ScreenHeight; i++)
		{
			m_FrameBuffer[i] = (uint32*)(m_ScreenBuffer + 4 * m_ScreenWidth * 4 * i);
		}

		GWindow = this;
	}

	Window::~Window()
	{
		delete[] m_Title;
		delete[] m_FrameBuffer;
		GWindow = nullptr;
	}

	void Window::Close()
	{
		if (m_Hdc != NULL)
		{
			if (m_Ob != NULL)
			{
				SelectObject(m_Hdc, m_Ob);
				m_Ob = NULL;
			}

			DeleteDC(m_Hdc);
			m_Hdc = NULL;
		}

		if (m_Hb != NULL)
		{
			DeleteObject(m_Hb);
			m_Hb = NULL;
		}

		if (m_Hwnd != NULL)
		{
			CloseWindow(m_Hwnd);
			m_Hwnd = NULL;
		}
	}

	void Window::Dispatch()
	{
		MSG Msg;
		ZeroMemory(&Msg, sizeof(MSG));
		while (!m_ScreenExit)
		{
			if (!PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE))
			{
				break;
			}
			if (!GetMessage(&Msg, NULL, 0, 0))
			{
				break;
			}
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	void Window::UpdateDC()
	{
		HDC HDC = GetDC(m_Hwnd);
		BitBlt(HDC, 0, 0, m_ScreenWidth, m_ScreenHeight, m_Hdc, 0, 0, SRCCOPY);
		ReleaseDC(m_Hwnd, HDC);
		Dispatch();
	}

	void Window::SetTitle(LPTSTR Title)
	{
		lstrcpyW(m_Title, Title);
		SetWindowText(m_Hwnd, m_Title);
	}

	Window* Window::GWindow = nullptr;

	LRESULT Window::MessageHandler(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
	{
		switch (UMsg)
		{
			case WM_KEYDOWN:
			{
				m_KeyDown[(uint32)WParam] = true;
				return 0;
			}
			case WM_KEYUP:
			{
				m_KeyDown[(uint32)WParam] = false;
				return 0;
			}
			default:
			{
				return DefWindowProc(HWnd, UMsg, WParam, LParam);
			}
		}
	}

	LRESULT CALLBACK WndProc(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
	{
		switch (UMsg)
		{
			case WM_DESTROY:
			{
				Window::GWindow->m_ScreenExit = true;
				return 0;
			}
			case WM_CLOSE:
			{
				Window::GWindow->m_ScreenExit = true;
				return 0;
			}
			default:
			{
				return Window::GWindow->MessageHandler(HWnd, UMsg, WParam, LParam);
			}
		}
		return 0;
	}

}