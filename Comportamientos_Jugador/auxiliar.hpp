#ifndef COMPORTAMIENTOAUXILIAR_H
#define COMPORTAMIENTOAUXILIAR_H

#include <chrono>
#include <time.h>
#include <thread>

#include "comportamientos/comportamiento.hpp"

class ComportamientoAuxiliar : public Comportamiento
{

public:
  ComportamientoAuxiliar(unsigned int size = 0) : Comportamiento(size)
  {
    // Inicializar Variables de Estado Niveles 0,1,4
    last_action=IDLE;
    tiene_zapatillas=false;
    giro45Izq=0;
    actualMia[0]='P'; actualMia[1]='P'; actualMia[2]='P';
    visitadas = std::vector<std::vector<int>>(
    mapaResultado.size(),
    std::vector<int>(mapaResultado[0].size(), 0));
    posAnteriorF=-1; posAnteriorC=-1;
  }
  ComportamientoAuxiliar(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    // Inicializar Variables de Estado Niveles 2,3
  }
  ComportamientoAuxiliar(const ComportamientoAuxiliar &comport) : Comportamiento(comport) {}
  
  ~ComportamientoAuxiliar() {}

  Action think(Sensores sensores);
  
  int VeoCasillaInteresanteA(char i, char c, char d, bool zap);
  char ViablePorAlturaA(char casilla, int dif);
  bool ChocaConRescatador(char frente);
  void SituarSensorEnMapaA(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores);
  int mejorOpcionA(bool zap);

  int interact(Action accion, int valor);

  Action ComportamientoAuxiliarNivel_0(Sensores sensores);
  Action ComportamientoAuxiliarNivel_1(Sensores sensores);
  Action ComportamientoAuxiliarNivel_2(Sensores sensores);
  Action ComportamientoAuxiliarNivel_3(Sensores sensores);
  Action ComportamientoAuxiliarNivel_4(Sensores sensores);

private:
  // Definir Variables de Estado
  	Action last_action;
	bool tiene_zapatillas;
	int giro45Izq=0;
	char actualMia[3];
	int rumbo_anterior;
	vector<vector<int>> visitadas;
	pair<int, int> pos_c, pos_i, pos_d;
	int posAnteriorF, posAnteriorC;
};

#endif
