//
// Created by Juan Galvez on 2019-12-01.
//

#ifndef PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_TORPEDO_BOAT_H
#define PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_TORPEDO_BOAT_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

class Torpedo_boat{
private:
    string name;
    int length;
    int rowPosition;
    int columnPosition;
    bool amIHorizontal;
    char boardCharacter;

public:
    Torpedo_boat(){
        name = "Torpedo_boat";
        length = 1;
        boardCharacter = 'T';
    }

    void setPiece(int row, int column, char direction)
    {
        if(direction == 'u')
        {
            rowPosition = row-(length-1);
            columnPosition = column;
            amIHorizontal = false;
        }
        else if(direction == 'd')
        {
            rowPosition = row;
            columnPosition = column;
            amIHorizontal = false;
        }
        else if(direction == 'l')
        {
            rowPosition = row;
            columnPosition = column - (length-1);
            amIHorizontal = true;
        }
        else if(direction == 'r')
        {
            rowPosition = row;
            columnPosition = column;
            amIHorizontal = true;
        }
        else
        {
            rowPosition = -1;
            columnPosition = -1;
        }
    }

    bool isHorizontal() const
    {
        return amIHorizontal;
    }

    int getTopLeftRow() const
    {
        return rowPosition;
    }

    int getTopLeftColumn() const
    {
        return columnPosition;
    }

    int getLength() const
    {
        return length;
    }

    string getName() const
    {
        return name;
    }

    char getBoardCharacter() const
    {
        return boardCharacter;
    }
};




#endif //PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_TORPEDO_BOAT_H
