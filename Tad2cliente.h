/**************************************************
*
* Declaracion del modulo Cliente
*
*
*****************************************************/
#pragma once
/*Variables globales*/
typedef char Palabra[20];
typedef struct TipoUso {
  int dia;
  int mes;
  int anno;
  int consumo;
  char TipoVehiculo;
};
typedef TipoUso VectorU [365];
/**Tad para el cliente**/
/*variable Cliente*/
typedef struct ClienteDatos { /*Cliente*/
  Palabra nombre;
  Palabra apellido;
  int idCliente;
  int IndiceUso;/*Indice que controla la posicion en la que se escribe del vector */
  VectorU uso; /*Vector para almacenaje de los datos de consumo*/
  int ObtenerConsumo(char vehiculo, int mes, int anno);/*Funcion para sumar el tiempo consumido*/
  void ImprimirDatosCliente();/*Imprimimos datos de un cliente*/
  void RequerirDatosCliente(int i);/*Creamos cliente*/
};
