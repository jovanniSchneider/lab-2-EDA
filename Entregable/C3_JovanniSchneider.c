#include <stdio.h>
#include <stdlib.h>
//#include "TDAlista.h"
#include "functions.h"

int main()
{
  //Se crean las 2 listas a utilizar
  TDAlista* lista = crearListaVacia();
  TDAlista * horarios = crearListaVacia();

  //Se guardan los datos del archivo de entrada y se "construye" la lista de horarios disponibles
  leerArchivo("entrada.in",lista);
  construirListaHorarios(horarios);

  //Se calcula la lista definitiva de horarios disponibles en los que se debe contratar personal extra
  calcularContratos(lista,horarios);
  int * dato = (int*)malloc(sizeof(int)*2);
  dato[0] = 143;
  dato[1] = 308;

  //Muestra el resultado de la lista final 
  printf("-----------Horarios disponibles-----------\n");
  recorrerLista(horarios,imprimirNodo,"Nodo: ");

  //Se crea la estructura de archivo de salida y se convierte su direccion en entero y luego en string
  FILE * archivo = fopen("salida.out","w");
  char * direccionArchivo;
  int direccionArchivoInt = (int)archivo;
  sprintf(direccionArchivo,"%d",direccionArchivoInt);

  //Se utiliza la funcion de recorrer lista junto con escribir nodo para escribir cada nodo de la lista
  recorrerLista(horarios,escribirNodo,direccionArchivo);

  //Se cierra el archivo y se libera la memoria utilizada por las listas
  fclose(archivo);
  liberarLista(lista);
  liberarLista(horarios);
  free(dato);
}