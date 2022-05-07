#include "TDAlista.h"
#include <stdio.h>
#include <stdlib.h>

// Entrada: nombre del archivo ("string") y puntero a estructura del tipo lista enlazada
// Salida: no entrega, ya que se utiliza paso por referencia
// Funcion: Lee el archivo y si es que existe guarda sus datos en la lista enlazada.
void leerArchivo(char *nombreArchivo, TDAlista *lista)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("Hubo un problema al leer el archivo\n");
    }
    else
    {
        int *dato = (int *)malloc(sizeof(int) * 2);
        while (fscanf(archivo, "%d %d", &dato[0], &dato[1]) != EOF)
        {
            insertarNodoFinal(lista, dato);
        }
        fclose(archivo);
    }
}


//Entrada: Una lista vacía en la cual se guardarán los horarios no cubiertos por algun trabajador
//Salida: no entrega, ya que se utiliza paso por referencia
//Funcion: Construye la lista de horarios disponibles, inicialmente todos
void construirListaHorarios(TDAlista *lista)
{
    int *rango = (int *)malloc(sizeof(int) * 2);
    rango[0] = 508;
    rango[1] = 522;
    for (int i = 0; i < 5; i++)
    {
        insertarInicio(lista, rango);
        rango[0] -= 100;
        rango[1] -= 100;
    }
}

//Entrada: Un nodo y un string que corresponde a lo que se imprime antes del nodo
//Salida: No entrega
//Funcion: Muestra el contenido de un nodo
void imprimirNodo(nodo *node, char *string)
{
    printf("%s %d %d\n", string, node->dato[0], node->dato[1]);
}


//Entrada: Un nodo y una lista enlazada que contiene los horarios no cubiertos
//Salida: no entrega
//Funcion: Utiliza un rango disponible en la lista de horarios y crea los nuevos rangos resultantes
void separarRangos(nodo *node, TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio; //nodo auxiliar para recorrer la lista
        int *rango = (int *)malloc(sizeof(int) * 2); //Rango auxiliar que servirá para guardar en la lista de horarios
        
        //Se definen los valores de los rangos a comparar [a,b] y [c,d]
        int a, b, c, d;
        int caso;
        a = node->dato[0];
        b = node->dato[1];
        while (auxiliar != NULL)
        {
            caso = 0; //El caso comienza en 0 para que no entre a ningun case del switch en caso de no cumplirse ninguna condicion de las siguientes
            
            //[c,d] varía, es el rango a comparar correspondiente al nodo actual de la lista horarios
            c = auxiliar->dato[0];
            d = auxiliar->dato[1];

            //En este bloque se definen los posibles casos especificados en el archivo Tabla de casas.xlsx
            if (a < c)
            {
                if (c - a < 14)
                {
                    if (b < d && b > c)
                    {
                        rango[0] = b;
                        rango[1] = d;
                        caso = 1;
                    }
                    else if (b >= d && b - d < 14)
                    {
                        caso = 2;
                    }
                }
            }
            else if (a == c)
            {
                if (b < d)
                {
                    rango[0] = b;
                    rango[1] = d;
                    caso = 1;
                }
                else if (b >= d && b - d < 14)
                {
                    caso = 2;
                }
            }
            else if (a > c)
            {
                if (b < d)
                {
                    caso = 3;
                }
                else if (b >= d && b - d < 14 && a < d)
                {
                    rango[0] = c;
                    rango[1] = a;
                    caso = 1;
                }
            }

            //Acá se toman las diferentes acciones segun el caso
            switch (caso)
            {
            case 1:
                //En las condiciones anteriores se definen los valores de rango para insertar en la lista de horarios
                insertarInicio(lista, rango);
                rango[0] = c;
                rango[1] = d;
                eliminarDato(lista, rango);

                break;

            case 2:
                //En este caso significa que se cubrió todo el rango disponible comparado, por lo que se elimina
                rango[0] = c;
                rango[1] = d;
                eliminarDato(lista, rango);

                break;
            case 3:
                //En este caso se cubre una porcion interna del rango [c,d]
                //Por lo que queda disponible el rango [c,a] y el [b,d]
                rango[0] = c;
                rango[1] = a;
                insertarInicio(lista, rango);
                rango[0] = b;
                rango[1] = d;
                insertarInicio(lista, rango);
                rango[0] = c;
                rango[1] = d;
                eliminarDato(lista, rango);
                break;
            }
            auxiliar = auxiliar->siguiente;
        }
    }
}

//Entrada: 2 listas enlazadas que contienen rangos de horarios, la primera contiene los rangos entregados por los trabajadores y la segunda los horarios disponibles
//Salida: No entrega
//Funcion: Recorre la lista entregada por los trabajadores y compara con la lista de horarios disponibles para terminar con una lista de horarios disponibles definitiva
void calcularContratos(TDAlista *lista, TDAlista *horarios)
{
    if (!esListaVacia(lista) && !esListaVacia(horarios))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            separarRangos(auxiliar, horarios);
            auxiliar = auxiliar->siguiente;
        }
    }
    else
        printf("La lista esta vacia\n");
}

//Entrada: Un nodo a escribir en un archivo y la direccion de un archivo en formato string
//Salida: Escribe en un archivo creado previamente
//Funcion: Convierte el string a una estructura FILE valida y escribe en esta el contenido del nodo
void escribirNodo(nodo *node, char *direccionArchivo)
{
    FILE *archivo = (FILE *)(atoi(direccionArchivo));
    fprintf(archivo, "%d %d\n", node->dato[0], node->dato[1]);
}
