#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("TextOutput");

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS wc;

    // ����������� ������ ����
    wc.hInstance = hInstance;
    wc.lpszClassName = WinName;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc))
        return 0;

    // �������� ����
    hWnd = CreateWindow(WinName, _T("�������� ��������� ������ ������"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        HWND_DESKTOP, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    // ���� ��������� ���������
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int fontSize = 12; // ��������� ������ ������
    static TCHAR text[] = _T("�������� ������ ������"); // ����� ��� ������
    static int textLength = lstrlen(text); // ����� ������

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 1000, NULL); // ��������� ������� �� 1 �������
        break;
    case WM_TIMER:
        if (fontSize < 72) // ����������� ������������� ������� ������ �� 72 ������� (1 ����)
        {
            fontSize++; // ���������� ������� ������ �� 1 �����
            InvalidateRect(hWnd, NULL, TRUE); // ���������� ����
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // ����� ������ � ������� ��������
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        // ����� ������ �� ������ ����
        RECT rect;
        GetClientRect(hWnd, &rect);
        DrawText(hdc, text, textLength, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        KillTimer(hWnd, 1); // ����������� �������
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
