#pragma once

//#include "../Chess/Shapes.h"
#include <windows.h>
#include <vector>

using namespace std;

class Board
{
    //HWND* hwnd;
    int sizeOfSquare;
    int Columns;
    int Rows;
    COLORREF BlackSquare;
    COLORREF WhiteSquare;
    vector<vector<Square>> board;
public:
    Board(int size = 80) : sizeOfSquare(size) , Columns(8), Rows(8)
    {
        BlackSquare = RGB(163, 97, 36);
        WhiteSquare = RGB(0, 0, 0);
        CreateBoard();
    }

    /*void SetHWND(HWND& h)
    {
        hwnd = &h;
    }*/

    void CreateBoard()
    {
        for (int i = 0; i < Rows; i++)//row
        {
            vector<Square> newRow;
            board.push_back(newRow);//adding a row

            for (int j = 0; j < Columns; j++)//column
            {
                RECT NewSquare = { 0 + (j * sizeOfSquare), 0 + (i * sizeOfSquare), sizeOfSquare + (j * sizeOfSquare), sizeOfSquare + (i * sizeOfSquare) };
                if ((i % 2 && j % 2) || (!(i % 2) && !(j % 2)))
                {
                    Square BoardSquare;
                    BoardSquare.Position = NewSquare;
                    BoardSquare.color = BlackSquare;
                    board[i].push_back(BoardSquare);//adding a square
                }
                else
                {
                    Square BoardSquare;
                    BoardSquare.Position = NewSquare;
                    BoardSquare.color = WhiteSquare;
                    board[i].push_back(BoardSquare);//adding a square
                }
            }
        }
    }

	void Display(HDC& hdc)
	{
        //HDC hdc = GetDC(*hwnd);
        HBRUSH hBrush;

        for (int i = 0; i < Rows; i++)//y axis
        {
            for (int j = 0; j < Columns; j++)//x axis
            {
                Square& currentSq = board[i][j];

                hBrush = CreateSolidBrush(currentSq.color);

                FillRect(hdc, &currentSq.Position, hBrush);
                DeleteObject(hBrush);
            }
        }

        //ReleaseDC(*hwnd, hdc);
        //HBRUSH coordinates;
        ////for the pawn
        //if (i == 1 || i == 6)
        //{
        //    //cout << 40 + (j * heightOfSquare) << " " << 30 + (i * heightOfSquare) << endl;
        //    Pawn p(*hdc, 40 + (j * heightOfSquare), 30 + (i * heightOfSquare), 15);
        //    //Pawn p(hdc, 40 + (j * heightOfSquare), 30 + (i * heightOfSquare), 15);
        //    //Pawn p(hdc, 40 , 30 , 15);
        //}
        ////for rooks
        //if ((i == 0 || i == 7) && (j == 0 || j == 7))
        //{
        //    Rook r(*hdc, 40 + (j * heightOfSquare), 40 + (i * heightOfSquare));
  
    }
};