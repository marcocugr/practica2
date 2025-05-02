#ifndef COMPORTAMIENTOAUXILIAR_H
#define COMPORTAMIENTOAUXILIAR_H

#include <chrono>
#include <time.h>
#include <thread>
#include<list>
#include <set>

#include "comportamientos/comportamiento.hpp"

	struct EstadoA {
	 int f;
	 int c;
	 int brujula;
	 bool zapatillas;
	 bool operator==(const EstadoA &st) const{
	 return f == st.f && c == st.c && brujula == st.brujula and zapatillas ==
	st.zapatillas;
	 }
	};
	
	struct NodoA{
	 EstadoA estado;
	 list<Action> secuencia;
	 bool operator==(const NodoA &node) const{
	 return estado == node.estado;
	 }
	 bool operator<(const NodoA &node) const{
	 if (estado.f < node.estado.f) return true;
	 else if (estado.f == node.estado.f and estado.c < node.estado.c) return true;
	 else if (estado.f == node.estado.f and estado.c == node.estado.c and estado.brujula <
	node.estado.brujula) return true;
	 else if (estado.f == node.estado.f and estado.c == node.estado.c and estado.brujula ==
	node.estado.brujula and estado.zapatillas < node.estado.zapatillas) return true;
	 else return false;
	 }
	};


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
    hayPlan=false;
  }
  ComportamientoAuxiliar(const ComportamientoAuxiliar &comport) : Comportamiento(comport) {}
  
  ~ComportamientoAuxiliar() {}

  Action think(Sensores sensores);
  
  int VeoCasillaInteresanteA(char i, char c, char d, bool zap);
  char ViablePorAlturaA(char casilla, int dif);
  bool ChocaConRescatador(char frente);
  void SituarSensorEnMapaA(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores);
  int mejorOpcionA(bool zap);
  
  bool esValidaA1(char casilla, int energia_actual);
  int VeoCasillaInteresanteA1(char i, char c, char d, bool zap, int energia, int fila, int col);
  int mejorOpcionA1(bool zap, int energia);
  int costeCasillaA1(char casilla, bool zap);

  int interact(Action accion, int valor);
  
  //funciones de los niveles 2 y 3
  list<Action> AvanzaASaltosDeCaballo();
  bool CasillaAccesibleAuxiliar(const EstadoA &st, const vector<vector<unsigned char>> &terreno,
  const vector<vector<unsigned char>> &altura);
  EstadoA NextCasillaAuxiliar(const EstadoA &st);
  EstadoA applyA(Action accion, const EstadoA & st, const vector<vector<unsigned char>> &terreno,
  const vector<vector<unsigned char>> &altura);
  bool Find (const NodoA & st, const list<NodoA> &lista);
  void AnularMatrizA(vector<vector<unsigned char>> &m);
  void VisualizaPlan(const EstadoA &st, const list<Action> &plan);
  list <Action> AnchuraAuxiliar(const EstadoA &ini, const EstadoA &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);
  list <Action> AnchuraAuxiliar_V2(const EstadoA &ini, const EstadoA &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  Action ComportamientoAuxiliarNivel_0(Sensores sensores);
  Action ComportamientoAuxiliarNivel_1(Sensores sensores);
  Action ComportamientoAuxiliarNivel_2(Sensores sensores);
  Action ComportamientoAuxiliarNivel_3(Sensores sensores);
  Action ComportamientoAuxiliarNivel_4(Sensores sensores);
  
  Action ComportamientoAuxiliarNivel_E(Sensores sensores);

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
	
	//niveles 2 y 3
	list<Action> plan;
	bool hayPlan;
	
};

#endif
