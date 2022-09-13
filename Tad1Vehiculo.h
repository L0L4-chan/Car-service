/**************************************************
*
* Declaracion del modulo Vehiculo
*
*
*****************************************************/
# pragma once
/*Variables globales*/
typedef char Texto[30];
const float pi = 3.1416;
/**Tad Vehiculo**/
typedef struct VehiculoDatos {     /*Vehiculos */
  int vehiculoID; /*Numero de referencia del vehivulo*/
  char TipoVehiculo;/*Letra que indica tipo de vehiculo entre las tres opciones*/
  bool estado;/*Booleano para indicar si el vehiculo esta disponible*/
  Texto Descripcion;/*Breve descripcion del vehiculo*/
  /*Datos para la localizacion del vehiculo*/
  int radio;/*Posición en referencia al centro*/
  float angulo;/*Posición en referencia al centro*/
  int Distancia;/*Posición en referencia al cliente*/
  float Direccion;/*Posición en referencia al cliente*/
  float x;/*Valor posicionalo en eje x*/
  float y;/*Valor posicional en eje Y*/
  int cliente; /*id del cliente que tiene el vehiculo activado cuando esta activado*/
  int indiceUsoCliente; //El indice dentro del TipoUso del cliente al que corresponde ese uso de vehiculo
  /*Coordenadas cartesianas de la localizacion*/
  void PuntoparaCalculo();
  /*Este procedimiento calcula nuevas coordenadas segun la distancia ha otro punto*/
  void DatosXCalculo(int x, int y);
  /*Calcula la distancia desde este punto al destino deseado*/
  void CalcularDistancia();
  /*Calcula el angulo o rumbo hacia el destino deseado*/
  void CalcularDireccion();
  /*Rellena los campos de informacion del vehiculo*/
  void RequerirDatosVehiculo(int i);
  /*Imprime los datos del vehiculo*/
  void ImprimirVehiculo();
};
