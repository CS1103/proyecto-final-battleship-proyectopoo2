//
// Created by Juan Galvez on 2019-11-25.
//

#ifndef PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_SUBMARINE_H
#define PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_SUBMARINE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

class Submarine {
private:
    string name;
    int length;
    int rowPosition;
    int columnPosition;
    bool Es_Horizontal;
    char boardCharacter;
public:
    Submarine(){
        name = "Submarine";
        length = 3;
        boardCharacter = 'S';
    }

    void Anadir_Piezas(int row, int column, char direction){
        if(direction == 'u'){
            rowPosition = row-(length-1);
            columnPosition = column;
            Es_Horizontal = false;
        }
        else if(direction == 'd'){
            rowPosition = row;
            columnPosition = column;
            Es_Horizontal = false;
        }
        else if(direction == 'l'){
            rowPosition = row;
            columnPosition = column - (length-1);
            Es_Horizontal = true;
        }
        else if(direction == 'r'){
            rowPosition = row;
            columnPosition = column;
            Es_Horizontal = true;
        }
        else{
            rowPosition = -1;
            columnPosition = -1;
        }
    }

    bool isHorizontal() const{
        return Es_Horizontal;
    }

    int getTopLeftRow() const{
        return rowPosition;
    }

    int getTopLeftColumn() const{
        return columnPosition;
    }

    int getLength() const{
        return length;
    }

    string getName() const{
        return name;
    }

    char getBoardCharacter() const{
        return boardCharacter;
    }
};
#endif //PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_SUBMARINE_H
