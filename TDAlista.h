#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int * dato;
  struct nodoGenerico* siguiente;
}nodo;

typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;


/*------------- operaciones -------------*/

TDAlista* crearListaVacia()
{
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}

int esListaVacia(TDAlista* lista)
{
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(TDAlista* lista, void (*f)(nodo*,char*))
{
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      (*f)(auxiliar,"Nodo:");
      auxiliar=auxiliar->siguiente;
    }
  }
  else
    printf("La lista está vacía\n");
}

void insertarInicio(TDAlista* lista, int * dato)
{
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=(int *)malloc(sizeof(int)*2);
  nuevo->dato[0] = dato[0];
  nuevo->dato[1] = dato[1];
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

void eliminarInicio(TDAlista* lista)
{
  nodo* auxiliar;
  if(!esListaVacia(lista))
  {
    auxiliar=lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    free(auxiliar);
  }
}


/*------------- Actividad 2 -------------*/
void liberarLista(TDAlista* lista);
int buscarDato(TDAlista* lista, int dato);
int obtenerNumeroNodos(TDAlista* lista);


//No es necesario usar free ya que se usa en eliminarInicio;
void liberarLista(TDAlista * lista){
	while (!esListaVacia(lista))
	{
		eliminarInicio(lista);
	}
}

//el nodo que se quiere eliminar se "salta", ahora el anterior apunta al que apuntaba el que se elimina
void eliminarDato(TDAlista * lista, int * dato){
	nodo * auxiliar = lista->inicio;
	nodo * siguiente = auxiliar->siguiente;
	while (siguiente->siguiente != NULL)
	{
		if (siguiente->dato[0] == dato[0] && siguiente->dato[1] == dato[1])
		{
			auxiliar->siguiente = siguiente->siguiente;
			free(siguiente);
			break;
		}
		auxiliar = siguiente;
		siguiente = siguiente->siguiente;
	}
	
}
//Inserta un nodo al final, el ultimo nodo de la lista preFuncion apunta al nuevo nodo y este apunta a null
void insertarNodoFinal(TDAlista *lista, int *dato)
{
  if (!esListaVacia(lista))
  {
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->dato = (int *)malloc(sizeof(int) * 2);
    nuevo->dato[0] = dato[0];
    nuevo->dato[1] = dato[1];
    nuevo->siguiente = NULL;
    nodo *auxiliar = lista->inicio;
    while (auxiliar->siguiente != NULL)
    {
      auxiliar = auxiliar->siguiente;
    }
    auxiliar->siguiente = nuevo;
  }else
  {
    insertarInicio(lista,dato);
  }
  
}