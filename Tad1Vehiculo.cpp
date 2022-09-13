/**************************************************
*
* Archivo de implementacion del modulo vehiculos
*
*
*****************************************************/#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Tad1Vehiculo.h"
/*--Procedimientos y funciones TAD Vehiculo--*/

void VehiculoDatos::PuntoparaCalculo() { /*Coordenadas cartesianas de la localizacion*/
  x = cosf(angulo)*radio;
  y = sinf(angulo)*radio;
}
void VehiculoDatos::DatosXCalculo (int coordenadaX, int coordenadaY) { /*Convertir datos en los requeridos para el calculo*/
  x = x-coordenadaX;
  y = y-coordenadaY;
}
void VehiculoDatos::CalcularDistancia () {/*Funcion para calcular distancia*/
  Distancia = sqrtf ((powf(x, 2.0))+(powf(y, 2.0)));
}
void VehiculoDatos::CalcularDireccion () { /*Funcion para calcular el rumbo*/
  Direccion = atanf (y/x);
  Direccion = (Direccion * 180)/ pi;
  }
void VehiculoDatos::RequerirDatosVehiculo (int i) {/*Añadir vehiculo al registro*/
  vehiculoID = i+1;
  printf ("     -- Alta nuevo vehiculo--\n");
  printf ("     Identificador: %d", vehiculoID );
  printf ("\n     Tipo de vehiculo (B/C/P)? ");
  scanf (" %c", &TipoVehiculo);
  printf ("     Descripcion? ");
  scanf ("\n %s", &Descripcion);
  printf ("     Radio (int): ");
  scanf ("\n %d", &radio );
  printf ("     Angulo (float): ");
  scanf ("\n %f", &angulo);
}
void VehiculoDatos::ImprimirVehiculo () { /*Imprimimos un vehiculo*/
  printf ("\n        Datos del vehiculo");
  printf ("\n Identificador: %4d",vehiculoID );
  printf ("   Tipo: %c", TipoVehiculo);
  printf ("\n Descripcion: %s", Descripcion);
}



