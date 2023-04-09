#include <windows.h>

HWND MainWindowHandle = 0;

//���ڳ�ʼ������
bool InitWindowsApp(HINSTANCE instanceHandle, int show);

//��ѭ������
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
	WNDCLASS wc;//һ��window�������
	wc.style = CS_HREDRAW | CS_VREDRAW;//ˮƽ�ʹ�ֱ������
	wc.lpfnWndProc = WndProc;//���ڻص��������������յ���Ϣ��ص��ú�����������Ҫ�Լ������������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;//�ô����������ĸ�instance��window�ϵ�instan���������Լ���������main������������
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);//Ĭ�ϴ���ͼ��
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);//Ĭ�����ͼ��
	wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));//��ɫ����
	wc.lpszMenuName = 0;//�������˵�
	wc.lpszClassName = "Hello";//��������֣������Ըô��ڵĹؼ���ʶ

	if (!::RegisterClass(&wc))//ע��ô�����
	{
		::MessageBox(0, "Register class failed!", 0, 0);
		return false;
	}
	//������Ĵ�������������һ�����ڵ�ʵ��
	MainWindowHandle = ::CreateWindow(
		"Hello"//�����wc.lpszClassName ����һ��
		, "Hello"//�������֣��ۿ����Լ�����
		, WS_OVERLAPPEDWINDOW//�ص�ʽ����
		, CW_USEDEFAULT//���ĸ������ֱ��Ǵ��ڵ�(x,y,width,height)
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, 0
		, 0
		, instanceHandle//�����Ǹ�ʵ������window
		, 0);

	if (MainWindowHandle == 0)
	{
		::MessageBox(0, "Create window failed!", 0, 0);
		return false;
	}
	//��ʾ����
	::ShowWindow(MainWindowHandle, show);
	//���´�������
	::UpdateWindow(MainWindowHandle);

	return true;
}

int Run()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(msg));
	//���ϲ�ѯ��ǰwindowsϵͳ���������Ӧ�ó���������Щ��Ϣ��message������Ϣ������˸����¼���event��
	while (::GetMessage(&msg,0,0,0))//���������������������ģ�Ҳ������ϵͳ�������¼�����������Ϣ����ʽ�����������Ӧ���е���Ϣ�����У�������Ҫ�Լ������
	{
		::TranslateMessage(&msg);//������Ϣ
		::DispatchMessage(&msg);//�ַ���Ϣ��������Ƿ������ǵ�ǰʵ����window�е�WndProc�����ص�������
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN://�����ϵ���һ�³�һ��С����
		::MessageBox(0, "Hello , world !", "Hello", MB_OK);
		return 0;
	case WM_KEYDOWN://����esc��ֱ���˳��������window
		if (wParam == VK_ESCAPE)
		{
			::DestroyWindow(MainWindowHandle);//����Ѿ����������hello world ���������ٰ�esc��������hello world ���ڣ��ɼ�message box Ҳ��һ�� window ��һ��ʵ�������кü��� window
			return 0;
		}
	case WM_DESTROY://�����������x�ţ���Ϣ������յ��˳��ĵ���Ϣ���Ӷ��˳���Ϣrunѭ��
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);//����һЩĬ�ϵ���Ϣ�¼������細����󻯡���С����������С��
}
