//Retorna la primera posición donde aparece el elemento, si no existe en la lista retorna -1
int buscarDato(TDAlista * lista, int dato){
	int contador;
	contador = 0;
	nodo * auxiliar = lista->inicio;
	while (auxiliar->siguiente != NULL && !(esListaVacia(lista)))
	{
		if (dato == auxiliar->dato)
		{
			return contador;
		}
		auxiliar = auxiliar->siguiente;
		contador++;
	}
	return -1;
}

//Recorre la lista y cuenta cada nodo
int obtenerNumeroNodos(TDAlista * lista){
	int contador;
	contador = 0;
	nodo * auxiliar = lista->inicio;
	do
	{
		contador++;
		auxiliar = auxiliar->siguiente;
	}while (auxiliar != NULL && !(esListaVacia(lista)));
	return contador;
}

/*------------- Actividad 3 -------------*/
void insertarNodoFinal(TDAlista* lista, int dato);
void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior);
void eliminarFinal(TDAlista* lista);
void eliminarDato(TDAlista* lista, int dato);
nodo* obtenerNodo(TDAlista* lista, int posicion);



//Inserta un nodo al final, el ultimo nodo de la lista preFuncion apunta al nuevo nodo y este apunta a null
void insertarNodoFinal(TDAlista * lista, int dato){
	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	nuevo->dato = dato;
	nuevo->siguiente = NULL;
	nodo * auxiliar = lista->inicio;
	while (auxiliar->siguiente != NULL)
	{
		auxiliar=auxiliar->siguiente;
	}
	auxiliar->siguiente = nuevo;
}

//El nuevo nodo apunta al nodo que apuntaba nodo de datoAnterior, y este ahora apunta al nuevo nodo

void insertarNodoDespues(TDAlista * lista, int dato, int datoAnterior){
	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	nodo * auxiliar = lista->inicio;
	while (auxiliar->siguiente != NULL)
	{
		if (auxiliar->dato == datoAnterior)
		{
			nuevo->dato = dato;
			nuevo->siguiente = auxiliar->siguiente;
			auxiliar->siguiente = nuevo;
			break;
		}
		auxiliar=auxiliar->siguiente;
	}
}


//libera el ultimo nodo y lo el penultimo lo apunta a nulo
void eliminarFinal(TDAlista * lista){
	nodo * auxiliar = lista->inicio;
	nodo * siguiente = auxiliar->siguiente;
	while (siguiente->siguiente != NULL)
	{
		auxiliar = siguiente;
		siguiente = siguiente->siguiente;
	}
	auxiliar->siguiente = NULL;
	free(siguiente);
}


//el nodo que se quiere eliminar se "salta", ahora el anterior apunta al que apuntaba el que se elimina
void eliminarDato(TDAlista * lista, int dato){
	nodo * auxiliar = lista->inicio;
	nodo * siguiente = auxiliar->siguiente;
	while (siguiente->siguiente != NULL)
	{
		if (siguiente->dato == dato)
		{
			auxiliar->siguiente = siguiente->siguiente;
			free(siguiente);
			break;
		}
		auxiliar = siguiente;
		siguiente = siguiente->siguiente;
	}
	
}

//Recorre la lista y devuelve el nodo cuando coincida contador y posicion
nodo* obtenerNodo(TDAlista* lista, int posicion){
	int contador = 0;
	nodo * auxiliar = lista->inicio;
	while (auxiliar->siguiente != NULL)
	{
		if (contador == posicion)
		{
			return auxiliar;
		}
		contador++;
		auxiliar = auxiliar->siguiente;
	}
}