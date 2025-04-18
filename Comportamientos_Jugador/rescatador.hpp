#ifndef COMPORTAMIENTORESCATADOR_H
#define COMPORTAMIENTORESCATADOR_H

#include <chrono>
#include <time.h>
#include <thread>

#include "comportamientos/comportamiento.hpp"

class ComportamientoRescatador : public Comportamiento
{

public:
  ComportamientoRescatador(unsigned int size = 0) : Comportamiento(size)
  {
    // Inicializar Variables de Estado Niveles 0,1,4
    last_action=IDLE;
    tiene_zapatillas=false;
    giro45Izq=0;
    actualMia[0]='P'; actualMia[1]='P'; actualMia[2]='P';
    visitadas = std::vector<std::vector<int>>(
    mapaResultado.size(),
    std::vector<int>(mapaResultado[0].size(), 0)
    
);

  }
  ComportamientoRescatador(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    // Inicializar Variables de Estado Niveles 2,3
  }
  ComportamientoRescatador(const ComportamientoRescatador &comport) : Comportamiento(comport) {}
  ~ComportamientoRescatador() {}

  Action think(Sensores sensores);

  int interact(Action accion, int valor);
  int VeoCasillaInteresanteR(char i, char c, char d, bool zap);
  char ViablePorAlturaR(char casilla, int dif, bool zap);
  bool ChocaConAuxiliar(char frente);
  void SituarSensorEnMapaR(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores);
  int mejorOpcion(bool zap);

  Action ComportamientoRescatadorNivel_0(Sensores sensores);
  Action ComportamientoRescatadorNivel_1(Sensores sensores);
  Action ComportamientoRescatadorNivel_2(Sensores sensores);
  Action ComportamientoRescatadorNivel_3(Sensores sensores);
  Action ComportamientoRescatadorNivel_4(Sensores sensores);

private:
  	Action last_action;
	bool tiene_zapatillas;
	int giro45Izq=0;
	char actualMia[3];
	int rumbo_anterior;
	vector<vector<int>> visitadas;
	pair<int, int> pos_c, pos_i, pos_d;
};

#endif
