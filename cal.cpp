/**************************************************
*
* Archivo de implementacion del modulo cal (Calendario)
*
*
*****************************************************/
#include <stdio.h>
#include "Tad2cliente.h"
#include "cal.h"
/*Implementacion del TAD calendario*/
typedef struct TipoFecha {
  int dia;
  int mes;
  int anno;
};

typedef enum TipoDia {Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo};

bool bisiesto ( int anno ) {
  return ((anno % 4 == 0) && (anno % 100 != 0)) || (anno % 400 == 0);
}

TipoDia SumarDias (int dia, int N) {/* N = el num�ro por el que se incrementa la fecha */
  const  int DiasSemana = 7;
  int aux;
  aux = (dia + N ) % DiasSemana;				/* Aux = ( D�a referencia + incremento ) menos semanas enteras */
  return TipoDia(aux);
}

TipoDia DiaDeLaSemana (int mes, int anno) {/*Calcular el comienzo de la semana*/
  int M = mes;
  TipoDia dia; /*Variable auxiliar para el return*/
  int A = anno;
  int IncreDias;						/* Incremento en d�as de la semana*/
  int IncreAnnos; 						/* Incremento en d�as por a�os enteros*/
  int IncreBisiesto;						/* Incremento en d�as por a�os bisiestos*/
  const int AnnoReferencia = 1601;				/* A�o por el que empieza*/
  switch (M) {/*Calculamos el comienzo del mes*/
  case 1:
  case 10:
  IncreDias = 0;
    break;
  case 2:
  case 3:
    IncreDias = 3;
    break;
  case 4:
  case 7:
    IncreDias = 6;
    break;
  case 5:
    IncreDias = 	1;
    break;
  case 6:
    IncreDias =  4;
    break;
  case 8:
  case 11:
    IncreDias = 2;
    break;
  default:
    IncreDias = 5;
  }
  IncreAnnos = A - AnnoReferencia;	                        /* C�lculo de incremento de d�as por a�os desde a�o	referencia*/
  IncreBisiesto = 0;                                       /* Para bisiestos, completar el a�o*/

  for (int N=1602; N<A; N++) {
    if (bisiesto (N)) {
      IncreBisiesto ++;
    }
  }

  if ( bisiesto (A) && 			                /* a�adir un d�a, si es despues de un d�a 29 de febrero*/
       ( M > 1 )) {
    IncreDias ++;
  }
  IncreDias = IncreDias + IncreAnnos + IncreBisiesto ;   /* C�lculo de incremento total de d�as*/
  dia = SumarDias(int(dia), IncreDias);
  return dia;
}

int DiasDelMes (int mes, int anno) {/* Funci�n para calcular el n�mero de d�as que contiene un mes*/
  switch (mes) {
  case 1:
    if (bisiesto (anno)) {
      return (29);
    } else {
      return (28);
    };
    break;
  case 3:
  case 5:
  case 8:
    return (30);
    break;
  default:
    return (31);
  }
}

void Calendario::ImprimirCalendario(ClienteDatos cliente) {
  int ind; 								/* contador de posiciones del calendario */
  TipoDia PrimerDia;
  int dia = 1;	/* iniciar el primer d�a de la fecha para poder determinar cual es el primer d�a del mes*/
  char lettersToPrint1, lettersToPrint2;  //Variables auxiliares pos si hay mas de un vehiculo por dia//
  bool printDayJO = true;               //Variable auxiliar para imprimir solo una vez el dia
  int lettersInDay = 0;                 //Variable auxiliar para el contador de usos en el mismo dia
  bool noMatchInMonth = true;           //Variable auxiliar para comprobar si no hay ningun uso en el mes
  PrimerDia = DiaDeLaSemana (mes, anno);					/* Calcular en que d�a de la semana cae el primer d�a del mes*/
  /*--- Dibujar cabecera de calendario ---*/
  if ((anno >= 1601) && (anno <= 3000)) {			/* el calendario no imprime nada para los a�os fuera del rango */
    printf ("\n");						/* espacio en blanco antes de la hoja del calendario */
    switch (mes) {
    case 1:
      printf ("ENERO     ");
      break;
    case 2:
      printf ("FEBRERO   ");
      break;
    case 3:
      printf ("MARZO     ");
      break;
    case 4:
      printf ("ABRIL     ");
      break;
    case 5:
      printf ("MAYO      ");
      break;
    case 6:
      printf ("JUNIO     ");
      break;
    case 7:
      printf ("JULIO     ");
      break;
    case 8:
      printf ("AGOSTO    ");
      break;
    case 9:
      printf ("SEPTIEMBRE");
      break;
    case 10:
      printf ("OCTUBRE   ");
      break;
    case 11:
      printf ("NOVIEMBRE ");
      break;
    case 12:
      printf ("DICIEMBRE ");
      break;
    }
    printf ("             ");
    printf ("%d\n",anno);
    printf ("===========================\n");
    printf ("LU  MA  MI  JU  VI | SA  DO\n");
    printf ("===========================\n");
    /*--- Dibujar calendario ---*/
    ind = 0;

    for (int k = int(PrimerDia); k >= 1; k --) {				/* imprimir blancos de principio de mes */
      if (ind % 7 == 5) {						/* imprimir barra de f�n de semana */
        printf ("| ");
      }
      if ( (ind %7 != 0) && (ind % 7 != 5) ) {	/* imprimir blanco entre campos si no es lunes o viernes */
        printf (" ");
      }
      printf (" . ");
      ind ++;
    }


    for (int k = 1; k <= DiasDelMes(mes, anno); k++) {			/* imprimir todos los d�as del mes*/
      if (ind != 0) {
        if (ind %7 == 0) {					/* cambio de semana (linea )*/
          printf ("\n");
        }
      }
      if (ind %7 == 5) {						/* imprimir barra separadora */
        printf ("| ");
      } else if ( (ind %7 != 0) && (ind % 7 != 5) ) {		/* imprimir blanco entre campos si no es lunes o viernes */
        printf ("  ");
      }

      printDayJO = true;
      for (int p = 0; p < 365; p++) {
        if ((anno == cliente.uso[p].anno)&&(mes == cliente.uso[p].mes)) {
          noMatchInMonth = false;
          if (k == cliente.uso[p].dia) {
            printDayJO = false;
            lettersInDay++;    //Incrementamos el contador de usos en el mismo dia
            if (lettersInDay == 1) {
              lettersToPrint1 = cliente.uso[p].TipoVehiculo;
            } else
              if (lettersInDay == 2) {
                lettersToPrint2 = cliente.uso[p].TipoVehiculo;
              }
          }
        }
      }
      switch (lettersInDay) {
      case 0:
        break;
      case 1:
        printf ("%c", lettersToPrint1);
        break;
      case 2:
        printf ("%c%c", lettersToPrint1, lettersToPrint2);
      break;
      default:
        printf ("%c%c",'T','O' );
      }

 //Imprimimos el dia, una unica vez independientemente de los usos encontrados en ese dia, y solo si no hay ningun uso, o si no se encuentra ningun dato con ese mes y ese ano, se imprime el dia sin mas*/
    if (printDayJO == true || noMatchInMonth == true) {
      printf ("%2d", k );
    }

    ind ++;
  }
}
}
