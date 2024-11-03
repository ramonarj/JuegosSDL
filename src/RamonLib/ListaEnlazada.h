#pragma once
#include <iostream>
#include <string>
#include <iterator>

namespace RamonLib
{
	template<class T>
	class ListaEnlazada
	{
	private:
		struct Nodo
		{
			T valor;
			Nodo* siguiente;

			Nodo(T elem) : valor(elem), siguiente(nullptr){}
			bool operator==(const Nodo& otro)
			{
				return (valor == otro.valor && siguiente == otro.siguiente);
			}
		};
		int tamaño;
		Nodo * primer;
		Nodo * ultimo;

		// Método privado para acceder a un nodo en concreto
		Nodo* nodo_num(int pos);

	public:
		// Constructora por defecto
		ListaEnlazada(): primer(nullptr), ultimo(nullptr), tamaño(0){}

		// Constructora con lista de inicialización
		ListaEnlazada(std::initializer_list<T> l)
		{	
			//const T* it = l.begin();
			auto it = l.begin(); // el tipo del iterador es 'const T*'
			//std::cout << typeid(it).name() << std::endl;
			while(it != l.end())
			{
				Aniade(*it);
				it++;
			}
		}

		// Constructora por copia
		ListaEnlazada(const ListaEnlazada& otra);

		// Operador de asignación
		ListaEnlazada& operator=(const ListaEnlazada& otra);

		// Destructora
		~ListaEnlazada()
		{
			while(tamaño > 0)
			{
				Nodo* n = primer;
				primer = primer->siguiente;
				delete n;
				tamaño--;
			}
			ultimo = nullptr;  //'primer' acaba siendo nullptr despues del bucle
		}

		// Operador de acceso
		T& operator[](int pos);

		// Getters
		unsigned int Tamanio() const { return tamaño; }

		// TODO: probar a pasarlo como referencia constante
		// Añade un nodo al final de la lista
		void Aniade(T elem);

		// Inserta un elemento en una posición dada
		void Inserta(T elem, int pos);

		// Elimina el elemento situado en esa posición
		void Elimina(int pos);

		// Imprime la información de la lista por consola
		void Imprime() const;

		// Añade información a la función 'Imprime'
		void ImprimeDebug(const std::string& nombreLista="") const;
	};

	template<typename T>
	ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada& otra) 
	{
		tamaño = otra.tamaño;
		if (tamaño == 0)
		{
			primer = ultimo = nullptr;
			return;
		}
		// Añadimos el primer elemento
		primer = new Nodo(otra.primer->valor);

		Nodo* nMio = primer;
		Nodo* nOtra = otra.primer;
		// Y todos los demás
		while(nOtra->siguiente != nullptr)
		{
			nMio->siguiente = new Nodo(nOtra->siguiente->valor);
			nMio = nMio->siguiente;
			nOtra = nOtra->siguiente;
		}
		ultimo = nMio; // ´Referencia al último
	}

	// TODO: unificar código con la constructora por copia
	template <typename T>
	ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada& otra) //otra = rhs
	{
		//	Evita auto-asignación
		if (this == &otra)
			return *this;
		tamaño = otra.tamaño;
		if (tamaño == 0)
		{
			primer = ultimo = nullptr;
			return *this;
		}
		// Añadimos el primer elemento
		primer = new Nodo(otra.primer->valor);

		Nodo* nMio = primer;
		Nodo* nOtra = otra.primer;
		// Y todos los demás
		while (nOtra->siguiente != nullptr)
		{
			nMio->siguiente = new Nodo(nOtra->siguiente->valor);
			nMio = nMio->siguiente;
			nOtra = nOtra->siguiente;
		}
		ultimo = nMio; // ´Referencia al último

		return *this;
	}

	template<typename T>
	T& ListaEnlazada<T>::operator[](int pos)
	{
		return nodo_num(pos)->valor;
	}

	// Al ser el struct 'Nodo' parte de la clase 'ListaEnlazada', hay que usar la palabra 'typename'
	// para acceder a su tipo desde fuera de la clase (dentro de la función, ya no,, porque estamos en la clase)
	template<typename T>
	typename ListaEnlazada<T>::Nodo* ListaEnlazada<T>::nodo_num(int pos)
	{
		if (pos<0 || pos >= tamaño)
			throw std::invalid_argument("Indice fuera del tamaño de la lista");
		int i = 0;
		Nodo* n = primer;
		while (i < pos)
		{
			n = n->siguiente;
			i++;
		}
		return n;
	}

	template<typename T>
	void ListaEnlazada<T>::Aniade(T elem)
	{
		Nodo* n = new Nodo(elem);
		// Lista vacia
		if (tamaño == 0)
			primer = ultimo = n;
		else
		{
			ultimo->siguiente = n;
			ultimo = n;
		}
		tamaño++;
	}


	template<typename T>
	void ListaEnlazada<T>::Inserta(T elem, int pos)
	{
		if (pos > tamaño)
			return;

		Nodo* nodo = new Nodo(elem);
		// Insertarlo en la primera posición
		if (pos == 0) 
		{
			nodo->siguiente = primer;
			primer = nodo;
		}
		// e.o.c.
		else
		{
			// Nodo anterior
			Nodo* ant = nodo_num(pos - 1);

			// Insertar
			nodo->siguiente = ant->siguiente;
			ant->siguiente = nodo;
			if (pos == tamaño) // = if(ant == ultimo)
				ultimo = nodo;
		}
		tamaño++;
	}

	// TODO: unificar código con 'inserta'
	// TODO: al eliminar el último elemento de la lista, peta  (poner ultimo a nullptr)
	template<typename T>
	void ListaEnlazada<T>::Elimina(int pos)
	{
		Nodo* borrado;
		// Eliminar primer elemento
		if(pos == 0)
		{
			borrado = primer;
			primer = primer->siguiente;
			delete borrado;
		}
		// e.o.c
		else
		{
			Nodo* ant = nodo_num(pos - 1);
			borrado = ant->siguiente;
			ant->siguiente = borrado->siguiente;
			// Eliminar último elemento
			if (borrado == ultimo)
				ultimo = ant;
			delete borrado;
		}
		borrado = nullptr;
		tamaño--;
		//if (tamaño == 0) // se queda vacía la lista
		//	ultimo = nullptr;
	}


	template<typename T>
	void ListaEnlazada<T>::Imprime() const
	{
		std::string tipoNodos = typeid(T).name();
		//std::cout << "Lista de tipo " << tipoNodos << " [" << tamaño << " elementos]\n";
		std::cout << "Lista enlazada " << "[" << tamaño << " elementos]\n";

		Nodo* n = primer;
		while (n != nullptr)
		{
			std::cout << n->valor << "->";
			n = n->siguiente;
		}
		std::cout << "nullptr";
	}

	template<typename T> 
	void ListaEnlazada<T>::ImprimeDebug (const std::string& nombreLista) const
	{
		std::string tipoNodos = typeid(T).name();
		//std::cout << "Lista de tipo " << tipoNodos << " [" << tamaño << " elementos]\n";
		std::cout << "Lista enlazada \"" << nombreLista << "\" [" << tamaño << " elementos] | ";
		if (tamaño > 0)
			std::cout << "Primero: " << primer->valor << " | " << "Ultimo: " << ultimo->valor;
		std::cout << "\n\t";

		Nodo* n = primer;
		while (n != nullptr)
		{
			std::cout << n->valor << "->";
			n = n->siguiente;
		}
		std::cout << "nullptr";
	}
}