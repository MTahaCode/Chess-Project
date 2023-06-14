#pragma once

#include <iostream>
//#include "../Chess/Shapes.h"
#include "../Chess/pieces.h"
#include <windows.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class PieceTracker
{
	vector<vector<Piece*>> AllPieces;
	vector<Piece*> BlackPieces;
	vector<Piece*> WhitePieces;
	//HWND* hwnd;
public:
	PieceTracker()
	{
		//hwnd = NULL;
		Create();
	}
	void Create()
	{

		for (int i = 0; i < 8; i++)
		{
			vector<Piece*> NewRow;
			AllPieces.push_back(NewRow);
			for (int j = 0; j < 8; j++)
			{
				string position = "";
				char Row = ('1' + (/*7-*/i));
				char Column = ('A' + j);
				//cout << "\nRow: "<<Row<<" Column: "<<Column<<endl;
				position += Column;
				position += Row;;
				//cout <<endl<< position;
				if (i == 1 || i == 6)
				{
					Pawn P(position);
					AllPieces[i].push_back(new Pawn(P));
				}
				else if ((i == 0 || i== 7) && (j == 1 || j == 6))
				{
					Knight P(position);
					AllPieces[i].push_back(new Knight(P));
				}
				else if ((i == 0 || i == 7) && (j == 0 || j == 7))
				{
					Rook P(position);
					AllPieces[i].push_back(new Rook(P));
				}
				else if ((i == 0 || i == 7) && (j == 2 || j == 5))
				{
					Bishop P(position);
					AllPieces[i].push_back(new Bishop(P));
				}
				else if ((i == 0 || i==7) && (j == 4))
				{
					King P(position);
					AllPieces[i].push_back(new King(P));
				}
				else if ((i == 0 || i == 7) && (j == 3))
				{
					Queen P(position);
					AllPieces[i].push_back(new Queen(P));
				}
				else
				{
					EmptyPiece empty(position);
					AllPieces[i].push_back(new EmptyPiece(empty));
				}

				if (i == 0 || i == 1)
				{
					AllPieces[i][j]->SetColor(200, 200, 200);
					BlackPieces.push_back(AllPieces[i][j]);
				}
				else if (i == 6 || i == 7)
				{
					AllPieces[i][j]->SetColor(0, 0, 0);
					WhitePieces.push_back(AllPieces[i][j]);
				}
			}
		}
	}

	void Replace(Position p1, Position p2, bool& turn)
	{
		cout << "In the replace Fucntion\n";

		//if its the same square
		if (p1 == p2)
		{
			cout << "Its the same square\n";
			return;
		}

		//can only move the nonEmpty piece
		if (AllPieces[p1.Row][p1.Column]->isEmpty())
		{
			cout << "the piece youre moving is an empty piece\n";
			return;
		}
		
		////for black
		//if (turn == 1 && AllPieces[p1.Row][p1.Column]->GetColor() == "200200200")
		//{
		//	cout << "Trying to move black when its not its turn\n";
		//	return;
		//}
		////for white
		//else if (turn == 0 && AllPieces[p1.Row][p1.Column]->GetColor() == "000")
		//{
		//	cout << "trying to move white when its not its turn\n";
		//	return;
		//}

		//if allowed move
		if (!AllPieces[p1.Row][p1.Column]->isAllowedMove(p1,p2,AllPieces))
		{
			cout << "move is not allowed\n";
			return ;
		}

		//if not the same color
		if (AllPieces[p1.Row][p1.Column]->GetColor() == AllPieces[p2.Row][p2.Column]->GetColor())
		{
			cout << "Trying to kill youre own piece\n";
			cout << AllPieces[p2.Row][p2.Column]->getType() << endl;
			cout << AllPieces[p1.Row][p1.Column]->GetColor() << endl;
			cout << AllPieces[p2.Row][p2.Column]->GetColor() << endl;
			return;
		}
		
		//to take a piece
		if (!AllPieces[p2.Row][p2.Column]->isEmpty())
		{
			char col = 'A' + p2.Column;
			string pos = col + to_string(p2.Row+1);
			cout << "Position: " << pos << endl;
			delete AllPieces[p2.Row][p2.Column];
			AllPieces[p2.Row][p2.Column] = new EmptyPiece(pos);
		}

		/*Position temp = AllPieces[0][0].getPos();
		AllPieces[0][0].setPos(AllPieces[1][1].getPos());
		AllPieces[1][1].setPos(temp);*/
		//swap(AllPieces[0][0], AllPieces[1][1]);

		//swapping what they are pointing
		Piece* temp = AllPieces[p1.Row][p1.Column];
		AllPieces[p1.Row][p1.Column] = AllPieces[p2.Row][p2.Column];
		AllPieces[p2.Row][p2.Column] = temp;

		//swapping the positions
		Position temp1 = AllPieces[p1.Row][p1.Column]->getPos();
		AllPieces[p1.Row][p1.Column]->setPos(AllPieces[p2.Row][p2.Column]->getPos());
		AllPieces[p2.Row][p2.Column]->setPos(temp1);

		AllPieces[p1.Row][p1.Column]->CreatePiece();
		AllPieces[p2.Row][p2.Column]->CreatePiece();

		turn = !turn;
	}
	void Display(HDC& hdc)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				AllPieces[i][j]->Display(hdc);
			}
		}
	}
	/*void SetHWND(HWND& h)
	{
		hwnd = &h;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				AllPieces[i][j]->SetHWND(*hwnd);
			}
		}
	}*/
};