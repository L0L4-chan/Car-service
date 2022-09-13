/***********************************************
*
* Programa de gestión de vehiculos compartidos
*
* Autor : Dolores Suarez
*
**************************************************/
/*Bibliotecas añadidas y Modulos*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Tad1Vehiculo.h"
#include "Tad2cliente.h"
#include "cal.h"

/*Variables globales*/
typedef ClienteDatos VectorC[50];
typedef VehiculoDatos VectorV[20];
typedef struct Listas { /* Variable para poder crear un funcion que devuelva un vector*/
  VectorV ListaVeh;
};
/*--Registro cliente--*/
int AltaDatosCliente (VectorC &c, int i) {/*creamos un cliente*/
  ClienteDatos cliente;/*Variable temporal para almacenar datos de un cliente*/
  char d = 'S';/*Variable para confirmar operacion*/
  while (d == 'S') {
    do {
      cliente.RequerirDatosCliente(i);/*Funcion para introducir datos*/
      printf ("\n     Datos correctos (S/N)?");
      scanf ("\n %c", &d);
      if (d=='S') {
        c[i]= cliente;/*Almacenamos cliente en el vector de clientes*/
        i= i+1;
      }
    } while (d == 'N');
    printf ("\n Otro Cliente(S/N)?");
    scanf ("\n %c", &d );
  }
  return i;
}
/*--Registro de vehiculo--*/
int AltaDatosVehiculo (VectorV &v, int i) {/*creeamos un vehiculo*/
  VehiculoDatos vehiculo;/*Variable para rellenar datos del vehiculo*/
  char d = 'S'; /*Variable para confirmar operacion*/
  while (d == 'S') {
    do {
      vehiculo.RequerirDatosVehiculo(i);
      printf ("\n     Datos correctos (S/N)?");
      scanf ("\n %c", &d);
      if (d == 'S') {
        vehiculo.estado = true;
        v[i]= vehiculo;
        i= i+1;
      }
    } while (d == 'N');

    printf ("\n  Otro Vehiculo(S/N)?");
    scanf ("\n %c",&d );
  }
  return i;
}
/*-Procedimiento para ordenar vehiculos en un vector-*/
void OrdenarVehiculos (VectorV &disponible, int numVehiculos) { /*ordenar vehiculos por distancia al cliente*/
  VehiculoDatos aux; /*creamos tres vehiculos para ordenarlos */

  for (int i = 0; i < numVehiculos; i++) {
    for (int j = 0; j < numVehiculos; j++) {
      if(disponible[i].Distancia < disponible[j].Distancia) {
        aux = disponible[j];
        disponible[j] = disponible[i];
        disponible[i] = aux;
      }
    }
  }
}
/*-Activacion de un vehiculo por parte del cliente-*/
void ActivarVehiculo (VectorV &v, VectorC &c) {/*Procedimiento para activar vehiculo*/
  VehiculoDatos vehiculo; /*vehiculo escogido*/
  VectorV disponible; /*vector para agupar vehiculos libres*/
  VehiculoDatos vehiculoVacio; /*vehiculo vacio*/
  int j,id, posicion, radio, dia, mes, anno, hora, minutos,x,y;/*Id = localizacion del cliente en vector cliente/ s =localizacion del vehiculo en vector vehiculo, y otras variables temporales*/
  float angulo;
  char tipo,Y;
  int contadorDisponibles = 0;    /*Contador para saber cuantos vehiculos hay disponibles*/
  Y = 'N';
  posicion = 0;
  j = 0;

  for(int i = 0; i < 20; i++) {
    disponible[i] = vehiculoVacio;
  }

  /*Solicitamos datos y reservamos en variables temporales**/
  printf ("\n     -- Activar Vehiculo -- \n");
  printf ("     Identificador del cliente: " );
  scanf ("%d", &id);
  printf ("     Ubicacion del cliente: Radio? ");
  scanf ("%d", &radio);
  printf ("     Ubicacion del cliente: Angulo? ");
  scanf ("%f", &angulo);
  printf ("     Tipo de vehiculo (B/C/P/T)? ");
  scanf ("\n %c", &tipo);
  printf ("     Fecha de activacion? ");
  scanf ("%2d/%2d/%4d", &dia, &mes, &anno );
  printf ("     Hora de activacion? ");
  scanf ("%2d:%2d", &hora, &minutos);

  /*convertimos la localizacion del cliente en coordenadas cardinales*/
  x =int (cosf(angulo)*radio);
  y =int (sinf(angulo)*radio);
  /*Seleccionamos vehiculos disponibles*/
  for (int i=0; i<=50; i++) {
    vehiculo = v[i];
    if ((tipo == 'T')||(tipo == vehiculo.TipoVehiculo)) {
      if (vehiculo.estado == true) {
        vehiculo.PuntoparaCalculo();
        vehiculo.DatosXCalculo(x,y);
        vehiculo.CalcularDireccion();
        vehiculo.CalcularDistancia();
        disponible[posicion]= vehiculo;
        posicion++;
        contadorDisponibles++;          /*Actualizamos el numero de vehiculos disponibles*/
      }
    }
  }

  if(contadorDisponibles == 0) {
    printf ("     --- NO HAY VEHICULOS DISPONIBLES ---" );
  }
  else {
    OrdenarVehiculos(disponible, contadorDisponibles); /*Ordenamos por distancia al cliente*/
    /*Imprimimos los cinco mas cercanos*/
    do {
      printf ("\n               Vehiculos Disponibles\n");
      printf ("   REF.   Identificador   Tipo   Distancia   Rumbo\n\n");
      for (int k = 0; k <contadorDisponibles; k++) {
        printf ("    %1d             %2d         %c          %5d      %5.2f\n", k+1, disponible[k].vehiculoID, disponible[k].TipoVehiculo, disponible[k].Distancia, disponible[k].Direccion);
      }
      printf ("\n     Ref. Vehiculo Seleccionado?: "); /*solicitamos seleccion de vehiculo entre los disponibles*/
      scanf ("%d", &posicion);
      posicion = posicion-1;
      printf ("\n     -- Datos del vehiculo seleccionado --\n");
      printf ("     Identificador: %d   Tipo: %c\n     Descripcion: %s \n     Distancia desde el cliente: %d \n     Rumbo desde el cliente: %f \n",disponible[posicion].vehiculoID, disponible[posicion].TipoVehiculo, disponible[posicion].Descripcion, disponible[posicion].Distancia, disponible[posicion].Direccion );
      printf ("\n     Datos correctos (S/N)?");
      scanf ("\n %c", &Y);
    } while (Y=='N');
    posicion = disponible[posicion].vehiculoID;
    v[posicion-1].cliente = id;
    v[posicion-1].indiceUsoCliente = c[id-1].IndiceUso; //Guardamos en el vehiculo el indice de uso del respectivo cliente para poder guardar los minutos de uso al devolverlo
    v[posicion-1].estado = false;
    c[id-1].uso[c[id-1].IndiceUso].dia = dia; /*Localizamos espacio vacio en el vector*/
    c[id-1].uso[c[id-1].IndiceUso].mes = mes;/*completamos el uso con los datos*/
    c[id-1].uso[c[id-1].IndiceUso].anno = anno;
    c[id-1].uso[c[id-1].IndiceUso].TipoVehiculo = v[posicion-1].TipoVehiculo;
    c[id-1].IndiceUso ++;
    printf  ("     El vehiculo con identificador %2d ha sido ACTIVADO\n     Desde %d:%d horas del dia %d/%d/%d \n",posicion,hora, minutos,dia,mes,anno);
  }
}
/*-Devolucion de un vehiculo por parte del cliente-*/
void DevolverVehiculo(VectorV &v, VectorC &c) {/*Procedimiento para devolver vehiculo*/
  VehiculoDatos aux; /*auxiliar para guardar datos*/
  int a,b,tiempo, indiceUso;/*a = identificador de cliente/ b= identificador del vehiculo*/
  char Y, tipo; /* Y = identificador para la continuacion o repeticion de procedimientos/ tipo= almacena tipo de vehiculo*/
  Y = 'N';
  /*Solicitud de datos*/
  printf ("\n     -- Devolver Vehiculo --\n");
  printf ("     Identificador del cliente: " );
  scanf ("%d", &a );
  printf ("     Identificador del Vehiculo: " );
  scanf ("%d", &b );
  aux.vehiculoID = b;
  printf ("     Nueva ubicacion del vehiculo: Radio? ");
  scanf ("%d", &aux.radio);
  printf ("     Nueva ubicacion del vehiculo: Angulo? ");
  scanf ("%f", &aux.angulo);
  printf ("     Tiempo de uso en minutos?");
  scanf ("%d", &tiempo);

  tipo = v[b-1].TipoVehiculo;
  while ( Y == 'N') {
    printf ("\n     -- Datos del vehiculo devuelto --");
    printf ("\n     Identificador: %4d", b );
    printf ("   Tipo: %c", tipo);
    printf ("\n     Descripcion: %s", v[b-1].Descripcion);
    printf ("\n     Nueva Ubicacion:Radio %d", aux.radio);
    printf ("\n     Nueva Ubicacion:Angulo %f", aux.angulo);
    printf ("\n\n     Datos correctos (S/N)?");
    scanf ("\n %c", &Y);
  }
  /*Accedemos al cliente, cuyo indice es su ID-1, dentro de ese cliente accedemos al vector de usos,y buscamos el que nos interesa usando el indice guardado en el vehiculo a devolver, ID-1*/
  indiceUso = v[b-1].indiceUsoCliente;
  c[a-1].uso[indiceUso].consumo = c[a-1].uso[indiceUso].consumo+ tiempo;
  v[b-1].estado = true;
  v[b-1].radio = aux.radio;
  v[b-1].angulo = aux.angulo;
  printf ("\n     El vehiculo con identificador %2d ha sido DEVUELTO\n     Despues de ser usado %d minutos.\n", b, tiempo);
}
/*-Imprimir calendario que indica el uso mensual de un cliente-*/
void ImprimirResumenMensual(VectorC c) {
  /*Variables auxiliares*/
  int id;
  Calendario calendario;
  char Y;
  Y = 'S';
  printf ("\n     -- Resumen mensual del cliente --");
  printf ("\n     Identificador de cliente?: ");
  scanf ("%d", &id);
  id = id-1;
  while (Y == 'S') {
    printf("     Seleccione mes:");
    scanf ("%d", &calendario.mes);
    printf ("     Seleccion año:");
    scanf ("%d", &calendario.anno);

    printf ("\n\nResumen uso cliente %s %s", c[id].nombre, c[id].apellido);
    calendario.ImprimirCalendario(c[id]);

    printf ("\n\n     Tiempo de uso de bicicleta: %d", c[id].ObtenerConsumo('B', calendario.mes, calendario.anno));
    printf ("\n     Tiempo de uso de coche: %d",c[id].ObtenerConsumo('C', calendario.mes, calendario.anno));
    printf ("\n     Tiempo de uso de patinete: %d",c[id].ObtenerConsumo('P', calendario.mes, calendario.anno));
    printf ("\n\n     B:Bicicleta;  C:Coche;  P:Patinete; TO: Mas de dos vehiculos");
    printf ("\n\n     Mostrar otro mes (S/N)?");
    scanf ("\n %c", &Y);
  }
}
/*--Programa principal--*/
int main () {

  int c, v; /*C= variable para ennumerar los clientes; V= variable para contar los vehiculos*/
  char S, operacion; /*Variable para indicar la seleccion entre opciones*/
  VectorC ListaCliente; /*Vector donde se almacenan los clientes*/
  VectorV ListaVehiculo;/*Vector donde se almacenan los vehiculos*/
  c=0; /*Inicializamos variable*/
  v=0;/*Inicializamos variable*/
  do {
    printf ("\n*** VehiCom: Gestion de Vehiculos compartidos***\n      Alta nuevo cliente              (Pulsar C)\n      Alta nuevo vehiculo             (Pulsar V)\n      Activar vehiculo                (Pulsar A)\n      Devolver vehiculo               (Pulsar D)\n      Resumen mensual                 (Pulsar R)\n      Salir                           (Pulsar S)\n Teclear una opcion valida (C|V|A|D|R|S)? ");
    scanf ("\n %c",& operacion);
    switch (operacion) {
    case 'C':
      c = AltaDatosCliente(ListaCliente, c);
      break;
    case 'V':
      v = AltaDatosVehiculo(ListaVehiculo, v);
      break;
    case 'A':
      ActivarVehiculo(ListaVehiculo, ListaCliente);
      break;
    case 'D':
      DevolverVehiculo(ListaVehiculo, ListaCliente);
      break;
    case 'R':
      ImprimirResumenMensual(ListaCliente);
      break;
    default:
      ;
    }
    printf ("\n Desea realizar otra operacion(S/N)? ");
    scanf ("\n %c",&S);
  } while (S == 'S');
}
