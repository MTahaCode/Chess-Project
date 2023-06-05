#pragma once

#include <iostream>
#include "../Chess/pieces.h"
#include <windows.h>
#include <string>
#include <algorithm>
using namespace std;

class PieceTracker
{
	vector<vector<Piece*>> AllPieces;
	HDC* hdc;
public:
	PieceTracker(HDC& h) : hdc(&h)
	{
		for (int i = 0; i < 8; i++)
		{
			vector<Piece*> NewRow;
			AllPieces.push_back(NewRow);
			for (int j = 0; j < 8; j++)
			{
				string position = "";
				char Row = ('1' + i);
				char Column = ('A' + j);
				//cout << "\nRow: "<<Row<<" Column: "<<Column<<endl;
				position += Column;
				position += Row;;
				//cout <<endl<< position;
				if (i == 0 && j == 0)
				{
					Piece P(*hdc, position);
					AllPieces[i].push_back(new Piece(P));
				}
				else
				{
					EmptyPiece empty(*hdc,position);
					AllPieces[i].push_back(new EmptyPiece(empty));
				}
			}
		}
	}
	void Replace(const Position p1,const Position p2)
	{
		/*Position temp = AllPieces[0][0].getPos();
		AllPieces[0][0].setPos(AllPieces[1][1].getPos());
		AllPieces[1][1].setPos(temp);*/
		//swap(AllPieces[0][0], AllPieces[1][1]);

		//swapping what they are pointing
		Piece* temp = AllPieces[p1.Row][p1.Column];
		AllPieces[p1.Column][p1.Row] = AllPieces[p2.Row][p2.Column];
		AllPieces[p2.Row][p2.Column] = temp;

		//swapping the positions
		Position temp1 = AllPieces[p1.Column][p1.Row]->getPos();
		AllPieces[p1.Column][p1.Row]->setPos(AllPieces[p2.Row][p2.Column]->getPos());
		AllPieces[p2.Row][p2.Column]->setPos(temp1);

		AllPieces[p1.Column][p1.Row]->CreatePiece();
		AllPieces[p2.Row][p2.Column]->CreatePiece();
	}
	void Display()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				AllPieces[i][j]->Display();
			}
		}
	}
};