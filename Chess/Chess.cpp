#include <windows.h>
#include <iostream>
#include "../Chess/pieces.h"
#include "../Chess/Board.h"

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        UnregisterClass(L"ChessClass", GetModuleHandle(NULL));
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw the board
        Board b(hdc);
        b.Display();

        EndPaint(hwnd, &ps);
    }
    break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main()
{
    // Step 1: Register a Window Class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"ChessClass";
    RegisterClass(&wc);

    // Step 2: Create the Window
    HWND hwnd = CreateWindowEx(
        0,//style of the extended window
        L"ChessClass",//the registered class of window
        L"Chess",//name of window
        WS_OVERLAPPEDWINDOW,//window style
        CW_USEDEFAULT,//for initializing horizontal position of window
        CW_USEDEFAULT,//for initializing vertical position of window
        700,//width
        20+700,//height
        NULL,//parent window handle
        NULL,//menu handle
        GetModuleHandle(NULL),//module that contains the window
        NULL);//optional creation parameters
    //checks if the window is properly shown
    if (hwnd == NULL)
    {
        return 1;
    }

    // Step 3: Show and Update the Window
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Step 4: Message Loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}