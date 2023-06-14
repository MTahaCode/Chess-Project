#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>
#include "../Chess/Shapes.h"


class Piece
{
protected:
    Position position;
    Square Shape;
    string Type;
public:
    Piece(string SquareName, string s="Piece")
    {
        position.Row = SquareName[1] - '1';
        position.Column = SquareName[0]- 'A';
        Type = s;
        CreatePiece();
    }
    virtual void CreatePiece()
    {
        //cout <<endl<< position.Column <<" " << position.Row<<endl;
        int CenterX = 40 + (position.Column * 80);
        int CenterY = 40 + (position.Row * 80);
        Shape.Position = { CenterX - 20, CenterY - 20, CenterX + 20, CenterY + 20 };
        Shape.red = 100;
        Shape.blue = 60;
        Shape.green = 60;
    }
    string GetColor()
    {
        string color = to_string(Shape.red) + to_string(Shape.blue) + to_string(Shape.green);
        //cout << color << endl;
        return color;
    }
    void SetColor(int r, int g, int b)
    {
        Shape.red = r;
        Shape.blue = g;
        Shape.green = b;
    }
    virtual void Display(HDC& hdc)
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));

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
    string getType()
    {
        return Type;
    }
    bool isEmpty()
    {
        if (this->Type == "Empty")
        {
            return 1;
        }
        return 0;
    }
    virtual bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        cout << "From the base\n";
        return 1;
    }
};

class Queen : public Piece
{
    RECT Head;
    RECT Torso;
    RECT Legs;
    Circle Spikes[3];
public:
    Queen(string SquareName) : Piece(SquareName,"Queen")
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
        int HeadCenterY = CenterY - 15;
        Head = { HeadCenterX - 20, HeadCenterY - 5, HeadCenterX + 20, HeadCenterY + 5 };

        Spikes[0].CreateCircle(position);
        Spikes[0].IncreaseHorizontal(2);
        Spikes[0].IncreaseVertical(2);

        Spikes[1].CreateCircle(position);
        Spikes[1].ScootRight(20);
        Spikes[1].ScootDown(5);

        Spikes[2].CreateCircle(position);
        Spikes[2].ScootLeft(20);
        Spikes[2].ScootDown(5);

        for (int i = 0; i < 3; i++)
        {
            Spikes[i].ScootUp(5);
            Spikes[i].IncreaseHorizontal(-2);
            Spikes[i].IncreaseVertical(-2);
        }

        /*int SpikesX = CenterX;
        int SpikesY = CenterY - 25;
        Spikes[0] = { SpikesX - 5, SpikesY - 7, SpikesX + 5, SpikesY + 5 };
        Spikes[1] = { SpikesX - 5 - 20, SpikesY - 5, SpikesX + 5 - 20, SpikesY + 5 };
        Spikes[2] = { SpikesX - 5 + 20, SpikesY - 5, SpikesX + 5 + 20, SpikesY + 5 };*/

        int LegsCenterX = CenterX;
        int LegsCenterY = CenterY + 20;
        Legs = { LegsCenterX - 25, LegsCenterY - 10, LegsCenterX + 25, LegsCenterY + 5 };
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));
        FillRect(hdc, &Torso, hBrush);
        FillRect(hdc, &Head, hBrush);
        FillRect(hdc, &Legs, hBrush);
        Ellipse(hdc, Spikes[0].Left, Spikes[0].Top, Spikes[0].Right, Spikes[0].Down);
        Ellipse(hdc, Spikes[1].Left, Spikes[1].Top, Spikes[1].Right, Spikes[1].Down);
        Ellipse(hdc, Spikes[2].Left, Spikes[2].Top, Spikes[2].Right, Spikes[2].Down);
        DeleteObject(hBrush);
    }
    bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        //for rook move
        if (p1.Column == p2.Column || p2.Row == p1.Row)
        {
            //do rook move
            if (!(p1.Row == p2.Row) && !(p1.Column == p2.Column))
            {
                return 0;
            }
            if (p1.Row == p2.Row)
            {
                /*for (int i = 0; i < abs(p1.Column - p2.Column); i++)
                {
                    if (AllPieces[p1.Row][i+abs(p1.Column - p2.Column)])
                }*/
                if (p1.Column > p2.Column)
                {
                    for (int i = p2.Column + 1; i < p1.Column; i++)
                    {
                        if (AllPieces[p1.Row][i]->getType() != "Empty")
                        {
                            return 0;
                        }
                    }
                }
                else if (p1.Column < p2.Column)
                {
                    for (int i = p1.Column + 1; i < p2.Column; i++)
                    {
                        if (!(AllPieces[p1.Row][i]->getType() == "Empty"))
                        {
                            return 0;
                        }
                    }
                }
            }
            else if (p1.Column == p2.Column)
            {
                if (p1.Row > p2.Row)
                {
                    for (int i = p2.Row + 1; i < p1.Row; i++)
                    {
                        if (!(AllPieces[i][p1.Column]->getType() == "Empty"))
                        {
                            return 0;
                        }
                    }
                }
                else if (p1.Row < p2.Row)
                {
                    for (int i = p1.Row + 1; i < p2.Row; i++)
                    {
                        if (!(AllPieces[i][p1.Column]->getType() == "Empty"))
                        {
                            return 0;
                        }
                    }
                }
            }
            return 1;

        }
        else
        {
            //do bishop move
            //checking for the diagnoal move
            bool CorrectMove = 0;
            //we make some arbitrary ones and then + or - until we find it

            int RowIncOrDec = (p1.Row < p2.Row) ? +1 : -1;
            int ColIncOrDec = (p1.Column < p2.Column) ? +1 : -1;

            Position First = p1;
            Position Second = p2;

            while (First.Row != Second.Row && First.Column != Second.Column)
            {
                if (!AllPieces[First.Row][First.Column]->isEmpty() && First.Row != p1.Row && First.Column != p1.Column)
                {
                    break;
                }
                First.Row += RowIncOrDec;
                First.Column += ColIncOrDec;
                if (First == Second)
                {
                    CorrectMove = 1;
                    break;
                }
            }

            //CorrectMove = !(abs((p1.Row + p1.Column) - (p2.Row + p2.Column)) % 2);

            return CorrectMove;
        }
        return 1;
    }
};

class Knight : public Piece
{
    RECT Head;
    RECT Torso;
    RECT Legs;
public:
    Knight(string SquareName) : Piece(SquareName,"Knight")
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
        Head = { HeadCenterX - 20, HeadCenterY - 10, HeadCenterX + 20, HeadCenterY + 5 };

        int LegsCenterX = CenterX;
        int LegsCenterY = CenterY + 20;
        Legs = { LegsCenterX - 25, LegsCenterY - 10, LegsCenterX + 25, LegsCenterY + 5 };
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));
        FillRect(hdc, &Torso, hBrush);
        FillRect(hdc, &Head, hBrush);
        FillRect(hdc, &Legs, hBrush);
        DeleteObject(hBrush);
    }
    bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        int RowDistance = abs(p1.Row-p2.Row);
        int ColDistance = abs(p1.Column-p2.Column);
        if ((RowDistance == 2 && ColDistance == 1) || (RowDistance == 1 && ColDistance == 2))
        {
            return 1;
        }
        cout << "distance problems\n";
        return 0;
    }
};

class King : public Piece
{
    RECT Head;
    RECT Torso;
    RECT Legs;
    RECT Spikes[3];
public:
    King(string SquareName) : Piece(SquareName,"King")
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
        int HeadCenterY = CenterY - 15;
        Head = { HeadCenterX - 20, HeadCenterY - 5, HeadCenterX + 20, HeadCenterY + 5 };

        int SpikesX = CenterX;
        int SpikesY = CenterY - 25;
        Spikes[0] = { SpikesX - 5, SpikesY - 7, SpikesX + 5, SpikesY + 5 };
        Spikes[1] = { SpikesX - 5 - 20, SpikesY - 5, SpikesX + 5 -20, SpikesY + 5 };
        Spikes[2] = { SpikesX - 5 + 20, SpikesY - 5, SpikesX + 5 + 20, SpikesY + 5 };

        int LegsCenterX = CenterX;
        int LegsCenterY = CenterY + 20;
        Legs = { LegsCenterX - 25, LegsCenterY - 10, LegsCenterX + 25, LegsCenterY + 5 };
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));
        FillRect(hdc, &Torso, hBrush);
        FillRect(hdc, &Head, hBrush);
        FillRect(hdc, &Legs, hBrush);
        FillRect(hdc, &Spikes[0], hBrush);
        FillRect(hdc, &Spikes[1], hBrush);
        FillRect(hdc, &Spikes[2], hBrush);
        DeleteObject(hBrush);
    }
    bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        if (abs(p1.Row - p2.Row) > 1)
        {
            cout << "Too Long Row\n";
            return 0;
        }
        if (abs(p1.Column - p2.Column) > 1)
        {
            cout << "Too Long Column\n";
            return 0;
        }
        return 1;
    }
};

class Bishop : public Piece
{
    Circle Head;
    Circle Torso;
    Circle Legs;
public:
    Bishop(string SquareName) : Piece(SquareName,"Bishop")
    {
        CreatePiece();
    }
    void CreatePiece()
    {
        int center = 40;
        int CenterX = (position.Column * 80) + center;
        int CenterY = (position.Row * 80) + center;

        Torso.CreateCircle(position);
        Torso.IncreaseVertical(15);
        Torso.ScootDown(20);

        Head.CreateCircle(position);
        Head.IncreaseVertical(2);
        Head.IncreaseHorizontal(2);

        Legs.CreateCircle(position);
        Legs.ScootDown(36);
        Legs.IncreaseHorizontal(13);
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));
        SelectObject(hdc, hBrush);
        Ellipse(hdc, Torso.Left, Torso.Top, Torso.Right, Torso.Down);
        Ellipse(hdc, Head.Left, Head.Top, Head.Right, Head.Down);
        Ellipse(hdc, Legs.Left, Legs.Top, Legs.Right, Legs.Down);
        DeleteObject(hBrush);
    }
    bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        //checking for the diagnoal move
        bool CorrectMove = 0;
        //we make some arbitrary ones and then + or - until we find it

        int RowIncOrDec = (p1.Row < p2.Row) ? +1 : -1;
        int ColIncOrDec = (p1.Column < p2.Column) ? +1 : -1;
        
        Position First = p1;
        Position Second = p2;

        while (First.Row != Second.Row && First.Column != Second.Column)
        {
            if (!AllPieces[First.Row][First.Column]->isEmpty() && First.Row != p1.Row && First.Column != p1.Column)
            {
                break;
            }
            First.Row += RowIncOrDec;
            First.Column += ColIncOrDec;
            if (First == Second)
            {
                CorrectMove = 1;
                break;
            }
        }

        //CorrectMove = !(abs((p1.Row + p1.Column) - (p2.Row + p2.Column)) % 2);

        return CorrectMove;
    }
};

class Rook : public Piece
{
    RECT Head;
    RECT Torso;
    RECT Legs;
public:
    Rook(string SquareName) : Piece(SquareName,"Rook")
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
        hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));
        FillRect(hdc, &Torso, hBrush);
        FillRect(hdc, &Head, hBrush);
        FillRect(hdc, &Legs, hBrush);
        DeleteObject(hBrush);
    }
    bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        if (!(p1.Row == p2.Row) && !(p1.Column == p2.Column))
        {
            return 0;
        }
        if (p1.Row == p2.Row)
        {
            /*for (int i = 0; i < abs(p1.Column - p2.Column); i++)
            {
                if (AllPieces[p1.Row][i+abs(p1.Column - p2.Column)])
            }*/
            if (p1.Column > p2.Column)
            {
                for (int i = p2.Column+1; i < p1.Column; i++)
                {
                    if (AllPieces[p1.Row][i]->getType() != "Empty")
                    {
                        return 0;
                    }
                }
            }
            else if (p1.Column < p2.Column)
            {
                for (int i = p1.Column+1; i < p2.Column; i++)
                {
                    if (!(AllPieces[p1.Row][i]->getType() == "Empty"))
                    {
                        return 0;
                    }
                }
            }
        }
        else if (p1.Column == p2.Column)
        {
            if (p1.Row > p2.Row)
            {
                for (int i = p2.Row+1; i < p1.Row; i++)
                {
                    if (!(AllPieces[i][p1.Column]->getType() == "Empty"))
                    {
                        return 0;
                    }
                }
            }
            else if (p1.Row < p2.Row)
            {
                for (int i = p1.Row+1; i < p2.Row; i++)
                {
                    if (!(AllPieces[i][p1.Column]->getType() == "Empty"))
                    {
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
};

class EmptyPiece : public Piece
{
public:
    EmptyPiece(string squareName) : Piece(squareName,"Empty")
    {
        CreatePiece();
    }
    void CreatePiece()
    {
        //cout <<endl<< position.Column <<" " << position.Row<<endl;
        Shape.Position = { 0, 0, 0, 0 };
        Shape.red = 60;
        Shape.blue = 60;
        Shape.green = 60;
    }
};

class Pawn : public Piece
{
    POINT torso[3];
    Circle Head;
    Triangle Torso;
    bool Moved;
public:
    Pawn(string SquareName) : Piece(SquareName,"Pawn")
    {
        Moved = 0;
        CreatePiece();
    }
    void CreatePiece()
    {
        Head.CreateCircle(position);
        Torso.CreateTriangle(position);
    }
    void Display(HDC& hdc)
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(Shape.red, Shape.blue, Shape.green));
        SelectObject(hdc, hBrush);
        Polygon(hdc, Torso.points, 3);
        Ellipse(hdc, Head.Left, Head.Top, Head.Right, Head.Down);
        DeleteObject(hBrush);
    }
    bool isAllowedMove(Position p1, Position p2, vector<vector<Piece*>> AllPieces)
    {
        //for black or white
        int Color = (AllPieces[p1.Row][p1.Column]->GetColor() == "200200200") ? -1: 1;
        
        if (Color + p2.Row != p1.Row && (Color*2) + p2.Row != p1.Row)
        {
            cout << "Finding out the color\n";
            return 0;
        }

        //for differnt column
        if (p1.Column != p2.Column)
        {
            cout << "Different Column";
            if (abs(p1.Column - p2.Column) > 1)
            {
                return 0;
            }
            if (abs(p1.Row - p2.Row) > 1)
            {
                return 0;
            }
            /*if (abs((p1.Row + p1.Column) - (p2.Row + p2.Column)) > 2)
            {
                cout << "Digonal kill is too far\n";
                return 0;
            }*/
            if (AllPieces[p2.Row][p2.Column]->isEmpty())
            //if (abs(p1.Row - p2.Row) > 1 || abs(p1.Column - p2.Column) > 1 && (AllPieces[p2.Row][p2.Column]->isEmpty()))
            {
                cout << "Diagonal kill is empty\n";
                return 0;
            }
            else
            {
                Moved = 1;
                return 1;
            }
        }
        //cout <<"The too long thing : " << abs(p1.Column - p2.Column) <<endl;
        if (abs(p1.Row - p2.Row) > 2)
        {
            cout << "Too long\n";
            return 0;
        }
        if (abs(p1.Row - p2.Row) == 2)
        {
            if (Moved)
            {
                return 0;
            }
        }
        if (!AllPieces[p2.Row][p2.Column]->isEmpty())
        {
            cout << "Something in front\n";
            return 0;
        }
        Moved = 1;
        return 1;
    }
};
