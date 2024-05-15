#include "tablut.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

///*-------IMPRESIÓN DE TABLERO---------*///
void imprimirTablero(char tablero[filas][columnas]) {
  cout << "  ";
  for (int i = 0; i < filas; ++i) {
    cout << i << " ";
  }
  cout << endl;
  for (int i = 0; i < filas; ++i) {
    cout << i << " ";
    for (int j = 0; j < columnas; ++j) {
      cout << tablero[i][j] << " ";
    }
    cout << endl;
  }
}
///*-------INCIAILIZAR EL TBALERO---------*///
void inicializarTablero(char tablero[filas][columnas]) {
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      tablero[i][j] = Nada;
    }
  }

  tablero[0][3] = tablero[0][4] = tablero[0][5] = Negro;
  tablero[1][4] = Negro;
  tablero[3][0] = tablero[3][8] = Negro;
  tablero[4][0] = tablero[4][1] = tablero[4][7] = tablero[4][8] = Negro;
  tablero[5][0] = tablero[5][8] = Negro;
  tablero[7][4] = Negro;
  tablero[8][3] = tablero[8][4] = tablero[8][5] = Negro;

  tablero[4][4] = Rey;

  tablero[2][4] = Blanco;
  tablero[3][4] = Blanco;
  tablero[4][2] = tablero[4][3] = tablero[4][5] = tablero[4][6] = Blanco;
  tablero[5][4] = Blanco;
  tablero[6][4] = Blanco;
}
///*-------FUNCIÓN POSICIÓN ES VÁLIDA---------*///
bool posicionValida(int fila, int columna) {
  return fila >= 0 && fila < filas && columna >= 0 && columna < columnas;
}
///*-------FUNCIÓN POSICIÓN ESTÁ OCUPADA---------*///
bool posicionOcupada(char tablero[filas][columnas], int fila, int columna) {
  return tablero[fila][columna] != Nada;
}
///*-------FUNCIÓN ES TRONO---------*///
bool esTrono(int fila, int columna) { return (fila == 4 && columna == 4); }
///*-------FUNCIÓN ES CASTILLO---------*///
bool esCastillo(int fila, int columna) {
  return (fila == 0 && columna == 4) || (fila == 8 && columna == 4) ||
         (fila == 4 && columna == 0) || (fila == 4 && columna == 8);
}
///*-------FUNCIÓN OCUPADA POR OTRO JUGADOR---------*///
bool posicionOcupadaPorJugador(char tablero[filas][columnas], int fila,
                               int columna, char jugador) {
  return tablero[fila][columna] == jugador;
}
///*-------FUNCIÓN GUARDAR PARTIDA---------*///
bool guardar_p(char tablero[filas][columnas]) {
  string n_partida;
  bool guardado = false;

  cout << "Ingrese el nombre para la partida: ";
  cin >> n_partida;
  n_partida = n_partida + ".txt";

  ofstream archivo(n_partida.c_str());

  do {
    if (archivo.is_open()) {
      for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
          archivo << tablero[i][j] << " ";
        }
        archivo << endl;
      }
      guardado = true;
      archivo.close();
      cout << "\nPartida guardada con éxito." << endl;
    } else {
      cout << "No se pudo guardar." << endl;
    }
  } while (guardado != true);

  return guardado;
}
///*-------FUNCIÓN CARGAR PARTIDA---------*///
bool cargar_p(char tablero[filas][columnas]) {
  string n_partida = "";
  int f = 0, c = 0;

  cout << "Ingrese el nombre de la partida: ";
  cin >> n_partida;

  ifstream partida_g(n_partida + ".txt");

  if (partida_g.is_open()) {
    cout << "Tablero cargado:" << endl;
    for (f = 0; f < filas; f++)
      for (c = 0; c < columnas; c++)
        partida_g >> tablero[f][c];
    imprimirTablero(tablero);

    cout << "\nPartida cargada con éxito." << endl;
    partida_g.close();
    return true;
  } else {
    cout << "\nNo se pudo cargar la partida." << endl;
    return false;
  }
}
///*-------FUNCIÓN MOVIMIENTO VÁLIDO---------*///
bool esMovimientoValido(char tablero[filas][columnas], int filaOrigen,
                        int columnaOrigen, int filaDestino, int columnaDestino,
                        char jugadorActual) {
  if (!posicionValida(filaDestino, columnaDestino)) {
    return false;
  }

  if (posicionOcupada(tablero, filaDestino, columnaDestino) &&
      !posicionOcupadaPorJugador(tablero, filaDestino, columnaDestino,
                                 jugadorActual)) {
    return false;
  }

  if (filaOrigen != filaDestino && columnaOrigen != columnaDestino) {
    return false; // Movimiento diagonal no permitido
  }

  // Verificar si el movimiento es horizontal
  if (filaOrigen == filaDestino) {
    int pasoColumna =
        (columnaDestino - columnaOrigen) / abs(columnaDestino - columnaOrigen);
    for (int j = columnaOrigen + pasoColumna; j != columnaDestino;
         j += pasoColumna) {
      if (posicionOcupada(tablero, filaOrigen, j)) {
        return false; // Casilla ocupada en el camino
      }
    }
  }

  // Verificar si el movimiento es vertical
  if (columnaOrigen == columnaDestino) {
    int pasoFila = (filaDestino - filaOrigen) / abs(filaDestino - filaOrigen);
    for (int i = filaOrigen + pasoFila; i != filaDestino; i += pasoFila) {
      if (posicionOcupada(tablero, i, columnaOrigen)) {
        return false; // Casilla ocupada en el camino
      }
    }
  }

  return true;
}
///*-------FUNCIÓN MOVER PIEZA---------*///
void moverPieza(char tablero[filas][columnas], int filaOrigen,
                int columnaOrigen, int filaDestino, int columnaDestino) {
  tablero[filaDestino][columnaDestino] = tablero[filaOrigen][columnaOrigen];
  tablero[filaOrigen][columnaOrigen] = Nada;
}
///*-------FUNCIÓN ESTADO DE JUEGO---------*///
EstadoJuego verificarEstadoJuego(char tablero[filas][columnas]) {
  bool reyCapturado = true;

  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      if (tablero[i][j] == Rey) {
        reyCapturado = false;
        break;
      }
    }
    if (!reyCapturado) {
      break;
    }
  }

  if (reyCapturado) {
    return NegroGana;
  }

  // Verificar si el rey llegó a una esquina
  if (tablero[0][0] == Rey || tablero[0][8] == Rey || tablero[8][0] == Rey ||
      tablero[8][8] == Rey) {
    return BlancoGana;
  }

  return EnPartida;
}
///*-------FUNCIÓN VERIFICACIÓN DE CAPTURAS---------*///
void verificarCapturas(char tablero[filas][columnas], int filaDestino,
                       int columnaDestino, char jugadorActual) {
  // Verificar capturas verticales
  if (filaDestino > 1 && filaDestino < filas - 2) {
    if (tablero[filaDestino - 1][columnaDestino] != jugadorActual &&
        tablero[filaDestino - 1][columnaDestino] != Nada &&
        tablero[filaDestino - 2][columnaDestino] == jugadorActual) {
      tablero[filaDestino - 1][columnaDestino] = Nada;
    }
    if (tablero[filaDestino + 1][columnaDestino] != jugadorActual &&
        tablero[filaDestino + 1][columnaDestino] != Nada &&
        tablero[filaDestino + 2][columnaDestino] == jugadorActual) {
      tablero[filaDestino + 1][columnaDestino] = Nada;
    }
  }

  // Verificar capturas horizontales
  if (columnaDestino > 1 && columnaDestino < columnas - 2) {
    if (tablero[filaDestino][columnaDestino - 1] != jugadorActual &&
        tablero[filaDestino][columnaDestino - 1] != Nada &&
        tablero[filaDestino][columnaDestino - 2] == jugadorActual) {
      tablero[filaDestino][columnaDestino - 1] = Nada;
    }
    if (tablero[filaDestino][columnaDestino + 1] != jugadorActual &&
        tablero[filaDestino][columnaDestino + 1] != Nada &&
        tablero[filaDestino][columnaDestino + 2] == jugadorActual) {
      tablero[filaDestino][columnaDestino + 1] = Nada;
    }
  }
}
///*-------FUNCIÓN TURNO JUGADOR---------*///
void turnoJugador(char tablero[filas][columnas], Jugadores t_jugador1,
                  Jugadores t_jugador2, char jugadorActual) {
  int filaOrigen, columnaOrigen, filaDestino, columnaDestino;
  do {
    cout << "\nTurno del jugador "
         << ((jugadorActual == Blanco) ? t_jugador1.nombre : t_jugador2.nombre)
         << endl;
    cout << "Ingrese la fila y columna de la pieza que desea mover (fila "
            "columna): ";
    cin >> filaOrigen >> columnaOrigen;
    cout << "Ingrese la fila y columna de la posición de destino (fila "
            "columna): ";
    cin >> filaDestino >> columnaDestino;
    cout << endl;
  } while (!esMovimientoValido(tablero, filaOrigen, columnaOrigen, filaDestino,
                               columnaDestino, jugadorActual));
  moverPieza(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);
  verificarCapturas(tablero, filaDestino, columnaDestino, jugadorActual);
}
///*-------FUNCIÓN CAMBIAR DE JUGADOR-------*///
char cambiarJugador(char jugadorActual) {
  return (jugadorActual == Blanco) ? Negro : Blanco;
}
