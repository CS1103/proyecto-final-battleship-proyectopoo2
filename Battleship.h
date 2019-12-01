//
// Created by Juan Galvez on 2019-11-25.
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
#include "Submarine.h"
#include "Battlecruiser.h"
#include "Torpedo_boat.h"

using namespace std;

const int TAMANO = 10; // tamaño tablero
const char DANO = 'X'; // Daño
const char FALLO = 'O'; // Fallo

class Battleship {
public:

    Battleship(){
        //JUGADOR
        for(int i =0; i < TAMANO; i++){
            for(int j=0; j < TAMANO; j++)
            {
                playerBoard[i][j] = '*';
            }
        }

        //COMPUTADORA
        for(int i =0; i < TAMANO; i++){
            for(int j=0; j < TAMANO; j++)
            {
                computerBoard[i][j] = '?';
            }
        }

        playerSub = Submarine();
        computerSub = Submarine();
    }

    void Anadir_Piezas_Jugador();

    void Anadir_Piezas_PC(string s);

    string Movimiento();

    string Movimiento_PC();

    int Juego_Terminado();

    void Mostrar_Tablero();

    void Mostrar_Tablero(string &move1, string &move2);

    void Mostrar_Tablero(const string & move1, const string & move2, char leftBoard[TAMANO][TAMANO], char rightBoard[TAMANO][TAMANO]);

    int Fila_char_int(char c){
        return c - 'a';
    }


private:
    char playerBoard[TAMANO][TAMANO];
    char computerBoard[TAMANO][TAMANO];
    Submarine playerSub;
    Submarine computerSub;

    bool Poner_Pieza_Posicion(Submarine& piece);

    void Anadir_Pieza_Tablero(char board[TAMANO][TAMANO], const Submarine& piece);
    
    bool Esta_hundido(char board[TAMANO][TAMANO], const Submarine& piece);
    
    bool Posicion_valida(char board[TAMANO][TAMANO], const Submarine& piece);


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


    char getFirstChar(const string & temp);

    int getFirstInt(const string &temp);
};
#endif //PROYECTO_FINAL_BATTLESHIP_PROYECTOPOO2_BATTLESHIP_H
