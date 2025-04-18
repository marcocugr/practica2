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
		// accion = ComportamientoAuxiliarNivel_1 (sensores);
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
	if(!zap){ 
		if(c=='D') return 2;
		else if(i=='D') return 1;
		else if(d=='D') return 3;
	}
	
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
			m[sensores.posF-1][sensores.posC-1]=sensores.superficie[1];
			m[sensores.posF-1][sensores.posC]=sensores.superficie[2];
			m[sensores.posF-1][sensores.posC+1]=sensores.superficie[3];
			a[sensores.posF-1][sensores.posC-1]=sensores.cota[1];
			a[sensores.posF-1][sensores.posC]=sensores.cota[2];
			a[sensores.posF-1][sensores.posC+1]=sensores.cota[3];
			pos_i.first=sensores.posF-1; pos_c.second=sensores.posC-1;
			pos_c.first=sensores.posF-1; pos_c.second=sensores.posC;
			pos_d.first=sensores.posF-1; pos_c.second=sensores.posC+1;
			break;
			
		case noreste: //bien
			m[sensores.posF-1][sensores.posC]=sensores.superficie[1];
			m[sensores.posF-1][sensores.posC+1]=sensores.superficie[2];
			m[sensores.posF][sensores.posC+1]=sensores.superficie[3];
			a[sensores.posF-1][sensores.posC]=sensores.cota[1];
			a[sensores.posF-1][sensores.posC+1]=sensores.cota[2];
			a[sensores.posF][sensores.posC+1]=sensores.cota[3];
			pos_i.first=sensores.posF-1; pos_c.second=sensores.posC;
			pos_c.first=sensores.posF-1; pos_c.second=sensores.posC+1;
			pos_d.first=sensores.posF; pos_c.second=sensores.posC+1;
			break;
			
		case este: //bien
			m[sensores.posF-1][sensores.posC+1]=sensores.superficie[1];
			m[sensores.posF][sensores.posC+1]=sensores.superficie[2];
			m[sensores.posF+1][sensores.posC+1]=sensores.superficie[3];
			a[sensores.posF-1][sensores.posC+1]=sensores.cota[1];
			a[sensores.posF][sensores.posC+1]=sensores.cota[2];
			a[sensores.posF+1][sensores.posC+1]=sensores.cota[3];
			pos_i.first=sensores.posF-1; pos_c.second=sensores.posC+1;
			pos_c.first=sensores.posF; pos_c.second=sensores.posC+1;
			pos_d.first=sensores.posF+1; pos_c.second=sensores.posC+1;
			break;
		
		case sureste: //bien
			m[sensores.posF][sensores.posC+1]=sensores.superficie[1];
			m[sensores.posF+1][sensores.posC+1]=sensores.superficie[2];
			m[sensores.posF+1][sensores.posC]=sensores.superficie[3];
			a[sensores.posF][sensores.posC+1]=sensores.cota[1];
			a[sensores.posF+1][sensores.posC+1]=sensores.cota[2];
			a[sensores.posF+1][sensores.posC]=sensores.cota[3];
			pos_i.first=sensores.posF; pos_c.second=sensores.posC+1;
			pos_c.first=sensores.posF+1; pos_c.second=sensores.posC+1;
			pos_d.first=sensores.posF+1; pos_c.second=sensores.posC;
			break;
			
		
		case sur: //bien
			m[sensores.posF+1][sensores.posC+1]=sensores.superficie[1];
			m[sensores.posF+1][sensores.posC]=sensores.superficie[2];
			m[sensores.posF+1][sensores.posC-1]=sensores.superficie[3];
			a[sensores.posF+1][sensores.posC+1]=sensores.cota[1];
			a[sensores.posF+1][sensores.posC]=sensores.cota[2];
			a[sensores.posF+1][sensores.posC-1]=sensores.cota[3];
			pos_i.first=sensores.posF+1; pos_c.second=sensores.posC+1;
			pos_c.first=sensores.posF+1; pos_c.second=sensores.posC;
			pos_d.first=sensores.posF+1; pos_c.second=sensores.posC-1;
			break;
		
		case suroeste: //bien
			m[sensores.posF+1][sensores.posC]=sensores.superficie[1];
			m[sensores.posF+1][sensores.posC-1]=sensores.superficie[2];
			m[sensores.posF][sensores.posC-1]=sensores.superficie[3];
			a[sensores.posF+1][sensores.posC]=sensores.cota[1];
			a[sensores.posF+1][sensores.posC-1]=sensores.cota[2];
			a[sensores.posF][sensores.posC-1]=sensores.cota[3];
			pos_i.first=sensores.posF+1; pos_c.second=sensores.posC;
			pos_c.first=sensores.posF+1; pos_c.second=sensores.posC-1;
			pos_d.first=sensores.posF; pos_c.second=sensores.posC-1;
			break;
		
		case oeste: //bien
			m[sensores.posF+1][sensores.posC-1]=sensores.superficie[1];
			m[sensores.posF][sensores.posC-1]=sensores.superficie[2];
			m[sensores.posF-1][sensores.posC-1]=sensores.superficie[3];
			a[sensores.posF+1][sensores.posC-1]=sensores.cota[1];
			a[sensores.posF][sensores.posC-1]=sensores.cota[2];
			a[sensores.posF-1][sensores.posC-1]=sensores.cota[3];
			pos_i.first=sensores.posF+1; pos_c.second=sensores.posC-1;
			pos_c.first=sensores.posF; pos_c.second=sensores.posC-1;
			pos_d.first=sensores.posF-1; pos_c.second=sensores.posC-1;
			break;
		
		case noroeste: //bien
			m[sensores.posF][sensores.posC-1]=sensores.superficie[1];
			m[sensores.posF-1][sensores.posC-1]=sensores.superficie[2];
			m[sensores.posF-1][sensores.posC]=sensores.superficie[3];
			a[sensores.posF][sensores.posC-1]=sensores.cota[1];
			a[sensores.posF-1][sensores.posC-1]=sensores.cota[2];
			a[sensores.posF-1][sensores.posC]=sensores.cota[3];
			pos_i.first=sensores.posF; pos_c.second=sensores.posC-1;
			pos_c.first=sensores.posF-1; pos_c.second=sensores.posC-1;
			pos_d.first=sensores.posF-1; pos_c.second=sensores.posC;
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
		giro45Izq=3;
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
				giro45Izq=5; //PONER 5 A LA DERECHA OSEA TURN_SR
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

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_1(Sensores sensores)
{
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
