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
  recorrerLista(horarios,imprimirNodo,"Nodo: ");
  FILE * archivo = fopen("salida.out","w");
  char * direccionArchivo;
  int direccionArchivoInt = (int)archivo;
  sprintf(direccionArchivo,"%d",direccionArchivoInt);
  printf("Direccion de archivo: %s\n",direccionArchivo);
  recorrerLista(horarios,escribirNodo,direccionArchivo);
  fclose(archivo);
  liberarLista(lista);
  liberarLista(horarios);
  free(dato);
}