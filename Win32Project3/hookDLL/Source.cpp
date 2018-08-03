#include <Windows.h>

#pragma data_seg(".HKT")
int speed;
HHOOK a = NULL;
#pragma data_seg () 
#pragma comment(linker, "/SECTION:.HKT,RWS")	


__declspec(dllexport) LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
//	EVENTMSG *em = (EVENTMSG*)lParam;
//	if (em->message == WM_KEYDOWN)
		switch (wParam) {
		case VK_UP:
			if (speed < 0 && speed - 5 < 0 && speed > -30)
				speed -= 5;
			if (speed > 0 && speed + 5 < 30)
				speed += 5;
			break;
		case VK_DOWN:
			if (speed < 0 && speed + 5 < 0)
				speed += 5;
			if (speed > 0 && speed - 5 > 0)
				speed -= 5;
			//
			break;
		}
		return CallNextHookEx(NULL, nCode, wParam, lParam);
}

extern "C" _declspec(dllexport) BOOL test2(int mspeed) {
	HHOOK b = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle(L"hookDLL.dll"), 0);
	//HHOOK b = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, 0);
	speed = mspeed;
	if (a) {
		return TRUE;
	}
	return FALSE;
}

extern "C" _declspec(dllexport) int setSpeed() {
	return speed;
}
extern "C" _declspec(dllexport) void getSpeed(int mspeed) {
	speed = mspeed;
}
BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpvReserved) {
	return TRUE;
}