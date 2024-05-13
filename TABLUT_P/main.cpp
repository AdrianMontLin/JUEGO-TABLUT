#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <string>
#include "tablut.h"

using namespace std;


int main() {
    char tablero[filas][columnas];
    EstadoJuego estado = EnPartida;
    char jugadorActual = Blanco;
    char iniciar_p, guardar = ' ';

    setlocale(LC_ALL, "spanish");


    cout << " ¡Bienvenido!  " << endl;
    cout << " AL JUEGO TABLUT  " << endl;

    inicializarTablero(tablero);
    imprimirTablero(tablero);
        cout << "\nDesea iniciar alguna partida? (y/n): ";
        cin  >> iniciar_p;
            if (iniciar_p == 'y'){
                if(!cargar_p( tablero)){
                    cout << "No se pudo cargar la partida." << endl;
                    cout << "Cargando nuevo juego." << endl;
                    inicializarTablero(tablero);
                    estado = EnPartida;
                }

            }
    while (estado == EnPartida) {
        turnoJugador(tablero, jugadorActual);

            cout << "Desea guardar partida? (y/n): ";
            cin >> guardar;
                if (guardar == 'y'){
                    guardar_p(tablero);
                    return 0;
                }

            estado = verificarEstadoJuego(tablero);
            jugadorActual = (jugadorActual == Blanco) ? Negro : Blanco;

        }

    if (estado == BlancoGana) {
        cout << "¡El jugador Blanco ha ganado!" << endl;
    } else if (estado == NegroGana) {
        cout << "¡El jugador Negro ha ganado!" << endl;
    }

    return 0;
}
