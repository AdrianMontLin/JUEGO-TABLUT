#include <iostream>
#include <fstream>
#include <cstdlib>
#include <locale>
#include <string>
#include "tablut.h"


using namespace std;


int main() {
        setlocale(LC_ALL, "spanish");
    
    char tablero[filas][columnas];
    EstadoJuego estado = EnPartida;
    Jugadores t_jugador1 , t_jugador2 ;
    char jugadorActual = Blanco;
    char iniciar_p= ' ', guardar = ' ';
    
    

    cout << " ¡Bienvenido!  " << endl;
    cout << " AL JUEGO TABLUT  " << endl;
    
    inicializarTablero(tablero);
    imprimirTablero(tablero);
        
        cout << "\nIngrese el nombre del jugador 1: ";
        cin  >> t_jugador1.nombre;
        cout << "Ingrese el nombre del jugador 2: ";
        cin  >> t_jugador2.nombre;
        
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
        cout << endl << "El jugador "<<t_jugador1.nombre<<" juega con ["
             << Blanco << "] y [" << Rey << "]" << endl;
        cout << endl << "El jugador "<<t_jugador2.nombre<<" juega con ["
             << Negro << "] " << endl << endl;
        while (estado == EnPartida) {
            turnoJugador(tablero, t_jugador1, t_jugador2, jugadorActual);
            imprimirTablero(tablero);
            cout << "\nDesea guardar partida? (y/n): ";
            cin >> guardar;
            if (guardar == 'y'){
                guardar_p(tablero);
            }
            imprimirTablero(tablero);
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
