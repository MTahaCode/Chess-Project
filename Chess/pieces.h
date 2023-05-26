#pragma once

#include <windows.h>

class Pawn
{
    int centerX;
    int centerY;
    int radius;
    HDC* hdc;
public:
    Pawn(HDC& h, int CenX = 0, int CenY = 0, int rad = 0) : hdc(&h), centerX(CenX), centerY(CenY), radius(rad)
    {
        POINT points[3] = { { centerX, centerY }, { centerX - 10, centerY + 30 }, { centerX + 10, centerY + 30 } };
        HBRUSH hBrush4 = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(*hdc, hBrush4);
        Polygon(*hdc, points, 3);
        DeleteObject(hBrush4);

        HBRUSH hBrush3 = CreateSolidBrush(RGB(255, 255, 255));
        Ellipse(*hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
        DeleteObject(hBrush3);
    }
};

class Rook
{
    int centerX;
    int centerY;
    HDC* hdc;
public:
    Rook(HDC& h, int CenX = 0, int CenY = 0) : hdc(&h), centerX(CenX), centerY(CenY)
    {
        RECT torso = { centerX-10, centerY -20, centerX+10, centerY+20 };
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(*hdc, &torso, hBrush);
        DeleteObject(hBrush);

        int HeadCenterX = centerX;
        int HeadCenterY = centerY - 20;
        RECT head = { HeadCenterX - 20, HeadCenterY - 5, HeadCenterX + 20, HeadCenterY + 5 };
        hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(*hdc, &head, hBrush);
        DeleteObject(hBrush);

        int FeetCenterX = centerX;
        int FeetCenterY = centerY + 20;
        RECT feet = { FeetCenterX - 25, FeetCenterY - 10, FeetCenterX + 25, FeetCenterY + 5 };
        hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(*hdc, &feet, hBrush);
        DeleteObject(hBrush);
    }
};
