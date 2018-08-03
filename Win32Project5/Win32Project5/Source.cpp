#include <Windows.h>
#include <Commctrl.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


#define BUTTON1_ID 6000
#define BUTTON2_ID 6001
#define BUTTON3_ID 6002
#define BUTTON4_ID 6003
#define BUTTON5_ID 6004
#define BUTTON6_ID 6005
#define BUTTON7_ID 6006
#define BUTTON8_ID 6007
#define BUTTON9_ID 6008
#define BUTTON0_ID 6009
#define BUTTONPLUS_ID 6010
#define BUTTONMINUS_ID 6011
#define BUTTONMULT_ID 6012
#define BUTTONDIV_ID 6013
#define BUTTONDEL_ID 6014
#define BUTTONENTER_ID 6015
#define BUTTONSQR_ID 6016
#define BUTTONREV_ID 6017
#define BUTTONMC_ID 6018
#define BUTTONMS_ID 6019
#define BUTTONMR_ID 6020
#define BUTTONMA_ID 6021
#define BUTTONCL_ID 6022
#define BUTTONBS_ID 6023


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


HINSTANCE hInst;
char *expression;
int cur_pos = 0;
BOOL checkMenu = TRUE;
BOOL memoryState = FALSE;

int memoryNominator = 0;
int memoryDenominator = 1;

HWND hButton1;
HWND hButton2;
HWND hButton3;
HWND hButton4;
HWND hButton5;
HWND hButton6;
HWND hButton7;
HWND hButton8;
HWND hButton9;
HWND hButton0;
HWND hEditBox;
HWND hButtonPlus;
HWND hButtonMinus;
HWND hButtonMult;
HWND hButtonDiv;
HWND hButtonDelim;
HWND hButtonEnter;
HWND hButtonSqr;
HWND hButtonRev;
HWND hButtonMemClean;
HWND hButtonMemSave;
HWND hButtonMemCopy;
HWND hButtonMemAdd;
HWND hButtonClear;
HWND hButtonBs;
HMENU smenu;

void Copy() {
	OpenClipboard(NULL);
	EmptyClipboard();
	HGLOBAL hStrMem = GlobalAlloc(GMEM_MOVEABLE, GetWindowTextLength(hEditBox) + 3);
	char* pStrMem = (char*)GlobalLock(hStrMem);
	char* str = (char*)malloc(GetWindowTextLength(hEditBox) + 3);
	GetWindowText(hEditBox, str, GetWindowTextLength(hEditBox) + 2);
	strcpy_s(pStrMem, GetWindowTextLength(hEditBox) + 3, str);
	GlobalUnlock(pStrMem);
	SetClipboardData(CF_TEXT, hStrMem);
	CloseClipboard();
}
void Paste() {
	HGLOBAL buf = NULL;
	if (IsClipboardFormatAvailable(CF_TEXT)) { 
		if (OpenClipboard(GetForegroundWindow())) {  
			buf = (HGLOBAL)GetClipboardData(CF_TEXT);
			char* str = (char*)GlobalLock(buf); 
			GlobalUnlock(buf);
			SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)str);
			CloseClipboard();
		}
	}
}
char* intToStrWSep(int nominator, int denominator) {
	char buf[40];
	int l = 0;
	_itoa_s(nominator, buf, 10);
	l += strnlen(buf,_countof(buf));
	_itoa_s(denominator, buf, 10);
	if (denominator != 1 && !checkMenu) {
		l += strnlen(buf, _countof(buf));
	}
	char* rbuf = (char*)malloc(l+2);
	_itoa_s(nominator, buf, 10);
	int rpos = 0;
	for (int j = 0; j < strnlen(buf,_countof(buf)); j++, rpos++) {
		rbuf[rpos] = buf[j];
	}
	if (denominator != 1 && !checkMenu) {
		rbuf[rpos] = '|';
		rpos++;
		_itoa_s(denominator, buf, 10);
		for (int j = 0; j < strnlen(buf, _countof(buf)); j++, rpos++) {
			rbuf[rpos] = buf[j];
		}
	}
	rbuf[rpos] = '\0';
	return rbuf;
}

void doOperation(int* nominator1, int nominator2, int* denominator1, int denominator2,
	char operation, BOOL isFirstSet, BOOL* isSecondSet, BOOL* isOperationSet) {

	if (operation == '+') {
		if (*denominator1 == denominator2) {
			*nominator1 += nominator2;
			*isSecondSet = FALSE;
			*isOperationSet = FALSE;
		}
		else if (*denominator1 != denominator2) {
				//spell checker here
			*nominator1 = *nominator1*denominator2 + nominator2*(*denominator1);
			*denominator1 = *denominator1*denominator2;
			*isSecondSet = FALSE;
			*isOperationSet = FALSE;
		}
		return;
	}
	if (operation == '-') {
		if (*denominator1 == denominator2) {
			*nominator1 -= nominator2;
			*isSecondSet = FALSE;
			*isOperationSet = FALSE;
		}
		else if (*denominator1 != denominator2) {
			*nominator1 = *nominator1*denominator2 - nominator2*(*denominator1);
			*denominator1 = *denominator1*denominator2;
			*isSecondSet = FALSE;
			*isOperationSet = FALSE;
		}
		return;
	}
	if (operation == '*') {
		*nominator1 *= nominator2;
		*denominator1 *= denominator2;
				//spell checker here
		*isSecondSet = FALSE;
		*isOperationSet = FALSE;
		return;
	}
	if (operation == '/') {
		*nominator1 *= denominator2;
		*denominator1 *= nominator2;
		*isSecondSet = FALSE;
		*isOperationSet = FALSE;
		return;
	}
}

BOOL SpellChecker(char* str, size_t str_length, BOOL setMemory, BOOL addMemory) {
	BOOL isFirstSet = FALSE, isSecondSet = FALSE, isOperationSet = FALSE;
	int nominator1, nominator2, denominator1, denominator2;
	char operation;
	for(int i = 0; i < str_length; i++) {
		
		if (isFirstSet && !isOperationSet) {
			if (str[i] == '+') {
				operation = '+';
				if(!isOperationSet)
					isOperationSet = TRUE;
				else return FALSE;
				continue;
			}
			if (str[i] == '-') {
				operation = '-';
				if(!isOperationSet)
					isOperationSet = TRUE;
				else return FALSE;
				continue;
			}
			if (str[i] == '*') {
				operation = '*';
				if(!isOperationSet)
					isOperationSet = TRUE;
				else return FALSE;
				continue;
			}
			if (str[i] == '/') {
				operation = '/';
				if(!isOperationSet)
					isOperationSet = TRUE;
				else return FALSE;
				continue;
			}
			if (str[i] == 's') {
				operation = 's';
				nominator1 *= nominator1;
				denominator1 *= denominator1;
				continue;
			}
			if (str[i] == 'r') {
				operation = 'r';
				int buf;
				if(nominator1 < 0)
					buf = -nominator1;
				else buf = nominator1;
				nominator1 = denominator1;
				denominator1 = buf;
				continue;
			}
		}
		if (str[i] == '-' && !isFirstSet) {
			int start = i;
			i++;
			int numlen = 1;
			while (isdigit(str[i])) {
				i++;
				numlen++;
			}
			char* num = (char*)malloc(numlen + 1);
			for (int j = start, k = 0; j < i; j++, k++) {
				num[k] = str[j];
			}
			num[numlen] = '\0';
			nominator1 = atoi(num);
			free(num);
			if (str[i] == '|') {
				i++;
				numlen = 0;
				start = i;
				while (isdigit(str[i])) {
					i++;
					numlen++;
				}
				num = (char*)malloc(numlen + 1);
				for (int j = start, k = 0; j < i; j++, k++) {
					num[k] = str[j];
				}
				num[numlen] = '\0';
				denominator1 = atoi(num);
			}
			else {
				denominator1 = 1;
			}
			if (!isFirstSet)
				isFirstSet = TRUE;
			i--;
			if (isFirstSet && isSecondSet && isOperationSet) 
				doOperation(&nominator1, nominator2, &denominator1, denominator2, 
					operation, isFirstSet, &isOperationSet, &isSecondSet);
			continue;
		}
		if (isdigit(str[i])) {
			int start = i;
			int numlen = 0;
			while (isdigit(str[i])) {
				i++;
				numlen++;
			}
			char* num = (char*)malloc(numlen + 1);
			for (int j = start, k = 0; j < i; j++, k++) {
				num[k] = str[j];
			}
			num[numlen] = '\0';
			if (isFirstSet) {
				nominator2 = atoi(num);
				isSecondSet = TRUE;
			}
			else {
				nominator1 = atoi(num);
			}
			free(num);
			if (str[i] == '|') {
				i++;
				numlen = 0;
				start = i;
				while (isdigit(str[i])) {
					i++;
					numlen++;
				}
				num = (char*)malloc(numlen + 1);
				for (int j = start, k = 0; j < i; j++, k++) {
					num[k] = str[j];
				}
				num[numlen] = '\0';
				if(isFirstSet)
					denominator2 = atoi(num);
				else {
					denominator1 = atoi(num);
					isFirstSet = TRUE;
				}
			}
			else {
				if (isFirstSet)
					denominator2 = 1;
				else {
					denominator1 = 1;
					isFirstSet = TRUE;
				}
			}
			i--;
			if (isFirstSet && isSecondSet && isOperationSet) 
				doOperation(&nominator1, nominator2, &denominator1, denominator2, 
					operation, isFirstSet, &isOperationSet, &isSecondSet);
			continue;
		}
		else return FALSE;
	}
	if (isFirstSet && isOperationSet) {
		doOperation(&nominator1, nominator1, &denominator1, denominator1,
			operation, isFirstSet, &isOperationSet, &isSecondSet);
	}
	
	if (setMemory) {
		memoryNominator = nominator1;
		memoryDenominator = denominator1;
	}
	if (addMemory) {
		memoryNominator += nominator1;
		memoryDenominator += denominator1;
	}
	SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)intToStrWSep(nominator1, denominator1));
	return TRUE;
}
void BackSpace(HWND hwnd) {
	size_t tl = GetWindowTextLength(hwnd);
	if (tl <= 1) return;
	char* exp = (char*)malloc(tl);
	GetWindowText(hwnd, exp, tl);
	exp[tl] = '\0';
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)exp);
}
void Append(HWND hwnd, char a) {
	size_t tl = GetWindowTextLength(hwnd);
	if (tl >= 30) return;
	char* exp = (char*)malloc(tl + 2);
	GetWindowText(hwnd, exp, tl + 1);
	exp[tl] = a;
	exp[tl + 1] = '\0';
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)exp);
}

BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); 
	return LineTo(hdc, x2, y2);
}

void PaintMain(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hWnd, &ps);

	/*
	* Background drawing
	*/
	RECT userSpaceRect;
	GetClientRect(hWnd, &userSpaceRect);
	HBRUSH brush = CreateSolidBrush(RGB(50, 50, 50)); 
	SelectObject(hdc, brush);
	FillRect(hdc, &userSpaceRect, brush);

	/*
	* Drawing lines for buttons and input zone
	*/

	HPEN pen = CreatePen(NULL, 2, RGB(100, 100, 100));
	SelectObject(hdc, pen);

	//Horizontal lines
	DrawLine(hdc, 0, 170, 1000, 170);
	DrawLine(hdc, 99, 270, 399, 270);
	DrawLine(hdc, 499, 270, 899, 270);
	DrawLine(hdc, 99, 370, 399, 370);
	DrawLine(hdc, 499, 370, 899, 370);
	DrawLine(hdc, 99, 470, 399, 470);
	DrawLine(hdc, 499, 470, 899, 470);
	DrawLine(hdc, 199, 570, 299, 570);
	DrawLine(hdc, 499, 570, 899, 570);

	//Vertical lines
	DrawLine(hdc, 0, 170, 0, 670);
	DrawLine(hdc, 100, 170, 100, 470);
	DrawLine(hdc, 200, 170, 200, 570);
	DrawLine(hdc, 300, 170, 300, 570);
	DrawLine(hdc, 400, 170, 400, 470);
	DrawLine(hdc, 500, 170, 500, 570);
	DrawLine(hdc, 600, 170, 600, 570);
	DrawLine(hdc, 700, 170, 700, 570);
	DrawLine(hdc, 800, 170, 800, 470);
	DrawLine(hdc, 900, 170, 900, 570);


	/*
	* Set font for edit box
	*/
	//Set note
	//SendMessage(hwndCommandLink, BCM_SETNOTE, 0, (LPARAM)L"with note");



	RECT rect = { 250, 300, 100, 300 };
	//hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
    //            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
	//DrawText(hdc, (LPCWSTR)text, 1, &userSpaceRect, DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	EndPaint(hWnd, &ps);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASSEX wcex;
	MSG msg;
	HWND hWnd;

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
	wcex.lpszClassName = "CALculator";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		return 1;
	}

	HMENU menu = CreateMenu();
	smenu = CreateMenu();
	HMENU pmenu = CreatePopupMenu();
	AppendMenu(smenu, MF_CHECKED, 126, "Показывать разделитель");
	AppendMenu(pmenu, MF_STRING, 123, "Вставить");
	AppendMenu(pmenu, MF_STRING, 124, "Копировать");
	AppendMenu(menu, MF_POPUP, (UINT)pmenu, "Правка");
	AppendMenu(menu, MF_POPUP, (UINT)smenu, "Настройки");
	AppendMenu(menu, MF_STRING, 125, "Справка");
	/*
	* WS_OVERLAPPEDWINDOW   Creates an overlapped window with the WS_OVERLAPPED,
	* WS_CAPTION, WS_SYSMENU, WS_THICKFRAME, WS_MINIMIZEBOX, and WS_MAXIMIZEBOX styles.
	* Main Window
	*/
	hWnd = CreateWindow("CALculator", "CALculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		50, 50, 1000, 700, NULL, NULL, hInstance, NULL);

	SetMenu(hWnd, menu);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_CREATE:
	{
		HFONT hwFont = CreateFont(50, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courier New"));
		/*
		* Input zone
		*/
		hEditBox = CreateWindow("Edit", TEXT(""), WS_CHILD | WS_VISIBLE | ES_RIGHT | NULL,
			250, 30, 700, 50, hWnd, (HMENU)BUTTON6_ID, hInst, 0);
		SelectObject(GetWindowDC(hButton1), hwFont);
		/*
		* Input buttons
		*/
		hButton1 = CreateWindow("BUTTON", "1", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
			101, 171, 98, 98, hWnd, (HMENU)BUTTON1_ID, hInst, NULL);

		hButton2 = CreateWindow("BUTTON", "2", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			201, 171, 98, 98, hWnd, (HMENU)BUTTON2_ID, hInst, NULL);

		hButton3 = CreateWindow("BUTTON", "3", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			301, 171, 98, 98, hWnd, (HMENU)BUTTON3_ID, hInst, NULL);

		hButton4 = CreateWindow("BUTTON", "4", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			101, 271, 98, 98, hWnd, (HMENU)BUTTON4_ID, hInst, NULL);

		hButton5 = CreateWindow("BUTTON", "5", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			201, 271, 98, 98, hWnd, (HMENU)BUTTON5_ID, hInst, NULL);

		hButton6 = CreateWindow("BUTTON", "6", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			301, 271, 98, 98, hWnd, (HMENU)BUTTON6_ID, hInst, NULL);

		hButton7 = CreateWindow("BUTTON", "7", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			101, 371, 98, 98, hWnd, (HMENU)BUTTON7_ID, hInst, NULL);

		hButton8 = CreateWindow("BUTTON", "8", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			201, 371, 98, 98, hWnd, (HMENU)BUTTON8_ID, hInst, NULL);

		hButton9 = CreateWindow("BUTTON", "9", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			301, 371, 98, 98, hWnd, (HMENU)BUTTON9_ID, hInst, NULL);

		hButton0 = CreateWindow("BUTTON", "0", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			201, 471, 98, 98, hWnd, (HMENU)BUTTON0_ID, hInst, NULL);

		hButtonPlus = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			501, 171, 98, 98, hWnd, (HMENU)BUTTONPLUS_ID, hInst, NULL);

		hButtonMinus = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			601, 171, 98, 98, hWnd, (HMENU)BUTTONMINUS_ID, hInst, NULL);

		hButtonMult = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			501, 271, 98, 98, hWnd, (HMENU)BUTTONMULT_ID, hInst, NULL);

		hButtonDiv = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			601, 271, 98, 98, hWnd, (HMENU)BUTTONDIV_ID, hInst, NULL);

		hButtonSqr = CreateWindow("BUTTON", "Sqr", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			501, 371, 98, 98, hWnd, (HMENU)BUTTONSQR_ID, hInst, NULL);

		hButtonRev = CreateWindow("BUTTON", "Rev", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			601, 371, 98, 98, hWnd, (HMENU)BUTTONREV_ID, hInst, NULL);

		hButtonDelim = CreateWindow("BUTTON", "|", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			501, 471, 98, 98, hWnd, (HMENU)BUTTONDEL_ID, hInst, NULL);

		hButtonEnter = CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			601, 471, 98, 98, hWnd, (HMENU)BUTTONENTER_ID, hInst, NULL);

		hButtonMemClean = CreateWindow("BUTTON", "MC", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			701, 171, 98, 98, hWnd, (HMENU)BUTTONMC_ID, hInst, NULL);

		hButtonMemSave = CreateWindow("BUTTON", "MS", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			801, 171, 98, 98, hWnd, (HMENU)BUTTONMS_ID, hInst, NULL);

		hButtonMemAdd = CreateWindow("BUTTON", "MA", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			701, 271, 98, 98, hWnd, (HMENU)BUTTONMA_ID, hInst, NULL);

		hButtonMemCopy = CreateWindow("BUTTON", "MR", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			801, 271, 98, 98, hWnd, (HMENU)BUTTONMR_ID, hInst, NULL);

		hButtonClear = CreateWindow("BUTTON", "Clear", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			701, 371, 98, 98, hWnd, (HMENU)BUTTONCL_ID, hInst, NULL);

		hButtonBs = CreateWindow("BUTTON", "Bs", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_FLAT,
			801, 371, 98, 98, hWnd, (HMENU)BUTTONBS_ID, hInst, NULL);

		SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM)GetWindowDC(hEditBox), (LPARAM)hWnd);
		SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"0");


		HFONT hFont = CreateFont(50, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courier New"));
		SendMessage(hEditBox, WM_SETFONT, (WPARAM)hFont, 0);


		//SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)"Text");
		break;
	}
	case WM_PAINT:
		PaintMain(hWnd);
		break;
		/*case WM_SETFOCUS:
			SetFocus(hEditBox);
			return 0;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_CTLCOLORBTN:
	{
		/*
		* WPARAM - Control HDC
		* LPARAM - HWND
		*/

		SetTextColor((HDC)wparam, RGB(150, 150, 150));
		SetBkColor((HDC)wparam, RGB(50, 50, 50));
		SetBkMode((HDC)wparam, OPAQUE);

		if ((HWND)lparam == hButton1)
			TextOut((HDC)wparam, 45, 40, "1", 1);
		if ((HWND)lparam == hButton2)
			TextOut((HDC)wparam, 45, 40, "2", 1);
		if ((HWND)lparam == hButton3)
			TextOut((HDC)wparam, 45, 40, "3", 1);
		if ((HWND)lparam == hButton4)
			TextOut((HDC)wparam, 45, 40, "4", 1);
		if ((HWND)lparam == hButton5)
			TextOut((HDC)wparam, 45, 40, "5", 1);
		if ((HWND)lparam == hButton6)
			TextOut((HDC)wparam, 45, 40, "6", 1);
		if ((HWND)lparam == hButton7)
			TextOut((HDC)wparam, 45, 40, "7", 1);
		if ((HWND)lparam == hButton8)
			TextOut((HDC)wparam, 45, 40, "8", 1);
		if ((HWND)lparam == hButton9)
			TextOut((HDC)wparam, 45, 40, "9", 1);
		if ((HWND)lparam == hButton0)
			TextOut((HDC)wparam, 45, 40, "0", 1);
		if ((HWND)lparam == hButtonPlus)
			TextOut((HDC)wparam, 45, 40, "+", 1);
		if ((HWND)lparam == hButtonMinus)
			TextOut((HDC)wparam, 45, 40, "-", 1);
		if ((HWND)lparam == hButtonMult)
			TextOut((HDC)wparam, 45, 40, "*", 1);
		if ((HWND)lparam == hButtonDiv)
			TextOut((HDC)wparam, 45, 40, "/", 1);
		if ((HWND)lparam == hButtonSqr)
			TextOut((HDC)wparam, 40, 40, "Sqr", 3);
		if ((HWND)lparam == hButtonRev)
			TextOut((HDC)wparam, 40, 40, "Rev", 3);
		if ((HWND)lparam == hButtonDelim)
			TextOut((HDC)wparam, 45, 40, "|", 1);
		if ((HWND)lparam == hButtonEnter)
			TextOut((HDC)wparam, 45, 40, "=", 1);
		if ((HWND)lparam == hButtonMemAdd)
			TextOut((HDC)wparam, 43, 40, "M+", 2);
		if ((HWND)lparam == hButtonMemClean)
			TextOut((HDC)wparam, 43, 40, "MC", 2);
		if ((HWND)lparam == hButtonMemCopy)
			TextOut((HDC)wparam, 43, 40, "MR", 2);
		if ((HWND)lparam == hButtonMemSave)
			TextOut((HDC)wparam, 43, 40, "MS", 2);
		if ((HWND)lparam == hButtonClear)
			TextOut((HDC)wparam, 45, 40, "C", 1);
		if ((HWND)lparam == hButtonBs)
			TextOut((HDC)wparam, 43, 40, "BS", 2);

		return(LRESULT)(CreateSolidBrush(RGB(50, 50, 50)));
	}
	break;
	case WM_CTLCOLOREDIT:
	{
		/*
		* WPARAM - Control HDC
		* LPARAM - HWND
		*/
		SetTextColor((HDC)wparam, RGB(150, 150, 150));
		SetBkColor((HDC)wparam, RGB(50, 50, 50));
		SetBkMode((HDC)wparam, OPAQUE);
		return (INT_PTR)CreateSolidBrush(RGB(50, 50, 50));
		break;
	}
	case WM_COMMAND:
		switch (wparam) {
		case 126:
			if (checkMenu) {
				CheckMenuItem(smenu, 126, MF_UNCHECKED);
				checkMenu = FALSE;
			}
			else {
				CheckMenuItem(smenu, 126, MF_CHECKED);
				checkMenu = TRUE;
			}
			break;
		case 123:
			Paste();
			break;
		case 124:
			Copy();
			break;
		case 125:
			MessageBox(hWnd, "Шубкин Роман", "Справка", MB_OK);
			break;
		case BUTTON1_ID:
			Append(hEditBox, '1');
			SetFocus(hWnd);
			break;
		case BUTTON2_ID:
			Append(hEditBox, '2');
			SetFocus(hWnd);
			break;
		case BUTTON3_ID:
			Append(hEditBox, '3');
			SetFocus(hWnd);
			break;
		case BUTTON4_ID:
			Append(hEditBox, '4');
			SetFocus(hWnd);
			break;
		case BUTTON5_ID:
			Append(hEditBox, '5');
			SetFocus(hWnd);
			break;
		case BUTTON6_ID:
			Append(hEditBox, '6');
			SetFocus(hWnd);
			break;
		case BUTTON7_ID:
			Append(hEditBox, '7');
			SetFocus(hWnd);
			break;
		case BUTTON8_ID:
			Append(hEditBox, '8');
			SetFocus(hWnd);
			break;
		case BUTTON9_ID:
			Append(hEditBox, '9');
			SetFocus(hWnd);
			break;
		case BUTTON0_ID:
			Append(hEditBox, '0');
			SetFocus(hWnd);
			break;
		case BUTTONPLUS_ID:
			Append(hEditBox, '+');
			SetFocus(hWnd);
			break;
		case BUTTONMINUS_ID:
			Append(hEditBox, '-');
			SetFocus(hWnd);
			break;
		case BUTTONMULT_ID:
			Append(hEditBox, '*');
			SetFocus(hWnd);
			break;
		case BUTTONDIV_ID:
			Append(hEditBox, '/');
			SetFocus(hWnd);
			break;
		case BUTTONDEL_ID:
			Append(hEditBox, '|');
			SetFocus(hWnd);
			break;
		case BUTTONSQR_ID:
			Append(hEditBox, 's');
			SetFocus(hWnd);
			break;
		case BUTTONREV_ID:
			Append(hEditBox, 'r');
			SetFocus(hWnd);
			break;
		case BUTTONCL_ID:
			SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"0");
			SetFocus(hWnd);
			break;
		case BUTTONBS_ID:
			BackSpace(hEditBox);
			SetFocus(hWnd);
			break;
		case BUTTONMC_ID:
			memoryState = FALSE;
			memoryNominator = 0;
			memoryDenominator = 1;
			SetFocus(hWnd);
			break;
		case BUTTONMS_ID:
		{
			size_t length = GetWindowTextLength(hEditBox);
			char* str = (char*)malloc(length + 1);
			GetWindowText(hEditBox, str, length + 1);
			if (!SpellChecker(str, length, TRUE, FALSE))
				SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"ERROR");
			else memoryState = TRUE;
			free(str);
			SetFocus(hWnd);
			break;
		}
		case BUTTONMA_ID:
		{
			size_t length = GetWindowTextLength(hEditBox);
			char* str = (char*)malloc(length + 1);
			GetWindowText(hEditBox, str, length + 1);
			if (!SpellChecker(str, length, FALSE, TRUE))
				SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"ERROR");
			else memoryState = TRUE;
			free(str);
			SetFocus(hWnd);
			break;
		}
		case BUTTONMR_ID:
		{
			char* mem = intToStrWSep(memoryNominator, memoryDenominator);
			SetWindowText(hEditBox, mem);
			SetFocus(hWnd);
			break;
		}
		case BUTTONENTER_ID:
		{
			size_t length = GetWindowTextLength(hEditBox);
			char* str = (char*)malloc(length + 1);
			GetWindowText(hEditBox, str, length + 1);
			if (!SpellChecker(str, length, FALSE, FALSE))
				SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"ERROR");
			free(str);
			SetFocus(hWnd);
			break;
		}
		}
		break;
	case WM_KEYDOWN:
		switch (wparam) {
		case 0x31:
			Append(hEditBox, '1');
			break;
		case 0x30:
			Append(hEditBox, '0');
			break;
		case 0x32:
			Append(hEditBox, '2');
			break;
		case 0x33:
			Append(hEditBox, '3');
			break;
		case 0x34:
			Append(hEditBox, '4');
			break;
		case 0x35:
			Append(hEditBox, '5');
			break;
		case 0x36:
			Append(hEditBox, '6');
			break;
		case 0x37:
			Append(hEditBox, '7');
			break;
		case 0x38:
			Append(hEditBox, '8');
			break;
		case 0x39:
			Append(hEditBox, '9');
			break;
		case VK_NUMPAD0:
			Append(hEditBox, '0');
			break;
		case VK_NUMPAD1:
			Append(hEditBox, '1');
			break;
		case VK_NUMPAD2:
			Append(hEditBox, '2');
			break;
		case VK_NUMPAD3:
			Append(hEditBox, '3');
			break;
		case VK_NUMPAD4:
			Append(hEditBox, '4');
			break;
		case VK_NUMPAD5:
			Append(hEditBox, '5');
			break;
		case VK_NUMPAD6:
			Append(hEditBox, '6');
			break;
		case VK_NUMPAD7:
			Append(hEditBox, '7');
			break;
		case VK_NUMPAD8:
			Append(hEditBox, '8');
			break;
		case VK_NUMPAD9:
			Append(hEditBox, '9');
			break;
		case VK_BACK:
			BackSpace(hEditBox);
			break;
		case VK_DIVIDE:
			Append(hEditBox, '/');
			break;
		case VK_MULTIPLY:
			Append(hEditBox, '*');
			break;
		case VK_ADD:
			Append(hEditBox, '+');
			break;
		case VK_SUBTRACT:
			Append(hEditBox, '-');
			break;
		case 0x52:
			Append(hEditBox, 'r');
			break;
		case 0x53:
			Append(hEditBox, 's');
			break;

		case VK_RETURN:
		{
			size_t length = GetWindowTextLength(hEditBox);
			char* str = (char*)malloc(length + 1);
			GetWindowText(hEditBox, str, length + 1);
			if (!SpellChecker(str, length, FALSE, FALSE))
				SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"ERROR");
			free(str);
			SetFocus(hWnd);
			break;
		}
		case VK_DELETE:
			SendMessage(hEditBox, WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
	case WM_CHAR:
		switch (wparam) {
		case '+':
			Append(hEditBox, '+');
			break;
		case '-':
			Append(hEditBox, '-');
			break;
		case '/':
			Append(hEditBox, '/');
			break;
		case '|':
			Append(hEditBox, '|');
			break;
		case '*':
			BackSpace(hEditBox);
			Append(hEditBox, '*');
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wparam, lparam);
		break;
	}
	return 0;
} 