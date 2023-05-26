#pragma once

#include "../Chess/pieces.h"
#include <windows.h>

class Board
{
    HDC* hdc;
    int heightOfSquare = 80;
public:
    Board(HDC& h) : hdc(&h) {}

	void Display()
	{
        for (int i = 0; i < 8; i++)//y axis
        {
            for (int j = 0; j < 8; j++)//x axis
            {


                RECT rect = { 0 + (j * heightOfSquare), 0 + (i * heightOfSquare), heightOfSquare + (j * heightOfSquare), heightOfSquare + (i * heightOfSquare) };
                HBRUSH hBrush;
                if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
                {
                    hBrush = CreateSolidBrush(RGB(0, 0, 0));
                }
                else
                {
                    hBrush = CreateSolidBrush(RGB(163, 97, 36));
                }
                //HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
                FillRect(*hdc, &rect, hBrush);
                DeleteObject(hBrush);

                //for the pawn
                if (i == 1 || i == 6)
                {
                    //cout << 40 + (j * heightOfSquare) << " " << 30 + (i * heightOfSquare) << endl;
                    Pawn p(*hdc, 40 + (j * heightOfSquare), 30 + (i * heightOfSquare), 15);
                    //Pawn p(hdc, 40 + (j * heightOfSquare), 30 + (i * heightOfSquare), 15);
                    //Pawn p(hdc, 40 , 30 , 15);
                }

                //for rooks
                if ((i == 0 || i == 7) && (j == 0 || j == 7))
                {
                    Rook r(*hdc, 40 + (j * heightOfSquare), 40 + (i * heightOfSquare));
                }
            }
        }
	}
};