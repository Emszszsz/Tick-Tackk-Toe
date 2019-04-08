
/* int iRetKey = MessageBox(0, "Fajne okno?", "App1", MB_YESNO);
 if (iRetKey == IDYES) MessageBox(0, "Fajnie", ":)", MB_OK);
 else MessageBox(0, "Lol", ":(", MB_OK|MB_ICONQUESTION);*/

#include <Windows.h>
#include "res.h"
#include <math.h>
#pragma comment(lib, "winmm.lib")
HINSTANCE hInst;
int aaiBoard[3][3];
const int fieldX = 80;
const int fieldY = 80;
const int marginX = 10;
const int marginY = 10;
const int innerMarginX = 10;
const int innerMarginY = 10;
int currentPlayer = 1;
bool close = FALSE;
bool close2 = FALSE;


int wygrany = 2;
HWND hwnd;

void DrawX(HDC hDC, int x, int y) {     //rysowanie iksika

	MoveToEx(hDC, x + innerMarginX, y + innerMarginY, NULL);
	LineTo(hDC, x + fieldX - innerMarginX, y + fieldY - innerMarginY);
	MoveToEx(hDC, x + fieldX - innerMarginX, y + innerMarginY, NULL);
	LineTo(hDC, x + innerMarginX, y + fieldY - innerMarginY);

}

void DrawO(HDC hDC, int x, int y) {

	int cX = x + fieldX / 2;
	int cY = y + fieldY / 2;
	int R = fieldX / 2 - innerMarginX;
	MoveToEx(hDC, cX + R, cY, NULL);
	for (int alpha = 0; alpha <= 360; alpha += 10) {

		LineTo(hDC, cX + R * cos(3.141592*alpha / 180), cY + R * sin(3.141592*alpha / 180));
	}

}



INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
	{
		HDC hDC = GetDC(hwnd);      //rysowanie szachownicy
		MoveToEx(hDC, marginX, fieldY + marginY, NULL);       //punkt poczatkowy
		LineTo(hDC, marginX + 3 * fieldX, fieldY + marginY);  //linia do punktu
		MoveToEx(hDC, marginX, 2 * fieldY + marginY, NULL);
		LineTo(hDC, marginX + 3 * fieldX, 2 * fieldY + marginY);
		MoveToEx(hDC, fieldX + marginX, marginY, NULL);
		LineTo(hDC, marginX + fieldX, 3 * fieldY + marginY);
		MoveToEx(hDC, 2 * fieldX + marginX, marginY, NULL);
		LineTo(hDC, marginX + 2 * fieldX, 3 * fieldY + marginY);

		//aaiBoard[1][2] = 1;

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (aaiBoard[i][j] == 2) DrawX(hDC, marginX + i * fieldX, marginY + j * fieldY);
				else if (aaiBoard[i][j] == 1) DrawO(hDC, marginX + i * fieldX, marginY + j * fieldY);

			}

		}

		ReleaseDC(hwnd, hDC);
		if (close) {

			PlaySound((LPCSTR)"C:\\Users\\Ems\\Desktop\\Zaawansowane\\tada.wav", 0, 0);
			Sleep(200);
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
		else if (close2) {

			PlaySound((LPCSTR)"C:\\Users\\Ems\\Desktop\\Zaawansowane\\remis.wav", 0, 0);
			Sleep(200);
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
		return TRUE;
	}
	case WM_LBUTTONDOWN:
	{
		int y = HIWORD(lParam);
		int x = LOWORD(lParam);
		int i = (x - marginX) / fieldX;
		int j = (y - marginY) / fieldY;




		if (aaiBoard[i][j] == 0) {    //8 ifów konca gry + mozliwosc remisu
			aaiBoard[i][j] = currentPlayer;
			if (currentPlayer == 2) currentPlayer = 1;
			else if (currentPlayer == 1) currentPlayer = 2;


			if ((aaiBoard[0][0] == 1) && (aaiBoard[0][1] == 1) && (aaiBoard[0][2] == 1) ||
				(aaiBoard[1][0] == 1) && (aaiBoard[1][1] == 1) && (aaiBoard[1][2] == 1) ||
				(aaiBoard[2][0] == 1) && (aaiBoard[2][1] == 1) && (aaiBoard[2][2] == 1) ||
				(aaiBoard[0][0] == 1) && (aaiBoard[1][0] == 1) && (aaiBoard[2][0] == 1) ||
				(aaiBoard[0][1] == 1) && (aaiBoard[1][1] == 1) && (aaiBoard[2][1] == 1) ||
				(aaiBoard[0][2] == 1) && (aaiBoard[1][2] == 1) && (aaiBoard[2][2] == 1) ||
				(aaiBoard[0][0] == 1) && (aaiBoard[1][1] == 1) && (aaiBoard[2][2] == 1) ||
				(aaiBoard[2][0] == 1) && (aaiBoard[1][1] == 1) && (aaiBoard[0][2] == 1))
			{
				close = TRUE;
				wygrany = 0;


			}
			else if ((aaiBoard[0][0] == 2) && (aaiBoard[0][1] == 2) && (aaiBoard[0][2] == 2) ||
				(aaiBoard[1][0] == 2) && (aaiBoard[1][1] == 2) && (aaiBoard[1][2] == 2) ||
				(aaiBoard[2][0] == 2) && (aaiBoard[2][1] == 2) && (aaiBoard[2][2] == 2) ||
				(aaiBoard[0][0] == 2) && (aaiBoard[1][0] == 2) && (aaiBoard[2][0] == 2) ||
				(aaiBoard[0][1] == 2) && (aaiBoard[1][1] == 2) && (aaiBoard[2][1] == 2) ||
				(aaiBoard[0][2] == 2) && (aaiBoard[1][2] == 2) && (aaiBoard[2][2] == 2) ||
				(aaiBoard[0][0] == 2) && (aaiBoard[1][1] == 2) && (aaiBoard[2][2] == 2) ||
				(aaiBoard[2][0] == 2) && (aaiBoard[1][1] == 2) && (aaiBoard[0][2] == 2))
			{
				close = TRUE;
				wygrany = 1;

			}

			else if ((aaiBoard[0][0] != 0) && (aaiBoard[0][1] != 0) && (aaiBoard[0][2] != 0) &&
				(aaiBoard[1][0] != 0) && (aaiBoard[1][1] != 0) && (aaiBoard[1][2] != 0) &&
				(aaiBoard[2][0] != 0) && (aaiBoard[2][1] != 0) && (aaiBoard[2][2] != 0))
			{
				close2 = TRUE;
				wygrany = 2;

			}

		}

		return TRUE;
	}


	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			switch (LOWORD(wParam)) {
				return TRUE;
			}
		}
		return FALSE;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) aaiBoard[i][j] = 0;
	}
	hInst = hInstance;
	HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
	MSG msg = {};
	ShowWindow(hwndMainWindow, iCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	/*KONIEC GRY*/
	if (wygrany == 1) MessageBox(hwnd, TEXT("Wygral krzyzk"), TEXT("X"), MB_OK);
	else if (wygrany == 0)  MessageBox(hwnd, TEXT("Wygralo kolko"), TEXT("X"), MB_OK);
	else  if (wygrany == 2) MessageBox(hwnd, TEXT("Remis!!"), TEXT("XOXO"), MB_OK);


	return 0;
}

