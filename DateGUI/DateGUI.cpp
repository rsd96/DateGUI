// DateGUI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DateGUI.h"
#include "DateClass.h"
#include <exception>

#define MAX_LOADSTRING 100
bool createDate(HWND hWnd);
void updateTime();

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//Textboxes
HWND dayBox;
HWND monthBox;
HWND yearBox;

//Labels
HWND header;
HWND dayName;
HWND leap;

//buttons
HWND incButton;
HWND decButton;
HWND cButton;

// Vars for creating a Date class 
DateClass d1;
int d, m, y;
string dName;
string YES = "YES";
string NO = "NO";

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DATEGUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DATEGUI));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DATEGUI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DATEGUI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int d = 1;
	int m = 2;
	int y = 3;
	const int inc = 4;
	const int dec = 5;
	const int check = 6;
	int buf1, buf2, buf3;

	
	

	switch (message)
	{

		case WM_CREATE: {
			header = CreateWindow(TEXT("static"), TEXT(" Day"), WS_VISIBLE | WS_CHILD, 100, 10, 40, 25, hWnd, (HMENU)3, NULL, NULL);
			dayBox = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL, 100, 40, 40, 25, hWnd, (HMENU)d, NULL, NULL);

			header = CreateWindow(TEXT("static"), TEXT("Month"), WS_VISIBLE | WS_CHILD, 170, 10, 50, 25, hWnd, (HMENU)3, NULL, NULL);
			monthBox = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL, 170, 40, 40, 25, hWnd, (HMENU)m, NULL, NULL);

			header = CreateWindow(TEXT("static"), TEXT(" Year"), WS_VISIBLE | WS_CHILD, 240, 10, 80, 25, hWnd, (HMENU)3, NULL, NULL);
			yearBox = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL, 240, 40, 80, 25, hWnd, (HMENU)y, NULL, NULL);

			cButton = CreateWindow(TEXT("BUTTON"), TEXT("Check"), WS_VISIBLE | WS_CHILD , 350, 30, 80, 20, hWnd, (HMENU)check, NULL, NULL);

			header = CreateWindow(TEXT("static"), TEXT(" Day Name"), WS_VISIBLE | WS_CHILD, 60, 100, 75, 25, hWnd, (HMENU)3, NULL, NULL);
			dayName = CreateWindow(TEXT("static"), TEXT(""), WS_VISIBLE | WS_CHILD, 48, 130, 100, 25, hWnd, (HMENU)3, NULL, NULL);

			header = CreateWindow(TEXT("static"), TEXT(" Leap Year"), WS_VISIBLE | WS_CHILD, 270, 100, 75, 25, hWnd, (HMENU)3, NULL, NULL);
			leap = CreateWindow(TEXT("static"), TEXT(" "), WS_VISIBLE | WS_CHILD, 270, 130, 100, 25, hWnd, (HMENU)3, NULL, NULL);

			incButton = CreateWindow(TEXT("BUTTON"), TEXT("Increment Day"), WS_CHILD | WS_VISIBLE, 80, 180, 120, 20, hWnd, (HMENU)inc, NULL, NULL);
			decButton = CreateWindow(TEXT("BUTTON"), TEXT("Decrement Day"), WS_CHILD | WS_VISIBLE, 220, 180, 120, 20, hWnd, (HMENU)dec, NULL, NULL);
		

			SendMessage(dayBox, EM_SETLIMITTEXT, 2, 0);
			SendMessage(monthBox, EM_SETLIMITTEXT, 2, 0);
			SendMessage(yearBox, EM_SETLIMITTEXT, 4, 0);
		}
				break;

		case WM_COMMAND:
		{
			
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case inc: 
					
					if (createDate(hWnd)) {
						if (d1.getDay() == 30 && d1.getMonth() == 12 && d1.getYear() == 3999)
							::MessageBox(hWnd, TEXT("Cannot increment above year 3999"), TEXT("Error!"), MB_OK);
						else {
							++d1;
							updateTime();
						}
					}
					
					break;

				case dec:
					if (createDate(hWnd)) {  
						if (d1.getDay() == 1 && d1.getMonth() == 1 && d1.getYear() == 1900)
							::MessageBox(hWnd, TEXT("Cannot decrement below year 1900"), TEXT("Error!"), MB_OK);
						else {
							--d1;
							updateTime();
						}
					}

					break;

				case check:

					if (createDate(hWnd)) 
						updateTime();
					
					break;

				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool createDate(HWND hWnd) {
	// requires only first 3 chars for day and month and 5 for year
	// since at that point the input is invalid
	// accepting more chars is waste of memory and gives chance for buffer overflow
	char day[3];
	char month[3];
	char year[5];
	
	GetWindowText(dayBox, (char *)day, 3);
	GetWindowText(monthBox, (char *)month, 3); 
	GetWindowText(yearBox, (char *)year, 5);
	
	try {
		d = atoi(day);
		m = atoi(month);
		y = atoi(year);
		
		// Year validation
		(y < 1900 || y > 3999) 
			? throw exception("Year should be between 1900 - 3999 inclusive!") 
			: d1.setYear(y);

		// Month validation
		(m < 1 || m > 12)
			? throw exception("Month should be between 1 - 12 inclusive!")
			: d1.setMonth(m);

		// Day validation 
		if (d1.getMonth() == 2 && d1.leapYear() && (d > 29 || d < 1) )
			throw exception("Day should be between 1 - 29 inclusive!");

		if (d1.getMonth() == 2 && !d1.leapYear() && (d > 28 || d < 1))
			throw exception("Day should be between 1 - 28 inclusive!");

		if (d1.isMonthsOf30() && (d > 30 || d < 1))
			throw exception("Day should be between 1 - 30 inclusive!");

		if (!d1.isMonthsOf30() && (d > 31 || d < 1))
			throw exception("Day should be between 1 - 31 inclusive!");

		// at this point, all inputs valid 
		d1.setDay(d);
	} catch (exception e) {
		::MessageBox(hWnd, TEXT(e.what()), TEXT("Error!"), MB_OK);
		return false; 
	}

	return true; 
}

void updateTime() {

	char result[10];

	d = d1.getDay(); //23
	m = d1.getMonth();
	y = d1.getYear();

	if (d1.leapYear())
		SetWindowText(leap, YES.c_str());
	else
		SetWindowText(leap, NO.c_str());

	_itoa_s(d, result, 10);
	SetWindowText(dayBox, result);

	_itoa_s(m, result, 10);
	SetWindowText(monthBox, result);

	_itoa_s(y, result, 10);
	SetWindowText(yearBox, result);

	dName = d1.DayOfWeek();
	SetWindowText(dayName, dName.c_str());
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}
