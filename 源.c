#include<windows.h>
#define TRANS_BK_COLOR RGB(255,255,255)
HINSTANCE hinst;
HBITMAP hbmpFighter;
LONG APIENTRY MainWndProc(
	HWND hwnd, 
	UINT msg, 
	WPARAM wParam, // 声明
	LPARAM lParam); // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
//HBITMAP bmpFlighter;
//HBITMAP bmpSky;
LONG CALLBACK FighterWindowProc
(HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{
	RECT rect;
	PAINTSTRUCT Ps;
	HDC hdc, hdcMem;//
					// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，读loadimage文档！！！
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		MoveWindow(hwnd, 100, 100, 100, 100, TRUE);
		hbmpFighter = (HBITMAP)LoadImage(NULL, "81214475.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//背景
		if (hbmpFighter == NULL)
		{
			MessageBox(hwnd, "bmp file not find", "ERROR!", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &Ps);//beginpaint 读文档 通知系统要开始画图了
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem,hbmpFighter);//内存dc
		GetClientRect(hwnd, &rect);//表示矩形 获得窗口大小
		StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, 550, 361, SRCCOPY);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &Ps);
		break;

	case WM_KEYDOWN:


		break;

	case WM_TIMER:


		break;
		/*case WM_LBUTTONDOWN:
		OnTimer(hwnd);
		GamePaint(hwnd);
		break;*/

	case WM_DESTROY:

		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}

BOOL RegesterFlight()
{
	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	//hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	wc.style = CS_HREDRAW | CS_VREDRAW;  // 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.lpfnWndProc = FighterWindowProc;  // 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.cbClsExtra = 0;  // no extra class memory 
	wc.cbWndExtra = 0;  // no extra window memory 
	wc.hInstance = hinst;  // handle to instance 
	wc.hIcon = NULL;   // 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hCursor = LoadCursor(NULL, // Cursor是鼠标光标，这里是设定了鼠标光标的样式。API函数
		IDC_HAND);   // 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HELP,IDC_HAND等样式 
	wc.hbrBackground = (HBRUSH)CreateSolidBrush // GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	(TRANS_BK_COLOR);  // 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.lpszMenuName = NULL;  // 窗口的菜单的资源名。
	wc.lpszClassName = "FighterClass"; // 给窗口类起一个名字，在创建窗口时需要这个名字。

									   // Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;
}

BOOL CreateFlighterWindow()
{
	HWND hwndFighter;
	hwndFighter = CreateWindowEx(
	    WS_EX_LAYERED|WS_EX_TOPMOST,
		"FighterClass",        // 窗口类名，必须是已经注册了的窗口类
		"",
		WS_POPUP | WS_VISIBLE, // 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,        // 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,        // 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,        // 窗口宽度 default width 
		CW_USEDEFAULT,        // 窗口高度 default height 
		(HWND)NULL,         // 父窗口句柄 no owner window 
		(HMENU)NULL,        // 窗口菜单的句柄 use class menu 
		hinst,           // 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);      // 指向附加数据的指针 no window-creation data 

	if (!hwndFighter)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	if (!SetLayeredWindowAttributes(hwndFighter, TRANS_BK_COLOR, 255, LWA_COLORKEY | LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}
	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwndFighter, SW_SHOW);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwndFighter);
	return TRUE;

}



/*******************************************************************************
* ##########   根据游戏界面的坐标系大小设置游戏窗口大小    ##########
*******************************************************************************/




HBITMAP bmpSky;


LONG APIENTRY MainWndProc(//主窗口消息处理函数
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{
	RECT rect;
	PAINTSTRUCT Ps;
	HDC hdc, hdcMem;//
					// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，读loadimage文档！！！
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		MoveWindow(hwnd, 100, 100, 100, 100, TRUE);
		bmpSky = (HBITMAP)LoadImage(NULL, "images.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//背景
		if (bmpSky == NULL)
		{
			MessageBox(hwnd, "bmp file not find", "ERROR!", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		if (RegesterFlight())
		{
			CreateFlighterWindow();
		}

		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &Ps);//beginpaint 读文档 通知系统要开始画图了
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, bmpSky);//内存dc
		GetClientRect(hwnd, &rect);//表示矩形 获得窗口大小
		StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, 259, 194, SRCCOPY);
		DeleteDC(hdcMem);
		//SelectObject(hdc, bmpSky);
		EndPaint(hwnd, &Ps);
		break;

	case WM_KEYDOWN:


		break;

	case WM_TIMER:


		break;
		/*case WM_LBUTTONDOWN:
		OnTimer(hwnd);
		GamePaint(hwnd);
		break;*/

	case WM_DESTROY:

		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,
		IDC_HAND);
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "MainWClass";
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}


	hwnd = CreateWindow("MainWClass", "飞机大战",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(HWND)NULL,
		(HMENU)NULL,
		hinstance,
		(LPVOID)NULL);

	if (!hwnd)
	{
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//fork clone