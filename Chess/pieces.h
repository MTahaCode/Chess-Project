#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include "../Chess/Shapes.h"


class Piece
{
protected:
    Position position;
    Square Shape;
public:
    Piece(string SquareName)
    {
        position.Row = SquareName[1] - '1';
        position.Column = SquareName[0]- 'A';
        CreatePiece();
    }
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

class Knight : public Piece
{
    RECT Head;
    RECT Torso;
    RECT Legs;
public:
    Knight(string SquareName) : Piece(SquareName)
    {
        CreatePiece();
    }
    void CreatePiece()
    {
        int center = 40;
        int CenterX = (position.Column * 80) + center;
        int CenterY = (position.Row * 80) + center;

        Torso = { CenterX - 10, CenterY - 20, CenterX + 10, CenterY + 20 };

        int HeadCenterX = CenterX + 10;
        int HeadCenterY = CenterY - 20;
        Head = { HeadCenterX - 20, HeadCenterY - 5, HeadCenterX + 20, HeadCenterY + 5 };

        int LegsCenterX = CenterX;
        int LegsCenterY = CenterY + 20;
        Legs = { LegsCenterX - 25, LegsCenterY - 10, LegsCenterX + 25, LegsCenterY + 5 };
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(Shape.color);
        FillRect(hdc, &Torso, hBrush);
        FillRect(hdc, &Head, hBrush);
        FillRect(hdc, &Legs, hBrush);
        DeleteObject(hBrush);
    }
};

class Rook : public Piece
{
    RECT Head;
    RECT Torso;
    RECT Legs;
public:
    Rook(string SquareName) : Piece(SquareName)
    {
        CreatePiece();
    }
    void CreatePiece()
    {
        int center = 40;
        int CenterX = (position.Column * 80) + center;
        int CenterY = (position.Row * 80) + center;

        Torso = { CenterX - 10, CenterY - 20, CenterX + 10, CenterY + 20 };

        int HeadCenterX = CenterX;
        int HeadCenterY = CenterY - 20;
        Head = { HeadCenterX - 20, HeadCenterY - 5, HeadCenterX + 20, HeadCenterY + 5 };

        int LegsCenterX = CenterX;
        int LegsCenterY = CenterY + 20;
        Legs = { LegsCenterX - 25, LegsCenterY - 10, LegsCenterX + 25, LegsCenterY + 5 };
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(Shape.color);
        FillRect(hdc, &Torso, hBrush);
        FillRect(hdc, &Head, hBrush);
        FillRect(hdc, &Legs, hBrush);
        DeleteObject(hBrush);
    }
};

class EmptyPiece : public Piece
{
public:
    EmptyPiece(string squareName) : Piece(squareName)
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

class Pawn : public Piece
{
    POINT torso[3];
    Circle Head;
    Triangle Torso;
public:
    Pawn(string SquareName) : Piece(SquareName)
    {
        CreatePiece();
    }
    void CreatePiece()
    {
        Head.CreateCircle(position);
        Torso.CreateTriangle(position);
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush = CreateSolidBrush(Shape.color);
        SelectObject(hdc, hBrush);
        Polygon(hdc, Torso.points, 3);
        Ellipse(hdc, Head.Left, Head.Top, Head.Right, Head.Down);
        DeleteObject(hBrush);
    }
};
