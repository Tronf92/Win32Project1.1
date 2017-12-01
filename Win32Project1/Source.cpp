#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//The main window class name
static TCHAR szWindowsClass[] = _T("Win32app");

//The string that appears in the aplication's title bar
static TCHAR szTitle[] = _T("Win32 Guided Tour Aplication");

HINSTANCE hInst;

//Forward declarations of functions included in this code module
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon (hInstance , MAKEINTRESOURCE(IDI_APPLICATION) ) ;
	wcex.hCursor = LoadCursor ( NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowsClass ;
	wcex.hIconSm = LoadIcon(wcex.hInstance , MAKEINTRESOURCE(IDI_APPLICATION));

	if(!RegisterClassEx(&wcex) ){
		MessageBox(NULL, _T("Call to Register ClassEx failed!"), _T("Win32 Guided Tour"),NULL);

		return 1;
	}

	hInst = hInstance; //store instance handle in our globar variable
	//The parameters to CreateWindow explained
	/*szWindowsClass: the name of the aplication
	szTitle : the text that appears in the title bar
	WS_OVERLAPPEDWINDOW : the type of window to create
	CW_USEDEFAULT, CW_USEDEFAULT : initial position (x,y)
	500,100 initial size (width, length)
	NULL: the parrent of this window
	NULL: this aplication does not have a menu bar
	hInstance:the 1st parameter from WinMain
	NULL: not used in this aplication*/

	HWND hWnd = CreateWindow(szWindowsClass, szTitle, WS_OVERLAPPEDWINDOW , CW_USEDEFAULT,CW_USEDEFAULT, 600,600, NULL , NULL , hInstance, NULL);

	if(!hWnd){
		MessageBox(NULL , _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL );

		return 1;

	}


	/* The parameters to show window explained
	hWnd : the value returned from CreateWindow
	nCmdShow : the 4th parameter from WinMain*/

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//Main Message loop

	MSG msg;
	while(GetMessage(&msg, NULL, 0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;

}


/*FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
Purpose: Processes messages for the main window

WM_PAINT :  Paint the main window
WM_DESTROY : post a quit message and return 
*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[]= _T("Hello World");
	
	
	
	switch (message){
	case WM_PAINT:
		hdc= BeginPaint(hWnd,&ps);
		

		//here your aplication is layed out.
		//For this introduction, we just print out "Hello World"
		//in the top left corner

		
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting) ); // end aplication-specific layout section
		
		 

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	

	return 0;
}
