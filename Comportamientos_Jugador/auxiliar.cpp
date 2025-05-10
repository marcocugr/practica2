#include "../Comportamientos_Jugador/auxiliar.hpp"
#include <iostream>
#include "motorlib/util.h"

Action ComportamientoAuxiliar::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoAuxiliarNivel_0 (sensores);
		break;
	case 1:
		accion = ComportamientoAuxiliarNivel_1 (sensores);
		break;
	case 2:
		//accion = ComportamientoAuxiliarNivel_2 (sensores);
		break;
	case 3:
		accion = ComportamientoAuxiliarNivel_3 (sensores);
		// accion = ComportamientoAuxiliarNivel_E (sensores);
		break;
	case 4:
		accion = ComportamientoAuxiliarNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoAuxiliar::interact(Action accion, int valor)
{
	return 0;
}

int ComportamientoAuxiliar::VeoCasillaInteresanteA(char i, char c, char d, bool zap, char ai, char ac, char ad){
	//si hay un puesto base acaba
	if(c=='X' and ac!='r') return 2; 
	else if (i=='X' and ai!='r') return 1;
	else if (d=='X' and ad!='r') return 3;
	
	//pillar zapatillas si no tiene
	//if(!zap){ 
		if(c=='D') return 2;
		else if(i=='D') return 1;
		else if(d=='D') return 3;
	//}
	
	//si hay algun camino
	if(c=='C' || i=='C' || d=='C'){
		int visitadas_centro=10000, visitadas_izquierda=10000, visitadas_derecha=10000;
		
		//ponemos los valores visitados de cada casilla
		if (c=='C') visitadas_centro=visitadas[pos_c.first][pos_c.second];
		if (i=='C') visitadas_izquierda=visitadas[pos_i.first][pos_i.second];
		if (d=='C') visitadas_derecha=visitadas[pos_d.first][pos_d.second];
		
		int minimo = std::min(visitadas_centro, std::min(visitadas_izquierda, visitadas_derecha));

		if (visitadas_centro == minimo) return 2;
    		if (visitadas_izquierda == minimo) return 1;
    		return 3;
	}
	return 0; //se queda donde esta
}

char ComportamientoAuxiliar::ViablePorAlturaA(char casilla, int dif){
	if(abs(dif)<=1)
		return casilla;
	else
		return 'P';
}

bool ComportamientoAuxiliar::ChocaConRescatador(char frente){
	return (frente=='r');
}

void ComportamientoAuxiliar::SituarSensorEnMapaA(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores){

	m[sensores.posF][sensores.posC]=sensores.superficie[0];
	a[sensores.posF][sensores.posC]=sensores.cota[0];
	
	int pos=1;
	switch(sensores.rumbo){
	
		case norte: //bien
			m[sensores.posF - 1][sensores.posC - 1] = sensores.superficie[1];
			m[sensores.posF - 1][sensores.posC] = sensores.superficie[2];
			m[sensores.posF - 1][sensores.posC + 1] = sensores.superficie[3];
			m[sensores.posF - 2][sensores.posC - 2] = sensores.superficie[4];
			m[sensores.posF - 2][sensores.posC - 1] = sensores.superficie[5];
			m[sensores.posF - 2][sensores.posC] = sensores.superficie[6];
			m[sensores.posF - 2][sensores.posC + 1] = sensores.superficie[7];
			m[sensores.posF - 2][sensores.posC + 2] = sensores.superficie[8];
			m[sensores.posF - 3][sensores.posC - 3] = sensores.superficie[9];
			m[sensores.posF - 3][sensores.posC - 2] = sensores.superficie[10];
			m[sensores.posF - 3][sensores.posC - 1] = sensores.superficie[11];
			m[sensores.posF - 3][sensores.posC] = sensores.superficie[12];
			m[sensores.posF - 3][sensores.posC + 1] = sensores.superficie[13];
			m[sensores.posF - 3][sensores.posC + 2] = sensores.superficie[14];
			m[sensores.posF - 3][sensores.posC + 3] = sensores.superficie[15];
			
			a[sensores.posF - 1][sensores.posC - 1] = sensores.cota[1];
			a[sensores.posF - 1][sensores.posC] = sensores.cota[2];
			a[sensores.posF - 1][sensores.posC + 1] = sensores.cota[3];
			a[sensores.posF - 2][sensores.posC - 2] = sensores.cota[4];
			a[sensores.posF - 2][sensores.posC - 1] = sensores.cota[5];
			a[sensores.posF - 2][sensores.posC] = sensores.cota[6];
			a[sensores.posF - 2][sensores.posC + 1] = sensores.cota[7];
			a[sensores.posF - 2][sensores.posC + 2] = sensores.cota[8];
			a[sensores.posF - 3][sensores.posC - 3] = sensores.cota[9];
			a[sensores.posF - 3][sensores.posC - 2] = sensores.cota[10];
			a[sensores.posF - 3][sensores.posC - 1] = sensores.cota[11];
			a[sensores.posF - 3][sensores.posC] = sensores.cota[12];
			a[sensores.posF - 3][sensores.posC + 1] = sensores.cota[13];
			a[sensores.posF - 3][sensores.posC + 2] = sensores.cota[14];
			a[sensores.posF - 3][sensores.posC + 3] = sensores.cota[15];
			
			pos_i.first=sensores.posF-1; pos_i.second=sensores.posC-1;
			pos_c.first=sensores.posF-1; pos_c.second=sensores.posC;
			pos_d.first=sensores.posF-1; pos_d.second=sensores.posC+1;
			break;
			
		case noreste: //bien
			m[sensores.posF - 1][sensores.posC] = sensores.superficie[1];
			m[sensores.posF - 1][sensores.posC + 1] = sensores.superficie[2];
			m[sensores.posF ][sensores.posC + 1] = sensores.superficie[3];
			m[sensores.posF - 2][sensores.posC] = sensores.superficie[4];
			m[sensores.posF - 2][sensores.posC + 1] = sensores.superficie[5];
			m[sensores.posF - 2 ][sensores.posC + 2] = sensores.superficie[6];
			m[sensores.posF - 1][sensores.posC + 2] = sensores.superficie[7];
			m[sensores.posF][sensores.posC + 2] = sensores.superficie[8];
			m[sensores.posF - 3][sensores.posC] = sensores.superficie[9];
			m[sensores.posF - 3][sensores.posC + 1] = sensores.superficie[10];
			m[sensores.posF - 3][sensores.posC + 2] = sensores.superficie[11];
			m[sensores.posF - 3][sensores.posC + 3] = sensores.superficie[12];
			m[sensores.posF - 2][sensores.posC + 3] = sensores.superficie[13];
			m[sensores.posF - 1][sensores.posC + 3] = sensores.superficie[14];
			m[sensores.posF][sensores.posC + 3] = sensores.superficie[15];
			
			a[sensores.posF - 1][sensores.posC] = sensores.cota[1];
			a[sensores.posF - 1][sensores.posC + 1] = sensores.cota[2];
			a[sensores.posF ][sensores.posC + 1] = sensores.cota[3];
			a[sensores.posF - 2][sensores.posC] = sensores.cota[4];
			a[sensores.posF - 2][sensores.posC + 1] = sensores.cota[5];
			a[sensores.posF - 2 ][sensores.posC + 2] = sensores.cota[6];
			a[sensores.posF - 1][sensores.posC + 2] = sensores.cota[7];
			a[sensores.posF][sensores.posC + 2] = sensores.cota[8];
			a[sensores.posF - 3][sensores.posC] = sensores.cota[9];
			a[sensores.posF - 3][sensores.posC + 1] = sensores.cota[10];
			a[sensores.posF - 3][sensores.posC + 2] = sensores.cota[11];
			a[sensores.posF - 3][sensores.posC + 3] = sensores.cota[12];
			a[sensores.posF - 2][sensores.posC + 3] = sensores.cota[13];
			a[sensores.posF - 1][sensores.posC + 3] = sensores.cota[14];
			a[sensores.posF][sensores.posC + 3] = sensores.cota[15];
			
			pos_i.first=sensores.posF-1; pos_i.second=sensores.posC;
			pos_c.first=sensores.posF-1; pos_c.second=sensores.posC+1;
			pos_d.first=sensores.posF; pos_d.second=sensores.posC+1;
			break;
			
		case este: //bien
			m[sensores.posF - 1][sensores.posC + 1] = sensores.superficie[1];
			m[sensores.posF][sensores.posC + 1] = sensores.superficie[2];
			m[sensores.posF + 1][sensores.posC + 1] = sensores.superficie[3];
			m[sensores.posF - 2][sensores.posC + 2] = sensores.superficie[4];
			m[sensores.posF - 1][sensores.posC + 2] = sensores.superficie[5];
			m[sensores.posF][sensores.posC + 2] = sensores.superficie[6];
			m[sensores.posF + 1][sensores.posC + 2] = sensores.superficie[7];
			m[sensores.posF + 2][sensores.posC + 2] = sensores.superficie[8];
			m[sensores.posF - 3][sensores.posC + 3] = sensores.superficie[9];
			m[sensores.posF - 2][sensores.posC +3] = sensores.superficie[10];
			m[sensores.posF - 1][sensores.posC + 3] = sensores.superficie[11];
			m[sensores.posF][sensores.posC + 3] = sensores.superficie[12];
			m[sensores.posF + 1][sensores.posC + 3] = sensores.superficie[13];
			m[sensores.posF + 2][sensores.posC + 3] = sensores.superficie[14];
			m[sensores.posF + 3][sensores.posC + 3] = sensores.superficie[15];
			
			a[sensores.posF - 1][sensores.posC + 1] = sensores.cota[1];
			a[sensores.posF][sensores.posC + 1] = sensores.cota[2];
			a[sensores.posF + 1][sensores.posC + 1] = sensores.cota[3];
			a[sensores.posF - 2][sensores.posC + 2] = sensores.cota[4];
			a[sensores.posF - 1][sensores.posC + 2] = sensores.cota[5];
			a[sensores.posF][sensores.posC + 2] = sensores.cota[6];
			a[sensores.posF + 1][sensores.posC + 2] = sensores.cota[7];
			a[sensores.posF + 2][sensores.posC + 2] = sensores.cota[8];
			a[sensores.posF - 3][sensores.posC + 3] = sensores.cota[9];
			a[sensores.posF - 2][sensores.posC +3] = sensores.cota[10];
			a[sensores.posF - 1][sensores.posC + 3] = sensores.cota[11];
			a[sensores.posF][sensores.posC + 3] = sensores.cota[12];
			a[sensores.posF + 1][sensores.posC + 3] = sensores.cota[13];
			a[sensores.posF + 2][sensores.posC + 3] = sensores.cota[14];
			a[sensores.posF + 3][sensores.posC + 3] = sensores.cota[15];
			
			pos_i.first=sensores.posF-1; pos_i.second=sensores.posC+1;
			pos_c.first=sensores.posF; pos_c.second=sensores.posC+1;
			pos_d.first=sensores.posF+1; pos_d.second=sensores.posC+1;
			break;
		
		case sureste: //bien
			m[sensores.posF ][sensores.posC + 1] = sensores.superficie[1];
			m[sensores.posF + 1][sensores.posC + 1] = sensores.superficie[2];
			m[sensores.posF + 1][sensores.posC] = sensores.superficie[3];
			m[sensores.posF][sensores.posC + 2] = sensores.superficie[4];
			m[sensores.posF + 1][sensores.posC + 2] = sensores.superficie[5];
			m[sensores.posF + 2][sensores.posC + 2] = sensores.superficie[6];
			m[sensores.posF + 2][sensores.posC + 1] = sensores.superficie[7];
			m[sensores.posF + 2][sensores.posC] = sensores.superficie[8];
			m[sensores.posF][sensores.posC + 3] = sensores.superficie[9];
			m[sensores.posF + 1][sensores.posC + 3] = sensores.superficie[10];
			m[sensores.posF + 2][sensores.posC + 3] = sensores.superficie[11];
			m[sensores.posF + 3][sensores.posC + 3] = sensores.superficie[12];
			m[sensores.posF + 3][sensores.posC + 2] = sensores.superficie[13];
			m[sensores.posF + 3][sensores.posC + 1] = sensores.superficie[14];
			m[sensores.posF + 3][sensores.posC] = sensores.superficie[15];
			
			a[sensores.posF ][sensores.posC + 1] = sensores.cota[1];
			a[sensores.posF + 1][sensores.posC + 1] = sensores.cota[2];
			a[sensores.posF + 1][sensores.posC] = sensores.cota[3];
			a[sensores.posF][sensores.posC + 2] = sensores.cota[4];
			a[sensores.posF + 1][sensores.posC + 2] = sensores.cota[5];
			a[sensores.posF + 2][sensores.posC + 2] = sensores.cota[6];
			a[sensores.posF + 2][sensores.posC + 1] = sensores.cota[7];
			a[sensores.posF + 2][sensores.posC] = sensores.cota[8];
			a[sensores.posF][sensores.posC + 3] = sensores.cota[9];
			a[sensores.posF + 1][sensores.posC + 3] = sensores.cota[10];
			a[sensores.posF + 2][sensores.posC + 3] = sensores.cota[11];
			a[sensores.posF + 3][sensores.posC + 3] = sensores.cota[12];
			a[sensores.posF + 3][sensores.posC + 2] = sensores.cota[13];
			a[sensores.posF + 3][sensores.posC + 1] = sensores.cota[14];
			a[sensores.posF + 3][sensores.posC] = sensores.cota[15];
			
			pos_i.first=sensores.posF; pos_i.second=sensores.posC+1;
			pos_c.first=sensores.posF+1; pos_c.second=sensores.posC+1;
			pos_d.first=sensores.posF+1; pos_d.second=sensores.posC;
			break;
			
		
		case sur: //bien
			m[sensores.posF + 1][sensores.posC + 1] = sensores.superficie[1];
			m[sensores.posF + 1][sensores.posC] = sensores.superficie[2];
			m[sensores.posF + 1][sensores.posC - 1] = sensores.superficie[3];
			m[sensores.posF + 2][sensores.posC + 2] = sensores.superficie[4];
			m[sensores.posF + 2][sensores.posC + 1] = sensores.superficie[5];
			m[sensores.posF + 2][sensores.posC] = sensores.superficie[6];
			m[sensores.posF + 2][sensores.posC - 1] = sensores.superficie[7];
			m[sensores.posF + 2][sensores.posC - 2] = sensores.superficie[8];
			m[sensores.posF + 3][sensores.posC + 3] = sensores.superficie[9];
			m[sensores.posF + 3][sensores.posC + 2] = sensores.superficie[10];
			m[sensores.posF + 3][sensores.posC + 1] = sensores.superficie[11];
			m[sensores.posF + 3][sensores.posC] = sensores.superficie[12];
			m[sensores.posF + 3][sensores.posC - 1] = sensores.superficie[13];
			m[sensores.posF + 3][sensores.posC - 2] = sensores.superficie[14];
			m[sensores.posF + 3][sensores.posC - 3] = sensores.superficie[15];
			
			a[sensores.posF + 1][sensores.posC + 1] = sensores.cota[1];
			a[sensores.posF + 1][sensores.posC] = sensores.cota[2];
			a[sensores.posF + 1][sensores.posC - 1] = sensores.cota[3];
			a[sensores.posF + 2][sensores.posC + 2] = sensores.cota[4];
			a[sensores.posF + 2][sensores.posC + 1] = sensores.cota[5];
			a[sensores.posF + 2][sensores.posC] = sensores.cota[6];
			a[sensores.posF + 2][sensores.posC - 1] = sensores.cota[7];
			a[sensores.posF + 2][sensores.posC - 2] = sensores.cota[8];
			a[sensores.posF + 3][sensores.posC + 3] = sensores.cota[9];
			a[sensores.posF + 3][sensores.posC + 2] = sensores.cota[10];
			a[sensores.posF + 3][sensores.posC + 1] = sensores.cota[11];
			a[sensores.posF + 3][sensores.posC] = sensores.cota[12];
			a[sensores.posF + 3][sensores.posC - 1] = sensores.cota[13];
			a[sensores.posF + 3][sensores.posC - 2] = sensores.cota[14];
			a[sensores.posF + 3][sensores.posC - 3] = sensores.cota[15];
			
			pos_i.first=sensores.posF+1; pos_i.second=sensores.posC+1;
			pos_c.first=sensores.posF+1; pos_c.second=sensores.posC;
			pos_d.first=sensores.posF+1; pos_d.second=sensores.posC-1;
			break;
		
		case suroeste: //bien
			m[sensores.posF + 1][sensores.posC] = sensores.superficie[1];
			m[sensores.posF + 1][sensores.posC - 1] = sensores.superficie[2];
			m[sensores.posF][sensores.posC - 1] = sensores.superficie[3];
			m[sensores.posF + 2][sensores.posC] = sensores.superficie[4];
			m[sensores.posF + 2][sensores.posC - 1] = sensores.superficie[5];
			m[sensores.posF + 2][sensores.posC - 2] = sensores.superficie[6];
			m[sensores.posF + 1][sensores.posC - 2] = sensores.superficie[7];
			m[sensores.posF][sensores.posC - 2] = sensores.superficie[8];
			m[sensores.posF + 3][sensores.posC] = sensores.superficie[9];
			m[sensores.posF + 3][sensores.posC -1] = sensores.superficie[10];
			m[sensores.posF + 3][sensores.posC  - 2] = sensores.superficie[11];
			m[sensores.posF + 3][sensores.posC - 3] = sensores.superficie[12];
			m[sensores.posF + 2][sensores.posC - 3] = sensores.superficie[13];
			m[sensores.posF + 1][sensores.posC - 3] = sensores.superficie[14];
			m[sensores.posF][sensores.posC - 3] = sensores.superficie[15];
			
			a[sensores.posF + 1][sensores.posC] = sensores.cota[1];
			a[sensores.posF + 1][sensores.posC - 1] = sensores.cota[2];
			a[sensores.posF][sensores.posC - 1] = sensores.cota[3];
			a[sensores.posF + 2][sensores.posC] = sensores.cota[4];
			a[sensores.posF + 2][sensores.posC - 1] = sensores.cota[5];
			a[sensores.posF + 2][sensores.posC - 2] = sensores.cota[6];
			a[sensores.posF + 1][sensores.posC - 2] = sensores.cota[7];
			a[sensores.posF][sensores.posC - 2] = sensores.cota[8];
			a[sensores.posF + 3][sensores.posC] = sensores.cota[9];
			a[sensores.posF + 3][sensores.posC -1] = sensores.cota[10];
			a[sensores.posF + 3][sensores.posC  - 2] = sensores.cota[11];
			a[sensores.posF + 3][sensores.posC - 3] = sensores.cota[12];
			a[sensores.posF + 2][sensores.posC - 3] = sensores.cota[13];
			a[sensores.posF + 1][sensores.posC - 3] = sensores.cota[14];
			a[sensores.posF][sensores.posC - 3] = sensores.cota[15];
			
			pos_i.first=sensores.posF+1; pos_i.second=sensores.posC;
			pos_c.first=sensores.posF+1; pos_c.second=sensores.posC-1;
			pos_d.first=sensores.posF; pos_d.second=sensores.posC-1;
			break;
		
		case oeste: //bien
			m[sensores.posF + 1][sensores.posC - 1] = sensores.superficie[1];
			m[sensores.posF][sensores.posC - 1] = sensores.superficie[2];
			m[sensores.posF - 1][sensores.posC - 1] = sensores.superficie[3];
			m[sensores.posF + 2][sensores.posC - 2] = sensores.superficie[4];
			m[sensores.posF + 1][sensores.posC - 2] = sensores.superficie[5];
			m[sensores.posF][sensores.posC - 2] = sensores.superficie[6];
			m[sensores.posF - 1][sensores.posC - 2] = sensores.superficie[7];
			m[sensores.posF - 2][sensores.posC - 2] = sensores.superficie[8];
			m[sensores.posF + 3][sensores.posC - 3] = sensores.superficie[9];
			m[sensores.posF + 2][sensores.posC - 3] = sensores.superficie[10];
			m[sensores.posF + 1][sensores.posC  - 3] = sensores.superficie[11];
			m[sensores.posF][sensores.posC - 3] = sensores.superficie[12];
			m[sensores.posF - 1][sensores.posC - 3] = sensores.superficie[13];
			m[sensores.posF - 2][sensores.posC - 3] = sensores.superficie[14];
			m[sensores.posF - 3][sensores.posC - 3] = sensores.superficie[15];
			
			a[sensores.posF + 1][sensores.posC - 1] = sensores.cota[1];
			a[sensores.posF][sensores.posC - 1] = sensores.cota[2];
			a[sensores.posF - 1][sensores.posC - 1] = sensores.cota[3];
			a[sensores.posF + 2][sensores.posC - 2] = sensores.cota[4];
			a[sensores.posF + 1][sensores.posC - 2] = sensores.cota[5];
			a[sensores.posF][sensores.posC - 2] = sensores.cota[6];
			a[sensores.posF - 1][sensores.posC - 2] = sensores.cota[7];
			a[sensores.posF - 2][sensores.posC - 2] = sensores.cota[8];
			a[sensores.posF + 3][sensores.posC - 3] = sensores.cota[9];
			a[sensores.posF + 2][sensores.posC - 3] = sensores.cota[10];
			a[sensores.posF + 1][sensores.posC  - 3] = sensores.cota[11];
			a[sensores.posF][sensores.posC - 3] = sensores.cota[12];
			a[sensores.posF - 1][sensores.posC - 3] = sensores.cota[13];
			a[sensores.posF - 2][sensores.posC - 3] = sensores.cota[14];
			a[sensores.posF - 3][sensores.posC - 3] = sensores.cota[15];
			
			pos_i.first=sensores.posF+1; pos_i.second=sensores.posC-1;
			pos_c.first=sensores.posF; pos_c.second=sensores.posC-1;
			pos_d.first=sensores.posF-1; pos_d.second=sensores.posC-1;
			break;
		
		case noroeste: //bien
			m[sensores.posF][sensores.posC - 1] = sensores.superficie[1];
			m[sensores.posF - 1][sensores.posC - 1] = sensores.superficie[2];
			m[sensores.posF - 1][sensores.posC] = sensores.superficie[3];
			m[sensores.posF][sensores.posC - 2] = sensores.superficie[4];
			m[sensores.posF - 1][sensores.posC - 2] = sensores.superficie[5];
			m[sensores.posF - 2][sensores.posC - 2] = sensores.superficie[6];
			m[sensores.posF - 2][sensores.posC - 1] = sensores.superficie[7];
			m[sensores.posF - 2][sensores.posC] = sensores.superficie[8];
			m[sensores.posF][sensores.posC - 3] = sensores.superficie[9];
			m[sensores.posF - 1][sensores.posC - 3] = sensores.superficie[10];
			m[sensores.posF - 2][sensores.posC  - 3] = sensores.superficie[11];
			m[sensores.posF - 3][sensores.posC - 3] = sensores.superficie[12];
			m[sensores.posF - 3][sensores.posC - 2] = sensores.superficie[13];
			m[sensores.posF - 3][sensores.posC - 1] = sensores.superficie[14];
			m[sensores.posF - 3][sensores.posC] = sensores.superficie[15];
			
			a[sensores.posF][sensores.posC - 1] = sensores.cota[1];
			a[sensores.posF - 1][sensores.posC - 1] = sensores.cota[2];
			a[sensores.posF - 1][sensores.posC] = sensores.cota[3];
			a[sensores.posF][sensores.posC - 2] = sensores.cota[4];
			a[sensores.posF - 1][sensores.posC - 2] = sensores.cota[5];
			a[sensores.posF - 2][sensores.posC - 2] = sensores.cota[6];
			a[sensores.posF - 2][sensores.posC - 1] = sensores.cota[7];
			a[sensores.posF - 2][sensores.posC] = sensores.cota[8];
			a[sensores.posF][sensores.posC - 3] = sensores.cota[9];
			a[sensores.posF - 1][sensores.posC - 3] = sensores.cota[10];
			a[sensores.posF - 2][sensores.posC  - 3] = sensores.cota[11];
			a[sensores.posF - 3][sensores.posC - 3] = sensores.cota[12];
			a[sensores.posF - 3][sensores.posC - 2] = sensores.cota[13];
			a[sensores.posF - 3][sensores.posC - 1] = sensores.cota[14];
			a[sensores.posF - 3][sensores.posC] = sensores.cota[15];
			
			pos_i.first=sensores.posF; pos_i.second=sensores.posC-1;
			pos_c.first=sensores.posF-1; pos_c.second=sensores.posC-1;
			pos_d.first=sensores.posF-1; pos_d.second=sensores.posC;
			break;
			
	}

}

int ComportamientoAuxiliar::mejorOpcionA(bool zap){ //veo las opciones que tiene actualmente en su derecha e izquierda en el caso de que se haya quedado sin salida SOLO SE USA SI POS ES 0

	//llegar al puesto base y acabar
	if (actualMia[0]=='X') return 1;
	else if (actualMia[2]=='X') return 3;
	
	else if(!zap){ //pillar zapatillas
		if(actualMia[0]=='D') return 1;
		else if(actualMia[2]=='D') return 3;
	}
	//avanzar por camino
	if (actualMia[0]=='C') return 1;
	else if (actualMia[2]=='C') return 3;
	
	return 0; //se queda donde esta
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_0(Sensores sensores)
{
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	// Actualizacion de variables de estado
	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);
	if(sensores.superficie[0]=='D'){
		tiene_zapatillas=true;
	}
	
	// Definicion del comportamiento
	if(sensores.superficie[0]=='X'){ //Llegue al objetivo
		accion=IDLE;
	}
	else if (giro45Izq!=0){ //Estoy girando TURN_SL
		accion=TURN_SR;
		giro45Izq--;
	}
	else if(ChocaConRescatador(sensores.agentes[2])==true){
		//giro45Izq=1;
		accion=TURN_SR;
	}
	else {
	
	//romper ciclos
	static int magia=5;
	if (visitadas[sensores.posF][sensores.posC] >= magia) {
		int probabilidad = std::rand() % 2; // 50% de probabilidad
		magia++;
		if (probabilidad == 0) {
			    giro45Izq=6; //PONER 5 A LA DERECHA OSEA TURN_SR
			    accion=TURN_SR;
		} else {
		    return TURN_SR;
		}
    	}
	
		char i= ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c= ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d= ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
		int pos=VeoCasillaInteresanteA(i, c, d, tiene_zapatillas, sensores.agentes[1], sensores.agentes[2], sensores.agentes[3]);
		switch(pos){
			case 2:
				accion=WALK;
				break;
			case 1:
				giro45Izq=6; //PONER 5 A LA DERECHA OSEA TURN_SR
				accion=TURN_SR;
				break;
			case 3:
				accion=TURN_SR;
				break;
			case 0:
			//cout << "estoy en case 0, porque no hay salida de frente, buscando un lado" << endl;
				int mejor=0; int rumbo_deseado;
				mejor=mejorOpcionA(tiene_zapatillas);	//veo donde es mejor ir, di izquierda o derecha
				if(mejor==0){ //si no habia salida, se da media vuelta 180º
					//cout << "no podia seguir ni a derecha ni a izquierda, me doy la vuelta" << endl;
					giro45Izq=2; //CAMBIA ESTO ANTES ESTABA EN 2
					accion=TURN_SR;
					
				} else { //si es el camino izquierdo o derecho
				//cout << "puedo seguir por derecha o izquierda" << endl;
					int rumbo_deseado = (mejor == 1) ? (rumbo_anterior - 1 + 8) % 8 : (rumbo_anterior + 1) % 8; //veo cual de los dos es y ajustamos cual es la direccion deseada, si izquierda o derecha
				/*
				int diferencia = (rumbo_deseado - sensores.rumbo); //deseado menos actual nos dasu proximo rumbo osea derecha o izquierda
				
				*/
				
				
				int diferencia = (rumbo_deseado - sensores.rumbo + 8) % 8; // Esto asegura que la diferencia siempre esté en el rango [0, 7]
    
    if (diferencia > 4) {
        diferencia -= 8; // Normalizamos la diferencia a [-4, 4]
    }
				bool esDiagonal = (rumbo_deseado % 2 != 0);
				
					if(esDiagonal==false){
					//cout << "estoy en una direccion diagonal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						//cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						//cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=4;
							accion=TURN_SR;
						}
					
					} else {
					//cout << "estoy en una direccion horizontal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						//cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						//cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=5;
							accion=TURN_SR;
						}
					}
				
				}
				
				break;
		}
	
	}
	
	
	//Devolver la siguiente acion a hacer
	//Devolver la siguiente acion a hacer
	last_action=accion;
	actualMia[0]=sensores.superficie[1];
	actualMia[1]=sensores.superficie[2]; 
	actualMia[2]=sensores.superficie[3];
	if(sensores.posF!=posAnteriorF or sensores.posC!=posAnteriorC) {
		visitadas[sensores.posF][sensores.posC]++;
	}
	posAnteriorF=sensores.posF;
	posAnteriorC=sensores.posC;
	//cout << "he actualizado mi casilla de veces visitadas, ahora vale" << visitadas[sensores.posF][sensores.posC] << endl;
	rumbo_anterior=sensores.rumbo;
	return accion;
	
}

bool ComportamientoAuxiliar::esValidaA1(char casilla, int energia_actual){

	if(casilla=='B') return false;
	else if(casilla=='T' && energia_actual>=20) return true;
	else if (casilla=='A' && energia_actual>=100) return true;
	else if (casilla=='P') return false;
	else if (casilla=='C' && energia_actual>=1) return true;
	else if (casilla=='S' && energia_actual>=2) return true;
	else if (casilla=='M') return false;
	else if (casilla=='D' && energia_actual>=1) return true;
	else if (casilla=='X' && energia_actual>=1) return true;
	else return false;

}

int ComportamientoAuxiliar::costeCasillaA1(char casilla, bool zap){

	if(casilla=='B' && zap==true) return 1; //para que no la coja ni loco
	else if(casilla=='T') return 20;
	else if (casilla=='A') return 100;
	else if (casilla=='P') return 10000; //para que no la coja ni loco
	else if (casilla=='C') return 1;
	else if (casilla=='S') return 2;
	else if (casilla=='M') return 10000; //para que no la coja ni loco
	else if (casilla=='D') return 1;
	else if (casilla=='X') return 1;
	else return 100000;

}


int ComportamientoAuxiliar::VeoCasillaInteresanteA1(char i, char c, char d, bool zap, int energia, int fila, int col){

	bool valida_i=esValidaA1(i,energia);
	bool valida_c=esValidaA1(c,energia);
	bool valida_d=esValidaA1(d,energia);
	int visitadas_actual=visitadas[fila][col];
	
	
	if (valida_i || valida_c || valida_d){
	
		//prioridad a las zapatillas
		if(!zap || visitadas_actual!=3){ 
			if(c=='D') return 2;
			else if(i=='D') return 1;
			else if(d=='D') return 3;
		}
		
		//si camino o sendero return
		int opcion_i=10000, opcion_d=10000, opcion_c=10000; //visitadas con prioridad
		
		if(valida_i && (i=='C' || i=='S' || i=='X')){
			opcion_i=visitadas[pos_i.first][pos_i.second];
		}
		if(valida_c && (c=='C' || c=='S' || c=='X')){
			opcion_c=visitadas[pos_c.first][pos_c.second];
		}
		if(valida_d && (d=='C' || d=='S' || d=='X')){
			opcion_d=visitadas[pos_d.first][pos_d.second];
		}
		
		int menos_visitada_prioridad = std::min(opcion_c, std::min(opcion_d, opcion_i));
		
		if(menos_visitada_prioridad!=10000){ // si hay algun sendero o camino
			if(menos_visitada_prioridad==opcion_c) return 2;
			if(menos_visitada_prioridad==opcion_i) return 1;
			return 3;
		}
		
		
		if(visitadas_actual>=2){
		
			//si base o bosque con zapatillas return
			int opcion_ib=10000, opcion_db=10000, opcion_cb=10000; //visitadas con prioridad
			
			if(valida_i && i=='X' || (i=='B' && zap==true)){
				opcion_ib=visitadas[pos_i.first][pos_i.second];
			}
			if(valida_c && c=='X' || (c=='B' && zap==true)){
				opcion_cb=visitadas[pos_c.first][pos_c.second];
			}
			if(valida_d && d=='X' || (d=='B' && zap==true)){
				opcion_db=visitadas[pos_d.first][pos_d.second];
			}
			
			int menos_visitada_prioridadB = std::min(opcion_cb, std::min(opcion_db, opcion_ib));
			
			if(menos_visitada_prioridadB!=10000){ // si hay alguna base
				if(menos_visitada_prioridadB==opcion_cb) return 2;
				if(menos_visitada_prioridadB==opcion_ib) return 1;
				return 3;
			}
			
			
			if(visitadas_actual>=2 || valida_i+valida_c+valida_d==1){
				//si agua return
				int opcion_ia=10000, opcion_da=10000, opcion_ca=10000; //visitadas con prioridad
				
				if(valida_i && i=='A'){
					opcion_ia=visitadas[pos_i.first][pos_i.second];
				}
				if(valida_c && c=='A'){
					opcion_ca=visitadas[pos_c.first][pos_c.second];
				}
				if(valida_d && d=='A'){
					opcion_da=visitadas[pos_d.first][pos_d.second];
				}
				
				int menos_visitada_prioridadA = std::min(opcion_ca, std::min(opcion_da, opcion_ia));
				
				if(menos_visitada_prioridadA!=10000){ // si hay alguna agua
					if(menos_visitada_prioridadA==opcion_ca) return 2;
					if(menos_visitada_prioridadA==opcion_ia) return 1;
					return 3;
				}
			}
			
		}
		
	}
	
	return 0; //se queda donde esta porque no puede avanzar
}

int ComportamientoAuxiliar::mejorOpcionA1(bool zap, int energia){ //veo las opciones que tiene actualmente en su derecha e izquierda en el caso de que se haya quedado sin salida SOLO SE USA SI POS ES 0

	//va a la que es valida, priorizando izquierda
	
	if(!zap){ //pillar zapatillas
		if(actualMia[0]=='D') return 1;
		else if(actualMia[2]=='D') return 3;
		
	} else { //va a la que es valida, priorizando izquierda
		if (esValidaA1(actualMia[0], energia)==true) return 1;
		else if (esValidaA1(actualMia[2], energia)==true) return 3;
	}
	
	return 0; //si hay encerrona se queda donde esta
}


Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_1(Sensores sensores)
{

	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	// Actualizacion de variables de estado
	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);
	if(sensores.superficie[0]=='D'){
		tiene_zapatillas=true;
	}
	
	// Definicion del comportamiento
	if (giro45Izq!=0){ //Estoy girando TURN_SL
		accion=TURN_SR;
		giro45Izq--;
	}
	else if(ChocaConRescatador(sensores.agentes[2])==true){
		giro45Izq=1;
		accion=TURN_SR;
	}
	else {
	
	//romper ciclos
	static int magia=5;
	if (visitadas[sensores.posF][sensores.posC] >= magia) {
		int probabilidad = std::rand() % 2; // 50% de probabilidad
		magia++;
		if (probabilidad == 0) {
			    giro45Izq=6; //PONER 5 A LA DERECHA OSEA TURN_SR
			    accion=TURN_SR;
		} else {
		    return TURN_SR;
		}
    	}
		char i= ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c= ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d= ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
		int pos=VeoCasillaInteresanteA1(i, c, d, tiene_zapatillas, sensores.energia, sensores.posF, sensores.posC);
		switch(pos){
			case 2:
				accion=WALK;
				break;
			case 1:
				giro45Izq=6; //PONER 5 A LA DERECHA OSEA TURN_SR
				accion=TURN_SR;
				break;
			case 3:
				accion=TURN_SR;
				break;
			case 0:
			//cout << "estoy en case 0, porque no hay salida de frente, buscando un lado" << endl;
				int mejor=0; int rumbo_deseado;
				mejor=mejorOpcionA1(tiene_zapatillas, sensores.energia);	//veo donde es mejor ir, di izquierda o derecha
				if(mejor==0){ //si no habia salida, se da media vuelta 180º
					//cout << "no podia seguir ni a derecha ni a izquierda, me doy la vuelta" << endl;
					giro45Izq=2;
					accion=TURN_SR;
					
				} else { //si es el camino izquierdo o derecho
				//cout << "puedo seguir por derecha o izquierda" << endl;
					int rumbo_deseado = (mejor == 1) ? (rumbo_anterior - 1 + 8) % 8 : (rumbo_anterior + 1) % 8; //veo cual de los dos es y ajustamos cual es la direccion deseada, si izquierda o derecha
				/*
				int diferencia = (rumbo_deseado - sensores.rumbo); //deseado menos actual nos dasu proximo rumbo osea derecha o izquierda
				
				*/
				
				
				int diferencia = (rumbo_deseado - sensores.rumbo + 8) % 8; // Esto asegura que la diferencia siempre esté en el rango [0, 7]
    
    if (diferencia > 4) {
        diferencia -= 8; // Normalizamos la diferencia a [-4, 4]
    }
				bool esDiagonal = (rumbo_deseado % 2 != 0);
				
					if(esDiagonal==false){
					//cout << "estoy en una direccion diagonal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						//cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						//cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=4;
							accion=TURN_SR;
						}
					
					} else {
					//cout << "estoy en una direccion horizontal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						//cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						//cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=5;
							accion=TURN_SR;
						}
					}
				
				}
				
				break;
		}
	
	}
	
	
	//Devolver la siguiente acion a hacer
	//Devolver la siguiente acion a hacer
	last_action=accion;
	actualMia[0]=sensores.superficie[1];
	actualMia[1]=sensores.superficie[2]; 
	actualMia[2]=sensores.superficie[3];
	if(sensores.posF!=posAnteriorF or sensores.posC!=posAnteriorC) {
		visitadas[sensores.posF][sensores.posC]++;
	}
	posAnteriorF=sensores.posF;
	posAnteriorC=sensores.posC;
	//cout << "he actualizado mi casilla de veces visitadas, ahora vale" << visitadas[sensores.posF][sensores.posC] << endl;
	rumbo_anterior=sensores.rumbo;
	return accion;

}

list<Action> ComportamientoAuxiliar::AvanzaASaltosDeCaballo(){
	list<Action> secuencia;
	secuencia.push_back(WALK);
	secuencia.push_back(WALK);
	secuencia.push_back(TURN_SR);
	secuencia.push_back(TURN_SR);
	secuencia.push_back(WALK);
	return secuencia;
	
}

//ve si es posible hacer un walk desde donde esta
bool ComportamientoAuxiliar::CasillaAccesibleAuxiliar(const EstadoA &st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
	EstadoA next = NextCasillaAuxiliar(st);
	bool check1 = false, check2 = false, check3 = false;
	check1 = terreno[next.f][next.c] != 'P' and terreno[next.f][next.c] != 'M';
	check2 = terreno[next.f][next.c] != 'B' or (terreno[next.f][next.c] == 'B' and st.zapatillas);
	check3 = abs(altura[next.f][next.c] - altura[st.f][st.c]) <= 1;
	return check1 and check2 and check3;
}

//Devuelve el estado en el que quedaría el agente Auxiliar después de hacer una acción WALK.
EstadoA ComportamientoAuxiliar::NextCasillaAuxiliar(const EstadoA &st){
	EstadoA siguiente = st;
	switch (st.brujula)
	{
	case norte:
		siguiente.f = st.f - 1;
		break;
		
	case noreste:
		siguiente.f = st.f - 1;
		siguiente.c = st.c + 1;
		break;
		
	case este:
		siguiente.c = st.c + 1;
		break;
		
	case sureste:
		siguiente.f = st.f + 1;
		siguiente.c = st.c + 1;
		break;
		
	case sur:
		siguiente.f = st.f + 1;
		break;
		
	case suroeste:
		siguiente.f = st.f + 1;
		siguiente.c = st.c - 1;
		break;
		
	case oeste:
		siguiente.c = st.c - 1;
		break;
		
	case noroeste:
		siguiente.f = st.f - 1;
		siguiente.c = st.c - 1;
	}
	
	return siguiente;
}

//devuelve un estado en el que se queda donde esta, avanza o gira
EstadoA ComportamientoAuxiliar::applyA(Action accion, const EstadoA & st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
	EstadoA next = st;
	switch(accion){
	case WALK:
		if (CasillaAccesibleAuxiliar(st,terreno,altura)){
			next = NextCasillaAuxiliar(st);
		}
		break;
		
	case TURN_SR:
		next.brujula = (next.brujula+1)%8;
		break;
	}
	return next;
}

//mira a ver si esta o no ese estado en esa lista
bool ComportamientoAuxiliar::Find(const NodoA & st, const list<NodoA> &lista){
	auto it = lista.begin();
	while (it != lista.end() and !((*it) == st)){
		it++;
	}
	return (it != lista.end());
}

//algoritmo dle nivel e
list <Action> ComportamientoAuxiliar::AnchuraAuxiliar(const EstadoA &ini, const EstadoA &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){

	NodoA current_node;
	list<NodoA> frontier;
	list<NodoA> explored;
	list<Action> path;
	
	current_node.estado=ini;
	frontier.push_back(current_node);
	bool SolutionFound=(current_node.estado.f==fin.f and current_node.estado.c==fin.c);
	
	while(!SolutionFound and !frontier.empty()){
	
		frontier.pop_front();
		explored.push_back(current_node);
		
		//mira a ver si tiene zapatillas
		if(terreno[current_node.estado.f][current_node.estado.c] == 'D'){
			current_node.estado.zapatillas=true;
		}
		
		//genera el hijo de hacer la accion WALK
		NodoA child_WALK=current_node;
		child_WALK.estado=applyA(WALK, current_node.estado, terreno, altura);
		if(child_WALK.estado.f==fin.f and child_WALK.estado.c==fin.c){
			//el hijo es la solucion
			child_WALK.secuencia.push_back(WALK);
			current_node=child_WALK;
			SolutionFound=true;
			
		} else if(!Find(child_WALK, frontier) and !Find(child_WALK, explored)){
			//se mete en la lista frontier despues de añadir a secuencia la accion
			child_WALK.secuencia.push_back(WALK);
			frontier.push_back(child_WALK);
		}
		
		//genero el hijo de hacer TURN_SR
		if(!SolutionFound){
			NodoA child_TURN_SR=current_node;
			child_TURN_SR.estado= applyA(TURN_SR, current_node.estado, terreno, altura);
			if(!Find(child_TURN_SR, frontier) and !Find(child_TURN_SR, explored)){
				child_TURN_SR.secuencia.push_back(TURN_SR);
				frontier.push_back(child_TURN_SR);
			}
		}
		
		if(!SolutionFound and !frontier.empty()){
			current_node=frontier.front();
			SolutionFound=(current_node.estado.f == fin.f and current_node.estado.c == fin.c);
		}
		
	
	}
	
	if(SolutionFound) path=current_node.secuencia;
	
	return path;

}

//algoritmo 2 del nivel e
list <Action> ComportamientoAuxiliar::AnchuraAuxiliar_V2(const EstadoA &ini, const EstadoA &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){

	NodoA current_node;
	list<NodoA> frontier;
	set<NodoA> explored;
	list<Action> path;
	
	current_node.estado=ini;
	frontier.push_back(current_node);
	bool SolutionFound=(current_node.estado.f==fin.f and current_node.estado.c==fin.c);
	
	while(!SolutionFound and !frontier.empty()){
	
		frontier.pop_front();
		explored.insert(current_node);
		
		//mira a ver si tiene zapatillas
		if(terreno[current_node.estado.f][current_node.estado.c] == 'D'){
			current_node.estado.zapatillas=true;
		}
		
		//genera el hijo de hacer la accion WALK
		NodoA child_WALK=current_node;
		child_WALK.estado=applyA(WALK, current_node.estado, terreno, altura);
		if(child_WALK.estado.f==fin.f and child_WALK.estado.c==fin.c){
			//el hijo es la solucion
			child_WALK.secuencia.push_back(WALK);
			current_node=child_WALK;
			SolutionFound=true;
			
		} else if(explored.find(child_WALK) == explored.end()){
			//se mete en la lista frontier despues de añadir a secuencia la accion
			child_WALK.secuencia.push_back(WALK);
			frontier.push_back(child_WALK);
		}
		
		//genero el hijo de hacer TURN_SR
		if(!SolutionFound){
			NodoA child_TURN_SR=current_node;
			child_TURN_SR.estado= applyA(TURN_SR, current_node.estado, terreno, altura);
			if(explored.find(child_TURN_SR)==explored.end()){
				child_TURN_SR.secuencia.push_back(TURN_SR);
				frontier.push_back(child_TURN_SR);
			}
		}
		
		//paso a evaluar el siguiente nodo en la lista frontier
		if(!SolutionFound and !frontier.empty()){
			current_node=frontier.front();
			while(explored.find(current_node) != explored.end() and !frontier.empty()){
				frontier.pop_front();
				current_node=frontier.front();
			}
		}
		
	
	}
	//devuelvo el camino si encuentra solucion
	if(SolutionFound) path=current_node.secuencia;
	
	return path;

}

void ComportamientoAuxiliar::AnularMatrizA(vector<vector<unsigned char>> &m){
	for (int i = 0; i < m[0].size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
		m[i][j] = 0;
		}
	}
}

void ComportamientoAuxiliar::VisualizaPlan(const EstadoA &st, const list<Action> &plan){
	
	AnularMatrizA(mapaConPlan);
	EstadoA cst = st;
	
	auto it = plan.begin();
	while (it != plan.end())
	{
		switch (*it)
		{
		case WALK:
			switch (cst.brujula)
			{
			case 0:
				cst.f--;
				break;
			case 1:
				cst.f--;
				cst.c++;
				break;
			case 2:
				cst.c++;
				break;
			case 3:
				cst.f++;
				cst.c++;
				break;
			case 4:
				cst.f++;
				break;
			case 5:
				cst.f++;
				cst.c--;
				break;
			case 6:
				cst.c--;
				break;
				
			case 7:
				cst.f--;
				cst.c--;
				break;
			}
			mapaConPlan[cst.f][cst.c] = 2;
			break;
			
		case TURN_SR:
			cst.brujula = (cst.brujula + 1) % 8;
			break;
		}
		it++;
	}
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_E(Sensores sensores){
	Action accion = IDLE;
	if (!hayPlan){
		// Invocar al método de búsqueda
		EstadoA inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapatillas = tiene_zapatillas;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		plan = AnchuraAuxiliar_V2(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlan(inicio,plan);
		hayPlan = plan.size() != 0 ;
	}
	if (hayPlan and plan.size()>0){
		accion = plan.front();
		plan.pop_front();
	}
	if (plan.size()== 0){
		hayPlan = false;
	}
	return accion;
}

double ComportamientoAuxiliar::calcularHeuristicaA(const EstadoA &actual, const EstadoA &destino){
	
	int dx=actual.f-destino.f;
	int dy=actual.c-destino.c;	
	return sqrt(dx*dx + dy*dy);
	
}

bool ComportamientoAuxiliar::estaEnPriorityQueue(priority_queue<NodoA, vector<NodoA>, ComparadorNodoA> pq, const NodoA& objetivo){

	while (!pq.empty()) {
        if (pq.top() == objetivo) {
            return true;
        }
        pq.pop();
    }
    return false;

}

//reemplaza un nodo en la cola si encuentra uno con menor coste g (camino más barato)
void ComportamientoAuxiliar::insertarElMejorNodo(priority_queue<NodoA, vector<NodoA>, ComparadorNodoA> &pq, const NodoA& nodo){
	
	priority_queue<NodoA, vector<NodoA>, ComparadorNodoA> copia;
	
	while (!pq.empty()) {
	
		NodoA actual = pq.top();
		pq.pop();
		
		if (actual == nodo){ //si ya esta el nodo, meto el del g mas bajo
			if(nodo.g<actual.g) copia.push(nodo);
			else copia.push(actual);
			
		} else {
		    copia.push(actual);
		}
		
        }
        pq=copia;
}

void ComportamientoAuxiliar::procesarSucesor(Action act, const NodoA& current_node, const EstadoA& fin,
                     const vector<vector<unsigned char>>& terreno,
                     const vector<vector<unsigned char>>& altura,
                     set<NodoA>& cerrados,
                     map<EstadoA, NodoA>& abiertos_map,
                     priority_queue<NodoA, vector<NodoA>, ComparadorNodoA>& abiertos) {

    NodoA sucesor = current_node;
    sucesor.estado = applyA(act, current_node.estado, terreno, altura);
    sucesor.g += costeCasillaA1(terreno[sucesor.estado.f][sucesor.estado.c], sucesor.estado.zapatillas);
    sucesor.h = calcularHeuristicaA(sucesor.estado, fin);
    sucesor.fn = sucesor.g + sucesor.h;
    sucesor.secuencia.push_back(act);
	
    //si esta en cerrados ni lo toca
    if (cerrados.find(sucesor) != cerrados.end()) return;
    
    //sino esta en abiertos o esta repey es el mejor le mete
    auto it = abiertos_map.find(sucesor.estado);
    if (it == abiertos_map.end() || sucesor.g < it->second.g) {
        abiertos_map[sucesor.estado] = sucesor;
        abiertos.push(sucesor);
    }
}

list <Action> ComportamientoAuxiliar::AlgoritmoAEstrella(const EstadoA &ini, const EstadoA &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	
	NodoA current_node; //nodo actual
	priority_queue<NodoA, vector<NodoA>, ComparadorNodoA> abiertos; //estos son los nodos pendientes de visitar/expandir con prioridad por f(n)
	set<NodoA> cerrados; //estos son los nodos ya visitados/expandidos que no vuelve a procesarlos
	list<Action> path;
	map<EstadoA, NodoA> abiertos_map;
	
	//inicializo el nodo actual
	current_node.estado=ini;
	current_node.g=0.0;
	current_node.h=calcularHeuristicaA(ini, fin);
	current_node.fn=current_node.g+current_node.h;
	
	//le metemos en abiertos porque no le hemos explorado todavia
	abiertos.push(current_node);
	abiertos_map[ini] = current_node;
	
	//hasta aqui abiertos tiene el nodo inicial y cerrados esta vacio
	
	bool SolutionFound=(current_node.estado.f==fin.f and current_node.estado.c==fin.c);	
	//implementacion del algoritmo
	//comienza un ciclo hasta que haya solucion o abiertos este vacio
	while(!SolutionFound and !abiertos.empty()){ 
	
		//selecciono el mejor nodo de los abiertos (sacando los repetidos obsoletos si tiene)
		do {
		    current_node = abiertos.top();
		    abiertos.pop();
		} while (abiertos_map.find(current_node.estado) != abiertos_map.end() && current_node.g > abiertos_map[current_node.estado].g);

	    	cerrados.insert(current_node);
	    	abiertos_map.erase(current_node.estado);
	    	
	    	//mira a ver si tiene zapatillas
			if(terreno[current_node.estado.f][current_node.estado.c] == 'D'){
				current_node.estado.zapatillas=true;
			}
	    	
	    	//si es un nodo objetivo, terminar
	    	if(current_node.estado.f==fin.f and current_node.estado.c==fin.c){
	    		SolutionFound=true;
	    		break;
	    	}	
		
		//si no hay solucion, se expande
		if(!SolutionFound){
		
			//generamos el sucesor WALK con su heurística
			procesarSucesor(WALK, current_node, fin, terreno, altura, cerrados, abiertos_map, abiertos);
			procesarSucesor(TURN_SR, current_node, fin, terreno, altura, cerrados, abiertos_map, abiertos);
			
		}
	}
	//devuelvo el camino si encuentra solucion
	if(SolutionFound) path=current_node.secuencia;
	
	return path;
}


Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_2(Sensores sensores)
{
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_3(Sensores sensores){

	Action accion = IDLE;
	if (!hayPlan){
		// Invocar al método de búsqueda
		EstadoA inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapatillas = tiene_zapatillas;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		plan = AlgoritmoAEstrella(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlan(inicio,plan);
		hayPlan = plan.size() != 0 ;
	}
	if (hayPlan and plan.size()>0){
		accion = plan.front();
		plan.pop_front();
	}
	if (plan.size()== 0){
		hayPlan = false;
	}
	return accion;

}

bool ComportamientoAuxiliar::esValidaLevel4(char casilla, int energia_actual, bool zap){

	if(casilla=='B' and !zap) return false;
	else if(casilla=='B' and zap) return true;
	else if(casilla=='T' && energia_actual>=20) return true;
	else if (casilla=='A' && energia_actual>=100) return true;
	else if (casilla=='P') return false;
	else if (casilla=='C' && energia_actual>=1) return true;
	else if (casilla=='S' && energia_actual>=2) return true;
	else if (casilla=='M') return false;
	else if (casilla=='D' && energia_actual>=1) return true;
	else if (casilla=='X' && energia_actual>=1) return true;
	else return false;

}

int ComportamientoAuxiliar::esaParteAjustadoA(char i, char c, char d, bool zap, int energia, int fila, int col){

	bool valida_i=esValidaLevel4(i,energia,zap);
	bool valida_c=esValidaLevel4(c,energia,zap);
	bool valida_d=esValidaLevel4(d,energia,zap);
	int visitadas_actual=visitadas[fila][col];
	
	
	if (valida_i || valida_c || valida_d){
	
		//prioridad a las zapatillas
		if(!zap || visitadas_actual!=3){ 
			if(c=='D') return 2;
			else if(i=='D') return 1;
			else if(d=='D') return 3;
		}
		
		//si camino o sendero return
		int opcion_i=10000, opcion_d=10000, opcion_c=10000; //visitadas con prioridad
		
		if(valida_i && (i=='C' || i=='S'|| (i=='B' && zap==true) || i=='X')){
			opcion_i=visitadas[pos_i.first][pos_i.second];
		}
		if(valida_c && (c=='C' || c=='S'|| (c=='B' && zap==true) || c=='X')){
			opcion_c=visitadas[pos_c.first][pos_c.second];
		}
		if(valida_d && (d=='C' || d=='S'|| (d=='B' && zap==true) || d=='X')){
			opcion_d=visitadas[pos_d.first][pos_d.second];
		}
		
		int menos_visitada_prioridad = std::min(opcion_c, std::min(opcion_d, opcion_i));
		
		if(menos_visitada_prioridad!=10000){ // si hay algun sendero o camino
			if(menos_visitada_prioridad==opcion_c) return 2;
			if(menos_visitada_prioridad==opcion_i) return 1;
			return 3;
		}
		
		
		//if(visitadas_actual>=2){
		
			//si base o bosque con zapatillas return
			int opcion_ib=10000, opcion_db=10000, opcion_cb=10000; //visitadas con prioridad
			
			if(valida_i && i=='T'){
				opcion_ib=visitadas[pos_i.first][pos_i.second];
			}
			if(valida_c && c=='T'){
				opcion_cb=visitadas[pos_c.first][pos_c.second];
			}
			if(valida_d && d=='T'){
				opcion_db=visitadas[pos_d.first][pos_d.second];
			}
			
			int menos_visitada_prioridadB = std::min(opcion_cb, std::min(opcion_db, opcion_ib));
			
			if(menos_visitada_prioridadB!=10000){ // si hay alguna base
				if(menos_visitada_prioridadB==opcion_cb) return 2;
				if(menos_visitada_prioridadB==opcion_ib) return 1;
				return 3;
			}
			
			
			//if(visitadas_actual>=2 || valida_i+valida_c+valida_d==1){
				//si agua return
				int opcion_ia=10000, opcion_da=10000, opcion_ca=10000; //visitadas con prioridad
				
				if(valida_i && i=='A'){
					opcion_ia=visitadas[pos_i.first][pos_i.second];
				}
				if(valida_c && c=='A'){
					opcion_ca=visitadas[pos_c.first][pos_c.second];
				}
				if(valida_d && d=='A'){
					opcion_da=visitadas[pos_d.first][pos_d.second];
				}
				
				int menos_visitada_prioridadA = std::min(opcion_ca, std::min(opcion_da, opcion_ia));
				
				if(menos_visitada_prioridadA!=10000){ // si hay alguna agua
					if(menos_visitada_prioridadA==opcion_ca) return 2;
					if(menos_visitada_prioridadA==opcion_ia) return 1;
					return 3;
				}
			//}
			
		//}
		
		
	}
	
	return 0; //se queda donde esta porque no puede avanzar

}

Action ComportamientoAuxiliar::ajustado(Sensores sensores){

	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	// Actualizacion de variables de estado
	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);
	if(sensores.superficie[0]=='D'){
		tiene_zapatillas=true;
	}
	
	// Definicion del comportamiento
	if (giro45Izq!=0){ //Estoy girando TURN_SL
		accion=TURN_SR;
		giro45Izq--;
	}
	else if(ChocaConRescatador(sensores.agentes[2])==true){
		giro45Izq=1;
		accion=TURN_SR;
	}
	else {
		char i= ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c= ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d= ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
		int pos=esaParteAjustadoA(i, c, d, tiene_zapatillas, sensores.energia, sensores.posF, sensores.posC);
		switch(pos){
			case 2:
				accion=WALK;
				break;
			case 1:
				giro45Izq=6; //PONER 5 A LA DERECHA OSEA TURN_SR
				accion=TURN_SR;
				break;
			case 3:
				accion=TURN_SR;
				break;
			case 0:
			//cout << "estoy en case 0, porque no hay salida de frente, buscando un lado" << endl;
				int mejor=0; int rumbo_deseado;
				mejor=mejorOpcionA1(tiene_zapatillas, sensores.energia);	//veo donde es mejor ir, di izquierda o derecha
				if(mejor==0){ //si no habia salida, se da media vuelta 180º
					//cout << "no podia seguir ni a derecha ni a izquierda, me doy la vuelta" << endl;
					giro45Izq=2;
					accion=TURN_SR;
					
				} else { //si es el camino izquierdo o derecho
				//cout << "puedo seguir por derecha o izquierda" << endl;
					int rumbo_deseado = (mejor == 1) ? (rumbo_anterior - 1 + 8) % 8 : (rumbo_anterior + 1) % 8; //veo cual de los dos es y ajustamos cual es la direccion deseada, si izquierda o derecha
				/*
				int diferencia = (rumbo_deseado - sensores.rumbo); //deseado menos actual nos dasu proximo rumbo osea derecha o izquierda
				
				*/
				
				
				int diferencia = (rumbo_deseado - sensores.rumbo + 8) % 8; // Esto asegura que la diferencia siempre esté en el rango [0, 7]
    
    if (diferencia > 4) {
        diferencia -= 8; // Normalizamos la diferencia a [-4, 4]
    }
				bool esDiagonal = (rumbo_deseado % 2 != 0);
				
					if(esDiagonal==false){
					//cout << "estoy en una direccion diagonal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						//cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						//cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=4;
							accion=TURN_SR;
						}
					
					} else {
					//cout << "estoy en una direccion horizontal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						//cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						//cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=5;
							accion=TURN_SR;
						}
					}
				
				}
				
				break;
		}
	
	}
	
	
	//Devolver la siguiente acion a hacer
	//Devolver la siguiente acion a hacer
	last_action=accion;
	actualMia[0]=sensores.superficie[1];
	actualMia[1]=sensores.superficie[2]; 
	actualMia[2]=sensores.superficie[3];
	if(sensores.posF!=posAnteriorF or sensores.posC!=posAnteriorC) {
		visitadas[sensores.posF][sensores.posC]++;
	}
	posAnteriorF=sensores.posF;
	posAnteriorC=sensores.posC;
	//cout << "he actualizado mi casilla de veces visitadas, ahora vale" << visitadas[sensores.posF][sensores.posC] << endl;
	rumbo_anterior=sensores.rumbo;
	return accion;

}

void ComportamientoAuxiliar::casillaDescubiertaMasCercana(int destinoF, int destinoC, int& fCercana, int& cCercana, const vector<vector<unsigned char>>& mapaResultado) {
    int filas = mapaResultado.size();
    int columnas = mapaResultado[0].size();
    double minDistancia = 50000000000000.0;  // Inicialmente una distancia imposible
    
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            // Ignorar casillas no descubiertas o intransitables
            if (mapaResultado[f][c] != '?' and mapaResultado[f][c] != 'P' and mapaResultado[f][c] != 'M'){
            
		     // Calcular distancia euclidiana (Pitagoras)
		    double distancia = sqrt(pow(destinoF - f, 2) + pow(destinoC - c, 2));
		    if (distancia < minDistancia) {
		        minDistancia = distancia;
		        fCercana = f;
		        cCercana = c;
		    }
	    }
        }
    }
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_4(Sensores sensores){
	
	Action devolver;
	static int contadorAvance = 0;
	static bool cuenta=false;
	
	//si no sabe donde esta, explora
	if (!sensores.venpaca || cuenta) {
	
		if(sensores.energia<2000 and (mapaResultado[sensores.posF][sensores.posC]=='C' || mapaResultado[sensores.posF][sensores.posC]=='S')){
			cout << "hola lvl " << endl;
			cout << "cuenta vale" << contadorAvance << endl;
			devolver=ComportamientoAuxiliarNivel_1(sensores);

			
		}  else {
			cout << "hola ajustado " << endl;
			cout << "cuenta vale" << contadorAvance << endl;
			devolver=ajustado(sensores);
		}
		
		if (devolver!=TURN_SR and cuenta){
			contadorAvance++;
		}

	//si no sabe donde esta pero le han llamado que vaya a una cercana a buscar y no tiene que contar casillas
	} else if(sensores.venpaca and !cuenta and visitadas[sensores.destinoF][sensores.destinoC]==0
					/*(
					mapaResultado[sensores.destinoF-1][sensores.destinoC]=='?' ||
					mapaResultado[sensores.destinoF-1][sensores.destinoC+1]=='?' ||
					mapaResultado[sensores.destinoF][sensores.destinoC+1]=='?' ||
					mapaResultado[sensores.destinoF+1][sensores.destinoC+1]=='?' ||
					mapaResultado[sensores.destinoF+1][sensores.destinoC]=='?' ||
					mapaResultado[sensores.destinoF+1][sensores.destinoC-1]=='?' ||
					mapaResultado[sensores.destinoF][sensores.destinoC-1]=='?' ||
					mapaResultado[sensores.destinoF-1][sensores.destinoC-1]=='?')*/){
		
		int fCercana=-1, cCercana=-1;
		casillaDescubiertaMasCercana(sensores.destinoF, sensores.destinoC, fCercana, cCercana, mapaResultado);
		
		if(sensores.posF==fCercana && sensores.posC==cCercana){
			cuenta=true;
			contadorAvance=0;
			cout << "salgo de pillado" << endl;
		}
		
		cout << "pillado" << endl;
		
		Action accion = IDLE;
		if(sensores.choque){
			hayPlan=false;
		}
		if (!hayPlan){
			// Invocar al método de búsqueda
			EstadoA inicio, fin;
			inicio.f = sensores.posF;
			inicio.c = sensores.posC;
			inicio.brujula = sensores.rumbo;
			inicio.zapatillas = tiene_zapatillas;
			fin.f = fCercana;
			fin.c = cCercana;
			plan = AlgoritmoAEstrella(inicio, fin, mapaResultado, mapaCotas);
			VisualizaPlan(inicio,plan);
			hayPlan = plan.size() != 0 ;
		}
		if (hayPlan and plan.size()>0){
			accion = plan.front();
			plan.pop_front();
		}
		if (plan.size()== 0){
			hayPlan = false;
		}
		devolver=accion;
	
	
	//si sabe donde esta, que trace un plan	
	} else if (sensores.venpaca and visitadas[sensores.destinoF][sensores.destinoC]>0) {
	cout << "hola a*" << endl;

		Action accion = IDLE;
		if(sensores.choque){
			hayPlan=false;
		}
		if (!hayPlan){
			// Invocar al método de búsqueda
			EstadoA inicio, fin;
			inicio.f = sensores.posF;
			inicio.c = sensores.posC;
			inicio.brujula = sensores.rumbo;
			inicio.zapatillas = tiene_zapatillas;
			fin.f = sensores.destinoF;
			fin.c = sensores.destinoC;
			plan = AlgoritmoAEstrella(inicio, fin, mapaResultado, mapaCotas);
			VisualizaPlan(inicio,plan);
			hayPlan = plan.size() != 0 ;
		}
		if (hayPlan and plan.size()>0){
			accion = plan.front();
			plan.pop_front();
		}
		if (plan.size()== 0){
			hayPlan = false;
		}
		devolver=accion;
        	
        } 
        
        /*
        //si avanza a una casilla nueva y no tiene que ir a la cercana, se incrementan los pasos
        if((sensores.posF!=posAnteriorF or sensores.posC!=posAnteriorC) and cuenta) {
		//contadorAvance++;
		cout << "contadorAvance incrementado a: " << contadorAvance << endl;
	}
	*/
	//si ha avanzado 50 y sigue sin encontrar, vuelve a la mas cercana a intentarlo de nuevo
	if(cuenta && contadorAvance >=50){
		cuenta=false;
		contadorAvance = 0;
        	cout << "reinicio de cuenta" << endl;
	}
	
	if(!sensores.venpaca){
		contadorAvance = 0;
		cuenta=false;
	}
        
        //actualizo posiciones
        posAnteriorF=sensores.posF;
	posAnteriorC=sensores.posC;
	
	return devolver;

}
