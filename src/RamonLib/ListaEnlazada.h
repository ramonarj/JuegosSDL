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
		int tama�o;
		Nodo * primer;
		Nodo * ultimo;

		// M�todo privado para acceder a un nodo en concreto
		Nodo* nodo_num(int pos);

	public:
		// Constructora por defecto
		ListaEnlazada(): primer(nullptr), ultimo(nullptr), tama�o(0){}

		// Constructora con lista de inicializaci�n
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

		// Operador de asignaci�n
		ListaEnlazada& operator=(const ListaEnlazada& otra);

		// Destructora
		~ListaEnlazada()
		{
			while(tama�o > 0)
			{
				Nodo* n = primer;
				primer = primer->siguiente;
				delete n;
				tama�o--;
			}
			ultimo = nullptr;  //'primer' acaba siendo nullptr despues del bucle
		}

		// Operador de acceso
		T& operator[](int pos);

		// Getters
		unsigned int Tamanio() const { return tama�o; }

		// TODO: probar a pasarlo como referencia constante
		// A�ade un nodo al final de la lista
		void Aniade(T elem);

		// Inserta un elemento en una posici�n dada
		void Inserta(T elem, int pos);

		// Elimina el elemento situado en esa posici�n
		void Elimina(int pos);

		// Imprime la informaci�n de la lista por consola
		void Imprime() const;

		// A�ade informaci�n a la funci�n 'Imprime'
		void ImprimeDebug(const std::string& nombreLista="") const;
	};

	template<typename T>
	ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada& otra) 
	{
		tama�o = otra.tama�o;
		if (tama�o == 0)
		{
			primer = ultimo = nullptr;
			return;
		}
		// A�adimos el primer elemento
		primer = new Nodo(otra.primer->valor);

		Nodo* nMio = primer;
		Nodo* nOtra = otra.primer;
		// Y todos los dem�s
		while(nOtra->siguiente != nullptr)
		{
			nMio->siguiente = new Nodo(nOtra->siguiente->valor);
			nMio = nMio->siguiente;
			nOtra = nOtra->siguiente;
		}
		ultimo = nMio; // �Referencia al �ltimo
	}

	// TODO: unificar c�digo con la constructora por copia
	template <typename T>
	ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada& otra) //otra = rhs
	{
		//	Evita auto-asignaci�n
		if (this == &otra)
			return *this;
		tama�o = otra.tama�o;
		if (tama�o == 0)
		{
			primer = ultimo = nullptr;
			return *this;
		}
		// A�adimos el primer elemento
		primer = new Nodo(otra.primer->valor);

		Nodo* nMio = primer;
		Nodo* nOtra = otra.primer;
		// Y todos los dem�s
		while (nOtra->siguiente != nullptr)
		{
			nMio->siguiente = new Nodo(nOtra->siguiente->valor);
			nMio = nMio->siguiente;
			nOtra = nOtra->siguiente;
		}
		ultimo = nMio; // �Referencia al �ltimo

		return *this;
	}

	template<typename T>
	T& ListaEnlazada<T>::operator[](int pos)
	{
		return nodo_num(pos)->valor;
	}

	// Al ser el struct 'Nodo' parte de la clase 'ListaEnlazada', hay que usar la palabra 'typename'
	// para acceder a su tipo desde fuera de la clase (dentro de la funci�n, ya no,, porque estamos en la clase)
	template<typename T>
	typename ListaEnlazada<T>::Nodo* ListaEnlazada<T>::nodo_num(int pos)
	{
		if (pos<0 || pos >= tama�o)
			throw std::invalid_argument("Indice fuera del tama�o de la lista");
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
		if (tama�o == 0)
			primer = ultimo = n;
		else
		{
			ultimo->siguiente = n;
			ultimo = n;
		}
		tama�o++;
	}


	template<typename T>
	void ListaEnlazada<T>::Inserta(T elem, int pos)
	{
		if (pos > tama�o)
			return;

		Nodo* nodo = new Nodo(elem);
		// Insertarlo en la primera posici�n
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
			if (pos == tama�o) // = if(ant == ultimo)
				ultimo = nodo;
		}
		tama�o++;
	}

	// TODO: unificar c�digo con 'inserta'
	// TODO: al eliminar el �ltimo elemento de la lista, peta  (poner ultimo a nullptr)
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
			// Eliminar �ltimo elemento
			if (borrado == ultimo)
				ultimo = ant;
			delete borrado;
		}
		borrado = nullptr;
		tama�o--;
		//if (tama�o == 0) // se queda vac�a la lista
		//	ultimo = nullptr;
	}


	template<typename T>
	void ListaEnlazada<T>::Imprime() const
	{
		std::string tipoNodos = typeid(T).name();
		//std::cout << "Lista de tipo " << tipoNodos << " [" << tama�o << " elementos]\n";
		std::cout << "Lista enlazada " << "[" << tama�o << " elementos]\n";

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
		//std::cout << "Lista de tipo " << tipoNodos << " [" << tama�o << " elementos]\n";
		std::cout << "Lista enlazada \"" << nombreLista << "\" [" << tama�o << " elementos] | ";
		if (tama�o > 0)
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