#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
///*-------DEFINES---------*///
#define Blanco 'B'
#define Negro 'N'
#define Rey 'R'
#define Nada  '.'
#define filas 9
#define columnas 9
///*-------ESTRUCTURAS---------*///
enum EstadoJuego {
    EnPartida,
    BlancoGana,
    NegroGana
};
///*-------FUNCIONES---------*///
void imprimirTablero(char tablero[filas][columnas]);
void inicializarTablero(char tablero[filas][columnas]);
bool posicionValida(int fila, int columna);
bool posicionOcupada(char tablero[filas][columnas], int fila, int columna);
bool esTrono(int fila, int columna);
bool esCastillo(int fila, int columna);
bool posicionOcupadaPorJugador(char tablero[filas][columnas], int fila, int columna, char jugador);
bool guardar_p(char tablero[filas][columnas]);
bool cargar_p(char tablero[filas][columnas]);
bool esMovimientoValido(char tablero[filas][columnas], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino, char jugador);
void moverPieza(char tablero[filas][columnas], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino);
EstadoJuego verificarEstadoJuego(char tablero[filas][columnas]);
void verificarCapturas(char tablero[filas][columnas], int filaDestino, int columnaDestino, char jugador);
void turnoJugador(char tablero[filas][columnas], char jugador);
