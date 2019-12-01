#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include "Submarine.h"
#include "Battleship.h"
#include "Aircraft.h"

using namespace std;

int main()
{
    srand(time(0));
    Battleship game;
    cout<<"Proyecto POO2: "<<endl;

    // Generacion tablero PC
    game.Anadir_Piezas_PC("");// implementación de lectura, pero no se usa.
    //6 piezas para el jugador
    for(int i=0;i<6;i++){
        game.Anadir_Piezas_Jugador();
    }

    cout << endl;
    game.Mostrar_Tablero();
    do{
        string playerMove = game.Movimiento();
        string computerMove = game.Movimiento_PC();
        cout << endl;
        game.Mostrar_Tablero(playerMove, computerMove);
    }while(game.Juego_Terminado() == 0);

    int gameOver = game.Juego_Terminado();
    if(gameOver == 1)
    {
        cout << "Perdiste!!"<<endl;
    }
    else if(gameOver == 2)
    {
        cout << "Ganaste!!"<<endl;
    }
    else if(gameOver == 3)
    {
        cout << "Empate!!"<<endl;
    }
}