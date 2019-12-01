//
// Created by Juan Galvez on 2019-12-01.
//
#include "Battleship.h"

void Battleship::Anadir_Piezas_Jugador() {
    bool correctPlacement;
    do{
        Mostrar_Tablero();
        correctPlacement = Poner_Pieza_Posicion(playerSub);
        if(!correctPlacement)
        {
            cout << "Poner una direccion valida"<<endl;
        }
    }while(!correctPlacement);

    Anadir_Pieza_Tablero(playerBoard, playerSub);
}

void Battleship::Anadir_Piezas_PC(string s) {
    ifstream in;
    if(s != "")
    {
        in.open(s.c_str());
        if(in.fail())
        {
            cout << "Error"<<endl;
        }
    }

    char tempBoard[TAMANO][TAMANO];
    for(int i=0; i<TAMANO; i++)
    {
        for(int j=0; j<TAMANO; j++)
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
            randomColumn = rand()%TAMANO;
            randomRow = rand()%TAMANO;

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
        correctPlacement = Posicion_valida(tempBoard, computerSub);
    }while(!correctPlacement);

    Anadir_Pieza_Tablero(tempBoard, computerSub);
    in.close();
}

string Battleship::Movimiento() {
    int attackRow;
    int attackColumn;
    string coordinate;

    do{
        cout << "¿Dónde te gustaria atacar?";
        coordinate = toLower(requeststring());
        attackRow = Fila_char_int(getFirstChar(coordinate));
        attackColumn = getFirstInt(coordinate)-1;
    }while( (attackRow < 0 || attackRow > TAMANO-1) || (attackColumn < 0 || attackColumn > TAMANO-1));

    int row = computerSub.getTopLeftRow();
    int column = computerSub.getTopLeftColumn();
    for(int i = 0; i < computerSub.getLength(); i++)
    {
        if(row == attackRow && column == attackColumn)
        {
            computerBoard[attackRow][attackColumn] = DANO;
            if(Esta_hundido(computerBoard,computerSub))
            {
                string result = computerSub.getName();
                result +=" Hundido En: ";
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

    computerBoard[attackRow][attackColumn] = FALLO;
    string result = "Fallo en: ";
    result +=toupper(getFirstChar(coordinate));
    result +=('0' + getFirstInt(coordinate));
    return result;
}

string Battleship::Movimiento_PC() {
    int attackRow = rand()%TAMANO;
    int attackColumn = rand()%TAMANO;

    string coordinate = "";
    coordinate+=(attackRow+'A');
    coordinate+=(attackColumn+'1');

    int row = playerSub.getTopLeftRow();
    int column = playerSub.getTopLeftColumn();
    for(int i = 0; i < playerSub.getLength(); i++)
    {
        if(row == attackRow && column == attackColumn)
        {
            playerBoard[attackRow][attackColumn] = DANO;
            if(Esta_hundido(playerBoard,playerSub))
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

    playerBoard[attackRow][attackColumn] = FALLO;

    string result="Fallo en: ";
    result += coordinate;
    return result;
}

int Battleship::Juego_Terminado() {
    int result = 0;

    int computerShipCoordinateTotal = 0;
    computerShipCoordinateTotal += computerSub.getLength();

    int playerShipCoordinateTotal = 0;
    playerShipCoordinateTotal += playerSub.getLength();


    int playerBoardHitTotal = 0;
    for(int i=0; i<TAMANO; i++){
        for(int j=0; j<TAMANO; j++)
        {
            if(playerBoard[i][j] == DANO)
            {
                playerBoardHitTotal++;
            }
        }
    }
    if(playerBoardHitTotal == playerShipCoordinateTotal){
        result+=1;
    }

    int computerBoardHitTotal = 0;
    for(int i=0; i<TAMANO; i++){
        for(int j=0; j<TAMANO; j++)
        {
            if(computerBoard[i][j] == DANO)
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

void Battleship::Mostrar_Tablero() {
    Mostrar_Tablero("", "", playerBoard, computerBoard);
}

void Battleship::Mostrar_Tablero(string &move1, string &move2) {
    Mostrar_Tablero(move1, move2, playerBoard, computerBoard);
}

void
Battleship::Mostrar_Tablero(const string &move1, const string &move2, char (*leftBoard)[10], char (*rightBoard)[10]) {
    cout << "  ";
    for(int i = 0; i < TAMANO; i++)
    {
        cout << setw(2) << i+1 << " ";
    }
    cout <<"                    ";
    cout << "   ";
    for(int i = 0; i < TAMANO; i++)
    {
        cout << setw(2) << i+1 << " ";
    }
    cout <<endl;

    for(int i = 0; i < TAMANO; i++)
    {
        char row = 'A'+i;
        cout << row << "  ";
        for(int j = 0; j < TAMANO; j++)
        {
            cout << leftBoard[i][j] << "  ";
        }
        cout <<"                    ";
        cout << row << "  ";
        for(int j = 0; j < TAMANO; j++)
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

bool Battleship::Poner_Pieza_Posicion(Submarine &piece) {
    cout << "¿Dónde te gustaria poner tu barco? " << toLower(piece.getName()) << " (tamaño "<<piece.getLength()<<")"<<endl;
    string coordinate = toLower(requeststring());
    cout << "¿Direccion? (up, down, left or right)"<<endl;
    string direction = toLower(requeststring());

    piece.Anadir_Piezas(Fila_char_int(getFirstChar(coordinate)), getFirstInt(coordinate)-1, getFirstChar(direction));

    return Posicion_valida(playerBoard, piece);
}

void Battleship::Anadir_Pieza_Tablero(char (*board)[10], const Submarine &piece) {
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

bool Battleship::Esta_hundido(char (*board)[10], const Submarine &piece) {
    int row = piece.getTopLeftRow();
    int column = piece.getTopLeftColumn();
    for(int i=0; i<piece.getLength(); i++)
    {
        if(board[row][column] != DANO)
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

bool Battleship::Posicion_valida(char (*board)[10], const Submarine &piece) {
    int row = piece.getTopLeftRow();
    int column = piece.getTopLeftColumn();

    if(column<0 || (column+piece.getLength()-1>TAMANO-1 && piece.isHorizontal())){
        return false;
    }
    if(row<0 || (row+piece.getLength()-1>TAMANO-1 && !piece.isHorizontal())){
        return false;
    }

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

char Battleship::getFirstChar(const string &temp) {
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

int Battleship::getFirstInt(const string &temp) {
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
