#pragma once

#include <windows.h>
#include <iostream>
//#include "../Chess/pieces.h"

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
    bool operator==(const Position& p)
    {
        if (this->Column == p.Column && this->Row == p.Row)
        {
            return 1;
        }
        return 0;
    }
    
};

struct Square
{
    RECT Position;
    int red;
    int blue;
    int green;

    /*bool operator==(const Square& s)
    {
        if (this->red == s.red && this->blue == s.blue && this->green == s.green)
        {
            return 1;
        }
        return 0;
    }*/

};

struct Circle
{
    Position Center;
    int Radius = 10;
    int Left;
    int Right;
    int Top;
    int Down;
    Circle(int x = 0, int y = 0) : Center(x,y)
    {
        CreateCircle(Center);
    }
    void CreateCircle(Position& pos)
    {
        int center = 40;
        int height = 20;
        Left = (pos.Column * 80) + center + Center.Column - Radius;
        Right = (pos.Column * 80) + center + Center.Column + Radius;
        Top = (pos.Row * 80) + center  + Center.Row - Radius - height;
        Down = (pos.Row * 80) + center + Center.Row + Radius - height;
    }
    void IncreaseHorizontal(int size)
    {
        Left -= size;
        Right += size;
    }
    void IncreaseVertical(int size)
    {
        Top -= size;
        Down += size;
    }
    void ScootLeft(int length)
    {
        Left -= length;
        Right -= length;
    }
    void ScootRight(int length)
    {
        Left += length;
        Right += length;
    }
    void ScootUp(int length)
    {
        Top -= length;
        Down -= length;
    }
    void ScootDown(int length)
    {
        Top += length;
        Down += length;
    }
};

struct Triangle
{
    POINT points[3];
    Position Center;
    int Distance = 20;
    Triangle(int x = 0, int y = 0) : Center(y, x)
    {
        CreateTriangle(Center);
    }
    void CreateTriangle(Position& pos)
    {
        int center = 40;
        points[0].x = (pos.Column * 80) + center + Center.Column;
        points[0].y = (pos.Row * 80) + center + Center.Row - Distance;

        points[1].x = (pos.Column * 80) + center + Center.Row + Distance;
        points[1].y = (pos.Row * 80) + center + Center.Row + Distance;

        points[2].x = (pos.Column * 80) + center + Center.Row - Distance;
        points[2].y = (pos.Row * 80) + center + Center.Row + Distance;
    }
};