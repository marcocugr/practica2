#ifndef COMPORTAMIENTORESCATADOR_H
#define COMPORTAMIENTORESCATADOR_H

#include <chrono>
#include <time.h>
#include <thread>
#include<list>
#include <set>
#include <cmath>
#include <queue>
#include <map>
#include <unordered_set>

#include "comportamientos/comportamiento.hpp"

	struct EstadoR {
		 int f;
		 int c;
		 int brujula;
		 bool zapatillas;
		 bool operator==(const EstadoR &st) const{
		 return f == st.f && c == st.c && brujula == st.brujula and zapatillas ==
		st.zapatillas;
		 }
		 bool operator<(const EstadoR& b) const {
	    if (f != b.f) return f < b.f;
	    if (c != b.c) return c < b.c;
	    if (brujula != b.brujula) return brujula < b.brujula;
	    return zapatillas < b.zapatillas;
	}


	};
	
	struct NodoR{
	 EstadoR estado;
	 int g; //coste
	 list<Action> secuencia;
	 bool operator==(const NodoR &node) const{
	 return estado == node.estado;
	 }
	 bool operator<(const NodoR &node) const{
	 if (estado.f < node.estado.f) return true;
	 else if (estado.f == node.estado.f and estado.c < node.estado.c) return true;
	 else if (estado.f == node.estado.f and estado.c == node.estado.c and estado.brujula <
	node.estado.brujula) return true;
	 else if (estado.f == node.estado.f and estado.c == node.estado.c and estado.brujula ==
	node.estado.brujula and estado.zapatillas < node.estado.zapatillas) return true;
	 else return false;
	 }
	};
	
	//para el Djkstra
	struct ComparadorNodoR {
	 bool operator()(const NodoR &a, const NodoR &b) const {
		return a.g > b.g; // menor g(n) tiene mayor prioridad (porque priority_queue ordena de mayor a menor)
	 }
	};


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
    posAnteriorF=-1; posAnteriorC=-1;
    doble_giroIzq=false;

  }
  ComportamientoRescatador(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    // Inicializar Variables de Estado Niveles 2,3
     hayPlan=false;
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
  
  bool esValidaR1(char casilla, int energia_actual);
  int VeoCasillaInteresanteR1(char i, char c, char d, bool zap, int energia, int fila, int col);
  int mejorOpcionR1(bool zap, int energia);
  int costeCasillaR1(char casilla);
  
  //funciones de los nivel e
  bool CasillaAccesibleRescatador(const EstadoR &st, const vector<vector<unsigned char>> &terreno,
  const vector<vector<unsigned char>> &altura);
  EstadoR NextCasillaRescatador(const EstadoR &st);
  EstadoR applyR(Action accion, const EstadoR & st, const vector<vector<unsigned char>> &terreno,
  const vector<vector<unsigned char>> &altura);
  void AnularMatrizR(vector<vector<unsigned char>> &m);
  void VisualizaPlanR(const EstadoR &st, const list<Action> &plan);
  void PintaPlanR(const list<Action> &plan, bool zap);
  bool esValidaR2(const EstadoR &estado, const vector<vector<unsigned char>> &terreno);
  bool diferenciaAlturasCorrecta(const EstadoR &e1, const EstadoR &e2, const vector<vector<unsigned char>> &altura);
  double costeMejoradoR2(const EstadoR &origen, const EstadoR &destino, Action accion, const vector<vector<unsigned char>>& terreno, const vector<vector<unsigned char>>& altura);
  bool PuedeCorrerRescatador(const EstadoR& st, const vector<vector<unsigned char>>& terreno,
                                                     const vector<vector<unsigned char>>& altura);
  
    //funciones niveles 2 y 3
  list <Action> AlgoritmoDjkstra(const EstadoR &ini, const EstadoR &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);
void procesarSucesorR(Action act, const NodoR& current_node, const EstadoR& fin,
                     const vector<vector<unsigned char>>& terreno,
                     const vector<vector<unsigned char>>& altura,
                     set<NodoR>& cerrados,
                     map<EstadoR, NodoR>& abiertos_map,
                     priority_queue<NodoR, vector<NodoR>, ComparadorNodoR>& abiertos);

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
	int posAnteriorF, posAnteriorC;
	bool doble_giroIzq;
	
	//niveles 2 y 3
	list<Action> plan;
	bool hayPlan;
	
};

#endif
