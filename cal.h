/**************************************************
*
* Declaracion del modulo Cal (Calendario)
*
*
*****************************************************/
#pragma once
/**TAD calendario**/
typedef struct Calendario {
  int mes;
  int anno;
  /* Imprime el calendario mensual con el consumo del cliente*/
  void ImprimirCalendario (ClienteDatos c);
};
