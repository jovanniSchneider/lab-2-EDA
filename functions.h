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
        int *datoAux = (int *)malloc(sizeof(int) * 2);
        while (auxiliar != NULL)
        {
            recorrerLista(lista, imprimirNodo);
            if (node->dato[0] == auxiliar->dato[0] && node->dato[1] == auxiliar->dato[1])
            {
                printf("1 condicion\n");
                eliminarDato(lista, auxiliar->dato);
                break;
            }else if (node->dato[0] < auxiliar->dato[0] && node->dato[1] == auxiliar->dato[1])
            {
                if(auxiliar->dato[0] - node->dato[0] <= 14){
                    eliminarDato(lista, auxiliar->dato);
                }
            }
            
            else if (node->dato[0] > auxiliar->dato[0] && node->dato[1] == auxiliar->dato[1])
            {
                printf("2 condicion\n");
                eliminarDato(lista, auxiliar->dato);
                datoAux[0] = auxiliar->dato[0];
                datoAux[1] = node->dato[0];
                insertarInicio(lista, datoAux);
                break;
            }
            else if (node->dato[0] == auxiliar->dato[0] && node->dato[1] < auxiliar->dato[1])
            {
                printf("3 condicion\n");
                eliminarDato(lista, auxiliar->dato);
                datoAux[0] = node->dato[1];
                datoAux[1] = auxiliar->dato[1];
                insertarInicio(lista, datoAux);
                break;
            }
            else if (node->dato[0] > auxiliar->dato[0] && node->dato[1] < auxiliar->dato[1])
            {
                printf("4 condicion\n");
                eliminarDato(lista, auxiliar->dato);
                datoAux[0] = auxiliar->dato[0];
                datoAux[1] = node->dato[0];
                insertarInicio(lista, datoAux);
                datoAux[0] = node->dato[1];
                datoAux[1] = auxiliar->dato[1];
                insertarInicio(lista, datoAux);
                break;
            }
            auxiliar = auxiliar->siguiente;
        }
        free(datoAux);
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
            separarRangos(auxiliar, horarios);
            auxiliar = auxiliar->siguiente;
        }
    }
    else
        printf("La lista está vacía\n");
}