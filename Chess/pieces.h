#pragma once

#include <windows.h>
#include "../Chess/Board.h"

struct Position
{
    int Row;
    int Column;
    Position(int i = 0, int j = 0) : Row(i), Column(j) {}
    bool operator==(const int& p)
    {
        if (this->Column == p && this->Row == p)
        {
            return 1;
        }
        return 0;
    }
};

class Piece
{
protected:
    Position position;
    /*COLORREF color;*/
    //HWND* hwnd;
    Square Shape;
public:
    Piece(/*HWND& h,*/ string SquareName)  //hwnd(&h)
    {
        position.Row = SquareName[1] - '1';
        position.Column = SquareName[0]- 'A';
        CreatePiece();
    }
    /*void SetHWND(HWND& h)
    {
        hwnd = &h;
    }*/
    virtual void CreatePiece()
    {
        //cout <<endl<< position.Column <<" " << position.Row<<endl;
        int CenterX = 40 + (position.Column * 80);
        int CenterY = 40 + (position.Row * 80);
        Shape.Position = { CenterX - 20, CenterY - 20, CenterX + 20, CenterY + 20 };
        Shape.color = RGB(200, 200, 200);
    }
    virtual void Display(HDC& hdc)
    {
        HBRUSH hBrush = CreateSolidBrush(Shape.color);

        FillRect(hdc, &Shape.Position, hBrush);
        DeleteObject(hBrush);
    }
    Position getPos() const
    {
        return this->position;
    }
    void setPos(const Position pos)
    {
        this->position = pos;
    }
};

class EmptyPiece : public Piece
{
public:
    EmptyPiece(/*HWND& h,*/ string squareName) : Piece(/*h,*/squareName)
    {
        CreatePiece();
    }
    void CreatePiece()
    {
        //cout <<endl<< position.Column <<" " << position.Row<<endl;
        Shape.Position = { 0, 0, 0, 0 };
        Shape.color = RGB(200, 200, 200);
    }
};

class Knight
{
    
};

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
