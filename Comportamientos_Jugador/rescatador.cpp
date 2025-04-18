#include "../Comportamientos_Jugador/rescatador.hpp"
#include <iostream>
#include "motorlib/util.h"


Action ComportamientoRescatador::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoRescatadorNivel_0 (sensores);
		break;
	case 1:
		// accion = ComportamientoRescatadorNivel_1 (sensores);
		break;
	case 2:
		// accion = ComportamientoRescatadorNivel_2 (sensores);
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
	if(c=='X') return 2; //llegar al puesto base y acabar
	else if (i=='X') return 1;
	else if (d=='X') return 3;
	else if(!zap){ //pillar zapatillas
		if(c=='D') return 2;
		else if(i=='D') return 1;
		else if(d=='D') return 3;
	}
	if (c=='C') return 2; //avanzar por camino
	else if (i=='C') return 1;
	else if (d=='C') return 3;
	else return 0; //se queda donde esta
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
			m[sensores.posF-1][sensores.posC-1]=sensores.superficie[1];
			m[sensores.posF-1][sensores.posC]=sensores.superficie[2];
			m[sensores.posF-1][sensores.posC+1]=sensores.superficie[3];
			a[sensores.posF-1][sensores.posC-1]=sensores.cota[1];
			a[sensores.posF-1][sensores.posC]=sensores.cota[2];
			a[sensores.posF-1][sensores.posC+1]=sensores.cota[3];
			break;
			
		case noreste: //bien
			m[sensores.posF-1][sensores.posC]=sensores.superficie[1];
			m[sensores.posF-1][sensores.posC+1]=sensores.superficie[2];
			m[sensores.posF][sensores.posC+1]=sensores.superficie[3];
			a[sensores.posF-1][sensores.posC]=sensores.cota[1];
			a[sensores.posF-1][sensores.posC+1]=sensores.cota[2];
			a[sensores.posF][sensores.posC+1]=sensores.cota[3];
			break;
			
		case este: //bien
			m[sensores.posF-1][sensores.posC+1]=sensores.superficie[1];
			m[sensores.posF][sensores.posC+1]=sensores.superficie[2];
			m[sensores.posF+1][sensores.posC+1]=sensores.superficie[3];
			a[sensores.posF-1][sensores.posC+1]=sensores.cota[1];
			a[sensores.posF][sensores.posC+1]=sensores.cota[2];
			a[sensores.posF+1][sensores.posC+1]=sensores.cota[3];
			break;
		
		case sureste:
			m[sensores.posF][sensores.posC+1]=sensores.superficie[1];
			m[sensores.posF+1][sensores.posC+1]=sensores.superficie[2];
			m[sensores.posF+1][sensores.posC]=sensores.superficie[3];
			a[sensores.posF][sensores.posC+1]=sensores.cota[1];
			a[sensores.posF+1][sensores.posC+1]=sensores.cota[2];
			a[sensores.posF+1][sensores.posC]=sensores.cota[3];
			break;
			
		
		case sur: //bien
			m[sensores.posF+1][sensores.posC+1]=sensores.superficie[1];
			m[sensores.posF+1][sensores.posC]=sensores.superficie[2];
			m[sensores.posF+1][sensores.posC-1]=sensores.superficie[3];
			a[sensores.posF+1][sensores.posC+1]=sensores.cota[1];
			a[sensores.posF+1][sensores.posC]=sensores.cota[2];
			a[sensores.posF+1][sensores.posC-1]=sensores.cota[3];
			break;
		
		case suroeste:
			m[sensores.posF+1][sensores.posC]=sensores.superficie[1];
			m[sensores.posF+1][sensores.posC-1]=sensores.superficie[2];
			m[sensores.posF][sensores.posC-1]=sensores.superficie[3];
			a[sensores.posF+1][sensores.posC]=sensores.cota[1];
			a[sensores.posF+1][sensores.posC-1]=sensores.cota[2];
			a[sensores.posF][sensores.posC-1]=sensores.cota[3];
			break;
		
		case oeste: //bien
			m[sensores.posF+1][sensores.posC-1]=sensores.superficie[1];
			m[sensores.posF][sensores.posC-1]=sensores.superficie[2];
			m[sensores.posF-1][sensores.posC-1]=sensores.superficie[3];
			a[sensores.posF+1][sensores.posC-1]=sensores.cota[1];
			a[sensores.posF][sensores.posC-1]=sensores.cota[2];
			a[sensores.posF-1][sensores.posC-1]=sensores.cota[3];
			break;
		
		case noroeste:
			m[sensores.posF][sensores.posC-1]=sensores.superficie[1];
			m[sensores.posF-1][sensores.posC-1]=sensores.superficie[2];
			m[sensores.posF-1][sensores.posC]=sensores.superficie[3];
			a[sensores.posF][sensores.posC-1]=sensores.cota[1];
			a[sensores.posF-1][sensores.posC-1]=sensores.cota[2];
			a[sensores.posF-1][sensores.posC]=sensores.cota[3];
			break;
			
	}

}

int ComportamientoRescatador::mejorOpcion(bool zap){ //veo las opciones que tiene actualmente en su derecha e izquierda en el caso de que se haya quedado sin salida

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
	SituarSensorEnMapaR(mapaResultado, mapaCotas, sensores); //actualiza el mapade casillas y alturas8
	if(sensores.superficie[0]=='D'){ //si esta encima de unas zapatillas se las pone
		tiene_zapatillas=true;
	}
	
	// Definicion del comportamiento
	if(sensores.superficie[0]=='X'){ //si he acabado me quedo quieto
		accion=IDLE;
	}
	else if (giro45Izq!=0){ //si estoy girando sigo girando
		accion=TURN_SR;
		cout << "estoy girando" << endl;
		giro45Izq--;
	}
	else if(ChocaConAuxiliar(sensores.agentes[2])==true){//si he chocado giro a la izquierda
		cout << "estoy enfrente del auxiliar" << endl;
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
			cout << "estoy en case 0, porque no hay salida de frente, buscando un lado" << endl;
				int mejor=0; int rumbo_deseado;
				mejor=mejorOpcion(tiene_zapatillas);	//veo donde es mejor ir, di izquierda o derecha
				if(mejor==0){ //si no habia salida, se da media vuelta 180º
					cout << "no podia seguir ni a derecha ni a izquierda, me doy la vuelta" << endl;
					giro45Izq=3;
					accion=TURN_SR;
					
				} else { //si es el camino izquierdo o derecho
				cout << "puedo seguir por derecha o izquierda" << endl;
					int rumbo_deseado = (mejor == 1) ? (rumbo_anterior - 1 + 8) % 8 : (rumbo_anterior + 1) % 8; //veo cual de los dos es y ajustamos cual es la direccion deseada, si izquierda o derecha
				int diferencia = (rumbo_deseado - sensores.rumbo); //deseado menos actual nos dasu proximo rumbo osea derecha o izquierda
				bool esDiagonal = (rumbo_deseado % 2 != 0);
				
					if(esDiagonal==false){
					cout << "estoy en una direccion diagonal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						cout << "tengo que girar a la derecha" << endl;
							giro45Izq=1;
							accion=TURN_SR;
						}else{ //tiene que girar a la izquierda
						cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=2;
							accion=TURN_SR;
						}
					
					} else {
					cout << "estoy en una direccion horizontal" << endl;
						if(diferencia>=0){ //tiene que girar a la derecha
						cout << "tengo que girar a la derecha" << endl;
							accion=TURN_L;
						}else{ //tiene que girar a la izquierda
						cout << "tengo que girar a la izquierda" << endl;
							giro45Izq=5;
							accion=TURN_SR;
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
	rumbo_anterior=sensores.rumbo;
	return accion;
	
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_1(Sensores sensores)
{
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_2(Sensores sensores)
{
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_3(Sensores sensores)
{
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_4(Sensores sensores)
{
}
