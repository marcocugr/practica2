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
		// accion = ComportamientoAuxiliarNivel_2 (sensores);
		break;
	case 3:
		// accion = ComportamientoAuxiliarNivel_3 (sensores);
		break;
	case 4:
		// accion = ComportamientoAuxiliarNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoAuxiliar::interact(Action accion, int valor)
{
	return 0;
}

int ComportamientoAuxiliar::VeoCasillaInteresanteA(char i, char c, char d, bool zap){
	//si hay un puesto base acaba
	if(c=='X') return 2; 
	else if (i=='X') return 1;
	else if (d=='X') return 3;
	
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
		char i= ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c= ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d= ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
		int pos=VeoCasillaInteresanteA(i, c, d, tiene_zapatillas);
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
		
		if(valida_i && (i=='C' || i=='S')){
			opcion_i=visitadas[pos_i.first][pos_i.second];
		}
		if(valida_c && (c=='C' || c=='S')){
			opcion_c=visitadas[pos_c.first][pos_c.second];
		}
		if(valida_d && (d=='C' || d=='S')){
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
		char i= ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c= ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d= ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
		int pos=VeoCasillaInteresanteA1(i, c, d, tiene_zapatillas, sensores.energia, sensores.posF, sensores.posC);
		switch(pos){
			case 2:
				accion=WALK;
				break;
			case 1:
				giro45Izq=5; //PONER 5 A LA DERECHA OSEA TURN_SR
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

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_2(Sensores sensores)
{
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_3(Sensores sensores)
{
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_4(Sensores sensores)
{
}
