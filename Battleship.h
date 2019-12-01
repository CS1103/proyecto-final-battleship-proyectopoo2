//
// Created by Juan Galvez on 2019-11-30.
//

#ifndef PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_BATTLESHIP_H
#define PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_BATTLESHIP_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include "Aircraft.h"
using namespace std;
const int SIZE = 10; // tamaño tablero
const char HIT = 'X'; // Daño
const char MISS = 'O'; // Fallo

class Battleship {
public:

    Battleship(){
        //JUGADOR
        for(int i =0; i < SIZE; i++){
            for(int j=0; j < SIZE; j++)
            {
                playerBoard[i][j] = '*';
            }
        }

        //COMPUTADORA
        for(int i =0; i < SIZE; i++){
            for(int j=0; j < SIZE; j++)
            {
                computerBoard[i][j] = '?';
            }
        }

        playerSub = Submarine();
        computerSub = Submarine();
    }

    void Anadir_Piezas_Jugador(){
        bool correctPlacement;
        do{
            displayBoards();
            correctPlacement = Poner_Pieza_Posicion(playerSub);
            if(!correctPlacement)
            {
                cout << "Poner una direccion valida"<<endl;
            }
        }while(!correctPlacement);

        addPieceToBoard(playerBoard, playerSub);
    }

    void Anadir_Piezas_PC(string s){

        ifstream in;
        if(s != "")
        {
            in.open(s.c_str());
            if(in.fail())
            {
                cout << "Error"<<endl;
            }
        }

        char tempBoard[SIZE][SIZE];
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                tempBoard[i][j] = '*';
            }
        }

        bool correctPlacement;
        do{
            int randomColumn, randomRow;
            string randomDirection;
            if(s == "") //
            {
                randomColumn = rand()%SIZE;
                randomRow = rand()%SIZE;

                int randomDirectionInt = rand()%4;
                randomDirection = "";
                switch(randomDirectionInt)
                {
                    case 0:
                        randomDirection = "up";
                        break;
                    case 1:
                        randomDirection = "down";
                        break;
                    case 2:
                        randomDirection = "left";
                        break;
                    case 3:
                        randomDirection = "right";
                        break;
                    default:
                        randomDirection = "";
                        break;
                }
            }
            else
            {
                if(in.eof())
                {
                    cout << "Error"<<endl;
                    exit(1);
                }

                string type;
                in >> type >> randomRow >> randomColumn >> randomDirection;
            }


            computerSub.Anadir_Piezas(randomRow, randomColumn, getFirstChar(randomDirection));
            correctPlacement = isValidPlacement(tempBoard, computerSub);
        }while(!correctPlacement);

        addPieceToBoard(tempBoard, computerSub);
        in.close();
    }

    string playerMove(){
        int attackRow;
        int attackColumn;
        string coordinate;

        do
        {
            cout << "¿Dónde te gustaria atacar?";
            coordinate = toLower(requeststring());
            attackRow = rowCharToInt(getFirstChar(coordinate));
            attackColumn = getFirstInt(coordinate)-1;
        }while( (attackRow < 0 || attackRow > SIZE-1) || (attackColumn < 0 || attackColumn > SIZE-1));

        int row = computerSub.getTopLeftRow();
        int column = computerSub.getTopLeftColumn();
        for(int i = 0; i < computerSub.getLength(); i++)
        {
            if(row == attackRow && column == attackColumn)
            {
                computerBoard[attackRow][attackColumn] = HIT;
                if(isSunk(computerBoard,computerSub))
                {
                    string result = computerSub.getName();
                    result +=" Submarino Hundido En:  ";
                    result +=toupper(getFirstChar(coordinate));
                    result +=('0'+getFirstInt(coordinate));
                    return result;
                }
                string result = "Daño en: ";
                result +=toupper(getFirstChar(coordinate));
                result +=('0' + getFirstInt(coordinate));
                return result;
            }

            if(computerSub.isHorizontal())
            {
                column++;
            }
            else
            {
                row++;
            }
        }

        computerBoard[attackRow][attackColumn] = MISS;
        string result = "Fallo en:  ";
        result +=toupper(getFirstChar(coordinate));
        result +=('0' + getFirstInt(coordinate));
        return result;
    }

    string computerMove(){
        int attackRow = rand()%SIZE;
        int attackColumn = rand()%SIZE;

        string coordinate = "";
        coordinate+=(attackRow+'A');
        coordinate+=(attackColumn+'1');

        int row = playerSub.getTopLeftRow();
        int column = playerSub.getTopLeftColumn();
        for(int i = 0; i < playerSub.getLength(); i++)
        {
            if(row == attackRow && column == attackColumn)
            {
                playerBoard[attackRow][attackColumn] = HIT;
                if(isSunk(playerBoard,playerSub))
                {
                    string result = playerSub.getName();
                    result += "Submarino Hundido En:";
                    result += coordinate;
                    return result;
                }
                string result = "Daño en: ";
                result += coordinate;
                return result;
            }

            if(playerSub.isHorizontal())
            {
                column++;
            }
            else
            {
                row++;
            }
        }

        playerBoard[attackRow][attackColumn] = MISS;

        string result="Fallo en: ";
        result += coordinate;
        return result;
    }

    int gameOver(){
        int result = 0;

        int computerShipCoordinateTotal = 0;
        computerShipCoordinateTotal += computerSub.getLength();

        int playerShipCoordinateTotal = 0;
        playerShipCoordinateTotal += playerSub.getLength();


        int playerBoardHitTotal = 0;
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                if(playerBoard[i][j] == HIT)
                {
                    playerBoardHitTotal++;
                }
            }
        }
        if(playerBoardHitTotal == playerShipCoordinateTotal)
        {
            result+=1;
        }

        int computerBoardHitTotal = 0;
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                if(computerBoard[i][j] == HIT)
                {
                    computerBoardHitTotal++;
                }
            }
        }
        if(computerBoardHitTotal == computerShipCoordinateTotal)
        {
            result+=2;
        }

        return result;
    }

    void displayBoards(){
        displayBoards("", "", playerBoard, computerBoard);
    }

    void displayBoards(string &move1, string &move2){
        displayBoards(move1, move2, playerBoard, computerBoard);
    }


    void displayBoards(const string & move1, const string & move2, char leftBoard[SIZE][SIZE], char rightBoard[SIZE][SIZE]){

        cout << "  ";
        for(int i = 0; i < SIZE; i++)
        {
            cout << setw(2) << i+1 << " ";
        }
        cout <<"                    ";
        cout << "   ";
        for(int i = 0; i < SIZE; i++)
        {
            cout << setw(2) << i+1 << " ";
        }
        cout <<endl;

        for(int i = 0; i < SIZE; i++)
        {
            char row = 'A'+i;
            cout << row << "  ";
            for(int j = 0; j < SIZE; j++)
            {
                cout << leftBoard[i][j] << "  ";
            }
            cout <<"                    ";
            cout << row << "  ";
            for(int j = 0; j < SIZE; j++)
            {
                cout << rightBoard[i][j] << "  ";
            }
            cout << endl;
        }

        if(move1 != "")
        {
            cout << "Tu movimiento: "<<endl;
            cout << move1 << endl;
        }
        if(move2 != "")
        {
            cout << "Movimiento de la PC: "<<endl;
            cout << move2 << endl;
        }
    }

    int rowCharToInt(char c){
        // (int)'a' = 97
        return c - 'a';
    }


private:
    char playerBoard[SIZE][SIZE];
    char computerBoard[SIZE][SIZE];
    Submarine playerSub;
    Submarine computerSub;
    Aircraft x;

    // query the user for where they want to put the "piece" and modify the class's variables to reflect this
    bool Poner_Pieza_Posicion(Submarine& piece){
        cout << "¿Dónde te gustaria poner tu barco? " << toLower(piece.getName()) << " (tamaño "<<piece.getLength()<<")"<<endl;
        string coordinate = toLower(requeststring());
        cout << "Direccion? (up, down, left or right)"<<endl;
        string direction = toLower(requeststring());

        piece.Anadir_Piezas(rowCharToInt(getFirstChar(coordinate)), getFirstInt(coordinate)-1, getFirstChar(direction));

        return isValidPlacement(playerBoard, piece);
    }


    // actually write the "piece" to the "board"
    void addPieceToBoard(char board[SIZE][SIZE], const Submarine& piece)
    {
        int row = piece.getTopLeftRow();
        int column = piece.getTopLeftColumn();

        for(int i =0; i < piece.getLength(); i++)
        {
            board[row][column] = piece.getBoardCharacter();

            if(piece.isHorizontal())
            {
                column++;
            }
            else
            {
                row++;
            }
        }
    }

    // checks to see if a certain "piece" is sunk or not (i.e. true if all spots of this "piece" are hit)
    bool isSunk(char board[SIZE][SIZE], const Submarine& piece)
    {
        int row = piece.getTopLeftRow();
        int column = piece.getTopLeftColumn();
        for(int i=0; i<piece.getLength(); i++)
        {
            if(board[row][column] != HIT)
            {
                return false;
            }

            if(piece.isHorizontal())
            {
                column++;
            }
            else
            {
                row++;
            }
        }

        return true;
    }

    // checks to see whether the input "piece" is a valid board position
    bool isValidPlacement(char board[SIZE][SIZE], const Submarine& piece)
    {
        int row = piece.getTopLeftRow();
        int column = piece.getTopLeftColumn();

        // check and see if the piece is actually on the board
        if(column<0 || (column+piece.getLength()-1>SIZE-1 && piece.isHorizontal()))
        {
            return false;
        }
        if(row<0 || (row+piece.getLength()-1>SIZE-1 && !piece.isHorizontal()))
        {
            return false;
        }

        // check to see if another ship is present
        for(int i =0; i < piece.getLength(); i++)
        {
            if(board[row][column] != '*')
            {
                return false;
            }

            if(piece.isHorizontal())
            {
                column++;
            }
            else
            {
                row++;
            }
        }

        return true;
    }


    string requeststring(){
        string temp;
        getline(cin, temp);

        return temp;
    }

    string toLower(string s){
        for(int i=0; i < static_cast<int>(s.length()); i++)
        {
            s[i] = tolower(s[i]);
        }

        return s;
    }


    char getFirstChar(string temp)
    {
        int i=0;
        char c;
        if(temp.length()==0)
        {
            c = 0;
        }
        else
        {
            while(i < static_cast<int>(temp.length()) && !isalpha(temp[i]))
            {
                i++;
            }
            if(i < static_cast<int>(temp.length()))
            {
                c = temp[i];
            }
            else
            {
                c = 0;
            }
        }

        return c;
    }

    int getFirstInt(string temp)
    {
        int i =0;
        if(temp.length()==0)
        {
            return 0;
        }

        while(i < static_cast<int>(temp.length()) && !isdigit(temp[i]))
        {
            i++;
        }

        string number = temp.substr(i);

        if(number == ""){
            return 0;
        }

        return atoi(number.c_str());
    }
};
#endif //PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_BATTLESHIP_H
