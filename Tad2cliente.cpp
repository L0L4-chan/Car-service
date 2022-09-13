/**************************************************
*
* Archivo de implementacion del modulo cliente
*
*
*****************************************************/#include <stdio.h>
#include "Tad1Vehiculo.h"
#include "Tad2cliente.h"
/* Funciones y procedimientos Tad cliente*/
int ClienteDatos::ObtenerConsumo(char vehiculo, int mes, int anno) {/*Funcion para sumar el tiempo consumido*/
  int consumo = 0;
  for (int i = 0; i <= IndiceUso; i++) {
    if(uso[i].mes == mes && uso[i].anno == anno && uso[i].TipoVehiculo == vehiculo) {
      consumo = consumo + uso[i].consumo;
    }
  }
  return consumo;
}

void ClienteDatos::ImprimirDatosCliente() {/*--Imprimir datos de un cliente--*/
  printf ("\nNombre: %s", nombre);
  printf ("\nApellido %s",apellido);
  printf ("\nNumero de cliente %d",idCliente);
}
void ClienteDatos::RequerirDatosCliente ( int i) {/*--Creamos un cliente--*/
  idCliente = i+1;
  printf ("\n     -- Alta nuevo cliente--\n");
  printf ("     Identificador: %d", idCliente );
  printf ("\n     Nombre? ");
  scanf ("%s", &nombre);
  printf ("     Apellido? ");
  scanf ("%s", &apellido);
}

