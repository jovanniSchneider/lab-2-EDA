#include <stdio.h>
#include <stdlib.h>
//#include "TDAlista.h"
#include "functions.h"

int main()
{
  TDAlista* lista = crearListaVacia();
  TDAlista * horarios = crearListaVacia();
  leerArchivo("entrada.in",lista);
  construirListaHorarios(horarios);
  calcularContratos(lista,horarios);
  int * dato = (int*)malloc(sizeof(int)*2);
  dato[0] = 143;
  dato[1] = 308;
  
  printf("calculado\n");
  recorrerLista(horarios,imprimirNodo);
  liberarLista(lista);
  liberarLista(horarios);
  free(dato);
}