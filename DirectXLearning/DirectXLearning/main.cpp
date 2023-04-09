#include <windows.h>

HWND MainWindowHandle = 0;

//窗口初始化函数
bool InitWindowsApp(HINSTANCE instanceHandle, int show);

//主循环函数
int Run();

LRESULT CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR pCmdLine,int nShowCmd)
{
	if (!InitWindowsApp(hInstance,nShowCmd))
	{
		::MessageBox(0, "Init failed!", "Error", MB_OK);
		return 0;
	}
	return Run();
}

bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
	WNDCLASS wc;//一个window类的描述
	wc.style = CS_HREDRAW | CS_VREDRAW;//水平和垂直可拉伸
	wc.lpfnWndProc = WndProc;//窗口回调函数，窗口类收到消息后回调该函数，我们需要自己处理这个函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;//该窗口类属于哪个instance，window上的instan不用我们自己创建，是main函数传进来的
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);//默认窗口图标
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);//默认鼠标图标
	wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));//白色背景
	wc.lpszMenuName = 0;//不包含菜单
	wc.lpszClassName = "Hello";//该类的名字，用来对该窗口的关键标识

	if (!::RegisterClass(&wc))//注册该窗口类
	{
		::MessageBox(0, "Register class failed!", 0, 0);
		return false;
	}
	//用上面的窗口类描述创建一个窗口的实例
	MainWindowHandle = ::CreateWindow(
		"Hello"//必须跟wc.lpszClassName 保持一致
		, "Hello"//窗口名字，咱可以自己定义
		, WS_OVERLAPPEDWINDOW//重叠式窗口
		, CW_USEDEFAULT//这四个参数分别是窗口的(x,y,width,height)
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, 0
		, 0
		, instanceHandle//基于那个实例创建window
		, 0);

	if (MainWindowHandle == 0)
	{
		::MessageBox(0, "Create window failed!", 0, 0);
		return false;
	}
	//显示窗口
	::ShowWindow(MainWindowHandle, show);
	//更新窗口内容
	::UpdateWindow(MainWindowHandle);

	return true;
}

int Run()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(msg));
	//不断查询当前windows系统向咱们这个应用程序发送了哪些消息（message），消息里包含了各种事件（event）
	while (::GetMessage(&msg,0,0,0))//，可能是我们主动产生的，也可能是系统产生的事件，都会用消息的形式发到我们这个应用中的消息队列中，我们需要自己查出来
	{
		::TranslateMessage(&msg);//翻译消息
		::DispatchMessage(&msg);//分发消息，这里就是发给我们当前实例的window中的WndProc函数回调给我们
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN://窗口上单击一下出一个小弹窗
		::MessageBox(0, "Hello , world !", "Hello", MB_OK);
		return 0;
	case WM_KEYDOWN://按下esc键直接退出并且清楚window
		if (wParam == VK_ESCAPE)
		{
			::DestroyWindow(MainWindowHandle);//如果已经弹出上面的hello world 窗口来，再按esc会先销毁hello world 窗口，可见message box 也是一个 window ，一个实例可以有好几个 window
			return 0;
		}
	case WM_DESTROY://如果主动点了x号，消息队里会收到退出的的消息，从而退出消息run循环
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);//处理一些默认的消息事件，比如窗口最大化、最小化、调整大小等
}
