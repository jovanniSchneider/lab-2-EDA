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
void imprimirNodo(nodo *node, char *string)
{
    printf("%s %d %d\n", string, node->dato[0], node->dato[1]);
}

void separarRangos(nodo *node, TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        int *rango = (int *)malloc(sizeof(int) * 2);
        int a, b, c, d;
        int caso;
        a = node->dato[0];
        b = node->dato[1];
        while (auxiliar != NULL)
        {
            caso = 0;
            c = auxiliar->dato[0];
            d = auxiliar->dato[1];

            printf("[%d,%d]\n", auxiliar->dato[0], auxiliar->dato[1]);
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

            switch (caso)
            {
            case 1:
                insertarInicio(lista, rango);
                printf("cubrir [%d,%d]\n", rango[0], rango[1]);

                printf("Eliminar [%d,%d]\n", auxiliar->dato[0], auxiliar->dato[1]);
                rango[0] = c;
                rango[1] = d;
                eliminarDato(lista, rango);

                break;

            case 2:
                printf("Eliminar [%d,%d]\n", auxiliar->dato[0], auxiliar->dato[1]);
                printf("Eliminar [%d,%d]\n", auxiliar->dato[0], auxiliar->dato[1]);
                rango[0] = c;
                rango[1] = d;
                eliminarDato(lista, rango);

                break;
            case 3:
                rango[0] = c;
                rango[1] = a;
                insertarInicio(lista, rango);
                printf("cubrir [%d,%d]\n", rango[0], rango[1]);

                rango[0] = b;
                rango[1] = d;
                insertarInicio(lista, rango);
                printf("cubrir [%d,%d]\n", rango[0], rango[1]);

                printf("Eliminar [%d,%d]\n", auxiliar->dato[0], auxiliar->dato[1]);
                rango[0] = c;
                rango[1] = d;
                eliminarDato(lista, rango);

                break;
            }
            auxiliar = auxiliar->siguiente;
        }
    }
}

void calcularContratos(TDAlista *lista, TDAlista *horarios)
{
    if (!esListaVacia(lista) && !esListaVacia(horarios))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            printf("Viendo rango = [%d , %d]\n", auxiliar->dato[0], auxiliar->dato[1]);
            printf("Lista de entrada\n");
            separarRangos(auxiliar, horarios);
            auxiliar = auxiliar->siguiente;
        }
    }
    else
        printf("La lista esta vacia\n");
}

void escribirNodo(nodo *node, char *direccionArchivo)
{
    FILE *archivo = (FILE *)(atoi(direccionArchivo));
    fprintf(archivo, "%d %d\n", node->dato[0], node->dato[1]);
}
