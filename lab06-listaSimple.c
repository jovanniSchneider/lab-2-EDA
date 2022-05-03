#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"

int main()
{
  TDAlista* lista=crearListaVacia();
  insertarInicio(lista,5);
  insertarInicio(lista,7);
  insertarInicio(lista,4);
  insertarInicio(lista,2);
  recorrerLista(lista);
  printf("%d\n",buscarDato(lista,4));
  printf("%d\n",obtenerNumeroNodos(lista));
  insertarNodoFinal(lista, 3);
  recorrerLista(lista);
  insertarNodoDespues(lista, 11, 7);
  recorrerLista(lista);
  eliminarFinal(lista);
  recorrerLista(lista);
  eliminarDato(lista,7);
  recorrerLista(lista);
  printf("%d\n",obtenerNodo(lista,2)->dato);
  liberarLista(lista);
  return 0;
}