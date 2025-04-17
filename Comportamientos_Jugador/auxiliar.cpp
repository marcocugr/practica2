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

int ComportamientoAuxiliar::VeoCasillaInteresanteA(char i, char c, char d){
	if(c=='X') return 2;
	else if (i=='X') return 1;
	else if (d=='X') return 3;
	else if (c=='C') return 2;
	else if (i=='C') return 1;
	else if (d=='C') return 3;
	else return 0;
}

char ComportamientoAuxiliar::ViablePorAlturaA(char casilla, int dif){
	if(abs(dif)<=1)
		return casilla;
	else
		return 'P';
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_0(Sensores sensores)
{
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	// Actualizacion de variables de estado
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
	else {
		char i= ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c= ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d= ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
		int pos=VeoCasillaInteresanteA(i, c, d);
		switch(pos){
			case 2:
				accion=WALK;
				break;
			case 1:
				giro45Izq=4; //PONER 3 A LA DERECHA OSEA TURN_SR
				accion=TURN_SR;
				break;
			case 3:
				accion=TURN_SR;
				break;
			case 0:
				giro45Izq=4;
				accion=TURN_SR; //PONER 3 A LA DERECHA OSEA TURN_SR
				break;
		}
	
	}
	
	
	//Devolver la siguiente acion a hacer
	last_action=accion;
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
