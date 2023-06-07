#include <windows.h>
#include <iostream>
#include "../Chess/pieces.h"
#include "../Chess/Board.h"
#include "../Chess/PieceTracker.h"

using namespace std;

//LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    //cout << "Inside the switch function\n";
//
//    PAINTSTRUCT ps;
//    HDC hdc = BeginPaint(hwnd, &ps);
//    Board b(hdc);
//    PieceTracker p(hdc);
//    // Draw the board
//    b.Display();
//    p.Display();
//    EndPaint(hwnd, &ps);
//
//    static bool FirstClickChecker = 0;
//    static bool SecondClickChecker = 0;
//
//    static Position firstClick(-1, -1), secondClick(-1, -1);
//
//    if ((firstClick.Column >= 0 && firstClick.Column < 8) && (firstClick.Row >= 0 && firstClick.Row < 8) &&
//        (secondClick.Column >= 0 && secondClick.Column < 8) && (secondClick.Row >= 0 && secondClick.Row < 8) &&
//        FirstClickChecker && SecondClickChecker)
//    {
//        cout << "In the big if\n";
//        p.Replace(firstClick, secondClick);
//        FirstClickChecker = 0;
//        SecondClickChecker = 0;
//
//        firstClick.Row = -1;
//        firstClick.Column = -1;
//        secondClick.Row = -1;
//        secondClick.Column = -1;
//        //b.Display();
//        //p.Display();
//    }
//
//    switch (msg)
//    {
//    case WM_CLOSE:
//        DestroyWindow(hwnd);
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        UnregisterClass(L"ChessClass", GetModuleHandle(NULL));
//        break;
//    case WM_LBUTTONDOWN:
//    {
//        if (!FirstClickChecker)
//        {
//            firstClick.Row = HIWORD(lParam);
//            firstClick.Column = LOWORD(lParam);
//            MappingClick(firstClick);
//            FirstClickChecker = 1;
//            cout << "First: " << firstClick.Row << " " << firstClick.Column << endl;
//        }
//        else if (!SecondClickChecker)
//        {
//            secondClick.Row = HIWORD(lParam);
//            secondClick.Column = LOWORD(lParam);
//            MappingClick(secondClick);
//            SecondClickChecker = 1;
//            cout << "Second: " << secondClick.Row << " " << secondClick.Column << endl;
//        }
//
//        /*secondClick.Row = HIWORD(lParam);
//        secondClick.Column = LOWORD(lParam*/
//    }
//    break;
//    default:
//        return DefWindowProc(hwnd, msg, wParam, lParam);
//    }
//    return 0;
//}
 
void MappingClick(Position& pos)
{
    if (pos.Column > 640 || pos.Column < 0 || pos.Row > 640 || pos.Row < 0)
    {
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pos.Row >= (0 + (i * 80)) && pos.Row < 80 * (i + 1) && pos.Column >= (0 + (j * 80)) && pos.Column < 80 * (j + 1))
            {
                pos.Row = i;
                pos.Column = j;
            }
        }
    }
}

Board b;
PieceTracker p;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool FirstClickChecker = 0;
    static bool SecondClickChecker = 0;
    static Position firstClick(-1, -1), secondClick(-1, -1);

    //b.SetHWND(hwnd);
    //p.SetHWND(hwnd);
    //p.Display();

    switch (msg)
    {
    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        UnregisterClass(L"ChessClass", GetModuleHandle(NULL));
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw the board
        b.Display(hdc);

        /*PieceTracker New(hwnd);
        p = New;*/

        p.Display(hdc);
        //Sleep(500);
        /*Sleep(1000);

        Position p1;
        p1.Row = 0;
        p1.Column = 0;

        Position p2;
        p2.Row = 2;
        p2.Column = 4;
        p.Replace(p1,p2);

        b.Display();
        p.Display();

        Sleep(1000);*/

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        if (!FirstClickChecker)
        {
            firstClick.Column = LOWORD(lParam);
            firstClick.Row = HIWORD(lParam);
            MappingClick(firstClick);
            FirstClickChecker = 1;
            cout << "First: " << firstClick.Row << " " << firstClick.Column << endl;
        }
        else if (!SecondClickChecker)
        {
            secondClick.Row = HIWORD(lParam);
            secondClick.Column = LOWORD(lParam);
            MappingClick(secondClick);
            SecondClickChecker = 1;
            cout << "Second: " << secondClick.Row << " " << secondClick.Column << endl;

            /*cout << "mouse clicked";
            int xPos = LOWORD(lParam);
            int yPos = HIWORD(lParam);

            cout << "Left mouse button down at: (" << xPos << ", " << yPos << ")" << endl;*/
        }

        if (FirstClickChecker && SecondClickChecker)
        {
            p.Replace(firstClick, secondClick);
            FirstClickChecker = 0;
            SecondClickChecker = 0;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        /*static bool FirstClickChecker = 0;
        static bool SecondClickChecker = 0;
        static Position firstClick(-1, -1), secondClick(-1, -1);
        if (!FirstClickChecker)
        {
            firstClick.Column = LOWORD(lParam);
                firstClick.Row = HIWORD(lParam);
            MappingClick(firstClick);
            FirstClickChecker = 1;
            cout << "First: " << firstClick.Row << " " << firstClick.Column << endl;
        }
        else if (!SecondClickChecker)
        {
            secondClick.Row = HIWORD(lParam);
            secondClick.Column = LOWORD(lParam);
            MappingClick(secondClick);
            SecondClickChecker = 1;
            cout << "Second: " << secondClick.Row << " " << secondClick.Column << endl;
        }*/
        /*secondClick.Row = HIWORD(lParam);
        secondClick.Column = LOWORD(lParam*/
        //InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
        //case WM_LBUTTONUP:
        //{
        //    int xPos = LOWORD(lParam);
        //    int yPos = HIWORD(lParam);

        //    // Handle the left mouse button up event
        //    // You can perform your desired actions here
        //    cout << "Left mouse button up at: (" << xPos << ", " << yPos << ")" << endl;

        //    // Trigger a repaint by invalidating the entire client area
        //    //InvalidateRect(hwnd, NULL, TRUE);
        //}
        //break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    //UpdateWindow(hwnd);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    AllocConsole();
    FILE* pCout;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCout, "CONIN$", "r", stdin);

    WNDCLASSW wc = {};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ChessClass";
    wc.lpfnWndProc = WinProc;

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(
        L"ChessClass",
        L"Chess",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        700,
        20 + 700,
        NULL,
        NULL,
        hInstance,
        NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    FreeConsole(); // Release the console before exiting

    return 0;
}


//int main()
//{
//    // Step 1: Register a Window Class
//    WNDCLASS wc = {};
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = GetModuleHandle(NULL);
//    wc.lpszClassName = L"ChessClass";
//    RegisterClass(&wc);
//
//    // Step 2: Create the Window
//    HWND hwnd = CreateWindowEx(
//        0,//style of the extended window
//        L"ChessClass",//the registered class of window
//        L"Chess",//name of window
//        WS_OVERLAPPEDWINDOW,//window style
//        CW_USEDEFAULT,//for initializing horizontal position of window
//        CW_USEDEFAULT,//for initializing vertical position of window
//        700,//width
//        20+700,//height
//        NULL,//parent window handle
//        NULL,//menu handle
//        GetModuleHandle(NULL),//module that contains the window
//        NULL);//optional creation parameters
//    //checks if the window is properly shown
//    if (hwnd == NULL)
//    {
//        return 1;
//    }
//
//    // Step 3: Show and Update the Window
//    ShowWindow(hwnd, SW_SHOWDEFAULT);
//    UpdateWindow(hwnd);
//
//    // Step 4: Message Loop
//    MSG msg = {};
//    while (GetMessage(&msg, NULL, 0, 0))
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return 0;
//}