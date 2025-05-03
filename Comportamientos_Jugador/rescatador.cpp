#include "../Comportamientos_Jugador/rescatador.hpp"
#include <iostream>
#include "motorlib/util.h"
#include <cstdlib>


Action ComportamientoRescatador::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoRescatadorNivel_0 (sensores);
		break;
	case 1:
		accion = ComportamientoRescatadorNivel_1 (sensores);
		break;
	case 2:
		accion = ComportamientoRescatadorNivel_2 (sensores);
		break;
	case 3:
		// accion = ComportamientoRescatadorNivel_3 (sensores);
		break;
	case 4:
		// accion = ComportamientoRescatadorNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoRescatador::interact(Action accion, int valor)
{
	return 0;
}

int ComportamientoRescatador::VeoCasillaInteresanteR(char i, char c, char d, bool zap){

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

char ComportamientoRescatador::ViablePorAlturaR(char casilla, int dif, bool zap){
	if(abs(dif)<=1 or (zap and abs(dif)<=2)) //si puede pasar, es valida
		return casilla;
	else //sino es valida la marca como que no puede pasar
		return 'P';
}

bool ComportamientoRescatador::ChocaConAuxiliar(char frente){
	return (frente=='a');
}

void ComportamientoRescatador::SituarSensorEnMapaR(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores){

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

int ComportamientoRescatador::mejorOpcion(bool zap){ //veo las opciones que tiene actualmente en su derecha e izquierda en el caso de que se haya quedado sin salida SOLO SE USA SI POS ES 0

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

Action ComportamientoRescatador::ComportamientoRescatadorNivel_0(Sensores sensores)
{
	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	// Actualizacion de variables de estado
	SituarSensorEnMapaR(mapaResultado, mapaCotas, sensores); //actualiza el mapade casillas y alturas
	if(sensores.superficie[0]=='D'){ //si esta encima de unas zapatillas se las pone
		tiene_zapatillas=true;
	}
	
	// Definicion del comportamiento
	if(sensores.superficie[0]=='X'){ //si he acabado me quedo quieto
		accion=IDLE;
	}
	else if (giro45Izq!=0){ //si estoy girando sigo girando
		accion=TURN_SR;
		giro45Izq--;
		
		
	}
	else if(doble_giroIzq==true){
		accion=TURN_L;
		doble_giroIzq=false;
	}
	else if(ChocaConAuxiliar(sensores.agentes[2])==true){//si he chocado giro a la izquierda
		//giro45Izq=3;
		//accion=TURN_SR;
		doble_giroIzq=true;
		accion=TURN_L;
	}
	
	else {
		//en estos 3 char, filtro y veo a ver si puedo o no pasar por la altura
		char i= ViablePorAlturaR(sensores.superficie[1], sensores.cota[1]-sensores.cota[0], tiene_zapatillas);
		char c= ViablePorAlturaR(sensores.superficie[2], sensores.cota[2]-sensores.cota[0], tiene_zapatillas);
		char d= ViablePorAlturaR(sensores.superficie[3], sensores.cota[3]-sensores.cota[0], tiene_zapatillas);
		
		//elijo de entre las posibles casillas
		int pos=VeoCasillaInteresanteR(i, c, d, tiene_zapatillas);
		switch(pos){
			case 2:
				accion=WALK; //si la mejor es la que tengo en frente, avanzo
				break;
				
			case 1:
				giro45Izq=1; //si la mejor es la que tengo a la izquierda, 45 grados, los giro
				accion=TURN_L;
				break;
				
			case 3:
				accion=TURN_SR; // si la mejor es la que tengo a la derecha 45 grados, los giro
				break;
				
			case 0: //si no hay salida
				int mejor=0; int rumbo_deseado;
				mejor=mejorOpcion(tiene_zapatillas);	//veo donde es mejor ir, di izquierda o derecha
				if(mejor==0){ //si no habia salida, se da media vuelta 180º
					//cout << "no podia seguir ni a derecha ni a izquierda, me doy la vuelta" << endl;
					giro45Izq=3;
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
							giro45Izq=4; //antes estaba en 2
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
							accion=TURN_SR; // antes era turn sr
						}
					}
				
				}
				
				break;
		}
	
	}
	
	
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


bool ComportamientoRescatador::esValidaR1(char casilla, int energia_actual){

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

int ComportamientoRescatador::costeCasillaR1(char casilla){

	if(casilla=='B') return 10000; //para que no la coja ni loco
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

int ComportamientoRescatador::VeoCasillaInteresanteR1(char i, char c, char d, bool zap, int energia, int fila, int col){

	bool valida_i=esValidaR1(i,energia);
	bool valida_c=esValidaR1(c,energia);
	bool valida_d=esValidaR1(d,energia);
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
		
			//si base return
			int opcion_ib=10000, opcion_db=10000, opcion_cb=10000; //visitadas con prioridad
			
			if(valida_i && i=='X'){
				opcion_ib=visitadas[pos_i.first][pos_i.second];
			}
			if(valida_c && c=='X'){
				opcion_cb=visitadas[pos_c.first][pos_c.second];
			}
			if(valida_d && d=='X'){
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

int ComportamientoRescatador::mejorOpcionR1(bool zap, int energia){ //veo las opciones que tiene actualmente en su derecha e izquierda en el caso de que se haya quedado sin salida SOLO SE USA SI POS ES 0

	//va a la que es valida, priorizando izquierda
	
	if(!zap){ //pillar zapatillas
		if(actualMia[0]=='D') return 1;
		else if(actualMia[2]=='D') return 3;
		
	} else { //va a la que es valida, priorizando izquierda
		if (esValidaR1(actualMia[0], energia)==true) return 1;
		else if (esValidaR1(actualMia[2], energia)==true) return 3;
	}
	
	return 0; //si hay encerrona se queda donde esta
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_1(Sensores sensores)
{

	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	// Actualizacion de variables de estado
	SituarSensorEnMapaR(mapaResultado, mapaCotas, sensores); //actualiza el mapade casillas y alturas
	if(sensores.superficie[0]=='D'){ //si esta encima de unas zapatillas se las pone
		tiene_zapatillas=true;
	}
	
	// Definicion del comportamiento
	if (giro45Izq!=0){ //si estoy girando sigo girando
		accion=TURN_SR;
		giro45Izq--;
		
		
	}
	else if(doble_giroIzq==true){
		accion=TURN_L;
		doble_giroIzq=false;
	}
	else if(ChocaConAuxiliar(sensores.agentes[2])==true){//si he chocado giro a la izquierda
		//giro45Izq=3;
		//accion=TURN_SR;
		doble_giroIzq=true;
		accion=TURN_L;
	}
	
	else {
		//en estos 3 char, filtro y veo a ver si puedo o no pasar por la altura
		char i= ViablePorAlturaR(sensores.superficie[1], sensores.cota[1]-sensores.cota[0], tiene_zapatillas);
		char c= ViablePorAlturaR(sensores.superficie[2], sensores.cota[2]-sensores.cota[0], tiene_zapatillas);
		char d= ViablePorAlturaR(sensores.superficie[3], sensores.cota[3]-sensores.cota[0], tiene_zapatillas);
		
		//elijo de entre las posibles casillas
		int pos=VeoCasillaInteresanteR1(i, c, d, tiene_zapatillas, sensores.energia, sensores.posF, sensores.posC);
		switch(pos){
			case 2:
				//cout << "hago un WALK" << endl;
				accion=WALK; //si la mejor es la que tengo en frente, avanzo
				break;
				
			case 1:
				//cout << "hago un giro izq 45º" << endl;
				giro45Izq=1; //si la mejor es la que tengo a la izquierda, 45 grados, los giro
				accion=TURN_L;
				break;
				
			case 3:
				//cout << "hago un giro der 45º" << endl;
				accion=TURN_SR; // si la mejor es la que tengo a la derecha 45 grados, los giro
				break;
				
			case 0: //si no hay salida
				int mejor=0; int rumbo_deseado;
				mejor=mejorOpcionR1(tiene_zapatillas, sensores.energia);	//veo donde es mejor ir, di izquierda o derecha
				if(mejor==0){ //si no habia salida, se da media vuelta 180º
					//cout << "no podia seguir ni a derecha ni a izquierda, me doy la vuelta" << endl;
					giro45Izq=3;
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
							giro45Izq=4; //antes estaba en 2
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
							accion=TURN_SR; //antes era turn_sr
						}
					}
				
				}
				
				break;
		}
	
	}
	
	
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

//ve si es posible hacer un walk desde donde esta
bool ComportamientoRescatador::CasillaAccesibleRescatador(const EstadoR &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){

	EstadoR next = NextCasillaRescatador(st);
	bool check1 = false, check2 = false;
	check1 = terreno[next.f][next.c] != 'P' and terreno[next.f][next.c] != 'M' and terreno[next.f][next.c] != 'B';
	check2 = abs(altura[next.f][next.c] - altura[st.f][st.c]) <= 1 or (abs(altura[next.f][next.c] - altura[st.f][st.c]) <= 2 and st.zapatillas);
	return check1 and check2;

}

void ComportamientoRescatador::AnularMatrizR(vector<vector<unsigned char>> &m){

	for (int i = 0; i < m[0].size(); i++){
		for (int j = 0; j < m.size(); j++){
			m[i][j] = 0;
		}
	}
}

EstadoR ComportamientoRescatador::NextCasillaRescatador(const EstadoR &st){

	EstadoR siguiente = st;
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

bool ComportamientoRescatador::esValidaR2(const EstadoR &estado, const vector<vector<unsigned char>> &terreno){

	if(terreno[estado.f][estado.c]=='B') return false;
	else if(terreno[estado.f][estado.c]=='T') return true;
	else if (terreno[estado.f][estado.c]=='A') return true;
	else if (terreno[estado.f][estado.c]=='P') return false;
	else if (terreno[estado.f][estado.c]=='C') return true;
	else if (terreno[estado.f][estado.c]=='S') return true;
	else if (terreno[estado.f][estado.c]=='M') return false;
	else if (terreno[estado.f][estado.c]=='D') return true;
	else if (terreno[estado.f][estado.c]=='X') return true;
	else return false;

}

bool ComportamientoRescatador::diferenciaAlturasCorrecta(const EstadoR &e1, const EstadoR &e2, const vector<vector<unsigned char>> &altura){

	int dif = (altura[e2.f][e2.c] - altura[e1.f][e1.c]);
        return (dif <= 1 || (e1.zapatillas && dif <= 2));


}

//devuelve un estado en el que se queda donde esta, avanza, gira o corre
EstadoR ComportamientoRescatador::applyR(Action accion, const EstadoR & st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
	EstadoR next = st;
	EstadoR intermedio;
	switch(accion){
	case WALK:
		if (CasillaAccesibleRescatador(st,terreno,altura)){
			next = NextCasillaRescatador(st);
		}
		break;
	RUN:{
		intermedio = NextCasillaRescatador(st); //seria como la siguiente a la actual
		EstadoR final = NextCasillaRescatador(intermedio); // es la objetivo
		//si la intermedia es transitable y no es la actual y 
		if (esValidaR2(intermedio,terreno) && CasillaAccesibleRescatador(intermedio,terreno,altura) && diferenciaAlturasCorrecta(st, final, altura)) {
			next = final;
		}
	}
	case TURN_L:
		next.brujula = (next.brujula+6)%8;
		break;
	case TURN_SR:
		next.brujula = (next.brujula+1)%8;
		break;
	}
	return next;
}

void ComportamientoRescatador::VisualizaPlanR(const EstadoR &st, const list<Action> &plan)
{
	AnularMatrizR(mapaConPlan);
	EstadoR cst = st;
	
	auto it = plan.begin();
	while (it != plan.end())
	{
		switch (*it)
		{
			case RUN:
			switch (cst.brujula)
			{
				case 0:
					cst.f-=1;
					break;
				case 1:
					cst.f-=1;
					cst.c+=1;
					break;
				case 2:
					cst.c+=1;
					break;
				case 3:
					cst.f+=1;
					cst.c+=1;
					break;
				case 4:
					cst.f+=1;
					break;
				case 5:
					cst.f+=1;
					cst.c-=1;
					break;
				case 6:
					cst.c-=1;
					break;
				case 7:
					cst.f-=1;
					cst.c-=1;
					break;
			}
			mapaConPlan[cst.f][cst.c] = 3;
			
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
			mapaConPlan[cst.f][cst.c] = 1;
			break;
			case TURN_SR:
				cst.brujula = (cst.brujula + 1) % 8;
				break;
			case TURN_L:
				cst.brujula = (cst.brujula + 6) % 8;
				break;
		}
		it++;
	}
}

double ComportamientoRescatador::costeMejoradoR2(const EstadoR &origen, const EstadoR &destino, Action accion, const vector<vector<unsigned char>>& terreno, const vector<vector<unsigned char>>& altura){

    double costeBase = 0;
    double incrementoDecrecimiento = 0;
    double alturaOr = altura[origen.f][origen.c];
    double alturaDest = altura[destino.f][destino.c];

    // Determinar el coste base según la acción y la casilla de origen
    switch (accion) {
        case WALK:
            switch (terreno[origen.f][origen.c]) {
                case 'A': costeBase = 100; break;
                case 'T': costeBase = 20; break;
                case 'S': costeBase = 2; break;
                default: costeBase = 1; break;
            }
            break;

        case RUN:
            switch (terreno[origen.f][origen.c]) {
                case 'A': costeBase = 150; break;
                case 'T': costeBase = 35; break;
                case 'S': costeBase = 3; break;
                default: costeBase = 1; break;
            }
            break;

        case TURN_L:
            switch (terreno[origen.f][origen.c]) {
                case 'A': costeBase = 30; break;
                case 'T': costeBase = 5; break;
                case 'S': costeBase = 1; break;
                default: costeBase = 1; break;
            }
            break;

        case TURN_SR:
            switch (terreno[origen.f][origen.c]) {
                case 'A': costeBase = 16; break;
                case 'T': costeBase = 3; break;
                case 'S': costeBase = 1; break;
                default: costeBase = 1; break;
            }
            break;

        default:
            return -1; // Si la acción no está contemplada
    }

    // Determinar el incremento o decremento de energía según la diferencia de alturas
    if (accion == WALK || accion == RUN) {
    
    	//si esta mas alta la casilla destino que la original
        if (alturaDest > alturaOr) { 
            switch (accion) {
		case WALK:
		    switch (terreno[origen.f][origen.c]) {
		        case 'A': incrementoDecrecimiento = 10; break;
		        case 'T': incrementoDecrecimiento = 5; break;
		        case 'S': incrementoDecrecimiento = 1; break;
		        default: incrementoDecrecimiento = 0; break;
		    }
		    break;

		case RUN:
		    switch (terreno[origen.f][origen.c]) {
		        case 'A': incrementoDecrecimiento = 15; break;
		        case 'T': incrementoDecrecimiento = 5; break;
		        case 'S': incrementoDecrecimiento = 2; break;
		        default: incrementoDecrecimiento = 0; break;
		    }
		    break;
		}
		
        } else if (alturaDest < alturaOr) {
        
            switch (accion) {
		case WALK:
		    switch (terreno[origen.f][origen.c]) {
		        case 'A': incrementoDecrecimiento = -10; break;
		        case 'T': incrementoDecrecimiento = -5; break;
		        case 'S': incrementoDecrecimiento = -1; break;
		        default: incrementoDecrecimiento = 0; break;
		    }
		    break;

		case RUN:
		    switch (terreno[origen.f][origen.c]) {
		        case 'A': incrementoDecrecimiento = -15; break;
		        case 'T': incrementoDecrecimiento = -5; break;
		        case 'S': incrementoDecrecimiento = -2; break;
		        default: incrementoDecrecimiento = 0; break;
		    }
		    break;
		}
        }
    }

    // Calcular el coste final: base + incremento o decremento
    double costeFinal = costeBase + incrementoDecrecimiento;
    return costeFinal;

}

void ComportamientoRescatador::procesarSucesorR(Action act, const NodoR& current_node, const EstadoR& fin,
                     const vector<vector<unsigned char>>& terreno,
                     const vector<vector<unsigned char>>& altura,
                     set<NodoR>& cerrados,
                     map<EstadoR, NodoR>& abiertos_map,
                     priority_queue<NodoR, vector<NodoR>, ComparadorNodoR>& abiertos) {
    
    NodoR sucesor = current_node;
    sucesor.estado = applyR(act, current_node.estado, terreno, altura);
    sucesor.g += costeMejoradoR2(current_node.estado, sucesor.estado, act, terreno, altura);
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

list <Action> ComportamientoRescatador::AlgoritmoDjkstra(const EstadoR &ini, const EstadoR &fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	
	NodoR current_node; //nodo actual
	priority_queue<NodoR, vector<NodoR>, ComparadorNodoR> abiertos; //estos son los nodos pendientes de visitar/expandir con prioridad por f(n)
	set<NodoR> cerrados; //estos son los nodos ya visitados/expandidos que no vuelve a procesarlos
	list<Action> path;
	map<EstadoR, NodoR> abiertos_map;
	
	//inicializo el nodo actual
	current_node.estado=ini;
	current_node.g=0.0;
	
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
		
		//mira a ver si tiene zapatillas
			if(terreno[current_node.estado.f][current_node.estado.c] == 'D'){
				current_node.estado.zapatillas=true;
			}
		
	    	cerrados.insert(current_node);
	    	abiertos_map.erase(current_node.estado);
	    	
	    	//si es un nodo objetivo, terminar
	    	if(current_node.estado.f==fin.f and current_node.estado.c==fin.c){
	    		SolutionFound=true;
	    		break;
	    	}	
		
		//si no hay solucion, se expande
		if(!SolutionFound){
		
			//generamos el sucesor WALK con su heurística
			procesarSucesorR(WALK, current_node, fin, terreno, altura, cerrados, abiertos_map, abiertos);
			procesarSucesorR(RUN, current_node, fin, terreno, altura, cerrados, abiertos_map, abiertos);
			procesarSucesorR(TURN_SR, current_node, fin, terreno, altura, cerrados, abiertos_map, abiertos);
			procesarSucesorR(TURN_L, current_node, fin, terreno, altura, cerrados, abiertos_map, abiertos);
			
		}
	}
	//devuelvo el camino si encuentra solucion
	if(SolutionFound) path=current_node.secuencia;
	
	return path;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_2(Sensores sensores){

	Action accion = IDLE;
	if (!hayPlan){
		// Invocar al método de búsqueda
		EstadoR inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapatillas = tiene_zapatillas;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		plan = AlgoritmoDjkstra(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlanR(inicio,plan);
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

Action ComportamientoRescatador::ComportamientoRescatadorNivel_3(Sensores sensores)
{
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_4(Sensores sensores)
{
}
