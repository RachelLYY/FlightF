#include<windows.h>
#define TRANS_BK_COLOR RGB(255,255,255)
HINSTANCE hinst;
HBITMAP hbmpFighter;
LONG APIENTRY MainWndProc(
	HWND hwnd, 
	UINT msg, 
	WPARAM wParam, // ����
	LPARAM lParam); // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
//HBITMAP bmpFlighter;
//HBITMAP bmpSky;
LONG CALLBACK FighterWindowProc
(HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	RECT rect;
	PAINTSTRUCT Ps;
	HDC hdc, hdcMem;//
					// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE����loadimage�ĵ�������
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		MoveWindow(hwnd, 100, 100, 100, 100, TRUE);
		hbmpFighter = (HBITMAP)LoadImage(NULL, "81214475.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//����
		if (hbmpFighter == NULL)
		{
			MessageBox(hwnd, "bmp file not find", "ERROR!", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		break;

		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &Ps);//beginpaint ���ĵ� ֪ͨϵͳҪ��ʼ��ͼ��
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem,hbmpFighter);//�ڴ�dc
		GetClientRect(hwnd, &rect);//��ʾ���� ��ô��ڴ�С
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
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	//hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	wc.style = CS_HREDRAW | CS_VREDRAW;  // ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.lpfnWndProc = FighterWindowProc;  // һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.cbClsExtra = 0;  // no extra class memory 
	wc.cbWndExtra = 0;  // no extra window memory 
	wc.hInstance = hinst;  // handle to instance 
	wc.hIcon = NULL;   // ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hCursor = LoadCursor(NULL, // Cursor������꣬�������趨����������ʽ��API����
		IDC_HAND);   // ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HELP,IDC_HAND����ʽ 
	wc.hbrBackground = (HBRUSH)CreateSolidBrush // GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	(TRANS_BK_COLOR);  // ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.lpszMenuName = NULL;  // ���ڵĲ˵�����Դ����
	wc.lpszClassName = "FighterClass"; // ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�

									   // Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;
}

BOOL CreateFlighterWindow()
{
	HWND hwndFighter;
	hwndFighter = CreateWindowEx(
	    WS_EX_LAYERED|WS_EX_TOPMOST,
		"FighterClass",        // �����������������Ѿ�ע���˵Ĵ�����
		"",
		WS_POPUP | WS_VISIBLE, // ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,        // ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,        // ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,        // ���ڿ�� default width 
		CW_USEDEFAULT,        // ���ڸ߶� default height 
		(HWND)NULL,         // �����ھ�� no owner window 
		(HMENU)NULL,        // ���ڲ˵��ľ�� use class menu 
		hinst,           // Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);      // ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwndFighter)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	if (!SetLayeredWindowAttributes(hwndFighter, TRANS_BK_COLOR, 255, LWA_COLORKEY | LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}
	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwndFighter, SW_SHOW);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwndFighter);
	return TRUE;

}



/*******************************************************************************
* ##########   ������Ϸ���������ϵ��С������Ϸ���ڴ�С    ##########
*******************************************************************************/




HBITMAP bmpSky;


LONG APIENTRY MainWndProc(//��������Ϣ������
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	RECT rect;
	PAINTSTRUCT Ps;
	HDC hdc, hdcMem;//
					// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE����loadimage�ĵ�������
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		MoveWindow(hwnd, 100, 100, 100, 100, TRUE);
		bmpSky = (HBITMAP)LoadImage(NULL, "images.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//����
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

		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &Ps);//beginpaint ���ĵ� ֪ͨϵͳҪ��ʼ��ͼ��
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, bmpSky);//�ڴ�dc
		GetClientRect(hwnd, &rect);//��ʾ���� ��ô��ڴ�С
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
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}


	hwnd = CreateWindow("MainWClass", "�ɻ���ս",
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
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
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