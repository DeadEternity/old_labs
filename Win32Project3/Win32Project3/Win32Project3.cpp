#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "stdafx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
RECT rect;
COLORREF pColor = RGB(228, 228, 228);
HPEN pen = CreatePen(PS_SOLID, 1, pColor);
HBRUSH brush = CreateSolidBrush(pColor);
HWND hWnd;
/*HMODULE hDLL;
int(*pSpeed) ();
void(*pgSpeed) (int mspeed);*/

int offset = 0, wdth, hght, ww=200, wh=100;
int x = 400, y = 400;
int speed = 5;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASSEX wcex;
	MSG msg;
	//HOOKPROC prc;

	/*hDLL = LoadLibrary(L"hookDLL.dll");
	BOOL(*pTest2) (int mspeed);
	(FARPROC &)pTest2 = GetProcAddress(hDLL, "test2");
	//prc = (HOOKPROC)GetProcAddress(hDLL, "KeyboardProc");
	DWORD x = GetLastError();
	BOOL bresult = (*pTest2) (speed);
	(FARPROC &)pSpeed = GetProcAddress(hDLL, "setSpeed");
	(FARPROC &)pgSpeed = GetProcAddress(hDLL, "getSpeed");
	//HHOOK a = SetWindowsHookEx(WH_KEYBOARD, prc, hDLL, NULL);
	//HHOOK a = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, (DWORD)GetCurrentThreadId());*/
	hInst = hInstance;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MyWindow";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		return 1;
	}

	hWnd = CreateWindow(L"MyWindow", L"MyWindow", WS_POPUP,
		x, y, ww, wh, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void Repaint() {
	InvalidateRect(hWnd, NULL, NULL);
	UpdateWindow(hWnd);
}

void paint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	RECT rect = { 0, 0, 200, 100};
	FillRect(hdc, &rect, brush);
	ValidateRect(hWnd, &rect);



	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_CREATE: {
		wdth = GetSystemMetrics(SM_CXSCREEN);
		hght = GetSystemMetrics(SM_CYSCREEN);
		SetTimer(hWnd, 1, 50, NULL);
		break;
	}
	case WM_PAINT:
		paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_TIMER: {
		//speed = (*pSpeed) ();
		if (x + speed < 0 || x + speed > wdth - 200) {
			if (x + speed < 0)
				x = 0;
			if (x + speed > wdth - 200)
				x = wdth - 200;
			speed = -speed;
			//pgSpeed(-speed);
		}
		else {
			x += speed;
		}
		MoveWindow(hWnd, x, y, ww, wh, FALSE);
		break;
	}
	case WM_KEYDOWN: 
	
	switch (wparam) {
		case VK_UP:
			if (speed < 0 && speed - 5 < 0 && speed > -30)
				speed -= 5;
			if(speed > 0 && speed + 5 < 30)
				speed += 5;
			break;
		case VK_DOWN:
			if (speed < 0 && speed + 5 < 0)
				speed += 5;
			if(speed > 0 && speed - 5 > 0)
				speed -= 5;
			break;
	}
	default:
		return DefWindowProc(hWnd, message, wparam, lparam);
		break;
	}
	return 0;
}